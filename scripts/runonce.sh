#!/bin/bash

# runonce.bash
# initial configuration script

# install necesary kernal objects
insmod /lib/modules/2.6.24.4/kernel/lib/crc16.ko
insmod /lib/modules/2.6.24.4/kernel/net/ax25/ax25.ko
insmod /lib/modules/2.6.24.4/kernel/drivers/net/hamradio/mkiss.ko

# run xuartctl to set up psudeo-terminal
xuartctl --server --speed=4800 --port=0 2> /tmp/Error
xout=$(</tmp/Error)
tty=${xout:8}

# kissattach to bind IP to axport
kissattach $tty sbc-ax 50



