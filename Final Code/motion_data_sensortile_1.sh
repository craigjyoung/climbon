#!/bin/sh
#
# Enter Device MAC Address and output file name as required
#
# Note 10 second acquisition period
#

gatttool -b <YOUR FIRST BGB MAC ADDRESS> -t random --char-write-req --handle=0x0012 --value=0100 --listen > sensor_data_stream_1.dat  &

sleep 10 

pkill gatttool

