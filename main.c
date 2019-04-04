#include "headers.h"
int is_bg;
int proc_count;
void sig_handler(int signo)
 {
	 if(signo==SIGINT)
	 {
		 fprintf(stderr,"\n");
	 }
}

int main()
{
	int j,i,n2;
	char** commands=(char**)malloc((sizeof(char)*buffer_size)*buffer_size);
	char** command_parts=(char**)malloc((sizeof(char)*buffer_size)*buffer_size);

	for(int i=0;i<buffer_size;i++)
		command_parts[i]='\0';



	get_vars();
	get_currd();
	make_home_dr(cwd);
	while(1)
	{
   	   signal (SIGINT, sig_handler);
  	   signal (SIGQUIT, sig_handler);
 	     signal (SIGTSTP, sig_handler);
	int stat;

  checkbg();

	Proc temp[100];
	int tempcount=0;

	for(i=1;i<=proc_count;i++)
	{
		if(kill(proc_arr[i].id,0)==-1 && errno==ESRCH)  continue;
		else{ tempcount++;  temp[tempcount]=proc_arr[i];}
	}
  proc_count = tempcount;
	for(i=1;i<=proc_count;i++) proc_arr[i]=temp[i];

	set_screen();

	char* command=read_command();
	int n1=parsing_commandline(command,commands);

	for(i=0;i<n1;i++)
	{
    is_bg=0;
	for(j=0;j<buffer_size;j++)
		command_parts[j]='\0';

    if(check(strdup(commands[i])) == -1) {
    if(in_r==1 || out_r==1)
    {
        int z=red_parsing(command,command_parts);

        run_built_in_commands(command_parts,z);
    }
    else
    {
		  n2=parsing_command(commands[i],command_parts);
			run_built_in_commands(command_parts,n2);
      }
	}
  else
      p_and_r(commands[i]);
}

	}
return 0;
}
