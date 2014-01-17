#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#define dist 26

int i,x,sock;
char buf[80];
void dropSpot()
{
    sprintf(buf, "C TRAIL\n");
    write(sock, buf, strlen(buf));
    memset(buf, 0, 80);
    read(sock, buf, 80);
}
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

void straightLine(int distance)
{
    
    sprintf(buf, "S MEL\n");
    write(sock, buf, strlen(buf));
    memset(buf, 0, 80);
    read(sock, buf, 80);
    x=reads();
    printf("X equals to : %d\n", x);
    i=x;
    float value = distance * 36/3.14;
    printf("The value is : %f\n", value);
    
    while(i-x <= value)
    {
        sprintf(buf, "M LR 10 10\n");
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

void turning(int angle,char dir)
{
    if(dir == 'r' || dir == 'R' )
    {
        sprintf(buf, "S MEL\n");
        write(sock, buf, strlen(buf));
        memset(buf, 0, 80);
        read(sock, buf, 80);
    
        int x;
        x=reads();
        printf("X equals to : %d\n", x);
        i=x;
        float value = 212.5 * angle / 90 ;
        printf("The value is: %f\n", value);
        while ( i-x <= value)
        {
            sprintf(buf, "M LR 10 -10\n");
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
    
    if(dir == 'l' || dir == 'L')
    {
        sprintf(buf, "S MER\n");
        write(sock, buf, strlen(buf));
        memset(buf, 0, 80);
        read(sock, buf, 80);
        
        int x;
        x=reads();
        printf("X equals to : %d\n", x);
        i=x;
        float value = 212 * angle / 90 ;
        printf("The value is: %f\n", value);
        while ( i-x <= value)
        {
            sprintf(buf, "M LR -10 10\n");
            write(sock, buf, strlen(buf));
            memset(buf, 0, 80);
            read(sock, buf, 80);
            sprintf(buf, "S MER\n");
            write(sock, buf, strlen(buf));
            memset(buf, 0, 80);
            read(sock, buf, 80);
            
            i=reads();
            printf("I equals to : %d\n",i);
        }

    }

}

void drawSquare(int distance)
{
    int w;
    for(w=1;w<=4;++w)
    {
        dropSpot();
        straightLine(distance);
        turning(90,'r');
    }
}

void drawTriangle(int distance)
{
    int w;
    for(w=1;w<=3;++w)
    {
        dropSpot();
        straightLine(distance);
        turning(60,'l');
    }
}
void drawStar(int size)
{
    
    int w=6;
    for(w=1;w<=6;++w)
    {
        dropSpot();
        straightLine(size);
        turning(60,'l');
        dropSpot();
        straightLine(size);
        turning(120,'r');
    }
}
void drawCircle(int speed, int radius) 
{
    sprintf(buf, "S MER\n");
    write(sock, buf, strlen(buf));
    memset(buf, 0, 80);
    read(sock, buf, 80);
    x=reads();
    i=x;
    int compare = radius * 36 / 3.14;
    int secondspeed = (int) speed*radius/(radius+23);
    while( i-x <= 72*radius )   // get the condition right
    {
        sprintf(buf, "M LR %d %d\n",speed,secondspeed);
        write(sock, buf, strlen(buf));
        memset(buf, 0, 80);
        read(sock, buf, 80);
        
        sprintf(buf, "S MER\n");
        write(sock, buf, strlen(buf));
        memset(buf, 0, 80);
        read(sock, buf, 80);
        i=reads();
        printf("I equals to: %d %d\n",i-x,72*radius);
    }
}


int main() {
	struct sockaddr_in s_addr;
    
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
    
    straightLine(26);
}