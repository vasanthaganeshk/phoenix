#include <stdio.h>
#include <unistd.h>
#include <seccomp.h>
#include <sys/prctl.h>
#include <sys/wait.h>

#define MAX_BOTS 2
#define MAX_TIME_QUANTUM 2000000

int
main(int argn, const char **args){
  // to not give addtional priviliges to children
  prctl(PR_SET_NO_NEW_PRIVS, 1);

  // ensure no escape is avialable through ptrace
  prctl(PR_SET_DUMPABLE, 0);

  // Define filter, allows all system calls by default
  scmp_filter_ctx filter;
  filter = seccomp_init(SCMP_ACT_ALLOW);

  //filter rules
  seccomp_rule_add(filter, SCMP_ACT_KILL, SCMP_SYS(clone), 0);
  seccomp_rule_add(filter, SCMP_ACT_KILL, SCMP_SYS(fork), 0);

  // engine program start  
  int pid = -1;
  char buf[2][1024];

  for(int i = 0; i< MAX_BOTS; i++){
    pid = fork();
    if(pid == -1){
      printf("Subprocess creation failed\n");
    }
    else if(pid == 0){
      seccomp_load(filter);
      printf("Start of bot: %d\n", i);
      snprintf(buf[i], 1024, "%s%s", "./bots/", args[i+1]);
      execl(buf[i], args[i+1], NULL);
    }
    else{
      wait(NULL);
      printf("Control back to engine\n");      
    }
  }

  printf("Game over - Engine terminated.\n");
  return 0;
}
