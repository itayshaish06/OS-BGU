#include "types.h"
#include "param.h"
#include "memlayout.h"
#include "riscv.h"
#include "defs.h"
#include "spinlock.h"
#include "channel.h"
#include "proc.h"


struct channel channels[NCHANNELS];

void
channelinit(void){
    struct channel *curr_chan;
    for(curr_chan = channels; curr_chan < &channels[NCHANNELS]; curr_chan++){
        initlock(&curr_chan->lock, "channel");
        curr_chan->state = FREE;
        curr_chan->counter = 0;
        curr_chan->p = 0;
    }
}

int
channel_create(void){
    struct channel *curr_chan;
    int index = -1;
    for (int i = 0;i < NCHANNELS; i++){
        curr_chan = &(channels[i]);
        acquire(&curr_chan->lock);
        if (curr_chan->state == FREE){
            index = i;
            goto found;
        }
        else{
            release(&curr_chan->lock);
        }
    }
  return -1;
found:
    curr_chan->state = CAN_WRITE;
    curr_chan->p = myproc();
    release(&curr_chan->lock);
    printf("Created channel %d\n", index);
    return index;
}

int
channel_put(int cd, int data){
    if (cd >= NCHANNELS || cd < 0) return -1;

    struct channel *curr_chan = &channels[cd];
    acquire(&curr_chan->lock);
    if (curr_chan->state == FREE) {
        release(&curr_chan->lock);
        return -1;
    }
    
    while (curr_chan->state == CAN_READ) { // Wait for CAN_WRITE or EXITTING
        curr_chan->counter++;
        // wakeup(&curr_chan->read_chan);
        sleep(&curr_chan->write_chan, &curr_chan->lock);
        curr_chan->counter--;
    }
    if (curr_chan->state == EXITING || curr_chan->state == FREE) {
        if (curr_chan->counter == 0) { // Last process on channel
            curr_chan->state = FREE;
        }
        release(&curr_chan->lock);
        wakeup(&curr_chan->read_chan);
        wakeup(&curr_chan->write_chan);
        return -1;
    } else { // State is CAN_WRITE
        curr_chan->data = data;
        curr_chan->state = CAN_READ;
        release(&curr_chan->lock);
        wakeup(&curr_chan->read_chan);
        return 0;
    }
}

int
channel_take(int cd, int *data) {
    if (cd >= NCHANNELS || cd < 0) return -1;

    struct channel *curr_chan = &channels[cd];
    acquire(&curr_chan->lock);
    if (curr_chan->state == FREE) {
        release(&curr_chan->lock);
        return -1;
    }

    while (curr_chan->state == CAN_WRITE) { // Wait for CAN_READ or EXITTING
        curr_chan->counter++;
        sleep(&curr_chan->read_chan, &curr_chan->lock);
        curr_chan->counter--;
    }

    if (curr_chan->state == EXITING || curr_chan->state == FREE) {
        if (curr_chan->counter == 0) { // Last process on channel
            curr_chan->state = FREE;
        }
        release(&curr_chan->lock);
        wakeup(&curr_chan->read_chan);
        wakeup(&curr_chan->write_chan);
        return -1;
    } else { // State is CAN_READ

        struct proc* p = myproc();
        int ret = copyout(p->pagetable, (uint64)data, (char *)&curr_chan->data, sizeof(curr_chan->data));
        curr_chan->state = CAN_WRITE;
        release(&curr_chan->lock);
        wakeup(&curr_chan->write_chan);
        return ret;
    }
}

int
channel_destory(int cd) {
    if (cd >= NCHANNELS || cd < 0) return -1;

    struct channel *curr_chan = &channels[cd];
    acquire(&curr_chan->lock);

    if (curr_chan->state == FREE) {
        release(&curr_chan->lock);
        return -1;
    }

    curr_chan->state = EXITING;
    release(&curr_chan->lock);
    wakeup(&curr_chan->read_chan);
    wakeup(&curr_chan->write_chan);
    return 0;
}

