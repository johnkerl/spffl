for n in `jot 1 1000`
do
	#r=`spiff f2prandom $n`
	r=`spiff f2pop 2 ^ $n - 1`
	if [ "`spiff z_test_prime $n`" = "PRIME" ]; then
		echo deg=$n $r =
		spiff f2pfactor $r
		echo ""
	fi
done
