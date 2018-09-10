/*

	mass_process.h

	a file to call process_data.c on many sets of data 



*/




#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <unistd.h>
#include <string.h>



int main( int argc, char* argv[] )
{
	if( argc != 4 )
	{	
		printf("Prog takes parameters startTrialNum, endTrialNum\n");
		exit(-1);
	}
	int end = atoi(argv[2]);
	int i = atoi(argv[1]);

	for(; i<= end; i++)
	{	
		char cmd[100];
		sprintf(cmd, "./process_data %d %s",i,argv[3]);
		system(cmd);
		
	}

}
