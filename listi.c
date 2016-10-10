//

#include <stdio.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <stdlib.h>

int n, N;
static int id, pid;

typedef struct State {
	DIR *dir;
	char *path;
}State;

State *stack, *ptr;



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

int directories(char *path, char *str) {

if(!directory(path)) return;
n++;

DIR *dir;
struct dirent *m;	// directory entry object

if((chdir(path))) return;

char *cwd;	//for current working directory
char *tmp;

#define push(s) *ptr++ = s; ++N
#define pop() *(--ptr); --N

State f;
stack = malloc(sizeof(*stack)*1000);
ptr = stack;


	printf("%d %s %d \n",n,path,N);
	dir = opendir(path);	// open a directory stream
	chdir(path);
	cwd = getcwd(NULL,0);	//get current working directory
	tmp = malloc(strlen(path)+257);
	tmp = strcpy(tmp,path);
	if(path[0] == '/' && path[1] != '\0')
		tmp = strcat(tmp,"/");
	f.dir = dir;
	f.path = tmp;
   push(f);
   char *p;
  // State *ptrs;

while(ptr != stack) {
	f = pop();
	
// read directory content
while((m = readdir(f.dir)))
{
  if((m->d_name[0] != '.' && m->d_name[1] != '.' && m->d_name[2] != '\0') || (m->d_name[0] != '.' && m->d_name[1] != '\0'))
  { 
	//directories(strcat(tmp,m->d_name));
	p = malloc(strlen(f.path)+257);
	p = strcpy(p,f.path);
	//assert()
	if(directory(strcat(p,m->d_name)) == 1) 
	{
		n++;
		push(f);
		printf("%d %s %d\n",n,p,N);
		
		//change state
		if((dir = opendir(p)))
		{
			State s;
			chdir(p);
			p = strcat(p,"/");
			s.path = p;
			s.dir = dir;
			f = s;
		}

	}
	else { free(p);
	if(strcmp(str,m->d_name) == 0) return 1; }
  }

}
closedir(f.dir);

 }

 return 0;

}
 

int main(int argc, char *argv[]) {

char *b;
n =0;
N=0;
if(argc == 0)  // if no argument is given then
b = getcwd(NULL,0); //get current working directory
else b = argv[1];	// otherwise use the given argument

char *str = argv[2];

if(directories(b,str) == 1) printf("found\n");

return 0;

}
