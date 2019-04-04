#include"headers.h"
void unsetenvv(char **command_parts,int tokens){
  if(tokens==1) printf("invalid syntax!!!");
  else  {unsetenv(command_parts[1]); return;}
}

void setenvv(char **command_parts, int tokens)
{
  if(tokens==1) printf("invalid syntax!!!!");
  else if(tokens>3) printf("Arguments no. exceded");
  else
  {
  if(tokens==2) setenv(command_parts[1] , " " , 1);
  else  setenv(command_parts[1] , command_parts[2] , 1);
  }
  return;
}
