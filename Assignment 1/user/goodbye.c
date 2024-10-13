#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
  // int child_pid = fork();
  // if(child_pid > 0){
  //   char ext_msg[32];
  //   wait(0,ext_msg);
  //   printf("%s\n",ext_msg);
  // }
  // else{
  //   exit(0,"hey Lior");
  // }

  exit(0, "Goodbye World xv6");
}
