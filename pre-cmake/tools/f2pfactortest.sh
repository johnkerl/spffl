for n in `jot 1 1000`
do
	#r=`spiff f2_p_random $n`
	r=`spiff f2_p_op 2 ^ $n - 1`
	if [ "`spiff z_test_prime $n`" = "PRIME" ]; then
		echo deg=$n $r =
		spiff f2_p_factor $r
		echo ""
	fi
done
