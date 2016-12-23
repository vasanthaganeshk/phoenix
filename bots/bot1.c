#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int
main(const int argn, const char *args){
  int pid = fork();
  if(pid == 0){
    printf("Hello World\n");
  }
  else if(pid > 0){
    wait(NULL);
  }
  return 0;
}
