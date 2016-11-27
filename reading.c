/*
  Krishna Thevathasan
  krishnat@my.yorku.ca
  212946893
*/

#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

void my_cnt(char* fileName) {

  int fd;
  int totalBytesRead = 0;
  int pagesize = getpagesize();
  int count = 0;
  int i = 0;
  struct stat mystat;
  char buf[pagesize];

  //Open file descriptor
  fd = open(fileName, O_RDONLY);
  if (fd == -1)  {
    fprintf(stderr, "reading.so - Couldn't open %s \n", fileName);
    exit(1);
  }

  //Get file stats, mainly for file size
  if(fstat(fd,&mystat) < 0) {
    fprintf(stderr, "reading.so - fstat error\n");
    close(fd);
    exit(1);
  }

  //read through file in pagesize chunks
  while(totalBytesRead < mystat.st_size ) {

    read(fd, buf, pagesize);

    while (i < mystat.st_size) {
      if (buf[i] == '\n' ) {
        count++;
      }
      i++;
    }
    i = 0;

    totalBytesRead = totalBytesRead + pagesize;
  }
  printf("There are %d newline character(s) in file %s \n", count, fileName);
  close(fd);
}
