#export m=11b
export m=104c11db7

f2ipmmatrand $m 20 20 > x
d=`f2ipmmatdet $m < x`
f2ipmmatinv $m < x > xi
di=`f2ipmmatdet $m < xi`

ddi=`f2ipmmul $m $d $di`

echo $d $di $ddi
