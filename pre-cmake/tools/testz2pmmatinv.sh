#export m=104c11db7
m=3a2d3b2a388706e04da471246607daae525
n=8

f2pmmatrand $m $n $n > x
d=`f2pmmatdet $m < x`
f2pmmatinv $m < x > xi
di=`f2pmmatdet $m < xi`

ddi=`f2pmmul $m $d $di`

echo $d $di $ddi
