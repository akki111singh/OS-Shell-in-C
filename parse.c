#include"headers.h"

int parsing_commandline(char *command,char ** commands)
{
	int command_num=0;
	char * part=strtok(command,";");
	while(part!=NULL)
	{
		commands[command_num]=part;
		command_num+=1;
		part=strtok(NULL,";");
	}
	return command_num;
}

//############################# PARSING OF THE COMMAND USING STRcommand_num###########################################################//

int parsing_command(char *command,char ** command_parts)
{
	int num=0;
	char * part=strtok(command,command_delms);
	while(part!=NULL)
	{
		command_parts[num]=part;
		num+=1;
		part=strtok(NULL,command_delms);

	}
	return num;
}
//########################checkforpipe##########################################################################################
int check(char* command) {
        int i;
				c_in=c_out=0;
				in_r=out_r=0;
				c_cat=0;
				piping=0;

        for( i = 0 ; command[i] ; ++i) {
                if(command[i] == '<') {
                        in_r = 1;
                        if(c_in==0)c_in = i;
                }
								if(command[i] == '|')piping = 1;

                if(command[i] == '>' && command[i+1] == '>')c_cat = 2;
								if(command[i] == '>')
								{
                        out_r = 1;
                        if(c_cat == 0)c_cat = 1;
                        if(c_out == 0 )c_out = i;
                }
        }
        if(piping==1) return 1;
        else return -1;
}
//############################## PARSING OF REDIRECTION #########################################################################
int red_parsing(char *command,char** command_parts)
{
	infile=outfile=NULL;
	int n=0;
	char * cmd_dup=strdup(command);
	c_in=0,c_out=0,i=0,in_r=0,out_r=0,c_cat=0;
	for(i=0;command[i];++i)
	{
		if(command[i]=='>' && command[i+1]=='>')c_cat=2;
		if(command[i]=='>')
		{
			out_r=1;
			if(c_cat==0)c_cat=1;
			if(c_out==0)c_out=i;
		}
		if(command[i]=='<')
		{
			in_r=1;
			if(c_in==0)c_in=i;
		}

	}
	if(in_r==1 && out_r==1)
	{
		char* parts;
		parts=strtok(cmd_dup," <>\t\n");
		while(parts!=NULL)
		{
			command_parts[n++]=strdup(parts);
			parts=strtok(NULL,"<> \t\n");
		}
		if(c_in>c_out){
			infile=strdup(command_parts[n-1]);
			outfile=strdup(command_parts[n-2]);
			}
		else
		{		outfile=strdup(command_parts[n-1]);
				infile=strdup(command_parts[n-2]);
		}
		command_parts[n- 2]=NULL;
		command_parts[n-1]=NULL;
		return n-2;
	}
	if(out_r==1)
	{
		char ** c_out_command=malloc((sizeof(char)*buffer_size)*buffer_size);
		char *parts;
		char * cmd_dup=strdup(command);
		if(c_cat==2)
		parts=strtok(cmd_dup, ">>");
		else if(c_cat==1)
		parts=strtok(cmd_dup, ">");

		while(parts!=NULL)
		{
		c_out_command[n++]=parts;
		if(c_cat==2)
		parts=strtok(NULL, ">>");
		else if(c_cat==1)
		parts=strtok(NULL, ">");
	}

	cmd_dup=strdup(c_out_command[n-1]);


	outfile=strdup(strtok(cmd_dup,"< |\t\n"));
	n=0;
	parts=strtok(c_out_command[0],command_delms);
	while(parts!=NULL)
	{
		command_parts[n]=strdup(parts);
		n=n+1;
		parts=strtok(NULL,command_delms);
	}
	} 	

if(in_r==1)
{
	char *parts;
	char * cmd_dup=strdup(command);
	char ** c_in_command=malloc((sizeof(char)*buffer_size)*buffer_size);

	parts=strtok(cmd_dup, "<");

	while(parts!=NULL)
	{
	c_in_command[n]=parts;
	n=n+1;
	parts=strtok(NULL,"<");}
  cmd_dup=strdup(c_in_command[n-1]
	);

 infile=strdup(strtok(cmd_dup,"> |\t\n"));
n=0;
parts=strtok(c_in_command[0],command_delms);
while(parts!=NULL)
{
	command_parts[n]=strdup(parts);
	n=n+1;
	parts=strtok(NULL,command_delms);
}
command_parts[n]=NULL;

}
if(out_r == 0 && in_r == 0 )
return parsing_command(command,command_parts);
else return n;
}

void piping_parse(char* cmd) {
        char* cmd_dup = strdup(cmd);
        char* part;
        int n=0;
        part = strtok(cmd_dup, "|");
        while(part!= NULL) {
                p_cmds[n] = part;
								n++;
                part = strtok(NULL, "|");
        }
        p_no =n;
}
