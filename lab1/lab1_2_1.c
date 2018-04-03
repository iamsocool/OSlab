#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
int main()
{
  int pid;
  while((pid=fork())<0);
  if(pid==0)
  {
    if(execlp("./lab1_1_2","lab1_1_2",NULL)<0)
      printf("execlp error\n");
  }
  else
    printf("parent...\n");
  return 0;
}
