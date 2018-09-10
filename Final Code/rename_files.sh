#!/bin/bash

#rename files after peak find has been called, before calling it again

cp waveform_gnuplot_x_2.csv waveform_gnuplot_x_1.csv
cp waveform_gnuplot_y_2.csv waveform_gnuplot_y_1.csv
cp waveform_gnuplot_z_2.csv waveform_gnuplot_z_1.csv
cp waveform_peaks_output_x_2.csv waveform_peaks_output_x_1.csv
cp waveform_peaks_output_y_2.csv waveform_peaks_output_y_1.csv
cp waveform_peaks_output_z_2.csv waveform_peaks_output_z_1.csv
cp /var/www/html/graphics/waveform_plot_2.png /var/www/html/graphics/waveform_plot_1.png

