#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

void test1(){
    int a = channel_create();
    printf("1st channel %d\n",a);
    int data = 7;
    int x = channel_put(a, data);
    printf("status: %d\n", x);

    int y = fork();
    if (y == 0) { // Child process
        int d;
        int x = channel_take(a, &d);
        printf("In child process, the retrieved data is: %d with exit value: %d\n", d, x);
    } else {
        sleep(2);
        int d;
        int x = channel_take(a, &d);
        printf("In parent process, the retrieved data is: %d with exit value: %d\n", d, x);
    }
    int ex = channel_destroy(a);
    printf("ex: %d\n", ex);
}

void test2(){
    int pid = fork();
    if(pid == 0){//generator process
        int ch = channel_create();
        printf("channel %d\n", ch);
        int data = 7;
        channel_put(ch, data);
        pid = fork();
        if(pid == 0){ //printer process
            int d;
            for(;;){
                d=0;
                int x = channel_take(ch, &d);
                printf("In child process, the retrieved data is: %d with exit value: %d\n", d, x);
                if(x == -1)
                    break;
            }
        }
        else{ //continous generator process
            for(data = 8;;data++)
                channel_put(ch, data);
        }
    }
    else{ //main process
        sleep(5);
        kill(pid);
        wait(0);
    }
}

void test3(){
    int cd = channel_create();
    if (cd < 0){
        printf("Failed to create channel\n");
        exit(1);
    }
    if (fork() == 0){
        if (channel_put(cd, 42) < 0){
            printf("Failed to put data in channel\n");
            exit(1);
        }
        channel_put(cd, 43); // Sleeps until cleared
        // Handle error
        channel_destroy(cd);
        // Handle error
    }
    else{
        int data;
        if (channel_take(cd, &data) < 0){ // 42
            printf("Failed to take data from channel\n");
            exit(1);
        }
        printf("Should be 42 %d\n", data);
        data = channel_take(cd, &data); // 43
        printf("Should be -1 %d\n", data);// Handle error
        data = channel_take(cd, &data); // Sleep until child destroys channel
        printf("Should be -1 %d\n", data);// Handle error
    }
}

int
main(int argc, char *argv[])
{
    // test1();
    // test2();
    test3();
    exit(0);
}
