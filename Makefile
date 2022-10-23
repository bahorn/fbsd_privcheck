
.PHONY: ./module/privcheck.ko ./tool/privcheck

build: ./module/privcheck.ko ./tool/privcheck

load: build
	sudo kldload ./module/privcheck.ko

unload: build
	sudo kldunload ./module/privcheck.ko

./module/privcheck.ko:
	make -C ./module

./tool/privcheck:
	make -C ./tool
