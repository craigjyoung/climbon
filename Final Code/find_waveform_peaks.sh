#!/bin/sh

#
# Usagei: enter input file name and peak find threshold values for X and Y axes 
#


if [ "$#" -ne 4 ]; then
	    echo "Enter Input File Name and X and Y axis peak find threshold"
	    exit
    fi

./waveform_peak_find $1 waveform_peaks_output_x_2.csv waveform_gnuplot_x_2.csv waveform_peaks_output_y_2.csv waveform_gnuplot_y_2.csv waveform_peaks_output_z_2.csv waveform_gnuplot_z_2.csv $2 $3 $4
gnuplot waveform_gnuplot_script
sudo cp waveform_plot.png /var/www/html/graphics/waveform_plot_2.png 
echo "If no error is reported, view the plot image at http://<Beaglebone IP Address>:8080/graphics/waveform_plot.png"

