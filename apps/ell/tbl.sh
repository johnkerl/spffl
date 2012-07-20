p=5
abc=0,0,1
if [ $# -eq 2 ]; then
	p=$1
	abc=$2
fi

pts="`fpellpts $p $abc`"

for u in $pts
do
	for v in $pts
	do
		echo -n " " `fpelladd $p $abc $u $v`
	done
	echo ""
done
