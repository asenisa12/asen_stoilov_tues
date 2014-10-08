#include <stdio.h>
#include <sys/inotify.h>
#include <errno.h>

#define EVENT_SIZE sizeof(struct inotify_event)
#define EVENT_BUF_LEN (1024 * EVENT_SIZE)

int main(int argc, char *argv[]){
	int fd = inotify_init();
	char buf[EVENT_BUF_LEN];

	if(fd<0) perror("init error!");
	
	int wd = inotify_add_watch(fd, argv[1], (IN_MOVED_TO));
	
	int length;
	if((length = read(fd, buf, EVENT_BUF_LEN)) < 0)
		perror("read err!");
	
	int i=0;
	while(i<length){
		struct inotify_event *event = (struct inotify_event*)&buf[i];
		if(event->len){
			if(event->mask & (IN_MOVED_TO)){
				printf("files is moved to :%s\n",argv[1]);				}			
		}
		i+=EVENT_SIZE + event->len;	
	}
	
	inotify_rm_watch(fd,wd);
	
	close(fd);
	
	return 0;
}
