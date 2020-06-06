#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <linux/fcntl.h>
int main()
{
	int fd;
	char buf_write[7]="group_6";//write
	char buf_read[7];
	if((fd=open("/dev/scull_6_0",O_RDWR))==-1){
		printf("open error\n");
		return 0;
	}
	printf("open success\n");
	write(fd,buf_write,sizeof(buf_write));
	lseek(fd,0,SEEK_SET);
	read(fd,buf_read,7);
	printf("read is %s\n",buf_read);
	return 0;
}
