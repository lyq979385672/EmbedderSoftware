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
  
  char recvBuff[6];  //������豸���� 3*2
  struct sockaddr_in serv_addr;


  

  if((sockfd = socket(AF_INET, SOCK_STREAM, 0))< 0)// ����socket���ӣ�Ϊsocket ���ݽṹ����洢�ռ� 
    {
      printf("\n Error : Could not create socket \n");
      return 1;
    }
  //��дԶ�̵�ַ��Ϣ
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_port = htons(5000);       //�˿ں�
  serv_addr.sin_addr.s_addr = inet_addr("192.168.137.24");    //��ݮ��IP��ַ
  printf("requesting......\n");*

  if(connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr))<0)//����
    {
      printf("\n Error : Connect Failed \n");
      return 1;
    }


  read(sockfd, recvBuff, sizeof(recvBuff));//��socket
 printf("The pm2.5 is: %c%c\n",recvBuff[0],recvBuff[1]);
  printf("The temperature is: %c%c\n",recvBuff[2],recvBuff[3]);
  printf("The humidity is: %c%c\n",recvBuff[4],recvBuff[5]);
  


  return 0;
}
