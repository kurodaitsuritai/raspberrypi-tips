#!/bin/sh
echo Start auto_launch
sleep 5
while true
do
	if ping -c 1 google.com > /dev/null; then
		echo "connected network"
		break
	else
		echo "retry"
		sleep 2
	fi	
	sleep 1
done
sleep 2
echo "インターネットに接続しました"
