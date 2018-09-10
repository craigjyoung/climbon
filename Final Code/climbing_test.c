/*
Fast Artificial Neural Network Library (fann)
Copyright (C) 2003-2016 Steffen Nissen (steffen.fann@gmail.com)

This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with this library; if not, write to the Free Software
Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

/*

Main test file for the neural network. Called by climb_on to classify a single set of data that was printed to climbing_test.dat

*/
#include <stdio.h>

#include "fann.h"

int main()
{
	unsigned int i;
	int ret = 0;
	fann_type vars[2];
	fann_type *calc_out;
	struct fann *ann;
	struct fann_train_data *data;
	printf("Fetching trained network.\n");
	ann = fann_create_from_file("climbing_float.net");

	if(!ann)
	{
		printf("Error creating ann --- ABORTING.\n");
		return -1;
	}

	fann_print_connections(ann);
	fann_print_parameters(ann);
#ifdef FIXEDFANN
	data = fann_read_train_from_file("climbing_fixed.data");
#else
	data = fann_read_train_from_file("climbing_test.dat");
#endif

	for(i = 0; i < fann_length_train_data(data); i++)
	{
		fann_reset_MSE(ann);
		calc_out = fann_test(ann, data->input[i], data->output[i]);
#ifdef FIXEDFANN
		printf("Climbing test (%d, %d) -> %d,%d should be %d,%d difference=%f, %f\n",
			   data->input[i][0], data->input[i][1], calc_out[0], calc_out[1], data->output[i][0], data->output[i][1],
			   ((float) fann_abs(calc_out[0] - data->output[i][0]) / fann_get_multiplier(ann)), ((float) fann_abs(calc_out[1] - data->output[i][1]) / fann_get_multiplier(ann)));

		if((float) fann_abs(calc_out[0] - data->output[i][0]) / fann_get_multiplier(ann) > 0.2)
		{
			printf("Test failed\n");
			ret = -1;
		}
#else

		printf("Climbing test (%f, %f) -> %f,%f\n",
			   data->input[i][0], data->input[i][1], calc_out[0], calc_out[1]);
		char *message;
		if (calc_out[0] < 0.5 && calc_out[1] < 0.5) 
			message = "You were smooth and stable. Great job you climbing wizard!";
		else if(calc_out[0] >= 0.5 && calc_out[1] < 0.5) 
			message = "You rushed your move but you were stable on arrival. Slow it down cowboy!";
		else if(calc_out[0] < 0.5  && calc_out[1] >= 0.5) 
			message = "You were smooth but unstable on arrival. Somersault jump!";
		else
			message = "You rushed your move and were unstable on arrival. Grasssssss tastes bad!";
		printf("%s\n",message);	
#endif
	}
	
	printf("Cleaning up.\n");
	fann_destroy_train(data);
	fann_destroy(ann);

	return ret;
}
