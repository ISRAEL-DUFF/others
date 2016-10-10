//my own implementation of cat program

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


int main(int argc, char *argv[]) {

if(argc < 2)
{
 printf("You forgot to enter the file name");
 exit(1);
}

  int n, m;
char buf[512];
 close(0);
 int fd = open(argv[1],O_RDONLY);

if(fd == -1) {
 printf("Invalid file name\n");
  exit(1);
}

while(((n = read(0,buf,512)) > 0)) // printf("Error while reading standard input");
   if((m = write(1,buf,n)) == -1) printf("Error while writting to standard input");

return 0;
}

