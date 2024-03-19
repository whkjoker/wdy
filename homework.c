#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/mman.h>
#include<regex.h>
#include<sys/types.h>
#include<sys/fcntl.h>
#include<sys/stat.h>
#include<pthread.h>
#include<unistd.h>
#include<errno.h>
#include<signal.h>
int main()
{
	//把文件内容拷贝到映射内存中
	int fd;
	if((fd=open("hhhh.txt",O_RDONLY))==-1)
	{
		perror("open failed");
	}
	//printf("fd=%d",fd);
	int size;
	size=lseek(fd,0,SEEK_END);
	if(size==-1)
	{
		perror("lseek faided");
	}
	char* ptr=NULL;
	if((ptr=mmap(NULL,size,PROT_READ,MAP_PRIVATE,fd,0))==NULL)
	{
		perror("mmap failed");	
	}
	char* ptr1=ptr;
	regex_t reg;
	char* reg_str="usercard=[^>]\\+\\?>\\([^<]\\+\\?\\)</a><a[^>]\\+\\?></a>:<span>\\([^<]\\+\\?\\)<[^>]\\+\\?></span>";
	regmatch_t match[3];
	regcomp(&reg,reg_str,0);
	close(fd);
	char name[2048];
	char span[2048];
	bzero(name,sizeof(name));
	bzero(span,sizeof(span));
	int err;
	while((regexec(&reg,ptr1,3,match,0))==0)
	{
		
		snprintf(name,match[1].rm_eo-match[1].rm_so+1,"%s",ptr1+match[1].rm_so);
		snprintf(span,match[2].rm_eo-match[2].rm_so+1,"%s",ptr1+match[2].rm_so);
		//printf("err:%d\n",err);
		printf("name：%s\n",name);
		printf("span: %s\n",span);
		ptr1+=match[0].rm_eo;
		bzero(name,sizeof(name));
		bzero(span,sizeof(span));
	}
	
	regfree(&reg);
	munmap(ptr,size);
	return 0;
}
