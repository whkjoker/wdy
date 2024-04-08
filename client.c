#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/fcntl.h>
#include<string.h>
typedef struct
{
	int id;
	char data[1024];
}msg_t;
int main()
{
	int fd;
	int flag=0;
	fd=open("shared_pipe",O_WRONLY);
	msg_t* msg=(msg_t*)malloc(sizeof(msg_t));
	while(1)
	{
		if(flag==0)
		{
			int id;
			scanf("%d",&id);
			msg->id=id;
			write(fd,msg,sizeof(msg_t));
			flag=1;
		}
		else
		{
			int id;
			char buf[1024];
			bzero(buf,sizeof(buf));
			scanf("%d %s",&id,buf);
			msg->id=id;
			sprintf(msg->data,"msg%d recv %s",msg->id,buf);
			printf("%d\n",sizeof(msg_t));
			write(fd,msg,sizeof(msg_t));
		}
	}
	close(fd);
	return 0;
}

