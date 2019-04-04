#include "headers.h"

int open_infile() {
        int fd = open(infile, O_RDONLY);
        if (fd < 0)
        {
          perror(infile);
        }
        dup2(fd, 0);
        close(fd);
        return fd;
}
int open_outfile() {
        int f;
        if(c_cat == 2){
          f = open(outfile, O_CREAT |O_APPEND | O_WRONLY);
        }
        else if(c_cat == 1){
          f = open(outfile,O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
        }
        if(f < 0) perror(outfile);
        dup2(f,1);
        close(f);
        return f;
}
