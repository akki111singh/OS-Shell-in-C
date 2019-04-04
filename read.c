#include"headers.h"
char* read_command()
{
	char c;
	int length=0;
	char* command = (char*)malloc(sizeof(char)*buffer_size);

	while(1)
	{
		c=getchar();
		if(c!='\n')
		{
			command[length++]=c;
		}
		else
		{
			command[length++]='\0';
			break;
		}
	}
	return command;
}
