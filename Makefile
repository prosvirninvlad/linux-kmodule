obj-m += kmodule.o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(shell pwd) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(shell pwd) clean

clear:
	rm -rf .*.*o* *.*o* *.symvers *.tmp*
