
# Folders
SRC_DIR := src
BUILD_DIR := build
TARGET_DIR := bin
PREFIX ?= /usr/local
INSTALL_BIN := $(PREFIX)/bin
INSTALL := install

# Flags
CFLAGS := -c $(ACFLAGS)
CXXFLAGS := -g -Wall -std=c++17 -O0 -Wno-unused-variable -I $(SRC_DIR)


all: $(TARGET_DIR)/wallet

$(TARGET_DIR)/wallet: $(BUILD_DIR)/app_wallet.o | $(TARGET_DIR)
	$(CXX) $^ -o $@

$(BUILD_DIR)/app_wallet.o: $(SRC_DIR)/app/wallet.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $(CFLAGS) -o $@ $<

$(BUILD_DIR)/components.o: $(SRC_DIR)/components.cpp $(SRC_DIR)/components.hpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $(CFLAGS) -o $@ $<

$(TARGET_DIR) $(BUILD_DIR):
	mkdir -p $@

install: all
	$(INSTALL) $(TARGET_DIR)/wallet $(INSTALL_BIN)

clean:
	$(RM) -r $(BUILD_DIR)/*.o $(TARGET_DIR)/wallet

.PHONY: all install clean
