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
	fd=open("shared_pipe",O_WRONLY);
	msg_t* msg=(msg_t*)malloc(sizeof(msg_t));
	int id;
	//char buf[1024];
	//bzero(buf,sizeof(buf));
	scanf("%d",&id);
	msg->id=id;
	//strcpy(msg->data,buf);
	write(fd,msg,sizeof(msg_t));
	close(fd);
	int read_fd;
	char path[1024];
	sprintf(path,"a%d",msg->id);
	read_fd=open(path,O_RDONLY);
	msg_t* msg1=(msg_t*)malloc(sizeof(msg_t));
	while(1)
	{
		ssize_t s=read(read_fd,msg1,sizeof(msg_t));
		if(s>0)
		printf("id:%d,recv:%s\n",msg1->id,msg1->data);
	}
	close(read_fd);
	return 0;
}

