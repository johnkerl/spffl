#!/bin/sh

mkdir -p data/outact

# ----------------------------------------------------------------
# Integer factorization

spiff ztestprime { zlist 0 100 }       > data/outact/ztestprime-0-100.txt
spiff zfactor    { zlist 0 100 }       > data/outact/zfactor-0-100.txt
spiff zdivisors  { zlist 0 100 }       > data/outact/zdivisors-0-100.txt

spiff ztestprime { zlist 1000000 100 } > data/outact/ztestprime-1000000-100.txt
spiff zfactor    { zlist 1000000 100 } > data/outact/zfactor-1000000-100.txt
spiff zdivisors  { zlist 1000000 100 } > data/outact/zdivisors-1000000-100.txt

# ----------------------------------------------------------------
# Polynomial classification

spiff   f2ptest  -ip { f2plist     0-8 } > data/outact/f2ptest-0-8.txt
spiffsf f2nptest   7 { f2nplist  7 0-4 } > data/outact/f2nptest-0-8.txt
spiff   fpptest    5 { fpplist   5 0-4 } > data/outact/fpptest-0-8.txt
spiff   f2pperiod    { f2plist     0-8 } > data/outact/f2pperiod-0-8.txt

# ----------------------------------------------------------------
# Finite field tables

spiff   f2pmtbl  13        + > data/outact/f2pm-13-add.txt
spiff   f2pmtbl  13        - > data/outact/f2pm-13-sub.txt
spiff   f2pmtbl  13        . > data/outact/f2pm-13-mul.txt
spiff   f2pmtbl  13        / > data/outact/f2pm-13-div.txt

spiffsf f2npmtbl 3 1:0:1:2 + > data/outact/f2npm-3-1012-add.txt
spiffsf f2npmtbl 3 1:0:1:2 - > data/outact/f2npm-3-1012-sub.txt
spiffsf f2npmtbl 3 1:0:1:2 . > data/outact/f2npm-3-1012-mul.txt
spiffsf f2npmtbl 3 1:0:1:2 / > data/outact/f2npm-3-1012-div.txt

spiff   fppmtbl  2 1011    + > data/outact/fppm-2-1011-add.txt
spiff   fppmtbl  2 1011    - > data/outact/fppm-2-1011-sub.txt
spiff   fppmtbl  2 1011    . > data/outact/fppm-2-1011-mul.txt
spiff   fppmtbl  2 1011    / > data/outact/fppm-2-1011-div.txt

spiff   fppmtbl  3 1021    + > data/outact/fppm-3-1021-add.txt
spiff   fppmtbl  3 1021    - > data/outact/fppm-3-1021-sub.txt
spiff   fppmtbl  3 1021    . > data/outact/fppm-3-1021-mul.txt
spiff   fppmtbl  3 1021    / > data/outact/fppm-3-1021-div.txt

# ----------------------------------------------------------------
# Polynomial factorization

spiff f2pfactor   { f2plist 0-5 } > data/outact/f2-smpols-factor.txt
spiff f2pdivisors { f2plist 0-5 } > data/outact/f2-smpols-divisors.txt
spiff f2ptest -ip { f2plist 0-5 } > data/outact/f2-smpols-test.txt
spiff f2pgcd        a f           > data/outact/f2-smpols-gcd.txt
spiff f2plcm        a f           > data/outact/f2-smpols-lcm.txt

spiffsf f2npfactor   b { f2nplist b 0-3 } > data/outact/f2n-smpols-factor.txt
spiffsf f2npdivisors b { f2nplist b 0-3 } > data/outact/f2n-smpols-divisors.txt
spiffsf f2nptest     b { f2nplist b 0-3 } > data/outact/f2n-smpols-test.txt
spiffsf f2npgcd      b   3:4:a 6:7:9      > data/outact/f2n-smpols-gcd.txt
spiffsf f2nplcm      b   3:4:a 6:7:9      > data/outact/f2n-smpols-lcm.txt

spiffsf fppfactor   7 { fpplist 7 0-3 }   > data/outact/fp-smpols-factor.txt
spiffsf fppdivisors 7 { fpplist 7 0-3 }   > data/outact/fp-smpols-divisors.txt
spiffsf fpptest     7 { fpplist 7 0-3 }   > data/outact/fp-smpols-test.txt
spiffsf fppgcd      7   1,3,2,6 2,4,5     > data/outact/fp-smpols-gcd.txt
spiffsf fpplcm      7   1,3,2,6 2,4,5     > data/outact/fp-smpols-lcm.txt


spiff f2pfactor `cat data/input/f2-pols.txt` \
	> data/outact/f2-pols-factor.txt
spiff f2pdivisors `cat data/input/f2-pols.txt` \
	> data/outact/f2-pols-divisors.txt
spiff f2ptest -ip `cat data/input/f2-pols.txt` \
	> data/outact/f2-pols-test.txt
spiff f2pgcd \
	`sed -n 1p data/input/f2-pols.txt` `sed -n 2p data/input/f2-pols.txt` \
	> data/outact/f2-pols-gcd.txt
spiff f2plcm \
	`sed -n 1p data/input/f2-pols.txt` `sed -n 2p data/input/f2-pols.txt` \
	> data/outact/f2-pols-lcm.txt

spiffsf f2npfactor 13 `cat data/input/f2n-pols.txt` \
	> data/outact/f2n-pols-factor.txt
spiffsf f2npdivisors 13 `cat data/input/f2n-pols.txt` \
	> data/outact/f2n-pols-divisors.txt
spiffsf f2nptest 13 `cat data/input/f2n-pols.txt` \
	> data/outact/f2n-pols-test.txt
spiffsf f2npgcd 13 \
	`sed -n 1p data/input/f2n-pols.txt` `sed -n 2p data/input/f2n-pols.txt` \
	> data/outact/f2n-pols-gcd.txt
spiffsf f2nplcm 13 \
	`sed -n 1p data/input/f2n-pols.txt` `sed -n 2p data/input/f2n-pols.txt` \
	> data/outact/f2n-pols-lcm.txt

spiffsf fppfactor 19 `cat data/input/fp-pols.txt` \
	> data/outact/fp-pols-factor.txt
spiffsf fppdivisors 19 `cat data/input/fp-pols.txt` \
	> data/outact/fp-pols-divisors.txt
spiffsf fpptest 19 `cat data/input/fp-pols.txt` \
	> data/outact/fp-pols-test.txt
spiffsf fppgcd 19 \
	`sed -n 1p data/input/fp-pols.txt` `sed -n 2p data/input/fp-pols.txt` \
	> data/outact/fp-pols-gcd.txt
spiffsf fpplcm 19 \
	`sed -n 1p data/input/fp-pols.txt` `sed -n 2p data/input/fp-pols.txt` \
	> data/outact/fp-pols-lcm.txt

# ----------------------------------------------------------------
# Matrix arithmetic

spiff f2matop '[[1 1 0] [0 1 1] [1 1 1]]' . '[[0 1 1] [0 1 0] [1 1 0]]' \
	> data/outact/f2-mat33.txt

spiff f2matop data/input/f2-mat1.txt . data/input/f2-mat2.txt \
	> data/outact/f2-mat-1-1.txt
spiff f2matop data/input/f2-mat3.txt . data/input/f2-mat4.txt \
	> data/outact/f2-mat-3-4.txt
spiff f2matop data/input/f2-mat5.txt . data/input/f2-mat6.txt \
	> data/outact/f2-mat-5-6.txt
spiff f2matop det data/input/f2-mat1.txt > data/outact/f2-mat-det-1.txt

spiff f2pmmatop 13 '[[6 a 9] [1 3 e] [c 7 0]]' . '[[1 f 1] [e b b] [d d 0]]' \
	> data/outact/f2pm-13-mat33.txt

spiffsf f2pmmatop 11b det data/input/f2pm-mat1.txt \
	> data/outact/f2pm-mat-det-1.txt
spiffsf f2pmmatop 11b inv data/input/f2pm-mat1.txt \
	> data/outact/f2pm-mat-inv-1.txt

spiffsf f2npmmatop 43 1:0:0:2 det data/input/f2npm-mat1.txt \
	> data/outact/f2npm-mat-det-1.txt
spiffsf f2npmmatop 43 1:0:0:2 inv data/input/f2npm-mat1.txt \
	> data/outact/f2npm-mat-inv-1.txt

spiff fpmatop 17 det data/input/fp-mat1.txt > data/outact/fp-mat-det-1.txt
spiff fpmatop 17 inv data/input/fp-mat1.txt > data/outact/fp-mat-inv-1.txt

spiff fppmmatop 11 1,0,9 det data/input/fppm-mat1.txt \
	> data/outact/fppm-mat-det-1.txt
spiff fppmmatop 11 1,0,9 inv data/input/fppm-mat1.txt \
	> data/outact/fppm-mat-inv-1.txt

# ----------------------------------------------------------------
diff -r data/outexp data/outact > diffs
rv=$?
if [ $rv -eq 0 ]; then
	echo SPFFL REGRESSION PASSED
else
	echo SPFFL REGRESSION FAILED
fi
exit $rv
