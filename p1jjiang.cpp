#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string>
#include <cstring>
#include <sys/wait.h>
#include <sys/types.h>
#include <signal.h>
#include <iostream>

using namespace std;

volatile sig_atomic_t flag = 0;
void my_function(int sig) {
   flag = 1;
}

int main () {
	
	char* strAry[10];
	char str1 [80];
	char str2 [] = " ";
	char* token;

	signal(SIGINT, my_function);

    while(!flag)
      {
	cout<< "#";
	cin.getline(str1, 80);
	token =strtok(str1, str2);

	int i = 0;

	while (token != NULL)
	 {
		strAry[i] = token;
		token = strtok(NULL, str2);
		i++;
	 }

	strAry[i] = NULL;
	
	int rc = fork();

	if(rc < 0)
	  exit(1);

	else if(rc == 0 )
	  execvp(strAry[0],strAry);

	else
	  wait(NULL);

        }

	return 0;
}
