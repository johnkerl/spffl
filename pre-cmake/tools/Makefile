top: build regression

build:
	make -f libspffl.so.mk
	make -f libspfflf.so.mk
#	make -f libspffl.a.mk
#	make -f libspfflf.a.mk
	make -f spiff.mk
	make -f spiffsf.mk
	make -f f2pmchart.mk
	sh mkinc

big:
	make -f libspffl.so.mk
#	make -f libspffl.a.mk
	make -f spiff.mk
	sh mkinc

small:
	make -f libspfflf.so.mk
#	make -f libspfflf.a.mk
	make -f spiffsf.mk
	sh mkinc

quick:
	make -f libspffl.so.mk
	make -f spiff.mk

regression:
	@echo ""
	cd ../regression && sh -x regress.sh

mk:
	yamm libspffl.so.mki
	yamm libspfflf.so.mki
#	yamm libspffl.a.mki
#	yamm libspfflf.a.mki
	yamm spiff.mki
	yamm spiffsf.mki
	yamm f2pmchart.mki

tags:
	#pushd .. && /usr/bin/ctags -R `pwd` && popd
	cd .. && /usr/bin/ctags -R `pwd` && cd tools

clean:
	make -f libspffl.so.mk clean
	make -f libspfflf.so.mk clean
#	make -f libspffl.a.mk clean
#	make -f libspfflf.a.mk clean
	make -f spiff.mk clean
	make -f spiffsf.mk clean
	make -f f2pmchart.mk clean
