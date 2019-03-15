#include <stdio.h>
#include <sys/time.h>
#include <time.h> 

int main() {
	
	 char buffer[30];
	 struct timeval tv;

	 time_t curtime;



	 gettimeofday(&tv, NULL); 
	 curtime=tv.tv_sec;

	 strftime(buffer,30,"%m-%d-%Y  %T.",localtime(&curtime));
	 printf("%s%ld\n",buffer,tv.tv_usec);
	 return 0;
}