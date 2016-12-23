#include <stdio.h>

int
main(const int argn, const char *args){
  char buf[80];
  snprintf(buf, 1024, "%s %s\n", "hello", "1234");
  printf("%s", buf);
  return 0;
}
