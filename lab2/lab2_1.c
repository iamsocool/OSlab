#include<stdlib.h>
#include<stdio.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#include<string.h>
#include<unistd.h>
#define SVKEY 75
#define REQ 1
struct msgbuf{
  long mytype;
  char mytext[1024];
}Msg;


void server()
{
  //waiting for the REQ type message
  Msg.mytype=REQ;
  int msgid;
  while((msgid=msgget(SVKEY,IPC_CREAT|0660))==-1);
  msgrcv(msgid,&Msg,1024,REQ,0);
  int* pint;
  pint=(int*)Msg.mytext;
  printf("this is server:\n");
  printf("serving for client:%d\n",*pint); 
  //sending message
  Msg.mytype=*pint;
  snprintf(Msg.mytext,sizeof(Msg.mytext),"%d",getpid());
  msgsnd(msgid,&Msg,sizeof(int),IPC_NOWAIT);
}
void client()
{
  printf("this is client:\n");
  //prepare sending message

  Msg.mytype=REQ;
  int pid=getpid();
  pid = getpid();
  int* pint;
  pint=(int*)Msg.mytext;
  *pint=pid;

  //seding client'id to get server
  int msgid;
  while((msgid=msgget(SVKEY,IPC_CREAT|0660))==-1);
  msgsnd(msgid,&Msg,1024,0);
  //receive message
  Msg.mytype=pid;
  msgrcv(msgid,&Msg,sizeof(int),Msg.mytype,0);
  printf("this is client:\n");
  printf("receive reply from server:%d\n",atoi(Msg.mytext));
}
int main()
{
  int pid1;
  while((pid1=fork())<0);
  if(pid1==0)
  {
    server();
  }
  else
  {
    client();
  }
  return 0;
}
