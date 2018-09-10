#!/bin/bash

#disconnects both STs from BGB before attempting to acquire data

address1=C0:83:25:31:4A:48
address2=C0:83:25:31:28:48
bluetoothctl << eof
disconnect $address1
disconnect $address2
exit
eof
