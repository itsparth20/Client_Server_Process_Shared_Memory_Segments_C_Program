//Developed by parth patel
#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <string.h>
#include <unistd.h>

int main()
{
	int shmgetid;
	char input[200];
	char* shmatpt = NULL;
	shmgetid = shmget(100, 200, 0777);
	shmatpt = shmat(shmgetid, NULL, 0); 
	while( 1 )
	{
		printf("> ");
		fgets(input, 200, stdin);
		input[strlen(input)-1] = '\0';
		strcpy(shmatpt, input);
		if( strcmp(input, "QUIT")==0){
			break;
		}
	}
}
