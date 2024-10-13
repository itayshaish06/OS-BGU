#include "kernel/types.h"
#include "user/user.h"
#include "kernel/spinlock.h"
#include "kernel/sleeplock.h"
#include "kernel/fs.h"
#include "kernel/file.h"
#include "kernel/fcntl.h"

#include "kernel/crypto.h"

void error_detected(struct crypto_op* op) {
  asm volatile ("fence rw,rw" : : : "memory");
  op->state = CRYPTO_OP_STATE_ERROR;
}

int main(void) {
  if(open("console", O_RDWR) < 0){
    mknod("console", CONSOLE, 0);
    open("console", O_RDWR);
  }
  dup(0);  // stdout
  dup(0);  // stderr

  printf("crypto_srv: starting\n");

  if (getpid() != 2) {
    exit(-1);
  }

  for (;;) {
    struct crypto_op* op;
    uint64 sz;
    if (take_shared_memory_request((void **) &op, &sz) == -1) continue;
    if (op->state != CRYPTO_OP_STATE_INIT || op->type != CRYPTO_OP_TYPE_DECRYPT || op->type == CRYPTO_OP_TYPE_ENCRYPT) {
      printf("crypto_srv: invalid crypto operation state/type\n");
      error_detected(op);
      continue;
    }
    int j = 0;
    for (int i = op->key_size; i < op->key_size + op->data_size; i++) {
      op->payload[i] = op->payload[i] ^ op->payload[j];
      j = (j + 1) % op->key_size;
    }
    asm volatile ("fence rw,rw" : : : "memory");
    op->state = CRYPTO_OP_STATE_DONE;

    remove_shared_memory_request(op, sz);
  }

  exit(0);
}
