#!/bin/bash

#puts recently created data files into folder according to loop bounds

ftype='.csv'
for i in {100..200}
do
	file="climbing_data_1_$i"
	file=$file$ftype
	file2="climbing_data_2_$i"
	file2=$file2$ftype
	if [ ! -f "data/$file" ]; then
		cp motion_data_output_1.csv data/$file
		mv motion_data_output_1.csv data/climbing_data_1_69.csv
		cp motion_data_output_2.csv data/$file2
		mv motion_data_output_2.csv data/climbing_data_2_69.csv
		break
	fi
done
		
