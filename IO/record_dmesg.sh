#!/bin/bash

while true; do
    sudo dmesg --since now | tail -n +2 >> dmesg_output.log | grep IOtest
    sleep 1
done