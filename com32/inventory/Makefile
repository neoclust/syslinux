## -----------------------------------------------------------------------
##
##   Copyright 2001-2008 H. Peter Anvin - All Rights Reserved
##   Copyright 2009 Intel Corporation; author: H. Peter Anvin
##
##   This program is free software; you can redistribute it and/or modify
##   it under the terms of the GNU General Public License as published by
##   the Free Software Foundation, Inc., 51 Franklin St, Fifth Floor,
##   Boston MA 02110-1301, USA; either version 2 of the License, or
##   (at your option) any later version; incorporated herein by reference.
##
## -----------------------------------------------------------------------

##
## registerinventory
##

VPATH = $(SRC)
include $(MAKEDIR)/elf.mk

LIBS      = $(objdir)/com32/libupload/libcom32upload.a
C_LIBS    += $(objdir)/com32/cmenu/libmenu/libmenu.c32
CFLAGS    += -I$(com32)/cmenu/libmenu -I$(com32) -I$(topdir)/core/lwip/src/include/ -I$(topdir)/core/lwip/src/include/ipv4

MODULES	  = inventory.c32
TESTFILES =

OBJS	  = $(subst $(SRC)/,,$(patsubst %.c,%.o,$(sort $(wildcard $(SRC)/*.c))))
VERSION   = $(shell $(SED) -n 's/\#define VERSION \"\(.*\)\"/\1/p' inventory.h)
CODENAME  = $(shell $(SED) -n 's/\#define CODENAME \"\(.*\)\"/\1/p' inventory.h)
NODASH_VERSION = $(shell echo $(VERSION) | $(SED) -e 's/-/_/g' | $(SED) -e 's/\./_/g')
SUM_FILE  = inventory-$(VERSION).checksums

MEMTEST_URL = http://memtest.org/download/4.20/memtest86+-4.20.bin
MEMTEST     = memtest.bin

KERNEL_VERSION          ?= $(shell uname -r)
MODULES_ALIAS_FILE      ?= /lib/modules/$(KERNEL_VERSION)/modules.alias
GZ_MODULES_ALIAS_FILE   ?= modules.alias.gz
MODULES_PCIMAP_FILE     ?= /lib/modules/$(KERNEL_VERSION)/modules.pcimap
GZ_MODULES_PCIMAP_FILE  ?= modules.pcimap.gz
ISO_DIR                 ?= iso
ISOLINUX_DIR            ?= isolinux
FLOPPY_DIR		?= floppy
PCI_IDS_FILE            ?= $(PWD)/$(FLOPPY_DIR)/pci.ids
GZ_PCI_IDS_FILE         ?= $(PCI_IDS_FILE).gz
MENU_COM32              ?= $(com32)/menu/menu.c32
CHAIN_COM32             ?= $(com32)/chain/chain.c32
ART_DIR                 ?= art/
QEMU			?= qemu-kvm

all: $(MODULES) $(TESTFILES) echo

inventory.elf : $(OBJS) $(LIBS) $(C_LIBS)
	$(LD)  $(LDFLAGS) -o $@ $^

echo:
	@echo "INFORMATION VARIABLE"
	@echo "******************************"
	@echo $(OBJS) $(LIBS) $(C_LIBS)
	@echo "******************************"
	@echo $(LD) $(LDFLAGS) -o $@ $^
	@echo "******************************"
	

tidy dist:
	rm -f *.o *.lo *.a *.lst *.elf .*.d *.tmp

clean: tidy
	rm -f *.lnx

spotless: clean
	rm -f *.lss *.c32 *.com inventory*.img inventory*.iso inventory*.img.gz
	
	
	rm -rf inventory-*checksums
	rm -f *~ \#*

install:

-include .*.d
