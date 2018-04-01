#include<stdio.h>
#include<unistd.h>
int main()
{
  int pid;
  while((pid=fork())<0);
  if(pid==0)
  {
    if(execlp("./lab1_2_1","lab1_2_1",NULL)<0)
      printf("execlp error\n");
  }
  else
    printf("parent...\n");
  return 0;
}
