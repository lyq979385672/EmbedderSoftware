#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h>

int main(void)
{
  int sockfd = 0;
  
  char recvBuff[6];  //传入的设备数据 3*2
  struct sockaddr_in serv_addr;


  

  if((sockfd = socket(AF_INET, SOCK_STREAM, 0))< 0)// 建立socket连接，为socket 数据结构分配存储空间 
    {
      printf("\n Error : Could not create socket \n");
      return 1;
    }
  //填写远程地址信息
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_port = htons(5000);       //端口号
  serv_addr.sin_addr.s_addr = inet_addr("192.168.137.24");    //树莓派IP地址
  printf("requesting......\n");*

  if(connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr))<0)//连接
    {
      printf("\n Error : Connect Failed \n");
      return 1;
    }


  read(sockfd, recvBuff, sizeof(recvBuff));//读socket
 printf("The pm2.5 is: %c%c\n",recvBuff[0],recvBuff[1]);
  printf("The temperature is: %c%c\n",recvBuff[2],recvBuff[3]);
  printf("The humidity is: %c%c\n",recvBuff[4],recvBuff[5]);
  


  return 0;
}
