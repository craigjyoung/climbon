/*


Acquire_data.c: Disconnects both STs from the BGB, then proceeds to collect data and then stores it in the data directory


*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

enum {
    OBSERVE1,
	EXIT,
} state;

int TestCount = 0;

int main(int argc, char* argv[]) {
	if (argc < 2) {
		printf("Please enter the number of iterations to run as an argument\n");
		exit(-1);
	}
	
	int iterationCount = atoi(argv[1]);
	state = OBSERVE1;
	while(1) {
		switch(state) {
			case(OBSERVE1):
				printf("Press Enter when the climber is ready...\n");
				char str = 0;
				while (str != '\n' && str != '\r') {
					str = getchar();
				}
				TestCount += 1;
				printf("Thank you for your input! Collecting data in 3 seconds...\n");
			
				system("./disconnect.sh");
			system("./Dual_SensorTile_Acquire.sh -t 3");
				sleep(15);		
				system("./check_file.sh");
				printf("Finished data acquisition for Test number %d!\n", TestCount);
				if (TestCount < iterationCount) {
					state = OBSERVE1;
				}
				else
					state = EXIT; 
				break;
			case(EXIT):
				return 0;
			default:
				break;
		}
	}			
}
