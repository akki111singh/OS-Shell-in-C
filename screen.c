#include"headers.h"
void get_vars()
{
	getlogin_r(user,buffer_size-1);
	gethostname(hostname,buffer_size-1);
}

void get_currd()
{
	getcwd(main_dir,buffer_size-1);
	strcpy(cwd,main_dir);
}

void set_screen()
{
	printf("%s@%s:%s$",user,hostname,cwd);
}

void make_home_dr(char* cwd) {
        int i, j;
        for(i = 0; cwd[i]==main_dir[i] && cwd[i]!='\0' && main_dir[i] != '\0'; i++);

        if(main_dir[i] == '\0') {
                cwd[0] = '~';
                for(j = 1; cwd[i]!='\0'; j++) {
                        cwd[j] = cwd[i++];
                }
                cwd[j] = '\0';
        }
}


void checkbg()
{
int status,i;
pid_t pid;
while((pid=waitpid(-1,&status,WNOHANG))>0)
{
	for(i=0;i<proc_count; i++)
	{
		if (proc_arr[i].id==pid)
		{
			proc_arr[i].is_active=0;
			break;
		}
	}
	if (WIFEXITED(status))
	{
		printf("Process with pid %d terminated with exit stauts: ",pid );
		printf("%d\n",WEXITSTATUS(status));
	}
	else
	{
		if (WIFSIGNALED(status))	printf("Process with pid %d exited due to signal no %d\n",pid,WTERMSIG(status));
	}
}
}

void childhandler(int sig)
{
	signal(SIGINT,SIG_DFL);
	signal(SIGTSTP,SIG_DFL);
	signal(SIGCHLD,SIG_DFL);
	int status,i;
	pid_t pid;
	if(sig==SIGCHLD)
	{
		while((pid=waitpid(-1,&status,WNOHANG))>0)
		{
			for(i=0;i<proc_count; i++)
			{
				if (proc_arr[i].id==pid)
				{
					proc_arr[i].is_active=0;
					break;
				}
			}
			if (WIFEXITED(status))
			{
				printf("Process with pid %d terminated with exit stauts: ",pid );
				printf("%d\n",WEXITSTATUS(status));
			}
			else
			{
				if (WIFSIGNALED(status))	printf("Process with pid %d exited due to signal no %d\n",pid,WTERMSIG(status));
			}

		}

}
}
