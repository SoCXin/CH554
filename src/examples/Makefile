# SUBDIRS = $(shell ls -d */)
SUBDIRS = $(shell ls -l | grep ^d | awk '{if($$9 != "build") if($$9 != "include") print $$9}')

.PHONY: $(SUBDIRS)


$(SUBDIRS):
	$(MAKE) -C $@

.DEFAULT_GOAL := all
all: $(SUBDIRS)


print-%  : ; @echo $* = $($*)
