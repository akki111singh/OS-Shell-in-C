#include"headers.h"

void get_info(char ** command_parts)
{
	pid_t pid;
	int num=0;
	int i,a=1;

	if(command_parts[1] == NULL) pid = getpid();
	else pid = atoi(command_parts[1]);

	char* path= malloc(sizeof(char)*1000);
	char* data=malloc(sizeof(char)*100000);
	char** pinf=malloc((sizeof(char)*1000)*1000);
	char buffer;
	char* buf=malloc(sizeof(char)*buffer_size);
	char * token=malloc(sizeof(char)*1024);

	sprintf(path,"/proc/%d/stat",pid);

	int fd=open(path,O_RDONLY);
	if(fd<0)
	{
		  perror("Error while opening the proc/pid/status file\n");
	}
	else{
			for(i=0;a>=0;i++)
			{
			a=lseek(fd,i,SEEK_SET);
			read(fd,&buffer,1);
			data[i]=buffer;
			if(buffer=='\n' || buffer=='\0')
				break;
			}
			token=strtok(data," ");
				while(token!=NULL)
				{
					pinf[num]=token;
					num+=1;
					token=strtok(NULL," ");
				}
				 printf("pid -- %d\n", pid);
				 printf("State -- %s\n",pinf[2]);
				 printf("Memory -- %s\n",pinf[22]);
			       sprintf(path, "/proc/%d/exe", pid);
			       int len = -1;
			       len = readlink(path,buf, buffer_size - 1);
			        if(len==-1) {
			                perror("Error while opening the proc/pid/exe file\n");
			        }
			        else {
			                buf[len] = '\0';
			                make_home_dr(buf);
			                printf("Executable Path -- %s\n", buf);
			        }
			}
close(fd);
}
