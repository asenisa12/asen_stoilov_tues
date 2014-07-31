#include <iostream>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <stdio.h>
#include <poll.h>
#include <time.h>
#include <string>
#include <errno.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>

using namespace std;

#define OPEN_MAX 256
#define INFTIM (-1)

int initiate_server(string ip, int port){

	struct sockaddr_in servaddr;
	int listenfd, connfd, i, maxi=0, sockfd;
	struct pollfd client[OPEN_MAX];
	struct sockaddr cliaddr;



	bzero(&servaddr,sizeof(servaddr));
	servaddr.sin_family =AF_INET;
	inet_pton(AF_INET, ip.c_str(), &(servaddr.sin_addr));
	servaddr.sin_port = htons(port);

	if((listenfd = socket(AF_INET, SOCK_STREAM, 0)) < 0){
		perror("socket:");
		return -1;
	}
	

	
	if(bind(listenfd,(struct sockaddr*)&servaddr, sizeof(servaddr))){
		perror("bind");
		return -1;
	}

	if(listen(listenfd, 100) < 0){
		perror("listen:");
		return -1;
	}

	client[0].fd = listenfd;
	client[0].events = POLLRDNORM;

	for(i=1; i<OPEN_MAX; i++)
		client[i].fd = -1;

	int nready, clicount=-1;
	for (;;){
		nready = poll(client, maxi+1, INFTIM);

		if((client[0].revents & POLLRDNORM) ){

			socklen_t clilen = sizeof(cliaddr);
			if((connfd = accept(listenfd, &cliaddr, &clilen))<0)
				perror("accept");
			
			for(i=1; i< OPEN_MAX; i++)
				if(client[i].fd < 0){
					client[i].fd = connfd;
					break;
				}

			if (clicount==OPEN_MAX){
				perror("too many clients");
				return -1;
			}

			client[i].events = POLLRDNORM;

			if(i>maxi)
				maxi = i+1;
			clicount+=1;
			printf("%d\n",i);
		}

		for(i=1; i< maxi; i++){

			if((sockfd = client[i].fd) < 0)
				continue;

			if (client[i].revents & (POLLRDNORM | POLLERR)){
				int size,n;
				
				if(ioctl(client[i].fd, FIONREAD, &size)>=0){
					string buf(size, 0);
					printf("I:%d\n",i);
					if ((n = read(client[i].fd, &buf[0], size))<0){
						if (errno == ECONNRESET){
							close(client[i].fd);
							client[i].fd = -1;
							clicount-=1;
						} else
							perror("read error");

					}else if (n==0){
						close(client[i].fd);
						client[i].fd = -1;
						clicount-=1;
					} else
						write(client[i].fd, &buf[0], n);
					if(--nready <=0)
						break;
				}
			}
		}
	}

	return 0;
}

int main(){


	initiate_server("0.0.0.0", 9877);
	return 0;
}