To compile and build AVR projects using **AVR-GCC**, we can create a modular `Makefile` that works for projects organized with `src`, `inc`, and `build` folders. Here’s a complete guide:

---

### **1. Project Structure**

Ensure your project is organized as follows:
```
project/
├── src/         # Source files (*.c)
│   ├── main.c
│   └── other_module.c
├── inc/         # Header files (*.h)
│   ├── main.h
│   └── other_module.h
├── build/       # Compiled files (*.elf, *.hex, etc.)
├── Makefile     # Makefile to build the project
```

---

### **2. AVR-GCC Commands for Compilation**

To compile manually, you would:
1. Include `src/*.c` for source files and `inc/` for header files:
   ```bash
   avr-gcc -mmcu=atmega16 -Iinc -Os -c src/main.c -o build/main.o
   avr-gcc -mmcu=atmega16 -Iinc -Os -c src/other_module.c -o build/other_module.o
   ```
2. Link object files to generate the final ELF and HEX:
   ```bash
   avr-gcc -mmcu=atmega16 -o build/main.elf build/main.o build/other_module.o
   avr-objcopy -O ihex -R .eeprom build/main.elf build/main.hex
   ```

These commands can be automated using a `Makefile`.

---

### **3. Makefile**

Here’s a modular `Makefile` for the project:

```makefile
# Project configuration
TARGET       = main                # Target name (without extension)
MCU          = atmega16            # Microcontroller type
F_CPU        = 16000000UL          # Clock frequency
SRC_DIR      = src                 # Source files directory
INC_DIR      = inc                 # Include files directory
BUILD_DIR    = build               # Build files directory

# Compiler settings
CC           = avr-gcc
OBJCOPY      = avr-objcopy
CFLAGS       = -mmcu=$(MCU) -DF_CPU=$(F_CPU) -Os -I$(INC_DIR)

# Source and object files
SRCS         = $(wildcard $(SRC_DIR)/*.c)
OBJS         = $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRCS))

# Build targets
all: $(BUILD_DIR)/$(TARGET).hex

# Compile source files to object files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Link object files to create ELF file
$(BUILD_DIR)/$(TARGET).elf: $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

# Convert ELF file to HEX file
$(BUILD_DIR)/$(TARGET).hex: $(BUILD_DIR)/$(TARGET).elf
	$(OBJCOPY) -O ihex -R .eeprom $< $@

# Clean up build files
clean:
	rm -rf $(BUILD_DIR)

# Print file structure (optional helper)
print:
	@echo "Sources: $(SRCS)"
	@echo "Objects: $(OBJS)"

# Phony targets
.PHONY: all clean print
```

---

### **4. Usage**

1. **Build the Project**:
   Run the following command to build the project:
   ```bash
   make
   ```

2. **Clean Build Files**:
   To clean the build directory, run:
   ```bash
   make clean
   ```

3. **Debug or Verify Configuration**:
   Use the `print` target to check source and object files:
   ```bash
   make print
   ```

4. **Upload the Code**:
   Use `avrdude` to upload the generated `main.hex`:
   ```bash
   avrdude -c usbasp -p m16 -U flash:w:build/main.hex
   ```

---

### **5. Notes**
- The `F_CPU` macro defines the clock frequency for the microcontroller, which is often required by delay functions like `_delay_ms()` in `<util/delay.h>`.
- The `BUILD_DIR` is created dynamically if it doesn't exist.
- Add additional `src/*.c` files to `src` and `inc/*.h` to `inc` without modifying the Makefile.

This `Makefile` is modular, reusable, and scalable for AVR projects.
