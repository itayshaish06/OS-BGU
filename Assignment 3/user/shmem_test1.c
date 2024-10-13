#include "kernel/types.h"
#include "user/user.h"
#include "kernel/fcntl.h"

int main() {
    char* va = (char*) malloc(30);
    int parent_pid = getpid();
    int pid = fork();
    if (pid == 0) { // Child process
        sleep(10);
        int child_pid = getpid();
        uint64 child_va = map_shared_pages(parent_pid, child_pid, (uint64) va, 30);
        if (child_va != 0) {
            printf("From child, read the message: %s\n", (char*)child_va);
        }

    } else { // Parent process
        strcpy(va, "Hello child");
        wait(0);
    }
    free(va);
    return 0;
}