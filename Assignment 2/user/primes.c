#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

_Atomic int exit_scheduler = 0;

int generate(int cd);
int check(int cd1, int cd2);
int print(int cd2);
int isPrime(int n);
void prime_numbers(int checkers);

int
main(int argc, char *argv[])
{
    int checkers = 3;
    if (argc > 1) 
        checkers = (int)(*argv[1] - '0');
    int run_checkers = 1;
    while(run_checkers == 1){
        prime_numbers(checkers);
        printf("Press 1 if you want to run the program again, anything else to exit\n");
        char c[3];
        gets(c, 3);
        run_checkers = (int)(*c - '0');
    }
    printf("\nProcess id: %d\nRole: generator is exiting\n\n", getpid());
    return 0;
}

void prime_numbers(int checkers) {

    int i;
    int cd1 = channel_create();
    int cd2 = channel_create();
    int PIDs[checkers];
    int status;
    for (i = 0; i < checkers; i++) {
        PIDs[i] = fork();
        if (PIDs[i] < 0) exit(-1);
        if (PIDs[i] == 0) {
            if (i == checkers - 1) {
                int printerPID = fork();
                if (printerPID < 0) exit(-1);
                if (printerPID == 0) {
                    status = print(cd2);
                    printerPID = getpid();
                    printf("Process id: %d\nRole: printer is exiting\n\n", printerPID);
                    exit_scheduler++;
                    exit(status);
                }
            }
            status = check(cd1, cd2);
            int pid = getpid();
            int checker = i+1;
            sleep(checker);
            printf("Process id: %d \nRole: checker %d is exiting\n\n",pid ,checker);
            exit_scheduler++;
            exit(status);
        }
    }

    // printf("generate\n");
    status = generate(cd1);
    // printf("status: %d\n", status);
    for (int j = 0; j < checkers; j++) {
        wait(0);
    }
    wait(0);
}

int generate(int cd) {
    int n = 2;
    int status = 0;
    while (status != -1) {
        status = channel_put(cd, n);
        n++;
    }
    return 0;
}

int check(int cd1, int cd2) {
    int n, status, status2;
    status = channel_take(cd1, &n);
    while (status != -1) {
        if (isPrime(n)) {
            status2 = channel_put(cd2, n);
            if (status2 == -1) {
                channel_destroy(cd1);
                }
        }
        status = channel_take(cd1, &n);
    }

    return status;
}

int print(int cd) {
    int n, status, counter = 0;
    status = channel_take(cd, &n);
    while (status != -1 && counter < 100) {
        printf("%d\n", n);
        counter++;
        status = channel_take(cd, &n);
    }
    channel_destroy(cd);
    return status;
}

int isPrime(int n) {
    if (n <= 1) {
        return 0;
    }
    for (int i = 2; i <= n / 2; i++) {
        if (n % i == 0) {
            return 0;
        }
    }
    return 1;
}