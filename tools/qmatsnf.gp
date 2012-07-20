foo(n)=
{
	randlim=10;
	A=matrix(n,n);

	\\ temp
	for(i=1,n,
		\\A[i,i]=random(2*randlim)-randlim;
		A[i,i]=(random(2*randlim)-randlim) / (1+random(randlim));
	);

	for(i=1,n,
		for(j=1,n,
			A[i,j]=random(2*randlim)-randlim;
			A[i,j]=(random(2*randlim)-randlim) / (1+random(randlim));
		);
	);

	xIA=-A;
	for(i=1,n,
		xIA[i,i] += x;
	);

	\\printp(A);
	m=matsnf(xIA,2);
	printp(matsnf(xIA,2));
	chp=charpoly(A);
	minp=chp/gcd(chp,chp');
	printp("A = ", A);
	printp("snf0 = ", m[1]);
	printp("minp = ", minp);
	printp("chp  = ", chp);
	printp("det = ", matdet(A));
	printp("tr  = ", trace(A));
}

setrand(extern("date +%s") + extern("date +%N"));
foo(4);
