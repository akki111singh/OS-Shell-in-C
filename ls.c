#include"headers.h"
int hide(const struct dirent *namelist)
{
    if(namelist->d_name[0] == '.') return 0;
    else return 1;
}

void print_perms(mode_t st) {
     char perms[11];
     if(st && S_ISREG(st)) perms[0]='-';
     else if(st && S_ISDIR(st)) perms[0]='d';
     else if(st && S_ISFIFO(st)) perms[0]='|';
     else if(st && S_ISSOCK(st)) perms[0]='s';
     else if(st && S_ISCHR(st)) perms[0]='c';
     else if(st && S_ISBLK(st)) perms[0]='b';
     else if(st && S_ISLNK(st)) perms[0]='l';  // S_ISLNK
     perms[1] = (st && S_IRUSR) ? 'r':'-';
     perms[2] = (st && S_IWUSR) ? 'w':'-';
     perms[3] = (st && S_IXUSR) ? 'x':'-';
     perms[4] = (st && S_IRGRP) ? 'r':'-';
     perms[5] = (st && S_IWGRP) ? 'w':'-';
     perms[6] = (st && S_IXGRP) ? 'x':'-';
     perms[7] = (st && S_IROTH) ? 'r':'-';
     perms[8] = (st && S_IWOTH) ? 'w':'-';
     perms[9] = (st && S_IXOTH) ? 'x':'-';
     perms[10] = '\0';
     printf("%s", perms);
 }

void ls(char* path,char fl)
{
  int i=0;
  int n;
  if(fl=='l') n=scandir(path,&namelist,hide,alphasort);
  if(fl=='a') n=scandir(path,&namelist,NULL,alphasort);
  while(i<n)
  {
    printf("%s  ",namelist[i]->d_name);
    i++;
  }
	printf("\n");
  free(namelist);
}

void ls_l(char* path,char fl){
int i;
int n;
struct stat buf;
char datestring[256];
struct tm *time;

if(fl=='l') n=scandir(path,&namelist,hide,alphasort);
if(fl=='a') n=scandir(path,&namelist,NULL,alphasort);

while(i<n)
{
  stat(namelist[i]->d_name,&buf);
  print_perms(buf.st_mode);

  printf(" %d", (int)buf.st_nlink);

  struct passwd * uname = getpwuid(buf.st_uid);
  struct group * ugroup = getgrgid(buf.st_gid);

  printf(" %s",uname->pw_name);
  printf(" %s",ugroup->gr_name);

  printf(" %5d", (int)buf.st_size);

  time=localtime(&buf.st_mtime);

  strftime(datestring, sizeof(datestring), "%b %d %H:%M", time);

  printf(" %s %s\n", datestring, namelist[i]->d_name);

  i++;
}
}
