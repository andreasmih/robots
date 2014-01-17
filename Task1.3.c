#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#define dist 10

char buf[80];

int reads()
{
    int q;
    int result=0;
    result=0;
    int j=0;
    while(buf[j]<48 || buf[j]>57)
        ++j;
    while(buf[j]>=48 && buf[j]<=57)
    {
        result = result*10 + ((int)buf[j]-48);
        ++j;
    }
    
    return result;
}

int main() {
	struct sockaddr_in s_addr;
	int i, sock;
    
	if ((sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0) {
		fprintf(stderr, "Failed to create socket\n");
		exit(1);
	}
    
	s_addr.sin_family = AF_INET;
	s_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	s_addr.sin_port = htons(55443);
    
	if (connect(sock, (struct sockaddr *) &s_addr, sizeof(s_addr)) < 0) {
		fprintf(stderr, "Failed to connect socket\n");
		exit(1);
	}
    
    sleep(1);
    read(sock, buf, 80);
    memset(buf, 0, 80);
    
    sprintf(buf, "S MEL\n");
    write(sock, buf, strlen(buf));
    memset(buf, 0, 80);
    read(sock, buf, 80);
    
    int x;
    x=reads();
    printf("X equals to : %d\n", x);
    i=x;
    
	while ( i-x < 211)
    {
        sprintf(buf, "M LR 1 -1\n");
		write(sock, buf, strlen(buf));
		memset(buf, 0, 80);
		read(sock, buf, 80);
        
        sprintf(buf, "S MEL\n");
		write(sock, buf, strlen(buf));
		memset(buf, 0, 80);
		read(sock, buf, 80);
        
        i=reads();
        printf("I equals to : %d\n",i);
	}
}