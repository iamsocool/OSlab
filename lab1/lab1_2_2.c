#include<stdio.h>
#include<stdlib.h>
#include<wait.h>
#include<unistd.h>
int main()
{
  int pid;
  int status=-1;
  while((pid=fork())<0);
  if(pid>0)
  {
    printf("this is parent %d\n",getpid());
    wait(&status);
  }
  else
  {
    printf("this is child %d\n",getpid());
    int i;
    int count=0;
    for(i=0;i<10;i++)
    {
      count++;
      sleep(1);
      printf("child runs task%d\n",count);
    }
    exit(5);
  }
  printf("child process ends with statue %d\n",WEXITSTATUS(status));
  printf("end of program form pid %d\n",getpid());
  return 0;
}
