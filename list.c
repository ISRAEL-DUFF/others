/* Recursive implementation of the Directory Listing program
   Given  a directory name Dname as input, the program would (assume Dname to be a root directory and would start to) list all subdirectories within Dname.

	input: Directory name
	output: list of all subdirectories within given Directory
*/ 

#include <stdio.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <stdlib.h>

int n;

int directory(char *path) {
struct stat mstat;
 int ret = stat(path, &mstat);
 if(ret) {
	perror("stat");	
        return 2;
 }

//determine whether it's a directory or not
if((mstat.st_mode & S_IFMT) != S_IFDIR)
  return 0; 
else return 1;

}

void directories(char *path) {

if(!directory(path)) return;
n++;

DIR *dir;
struct dirent *m;	// directory entry object
if(!(dir = opendir(path))) return;	// open a directory stream

if((chdir(path))) return;

char *cwd = getcwd(NULL,0);	//get current working directory
char *tmp;
tmp = malloc(strlen(path)+257);
tmp = strcpy(tmp,path);

if(path[0] == '/' && path[1] != '\0')
tmp = strcat(tmp,"/");

printf("%d %s\n",n,path);
// read directory content
while((m = readdir(dir))) {
 if((m->d_name[0] != '.' && m->d_name[1] != '.' && m->d_name[2] != '\0') || (m->d_name[0] != '.' && m->d_name[1] != '\0')) 
	directories(strcat(tmp,m->d_name));
 tmp = strcpy(tmp,path);
tmp = strcat(tmp,"/");
 
}

closedir(dir);

}
 

int main(int argc, char *argv[]) {

char *b;
n = 0;
if(argc == 0)  // if no argument is given then
b = getcwd(NULL,0); //get current working directory
else b = argv[1];	// otherwise use the given argument

directories(b);

return 0;

}
