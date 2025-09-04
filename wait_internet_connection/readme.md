# 起動後、インターネット接続が確立されるまで待機する

```sh wait_internet_connection.sh
#!/bin/sh
echo "waiting internet connection..."
sleep 5
while true
do
	if ping -c 1 google.com > /dev/null; then
		echo "connected"
		break
	else
		echo "retry"
		sleep 2
	fi	
	sleep 1
done
sleep 2
echo "completed"
```