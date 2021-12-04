#!/bin/bash

# This script to be run while the executable is run
# It keeps printing leaks report every defined seconds by user

printf "Check leaks every(in seconds): "

read seconds

while true
do
	leaks minishell | grep Process | tail -n 2
	printf "\n\n"
	sleep $seconds
done
