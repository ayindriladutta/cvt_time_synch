
#include <string.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#define MYPORT 3490
//#define SIZE_TO_SEND 1000
#define MY_IP "127.0.0.1"

int main(int argc, char *argv[]) {
	 int sockfd,sockfd2;
	 char tosend = 's'; //a char (1byte) to send to receivers
	 char ack;
	 struct sockaddr_in my_addr,rcvr_addr;
	 struct timeval start,end;
	 int sin_size = sizeof(my_addr),i,k,num_packet_sent,optval;
	 double t1,t2;

	 //open TCP socket,bind and accept RECEIVERS connections 
	 if( (sockfd = socket(PF_INET, SOCK_STREAM, 0)) ==-1){
		  perror("socket error");
		  exit(1);
	 }
	 my_addr.sin_family = AF_INET;
	 my_addr.sin_port = htons(MYPORT);
	 my_addr.sin_addr.s_addr = inet_addr(MY_IP);
	 memset(my_addr.sin_zero, '\0', sizeof(my_addr.sin_zero));
	 //allow reuse of port
	 optval = 1;
	 if (setsockopt(sockfd,SOL_SOCKET,SO_REUSEADDR,&optval,sizeof(int)) == -1) {
		  perror("setsockopt");
		  exit(1);
	 }
	 //bind(socketfd, struct about my address,sizeofmy address);
	 if (bind(sockfd, (struct sockaddr *)&my_addr, sizeof my_addr) == -1) {
		  perror("bind");
		  exit(1);
	 }

	 listen(sockfd,3);

	 if (listen(sockfd, 3) == 0){
	        printf("listening...\n");
	 }
	 else{
	        printf("error in listening");
	 }
	 while (1){
 		sockfd2 = accept(sockfd, (struct sockaddr *)&rcvr_addr, &sin_size);

 		char buf[1024];
 		optval=recv(sockfd2,buf,1024,0);

 		struct timeval tv;
	 	gettimeofday(&tv, NULL); 

	 	send(sockfd2,&tv,sizeof(struct timeval),0);
	 	
	}
 	shutdown(sockfd2,2);
 	shutdown(sockfd,2);
 	exit(0);
}
