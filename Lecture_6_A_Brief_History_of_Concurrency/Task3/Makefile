# Compiles the sketch for the ESP32-C3 into build/, where wokwi.toml expects the firmware.
#   make         compile
#   make clear   remove build/
ARDUINO_CLI := $(shell command -v arduino-cli || echo $(HOME)/.local/bin/arduino-cli)
FQBN := esp32:esp32:esp32c3
SKETCH := $(notdir $(CURDIR)).ino
BUILD_DIR := build
FIRMWARE := $(BUILD_DIR)/$(SKETCH).merged.bin

.PHONY: make clear

make: $(FIRMWARE)

$(FIRMWARE): $(SKETCH) $(wildcard *.cpp *.h)
	$(ARDUINO_CLI) compile --fqbn $(FQBN) --output-dir $(BUILD_DIR) .

clear:
	rm -rf $(BUILD_DIR)
