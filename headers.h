#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string.h>
#include <sys/dir.h>
#include <sys/types.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <locale.h>
#include<fcntl.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/wait.h>
#include<errno.h>

void run_built_in_commands(char ** command_parts,int tokens);
void run_command(char** command_parts);
void cd(char ** command_parts,char *cwd,char *main_dir);
void echo(char ** command_parts);
void pwd(char ** command_parts);
void get_info(char ** command_parts);
void reminder(char ** command_parts,int tokens);
void ls_l(char* path,char fl);
void ls(char* path,char fl);
void print_perms(mode_t st);
int hide(const struct dirent *namelist);
int parsing_command(char *command,char ** command_parts);
int parsing_commandline(char *command,char ** commands);
char* read_command();
void make_home_dr(char* cwd);
void set_screen();
void get_currd();
void get_vars();
void jobs();
int open_infile();
int open_outfile();
void initialize_shell();
void overkill();
void piping_parse(char* cmd);
void addjob(char ** command_parts,int wpid);
void rem_job(int wpid);
void checkbg();
int check(char* command);
char * get_state(int wpid);
void fg(int tokens,char ** command_parts);
void bg(int tokens,char ** command_parts);
void kjob(int tokens,char ** command_parts);
void unsetenvv(char **command_parts,int tokens);
void setenvv(char **command_parts,int tokens);
int red_parsing(char *command,char** command_parts);
int both_in_out();
int c_in,c_out,i,in_r,out_r,c_cat,piping;
struct dirent **namelist;
char * infile;
char * outfile;
#define buffer_size 1024
#define command_delms " \t\n"

char user[buffer_size];
char hostname[buffer_size];
char cwd[buffer_size];
char main_dir[buffer_size];
char* p_cmds[buffer_size];
void p_and_r(char* cmd);
void childhandler();
int p_no;
char** c_in_command;
char** c_out_command;
pid_t kidpid;

typedef struct
{
  int id;
  char name[100];
  char state[100];
  int is_active;
} Proc;

extern int is_bg;
extern int proc_count;
Proc proc_arr[100];
