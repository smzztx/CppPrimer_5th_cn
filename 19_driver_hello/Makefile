#!/bin/bash

obj-m += driver_hello_module.o
# KDIR := /usr/src/linux-headers-4.4.0-119-generic
KDIR := /lib/modules/`uname -r`/build
# KDIR := /usr/src/linux-headers-`uname -r`
PWD ?= $(shell pwd)
all:
	make -C $(KDIR) M=$(PWD) modules
clean:
	rm -rf *.o

