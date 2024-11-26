# Compiler and tools
CC        = avr-gcc
OBJCOPY   = avr-objcopy
AVRDUDE   = avrdude

# Microcontroller settings
MCU       = atmega328p
F_CPU     = 16000000  # Adjust based on the clock speed
BAUD      = 9600      # Serial baud rate (if applicable)

# File and directory locations
SRC_DIR   = src
INC_DIR   = inc
BUILD_DIR = build

# Source and object files
SRCS      = $(wildcard $(SRC_DIR)/*.c)
OBJS      = $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRCS))

# Output file name (the hex file to be generated)
OUTPUT    = $(BUILD_DIR)/firmware.hex

# Compiler flags
CFLAGS    = -Wall -std=c99 -g -Os -mmcu=$(MCU) -DF_CPU=$(F_CPU) -I$(INC_DIR)
LDFLAGS   = -mmcu=$(MCU)

# Default target (build the firmware)
all: $(OUTPUT)

# Rule to build the firmware .hex file
$(OUTPUT): $(OBJS)
	@echo "Linking..."
	$(CC) $(LDFLAGS) $(OBJS) -o $(BUILD_DIR)/firmware.elf
	$(OBJCOPY) -O ihex $(BUILD_DIR)/firmware.elf $(OUTPUT)

# Rule to build object files from source files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@echo "Compiling $<..."
	$(CC) $(CFLAGS) -c $< -o $@

# Clean build artifacts
clean:
	@echo "Cleaning up..."
	rm -rf $(BUILD_DIR)/*

# Flash the firmware to the microcontroller using avrdude
flash: $(OUTPUT)
	@echo "Flashing firmware to $(MCU)..."
	$(AVRDUDE) -c usbasp -p $(MCU) -U flash:w:$(OUTPUT):i

# Target to create the build directory if it doesn't exist
$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)

print:
	echo "Source: $(SRCS)"
	echo "Object: $(OBJS)"

.PHONY: all clean flash
