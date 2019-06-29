#!/bin/bash

while true;
do
	ps aux|grep ZHY630YUYANG >> log.log; 
#	echo `ps aux|grep SQWORK`;
	echo `date +%Y%m%d%H%M%S` >> log.log;
	sleep 5;
done;
