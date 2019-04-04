#include"headers.h"
extern int is_bg;
extern  int proc_count;
int flag=0;

//################################# REMIND_ME_COMMAND_######################################################################
void remindme(char ** command_parts,int tokens)
{
	if(command_parts[1]==NULL)
	{
		printf("Invalid syntax: Specify time\n");
		return;
	}
	else if(command_parts[2]==NULL && command_parts[1]!=NULL)
	{
		printf("Invalid syntax: Specify some message\n");
		return;
	}

	for(int j=0;j<strlen(command_parts[1]);j++)
	{
		if(command_parts[1][j]<=57 && command_parts[1][j]>=48)
		{
			continue;
		}
		else
		{
			printf("Invalid syntax");
			return;
		}
	}
	pid_t rem_pid;
	int t=atoi(command_parts[1]);
	rem_pid=fork();
	if(rem_pid<0)
	{
		perror("Error");
	}
	else if(rem_pid==0)
	{
		sleep(t);
		printf("\nREMINDER: ");
		for(int i=2;i<tokens;i++)
		{
			printf("%s ",command_parts[i]);
		}
		printf("\n");
		return;
	}
	else
	{
		printf("Reminder has been set with pid %d\n",rem_pid);
	}

}
//############################CLOCK_COMMAND ##########################################################################################

void clock_(char ** command_parts,int tokens)
{
	char 	Date[20];
	char  Time[20];
	FILE * date_file;
	FILE * time_file;
	if(tokens<5)
	{
		printf("Invalid syntax\n");
		return;
	}

	if(strcmp(command_parts[1],"-t")!=0 && strcmp(command_parts[3],"-n")!=0)
	{
		printf("Invalid syntax\n");
		return;
	}

	for(int j=0;j<strlen(command_parts[2]);j++)
	{
		if(command_parts[2][j]<=57 && command_parts[2][j]>=48)
		{
			continue;
		}
		else
		{
			printf("Invalid syntax");
			return;
		}
	}


		for(int j=0;j<strlen(command_parts[4]);j++)
		{
			if(command_parts[4][j]<=57 && command_parts[4][j]>=48)
			{
				continue;
			}
			else
			{
				printf("Invalid syntax");
				return;
			}
		}

	int n=atoi(command_parts[4]);
	while(1)
	{
		if(n<0)
		{
			break;
		}
		date_file=fopen("/sys/class/rtc/rtc0/date","r");
		time_file=fopen("/sys/class/rtc/rtc0/time","r");

	if(time_file==NULL)
	{
		printf("ERROR IN OPENING /sys/class/rtc/rtc0/date\n");
		return;
	}
	fscanf(date_file,"%s",Date);
	printf("%s, ",Date);

	fscanf(time_file,"%s",Time);
	printf("%s\n",Time);
	sleep(atoi(command_parts[2]));
	n=n-atoi(command_parts[2]);
}
}
//###################################run_command_#######################################################################################

void run_command(char** command_parts)
{
	int status;
	pid_t wpid;
	wpid=fork();

	if(wpid<0)
	{
		perror("Child Proc. not created\n");

	}
	else if(wpid==0)
	{
		int in,out;

		if(is_bg==1)
		{
			setpgid(0,0);
		}
		if(in_r){
				in = open_infile();
				if(in == -1) _exit(-1);
		}
		if(out_r){
				out = open_outfile();
				if(out == -1) _exit(-1);
		}

		int ret;
		if((ret = execvp(command_parts[0],command_parts)) < 0){
		perror("Error executing command!\n");
			_exit(-1);
	}
	}
	else if (is_bg==0) {
		kidpid=getpid();
		int status;
		waitpid(wpid, &status, WUNTRACED);

		if(!WIFSTOPPED(status)) rem_job(wpid);
		else
		{
			 addjob(command_parts,wpid);
			 char state[10];
			 fprintf(stderr, "\n%s with pid %d has stopped!\n", command_parts[0], wpid);
			 strcpy(state,get_state(wpid));

			 for(int i=1;i<=proc_count;i++)
			 {
				 if(proc_arr[i].id==wpid)
				 {
					 strcpy(proc_arr[i].state,state);
				 }
			 }
		}

	}
else{
	signal(SIGCHLD,childhandler);
	addjob(command_parts,wpid);
  }
}

void run_built_in_commands(char ** command_parts,int tokens)
{
	if(tokens>0)
	{
	if(strcmp(command_parts[0], "cd\0") == 0)
	     cd(command_parts, cwd, main_dir);
        else if(strcmp(command_parts[0], "pwd\0") == 0)
						pwd(command_parts);
        else if(strcmp(command_parts[0], "quit\0") == 0)
            _exit(0);
				else if(strcmp(command_parts[0], "echo\0") == 0)
						echo(command_parts);
				else if(strcmp(command_parts[0], "jobs\0") == 0)
					jobs();
				else if(strcmp(command_parts[0], "overkill\0") == 0)
						overkill();
				else if(strcmp(command_parts[0], "fg\0") == 0)
							fg(tokens,command_parts);
				else if(strcmp(command_parts[0], "bg\0") == 0)
										bg(tokens,command_parts);
				else if(strcmp(command_parts[0], "kjob\0") == 0)
							kjob(tokens,command_parts);
				else if(strcmp(command_parts[0], "setenv\0") == 0)
							setenvv(command_parts,tokens);
				else if(strcmp(command_parts[0], "unsetenv\0") == 0)
							unsetenvv(command_parts,tokens);

				else if(strcmp(command_parts[0], "pinfo\0") == 0)
						get_info(command_parts);
				else if(strcmp(command_parts[tokens-1], "&\0") == 0)
				 	 {
							command_parts[tokens - 1] = NULL;
									is_bg = 1;
							run_command(command_parts);
					}
				else if(strcmp(command_parts[0], "clock\0") == 0)
							{
								clock_(command_parts,tokens);
							}
				else if(strcmp(command_parts[0],"remindme\0")==0)
				{
					remindme(command_parts,tokens);
				}
				else if(isalpha(command_parts[0][0]))
				{
              run_command(command_parts);
				}
			}
}

//####################### ADD_JOB ########################################################################
void addjob(char ** command_parts,int wpid)
{
	char state[10];
	proc_count++;
	proc_arr[proc_count].id = (int) wpid;
	strcpy(proc_arr[proc_count].name,command_parts[0]);

	printf("[%d]  %d\n",proc_count,wpid);

	strcpy(state,get_state(wpid));
	proc_arr[proc_count].is_active=1;
	strcpy(proc_arr[proc_count].state,state);
}
//#######################################REM-job ################################################

void rem_job(int wpid) {
        int i;
        for(i = 1 ; i <= proc_count; i++) {
                if(proc_arr[i].id == wpid) {
                        proc_arr[i].is_active = 0;
                        break;
                }
        }
}

//######################################GET_CURRENT_STATE ################################################################
char* get_state(int wpid)
{
	int num=0;
	int i,a=1;
	char* path= malloc(sizeof(char)*1000);
	char buffer;
	char* data=malloc(sizeof(char)*100000);
	char * token=malloc(sizeof(char)*1024);
	char** pinf=malloc((sizeof(char)*1000)*1000);

	sprintf(path,"/proc/%d/stat",wpid);

	int fd=open(path,O_RDONLY);
	if(fd<0)
	{
		  perror("Error while opening the proc/pid/status file\n");
			_exit(-1);
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
			return pinf[2];
		}
	}

	void p_and_r(char* cmd){
	        int pid, in, out,i,status,j;
					char** commands_parts = malloc((sizeof(char)*buffer_size)*buffer_size);
	        piping_parse(cmd);

	        int* pipes = (int* )malloc(sizeof(int)*(2*(p_no - 1)));
	        for(i=0;i<2*p_no-3;i+=2) {
	                if(pipe(pipes+i)< 0) {
	                    perror("pipe is not opened!\n");
	                      return;
	                }
	        }
	        for(i=0;i<p_no;++i) {
									int tokens =red_parsing(strdup(p_cmds[i]), commands_parts);
									pid = fork();
	                is_bg = 0;

	                if(pid < 0)
	                        perror("forking Error!\n");
	                else if(pid == 0) {
	                        if(i < p_no - 1)
													dup2(pipes[2*i + 1], 1);
													else if(out_r==1) out = open_outfile();

												if(i > 0 )
												dup2(pipes[2*i -2], 0);
	                       else if(in_r==1) in = open_infile();

	                        int j;
	                        for(j=0;j<2*p_no-2; ++j)
													{
														close(pipes[j]);
													}
	                        if(execvp(commands_parts[0], commands_parts) < 0 )
													{
	                                perror(" Error Execvp!!\n");
	                                _exit(-1);
	                        }
	                }
	        }
	        for(i=0;i<2*p_no-2;++i)
					{
						 close(pipes[i]);
					}
	}
