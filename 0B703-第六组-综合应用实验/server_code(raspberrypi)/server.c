#include<stdio.h>
#include<stdlib.h>
#include <sys/syscall.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>


int main()
{
    printf("begin\n");
    char input_buf0[]="54";//假设的pm2.5值
    char input_buf1[]="25";//假设的温度值
    char input_buf2[]="47";//假设的湿度值
    char buf_read0[3];
    char buf_read1[3];
    char buf_read2[3];
    char buf0[3];
    char buf1[3];
    char buf2[3];
    memset(buf0, 0,sizeof(buf0));
    memset(buf1, 0,sizeof(buf1));
    memset(buf2, 0,sizeof(buf2));
    int init0,init1,init2;//对应三个设备
    if((init0=open("/dev/scull_6_0",O_RDWR)) != -1)//pm2.5
    {
      write(init0,input_buf0,sizeof(input_buf0));//把buf中的内容写入设备,即模拟传感器感知环境pm2.5
      lseek(init0,0,SEEK_SET);//把文件指针重新定位到文件开始的位置
      read(init0,buf_read0,3);//从传感器读出环境信息
	    printf("server pm2.5 is %s\n",buf_read0);
      FILE *fpWrite0=fopen("/mnt/my_ext4/pm2.5.txt","w");//环境数据存储在特定文件系统
      fprintf(fpWrite0,"%s",buf_read0);
      fclose(fpWrite0);
      close (init0);
    }

    if((init1=open("/dev/scull_6_1",O_RDWR)) != -1)//温度
    {
      write(init1,input_buf1,sizeof(input_buf1));//把buf中的内容写入设备,即模拟传感器感知环境温度
      lseek(init1,0,SEEK_SET);//把文件指针重新定位到文件开始的位置
      read(init1,buf_read1,3);//从传感器读出环境信息
	    printf("server temperature is %s\n",buf_read1);
      FILE *fpWrite1=fopen("/mnt/my_ext4/tem.txt","w");//环境数据存储在特定文件系统
      fprintf(fpWrite1,"%s",buf_read1);
      fclose(fpWrite1);
      close (init1);
    }
    if((init2=open("/dev/scull_6_2",O_RDWR)) != -1)//温度
    {
      write(init2,input_buf2,sizeof(input_buf2));//把buf中的内容写入设备,即模拟传感器感知环境温度
      lseek(init2,0,SEEK_SET);//把文件指针重新定位到文件开始的位置
      read(init2,buf_read2,3);//从传感器读出环境信息
	    printf("server humidity is %s\n",buf_read2);
      FILE *fpWrite2=fopen("/mnt/my_ext4/hum.txt","w");//环境数据存储在特定文件系统
      fprintf(fpWrite2,"%s",buf_read2);
      fclose(fpWrite2);
      close (init2);
    }
   
    int listenfd = 0,connfd = 0;
    struct sockaddr_in serv_addr;
    struct sockaddr_in client_addr;
    socklen_t addrlen;
    char sendBuff[6];//3*2  

  listenfd = socket(AF_INET, SOCK_STREAM, 0);//创建一个socket描述符

  memset(&serv_addr, '0', sizeof(serv_addr));
  memset(sendBuff, '0', sizeof(sendBuff));
  //远程地址信息
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);//自动
  serv_addr.sin_port = htons(5000);//与客户端一致

  //将本地IP地址绑定端口号，并将地址与sockfd关联起来
  bind(listenfd, (struct sockaddr*)&serv_addr,sizeof(serv_addr));
//进入监听模式
  if(listen(listenfd, 10) == -1){
      printf("Failed to listen\n");
      return -1;
  }
  addrlen = sizeof(client_addr);
    while(1)
    {
        
      connfd = accept(listenfd, (struct sockaddr*)&client_addr,&addrlen);
       //从特定文件系统获取
    FILE *fpWrite0;
     if((fpWrite0=fopen("/mnt/my_ext4/pm2.5.txt","r"))== NULL)
      {
        perror("fail to read");
        exit (1) ;
      }
    fread(buf0,sizeof(buf0),2,fpWrite0);
    fclose(fpWrite0);
    FILE *fpWrite1;
     if((fpWrite1=fopen("/mnt/my_ext4/tem.txt","r"))== NULL)
      {
        perror("fail to read");
        exit (1) ;
      }
    fread(buf1,sizeof(buf1),2,fpWrite1);
    fclose(fpWrite1);
      FILE *fpWrite2;
     if((fpWrite2=fopen("/mnt/my_ext4/hum.txt","r"))== NULL)
      {
        perror("fail to read");
        exit (1) ;
      }
    fread(buf2,sizeof(buf2),2,fpWrite2);
    fclose(fpWrite2);
    //pm2.5
      sendBuff[0] = buf0[0];
      sendBuff[1] = buf0[1];
       //tem
      sendBuff[2] = buf1[0];
      sendBuff[3] = buf1[1];
       //hum
      sendBuff[4] = buf2[0];
      sendBuff[5] = buf2[1];
      printf("server message: %s\n",sendBuff);
      //socket send
      write(connfd, sendBuff, strlen(sendBuff));

      close(connfd);
      sleep(1);

      }
   
    return 0;
}
