CC=g++ -std=c++11 
INCLUDE=-I.
DEBUG=-O2
CXXFLAGS=-Wall $(INCLUDE)

Q ?=@ # Helper to make commands silent

# Linking and specific compile flags
LINK_WIRING_PI=-lwiringPi
SHARED_LIB_FLAGS=-fPIC -shared

TEST_DIR=test

#Install instructions
DEST_DIR?=/usr
PREFIX?=/local
LDCONFIG=ldconfig

# Inkyphat
INKY_DIR=inkyphat
INKY_LIB_NAME=libinkyphat.so
INKY_HEADERS=$(INKY_DIR)/*.h;

# Blinkt
BLINKT_DIR=blinkt
BLINKT_LIB_NAME=libblinkt.so
BLINKT_HEADERS=$(BLINKT_DIR)/*h;

all: install-inkyphat install-blinkt

# Inkyphat
$(INKY_LIB_NAME): $(INKY_DIR)/*cpp $(INKY_HEADERS)
	$Q $(CC) $(CXXFLAGS) $(LINK_WIRING_PI) $(SHARED_LIB_FLAGS) -o $(INKY_LIB_NAME) $^

.PHONY: install-inkyphat
install-inkyphat: $(INKY_LIB_NAME)
	$Q echo "[Installing Inkyphat headers]"
	$Q install -m 0755 -d					$(DEST_DIR)$(PREFIX)/include #Creates the directory if it doesn't exist
	$Q install -m 0644 $(INKY_DIR)/$(INKY_HEADERS) 		$(DEST_DIR)$(PREFIX)/include #Installs the headers in the new folder
	$Q echo "[Installing Inkyphat shared library]"
	$Q install -m 0755 -d					$(DEST_DIR)$(PREFIX)/lib #Creates the directory if it doesn't exist
	$Q install -m 0755 $(INKY_LIB_NAME) 		$(DEST_DIR)$(PREFIX)/lib/$(INKY_LIB_NAME) #Installs the library in the appropriate folder
	$Q (LDCONFIG)

.PHONY: uninstall-inkyphat
install-inkyphat:
	$Q echo "[Uninstalling Inkyphat]"
	$Q cd $(DEST_DIR)$(PREFIX)/include/ && rm -f $(INKY_HEADERS)
	$Q cd $(DEST_DIR)$(PREFIX)/lib/ && rm -f $(INKY_LIB_NAME)
	$Q $(LDCONFIG)

.PHONY: test-inkyphat
test-inkyphat:
	$Q mkdir -p $(TEST_DIR)
	$Q $(CC) $(CXXFLAGS) $(INKY_DIR)_test/main.cpp $(LINK_WIRING_PI) -linkyphat -o $(TEST_DIR)/inky_test.out

# Blinkt
.PHONY: install-blinkt
install-blinkt: $(BLINKT_LIB_NAME)
	$Q echo "[Installing Blinkt headers]"
	$Q install -m 0755 -d					$(DEST_DIR)$(PREFIX)/include #Creates the directory if it doesn't exist
	$Q install -m 0644 $(BLINKT_DIR)/$(BLINKT_HEADERS) 		$(DEST_DIR)$(PREFIX)/include #Installs the headers in the new folder
	$Q echo "[Installing Blinkt shared library]"
	$Q install -m 0755 -d					$(DEST_DIR)$(PREFIX)/lib #Creates the directory if it doesn't exist
	$Q install -m 0755 $(BLINKT_LIB_NAME) 		$(DEST_DIR)$(PREFIX)/lib/$(BLINKT_LIB_NAME) #Installs the library in the appropriate folder
	$Q (LDCONFIG)

.PHONY: uninstall-blinkt
install-blinkt:
	$Q echo "[Uninstalling Blinkt]"
	$Q cd $(DEST_DIR)$(PREFIX)/include/ && rm -f $(BLINKT_HEADERS)
	$Q cd $(DEST_DIR)$(PREFIX)/lib/ && rm -f $(BLINKT_LIB_NAME)
	$Q $(LDCONFIG)

.PHONY: test-blinkt
test-blinkt:
	$Q mkdir -p $(TEST_DIR)
	$Q $(CC) $(CXXFLAGS) $(BLINKT_DIR)_test/main.cpp $(LINK_WIRING_PI) -lblinkt -o $(TEST_DIR)/blinkt_test.out

.PHONY: clean
clean:
	rm -fr $(OBJ_DIR)
	rm -fr $(TEST_DIR)