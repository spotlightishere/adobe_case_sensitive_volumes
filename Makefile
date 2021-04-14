INSTALLER_PATH=/Volumes/*CS3*/*/Setup.app/Contents/MacOS/Setup

liboverride_volume_sensitivity_check.dylib: src/override_volume_sensitivity_check.c src/authexec.m
	gcc -DDEBUG -ggdb -arch ppc -Wall -framework CoreServices -o liboverride_volume_sensitivity_check.dylib -dynamiclib src/override_volume_sensitivity_check.c

.PHONY: clean run

test:
	@echo $(INSTALLER_PATH)

clean:
	rm -rf ./*.dylib* *~ core

run: liboverride_volume_sensitivity_check.dylib
ifneq ($(shell whoami),root)
	@echo "You are not root. Please rerun this command as root (sudo make run)"
else
	DYLD_INSERT_LIBRARIES=$(shell pwd)/liboverride_volume_sensitivity_check.dylib $(INSTALLER_PATH)
endif
