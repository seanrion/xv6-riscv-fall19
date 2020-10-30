#include "kernel/types.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
  if(argc != 2) {
    fprintf(2, "need second argument\n");
    exit();
  }
  sleep(atoi(argv[1]));
  printf("(nothing happens for a little while)\n");
  exit();
}