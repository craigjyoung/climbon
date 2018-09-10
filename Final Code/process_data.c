/*
    process_peaks.c

    A program to process the motion data. Calls find_waveform_peaks.sh and stores waveforms in <BGB ADDRESS>:8080/graphics.




*/


#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>
#include <string.h>
#include "process_timing.h"
#include "process_shaking.h"

int main(int argc, char *argv[]) {

	if (argc != 3) {
		printf("Needs 3 Arguments. First is set number and second is hand number (1 for left, 2 for right)\n");
		exit(-1);
	}
    char cmd[256];
    sprintf( cmd, "./find_waveform_peaks.sh data/climbing_data_1_%s.csv 150 150 150",argv[1]);
    printf(cmd);
    system( cmd );

    system( "./rename_files.sh" );

    sprintf( cmd, "./find_waveform_peaks.sh data/climbing_data_2_%s.csv 150 150 150",argv[1]);
    system(cmd);
	extractData(argv[2], argv[1]);
	extractShaking(argv[2], argv[1]);
}
