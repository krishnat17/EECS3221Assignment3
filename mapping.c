/*
  Krishna Thevathasan
  krishnat@my.yorku.ca
  212946893
*/

#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>

void my_cnt(char* fileName) {

  int fd;
  int i = 0;
  int count = 0;
  struct stat mystat;
  char *map;

  fd = open(fileName, O_RDONLY);
  if (fd == -1)  {
    fprintf(stderr, "mapping.so - Couldn't open %s \n", fileName);
    exit(1);
  }

  if(fstat(fd,&mystat) < 0) {
    fprintf(stderr, "mapping.so - fstat error\n");
    close(fd);
    exit(1);
  }

  map = mmap((caddr_t)0, mystat.st_size, PROT_READ, MAP_SHARED, fd, 0);
  if (map == MAP_FAILED) {
    fprintf(stderr, "mapping.so - mmap error\n");
    close(fd);
    exit(1);
  }

  while (i < mystat.st_size) {
    if (map[i] == '\n' ) {
      count++;
    }
    i++;
  }

  printf("There are %d newline character(s) in file %s \n", count, fileName);
  close(fd);


}
