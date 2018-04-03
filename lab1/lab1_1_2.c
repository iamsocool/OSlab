#include <stdio.h>
int main()
{
  int p1,p2;
  while((p1=fork())<0);
  if(p1==0)
    printf("child1...\n");
  else
  {
    while((p2=fork())<0);
    if(p2==0)
      printf("child2...\n");
    else
      printf("parent...\n");
  }
  return 0;
}
