/*


climb_on.c: End user program to test a single move with the neural network. Takes the hand number as an argument


*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
	if (argc != 2) {
		printf("Please include the hand number when calling this test program. This is the hand executing the move.\n");
		exit(-1);
	}

	printf("Welcome to Climb On! The sophisitcated climbing classification system.\nHave your climber ready to go! Please press Enter to continue.\n");
	
	char str = 0;
	while (str != '\n' && str != '\r') {
		str = getchar();
	}
	char processBuff[1024];
	
	system("./acquire_data 1");
	printf("Beginning Data Processing. Classification soon to follow...");
	
    sprintf(processBuff, "./process_data 69 %s",argv[1]); 
	system(processBuff);

	printf("Attempting to read testing file\n");
	FILE * test_file;

        if (( test_file = fopen( "climbing_test.dat", "r")) == NULL)
        {   
    	    printf("Testing file could not be opened\n");
            exit(-1);
        }
	int counter = 0;
	float timing;
	float shaking;

	char line[1024];
	char num[1024];
	int i = 0;
	int j = 0;

	//read test file data

    while(fscanf(test_file, "%[^\n]%*c", &line) != -1) 
        {
	    while(line[i] != 0) 
        {
			if(line[i] == ' ' || line[i] == '\n') 
            {	
		    	switch(counter) 
                {
					case 0:
						timing = atof(num);
						break;
					case 1:
						shaking = atof(num);
						break;
		    	}	
		    	counter++;
		    	for (j = 0; j != 1024; j++) 
                {
		        	num[j] = 0;
		    	}
		    	j = 0;
			}	
			else 
			{
		    	num[j] = line[i];
				j++;
			}
			i++;
	    }
	}

    fclose(test_file);
   	printf("Timing: %f Shaking: %f\n", timing, shaking);
    printf("Finished reading test file line\n");
    printf("Reading normalization file\n");
    if (( test_file = fopen( "normalization_values.dat", "r")) == NULL)
    {   
    	printf("Normalization values could not be read. Make sure your neural network is trained\n");
        exit(-1);
    }

	counter = 0;
	char line1[1024];
	char num1[1024];
	i = 0;
	j = 0;
	float minTiming;
	float maxTiming;
	float minShaking;
	float maxShaking;

	//read normalization values from training program

    while(fscanf(test_file, "%[^\n]%*c", &line1) != -1) {
		while(line1[i] != 0) 
		{
			if(line1[i] == ' ') 
			{
				switch(counter) 
				{
					case 0:
						minTiming = atof(num1);
					case 1:
						maxTiming = atof(num1);
					case 2:
						minShaking = atof(num1);
					case 3:
						maxShaking = atof(num1);
				}
				counter++;
				for (j = 0; j != 1024; j++) {
					num1[j] = 0;
				}
				j = 0;
			}
			else
			{
				num1[j] = line1[i];
				j++;
			}
			i++;
		}
	}
	fclose(test_file);

	timing = (timing - minTiming)/(maxTiming - minTiming);
	shaking = (shaking - minShaking)/(maxShaking - minShaking);
    if (( test_file = fopen( "climbing_test.dat", "w")) == NULL)
    {   
    	printf("Testing file could not be written to");
        exit(-1);
    }

	//create test file with dummy output values

	fprintf(test_file, "1 2 2\n%f %f\n0 0\n", timing, shaking);
	fclose(test_file);

    printf("Finished normalizing test values\n");
    printf("Attempting to test neural net\n");
    system("./climbing_test");

}
