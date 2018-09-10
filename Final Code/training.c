/*


Analyze a range of data sets, and create normalization values for future test files to use. 
Argument 1: starting number, Argument 2: ending number, Argument 3: hand number


*/


#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>
#include <string.h>
int main(int argc, char * argv[]) {
	
	if (argc != 4) {
		printf("3 Arguments Needed. Exiting\n");
		exit(-1);
	}

	//remove staging files and start fresh
	system("rm timing_data.dat");
	system("rm shaking_data.dat");

	int start = atof(argv[1]);
	int end = atof(argv[2]);

	//call c function that loops through and processes a certain set of data
	char callBuff[1024];
	snprintf(callBuff, sizeof(callBuff), "./mass_process %d %d %s", start, end, argv[3]);
	system(callBuff);
	

	FILE *fp;
	char buffer[1024];
	float peaks[500];
	float timing[500];
	float shaking[500];
	int peakCount = 0;
	int timingCount = 0;
	int shakingCount = 0;

	if ((fp =
	 fopen("shaking_data.dat", "r")) == NULL) {
		printf
			("Error file, shaking_data.dat, cannot be opened\n");
		exit(-1);
	}

    while(fscanf(fp, "%[^\n]%*c", &buffer) != -1) {
		shaking[shakingCount] = atof(buffer);
		shakingCount++;
	}
	
	fclose(fp);

	if ((fp =
	 fopen("timing_data.dat", "r")) == NULL) {
		printf
			("Error file, shaking_data.dat, cannot be opened\n");
		exit(-1);
	}

    while(fscanf(fp, "%[^\n]%*c", &buffer) != -1) {
		timing[timingCount] = atof(buffer);
		timingCount++;
	}

	int i;
	float maxShaking = 0;
	float minShaking = 1000000;
	float maxTiming = 0;
	float minTiming = 1000;

	for (i = 0; i != shakingCount; i++) {
		if (shaking[i] > maxShaking) {
			maxShaking = shaking[i];
		}
		if (shaking[i] < minShaking) {
			minShaking = shaking[i];
		}
		if (timing[i] > maxTiming) {
			maxTiming = timing[i];
		}
		if (timing[i] < minTiming) {
			minTiming = timing [i];
		}
	}


	if ((fp =
	 fopen("climbing_training_file.dat", "w")) == NULL) {
		printf
			("Error file, climbing_training_file.dat, cannot be opened\n");
		exit(-1);
	}
	
	fprintf(fp, "%d 2 2\n", end-start+1); 
	for (i = 0; i != shakingCount; i++) {
		timing[i] = (timing[i] - minTiming)/(maxTiming - minTiming);
		shaking[i] = (shaking[i] - minShaking)/(maxShaking - minShaking);
		fprintf(fp,"%f %f\n", timing[i], shaking[i]);
	}
	fclose(fp);

	
	if ((fp =
	 fopen("normalization_values.dat", "w")) == NULL) {
		printf
			("Error file, climbing_training_file.dat, cannot be opened\n");
		exit(-1);
	}

	// printf normalization values so that future test files can use it

	fprintf(fp, "%f %f %f %f\n", minTiming, maxTiming, minShaking, maxShaking);
	


}
