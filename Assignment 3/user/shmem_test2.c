#include "kernel/types.h"
#include "user/user.h"
#include "kernel/fcntl.h"

#define SIZE 2000

void print_size(char* msg){
    printf("%s : %d\n", msg, (uint64)sbrk(0)); 
}

int main() { 
    print_size("Before malloc");
    char* va = (char*) malloc(SIZE);
    print_size("After malloc");
    int parent_pid = getpid();
    int pid = fork();
    
    if (pid == 0) { // Child process
        int child_id = getpid();
        print_size("Child before mapping");
        char* shared_va = (char*) map_shared_pages(parent_pid, child_id, (uint64) va, SIZE);
        if (shared_va != 0) {
            print_size("Child after mapping");
            strcpy(shared_va, "Hello daddy");
            unmap_shared_pages(child_id, (uint64) shared_va, SIZE);
            print_size("Child after unmapping");
            char* msg = (char*) malloc(SIZE);
            strcpy(msg, "Child after malloc");
            print_size(msg);
            free(msg);
        }
    }
    else { // Parent process
        sleep(10);
        printf("From parent, read the message: %s\n", va);
        wait(0);
        free(va);
    }

    return 0;
}
