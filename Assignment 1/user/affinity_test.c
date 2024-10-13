#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
    int mask = 7; // 111
    set_affinity_mask(mask);
    int pid = getpid();
    printf("pid: %d\n", pid);
    for(;;){
        // printf("pid: %d\n", pid);
    }
  exit(0, "chapa chapa");
}
