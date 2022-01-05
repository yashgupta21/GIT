#!/bin/bash

while true
	do
		echo "The msg from server:  $var"
		echo "Enter msg to server: "
		read  var1
		export var1
		./demo.sh
	done

