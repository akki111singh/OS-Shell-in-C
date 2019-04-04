#include"headers.h"
extern int proc_count;
void cd(char ** command_parts,char *cwd,char *main_dir)
{
	if(command_parts[1]==NULL || strcmp(command_parts[1],"~\0")==0 || strcmp(command_parts[1],"~/\0")==0)
	{
		chdir(main_dir);
		strcpy(cwd,main_dir);
		make_home_dr(cwd);
	}
	else if(chdir(command_parts[1])==0)
	{
		getcwd(cwd,buffer_size);
		make_home_dr(cwd);
	}
	else
	{
		perror("Error executing cd command...");
	}
}

void pwd(char ** command_parts)
{
	char p_w_d[buffer_size];
	getcwd(p_w_d,buffer_size-1);
	printf("%s\n",p_w_d);
}

void echo(char ** command_parts)
{
	int i;
	if(command_parts[0]==NULL)
	{
		printf("\n");
	}
	for(i=1;command_parts[i]; i++)
		printf("%s",command_parts[i]);
}

void jobs(){
	int i;

	for(i = 1; i <= proc_count ; i++) {
		if(proc_arr[i].is_active == 1) {
			printf("[%d] %s %s [%d]\n", i,proc_arr[i].state,proc_arr[i].name, proc_arr[i].id);
		}
	}
}
void overkill() {
	int i;
	for(i = 1 ; i <= proc_count ; i++) {
		if(proc_arr[i].is_active == 1) {
			proc_arr[i].is_active=0;
			if(kill(proc_arr[i].id, SIGKILL) < 0)
				perror("Error killing process!\n");

		}
	}
}

void kjob(int tokens, char** command_parts) {
	if(tokens != 3) {
		fprintf(stderr, "Invalid usage!!!\n");
		return;
	}
	int jno = atoi(command_parts[1]);
	if(proc_arr[jno].is_active == 1)
	{
		if(kill(proc_arr[jno].id, atoi(command_parts[2])) < 0)
			fprintf(stderr, "Signal not sent!\n");
	}
	else fprintf(stderr, "Job not found\n");
}

void bg(int tokens, char** command_parts) {

	if(tokens != 2) {
		fprintf(stderr, "Invalid usage of bg");
		return;
	}

	int i,status;
	int jno = atoi(command_parts[1]);
	if(proc_arr[jno].is_active == 0) {
		printf("No such job exists\n");
		return;
	}

	if(proc_arr[jno].is_active == 1){

		int pid = proc_arr[jno].id;
		kill(pid,SIGCONT);

		strcpy(proc_arr[jno].state,"R");
	}

	else fprintf(stderr, "No job found\n");
}

void fg(int tokens, char** command_parts) {
	if(tokens != 2) {
		fprintf(stderr, "Invalid usage of fg");
		return;
	}
	int i, status;
	int jno = atoi(command_parts[1]);

	if(proc_arr[jno].is_active == 0) {
		printf("No such job exists\n");
		return;
	}
	if(proc_arr[jno].is_active == 1){
		int pid = proc_arr[jno].id;

		kill(pid,SIGCONT);
		waitpid(pid, &status, WUNTRACED);

		if(!WIFSTOPPED(status)) {
			proc_arr[jno].is_active = 0;
		}
		else
		{
			char state[10];
			fprintf(stderr, "\n%s with pid %d has stopped!\n", command_parts[0], pid);
			strcpy(state,get_state(pid));
			for(int i=1;i<=proc_count;i++)
			{
				if(proc_arr[i].id==pid)
				{
					strcpy(proc_arr[i].state,state);
				}
			}
		}
	}
	else fprintf(stderr, "No job found\n");
}
