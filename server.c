#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<sys/fcntl.h>
typedef struct
{
	int id;
	char data[1024];
}msg_t;
int main()
{
	int shared_fd;
	int count;
	if((shared_fd=open("shared_pipe",O_RDONLY))<0)
	{
		perror("open failed");
	}
	msg_t* msg=(msg_t*)malloc(sizeof(msg_t));
	while(1)
	{
		ssize_t s=read(shared_fd,msg,sizeof(msg_t));
		//printf("%d %s\n",msg->id,msg->data);
		if(s>0)
		{
			printf("%s\n",msg->data);
			if(msg->id>0&&msg->data[0]=='\0')
			{
					printf("成功接收创建从端代码\n");
					char buffer[1024];
					bzero(buffer,sizeof(buffer));
					sprintf(buffer,"./a%d",msg->id);
					mkfifo(buffer,0664);
					printf("成功创建私有管道%s\n",buffer);
					count++;
			}
			else if(msg->id>0&&msg->data[0]!='\0')
			{
				printf("成功接收信息包\n");
				printf("%d,%s\n",msg->id,msg->data);
				for(int i=1;i<=count;i++)
				{
					if(i!=msg->id)
					{	
						int write_fd;
						char buffer[1024];
						sprintf(buffer,"a%d",i);
						write_fd=open(buffer,O_WRONLY);
						write(write_fd,msg,sizeof(msg_t));
						close(write_fd);
					}
				}
			}
		}
		else
		{
			printf("read failed\n");
		}
	}
	close(shared_fd);
	return 0;
}

