//Developed by Parth Patel
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <string.h>


void handlecontrolC(int);
int shmgetid, id=0;
char* shmatpt = NULL;

int main()
{ 

	signal(SIGINT, handlecontrolC); 
	shmgetid = shmget(100, 200, IPC_CREAT | IPC_EXCL | 0777);
	shmatpt = shmat(shmgetid, NULL, 0);
	
	while(1)
	{
		if(strcmp(shmatpt, "HI")==0)
		{
			printf("Greetings!\n");
			fflush(stdout);
			shmatpt[0] = '\0';

		}
		else if(strcmp(shmatpt, "PID")==0)
		{
			id = (int)getpid();
			printf("Server pid: %i\n", id);
			fflush(stdout);
			shmatpt[0] = '\0';

		}
		else if(strcmp(shmatpt, "QUIT")==0){
			shmctl(shmgetid, IPC_RMID, NULL);
			shmdt(shmatpt);
			printf("GOODBYE!\n");
			exit(0);      
		}
	}
}

void handlecontrolC(int XYZ)
{
	shmctl(shmgetid, IPC_RMID, NULL);
	shmdt(shmatpt);
	printf("GOODBYE!\n");
	exit(0);
}


