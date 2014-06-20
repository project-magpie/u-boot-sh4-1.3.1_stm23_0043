if [ -z $1 ]; then
	dcu_ip="192.168.40.34"
else
	dcu_ip="$1"
fi
sh4-linux-gdb -ex "sh4tp $dcu_ip:sat7111:st40,no_convertor_abort=1,seuc=1" -ex load -exec u-boot
