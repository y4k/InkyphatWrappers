CC=g++ -std=c++11 
DEBUG=-O2
CXXFLAGS=-Wall $(DEBUG)

Q ?=@ # Helper to make commands silent

# Linking and specific compile flags
LINK_WIRING_PI=-lwiringPi
LINK_ASIO=-DASIO_STANDALONE -lpthread
SHARED_LIB_FLAGS=-fPIC -shared

OUT_DIR=bin
TEST_DIR=test

#Install instructions
DEST_DIR=/usr
PREFIX=/local
LDCONFIG=ldconfig

# Utilities
UTILITIES_DIR=utilities
UTILITIES_HEADERS=$(UTILITIES_DIR)/*.hpp

# Inkyphat
INKY_DIR=inkyphat
INKY_LIB_NAME=libinkyphat.so
INKY_HEADERS=$(INKY_DIR)/*.hpp

# Blinkt
BLINKT_DIR=blinkt
BLINKT_LIB_NAME=libblinkt.so
BLINKT_HEADERS=$(BLINKT_DIR)/*.hpp

# JoyBonnet
JOY_BONNET_DIR=joy_bonnet
JOY_BONNET_LIB_NAME=libjoybonnet.so
JOY_BONNET_HEADERS=$(JOY_BONNET_DIR)/*.hpp

OBJECTS = $(SOURCES:.cpp=.o)

.PHONY: install-all
install-all: install-inkyphat install-blinkt install-joybonnet

# Inkyphat
$(INKY_LIB_NAME): $(INKY_DIR)/*cpp $(INKY_HEADERS)
	$Q $(CC) $(CXXFLAGS) $(SHARED_LIB_FLAGS) -o $@ $^

.PHONY: install-inkyphat
install-inkyphat: $(INKY_LIB_NAME)
	$Q echo "[Installing Inkyphat headers]"
	$Q install -m 0755 -d                                   $(DEST_DIR)$(PREFIX)/include #Creates the directory if it doesn't exist
	$Q install -m 0644 $(INKY_HEADERS)                 $(DEST_DIR)$(PREFIX)/include #Installs the headers in the new folder
	$Q echo "[Installing Inkyphat shared library]"
	$Q install -m 0755 -d                                   $(DEST_DIR)$(PREFIX)/lib #Creates the directory if it doesn't exist
	$Q install -m 0755 $(INKY_LIB_NAME)                     $(DEST_DIR)$(PREFIX)/lib/$(INKY_LIB_NAME) #Installs the library in the appropriate folder
	$Q $(LDCONFIG)

.PHONY: uninstall-inkyphat
uninstall-inkyphat:
	$Q echo "[Uninstalling Inkyphat]"
	$Q cd $(DEST_DIR)$(PREFIX)/include/ && $(RM) $(notdir $(INKY_HEADERS))
	$Q cd $(DEST_DIR)$(PREFIX)/lib/ && $(RM) $(INKY_LIB_NAME)
	$Q $(LDCONFIG)

# Blinkt
$(BLINKT_LIB_NAME): $(BLINKT_DIR)/*cpp $(BLINKT_HEADERS)
	$Q $(CC) $(CXXFLAGS) $(SHARED_LIB_FLAGS) -o $@ $^

.PHONY: install-blinkt
install-blinkt: $(BLINKT_LIB_NAME)
	$Q echo "[Installing Blinkt headers]"
	$Q install -m 0755 -d                                   $(DEST_DIR)$(PREFIX)/include #Creates the directory if it doesn't exist
	$Q install -m 0644 $(BLINKT_HEADERS)      $(DEST_DIR)$(PREFIX)/include #Installs the headers in the new folder
	$Q echo "[Installing Blinkt shared library]"
	$Q install -m 0755 -d                                   $(DEST_DIR)$(PREFIX)/lib #Creates the directory if it doesn't exist
	$Q install -m 0755 $(BLINKT_LIB_NAME)                   $(DEST_DIR)$(PREFIX)/lib/$(BLINKT_LIB_NAME) #Installs the library in the appropriate folder
	$Q $(LDCONFIG)

.PHONY: uninstall-blinkt
uninstall-blinkt:
	$Q echo "[Uninstalling Blinkt]"
	$Q cd $(DEST_DIR)$(PREFIX)/include/ && $(RM) $(notdir $(BLINKT_HEADERS))
	$Q cd $(DEST_DIR)$(PREFIX)/lib/ && $(RM) $(BLINKT_LIB_NAME)
	$Q $(LDCONFIG)

$(JOY_BONNET_LIB_NAME): $(JOY_BONNET_DIR)/*cpp $(JOY_BONNET_HEADERS)
	$Q $(CC) $(CXXFLAGS) $(SHARED_LIB_FLAGS) $(LINK_ASIO) -o $@ $^

# JoyBonnet
.PHONY: install-joybonnet
install-joybonnet: $(JOY_BONNET_LIB_NAME)
	$Q echo "[Installing JoyBonnet headers]"
	$Q install -m 0755 -d                                   $(DEST_DIR)$(PREFIX)/include #Creates the directory if it doesn't exist
	$Q install -m 0644 $(JOY_BONNET_HEADERS)  		    	$(DEST_DIR)$(PREFIX)/include #Installs the headers in the new folder
	$Q echo "[Installing JoyBonnet shared library]"
	$Q install -m 0755 -d                                   $(DEST_DIR)$(PREFIX)/lib #Creates the directory if it doesn't exist
	$Q install -m 0755 $(JOY_BONNET_LIB_NAME)               $(DEST_DIR)$(PREFIX)/lib/$(JOY_BONNET_LIB_NAME) #Installs the library in the appropriate folder
	$Q $(LDCONFIG)

.PHONY: uninstall-joybonnet
uninstall-joybonnet:
	$Q echo "[Uninstalling JoyBonnet]"
	$Q cd $(DEST_DIR)$(PREFIX)/include/ && $(RM) $(notdir $(JOY_BONNET_HEADERS))
	$Q cd $(DEST_DIR)$(PREFIX)/lib/ && $(RM) $(JOY_BONNET_LIB_NAME)
	$Q $(LDCONFIG)

# Skywriter

# Utilities
.PHONY: clean
clean:
	$Q echo "[Cleaning. Removing *.so and *.o along with the output directory]"
	$Q $(RM) -r $(OUT_DIR)
	$Q $(RM) *.so
	$Q $(RM) *.o