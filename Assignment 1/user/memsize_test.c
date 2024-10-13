#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
    int process_size = memsize();
    printf("the current proccess size is %d\n",process_size);
    void* mem = malloc(20000);
    process_size = memsize();
    printf("after malloc() - the current proccess size is %d\n",process_size);
    free(mem);
    process_size = memsize();
    printf("after freeing the 20k - the current proccess size is %d\n",process_size);
    exit(0);
}
