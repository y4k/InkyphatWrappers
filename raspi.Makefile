Q ?=@ # Helper to make commands silent

# All subdirectories
SUBDIRS := blinkt
MAKEEXT := Makefile

#Install instructions
DEST_DIR := /usr
PREFIX := /local
LDCONFIG := ldconfig

.PHONY:all
all: $(SUBDIRS)
	$(MAKE) -C $^ -f $(MAKEEXT)

.PHONY:clean-all
clean-all: $(SUBDIRS)
	$(MAKE) -C $^ -f $(MAKEEXT) clean

.PHONY: install-all
install-all: $(SUBDIRS)
	$Q echo "[Installing $(OUTNAME) headers]"
	$Q install -m 0755 -d                           $(DEST_DIR)$(PREFIX)/include #Creates the directory if it doesn't exist
	$Q install -m 0644 $(HEADERS)                   $(DEST_DIR)$(PREFIX)/include #Installs the headers in the new folder
	$Q echo "[Installing $(OUTNAME) shared library]"
	$Q install -m 0755 -d                           $(DEST_DIR)$(PREFIX) #Creates the directory if it doesn't exist
	$Q install -m 0755 $(TARGET)                    $(DEST_DIR)$(PREFIX)/$(TARGET) #Installs the library in the appropriate folder
	$Q $(LDCONFIG)

.PHONY: uninstall
uninstall:
	$Q echo "[Uninstalling $(OUTNAME)]"
	$Q cd $(DEST_DIR)$(PREFIX)/include/ && $(RM) $(notdir $(HEADERS))
	$Q cd $(DEST_DIR)$(PREFIX) && $(RM) $(TARGET)
	$Q $(LDCONFIG)



.PHONY: uninstall-all
uninstall-all: $(SUBDIRS)