


#include <string.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include<unistd.h>
#include <sys/time.h>
#include <time.h>

#define SENDER_PORT 3490
#define SENDER_IP "127.0.0.1"



int main(int argc, char *argv[]) {

	 int sockfd;
	 int rcv_num,loop_count,i;
	 char buf[1024];
	 struct sockaddr_in sender_addr;

	 struct timeval start,end;

	 //open socket and connect
	 if( (sockfd = socket(PF_INET, SOCK_STREAM, 0)) ==-1){
		  perror("socket error"); // do some error checking!
		  exit(1);
	 }

	 sender_addr.sin_family = AF_INET;
	 sender_addr.sin_port = htons(SENDER_PORT);
	 sender_addr.sin_addr.s_addr = inet_addr(SENDER_IP);
	 memset(sender_addr.sin_zero, '\0', sizeof(sender_addr.sin_zero));

	 if ((connect(sockfd,(struct sockaddr *)&sender_addr,sizeof(sender_addr))) ==-1){
		  perror("connect error"); // do some error checking!
		  exit(1);
	 }

	 char buffer1[30];
	 struct timeval tv;
	 			time_t
curtime1;																																							
	 gettimeofday(&tv, NULL); 
	 curtime1=tv.tv_sec;

	 strftime(buffer1,30,"%m-%d-%Y  %T.",localtime(&curtime1));
	 printf("Client time : %s%ld\n",buffer1,tv.tv_usec);

	//Sending request
	strcpy(buf,"get_time");
	//Starting timmer
	gettimeofday(&start,NULL);
	send(sockfd,&buf,1024,0);

	//Getting response
	struct timeval t1;
	rcv_num = recv(sockfd,&t1,sizeof(struct timeval),0);

	//Stoping timmer
	gettimeofday(&end,NULL);
	

	t1.tv_sec += (end.tv_sec - start.tv_sec)/2;

	char buffer[30];
	time_t curtime;

	curtime=t1.tv_sec;

	 strftime(buffer,30,"%m-%d-%Y  %T.",localtime(&curtime));
	 printf("Updeted Time : %s%ld\n",buffer,t1.tv_usec);

	 double tt1,tt2;
	 tt1 =start.tv_sec+(start.tv_usec/1000000.0);
     tt2 =end.tv_sec+(end.tv_usec/1000000.0);

	 printf("Round Trip Time : %g\n", (tt2 - tt1));

	 printf("\nClose socket and exit\n");
	 close(sockfd);
	 exit(0);
}
