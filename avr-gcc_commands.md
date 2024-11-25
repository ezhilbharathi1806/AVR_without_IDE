 **AVR GCC commands** commonly used for compiling, linking, and flashing code to an AVR microcontroller. These commands are useful for embedded development with microcontrollers like **ATmega** or **ATtiny** series.

---

### 1. **Compiling C Code to Assembly**

To convert a C file to assembly code (.s):

```bash
avr-gcc -mmcu=<mcu> -S file.c
```

- `-mmcu=<mcu>`: Specifies the target microcontroller (e.g., `atmega328p`).
- `-S`: Generate assembly output instead of object code.
- `file.c`: C source file.

Example:
```bash
avr-gcc -mmcu=atmega328p -S main.c
```

---

### 2. **Compiling C Code to Object File**

To compile a C file into an object file (.o):

```bash
avr-gcc -mmcu=<mcu> -c file.c
```

- `-c`: Compile the source file into an object file, but don't link.
- `file.c`: C source file.

Example:
```bash
avr-gcc -mmcu=atmega328p -c main.c
```

---

### 3. **Linking Object Files to Create an Executable**

To link one or more object files into an executable `.elf` file:

```bash
avr-gcc -mmcu=<mcu> -o output.elf file1.o file2.o
```

- `-o output.elf`: Specify the output file name (in ELF format).
- `file1.o file2.o`: Object files to link.

Example:
```bash
avr-gcc -mmcu=atmega328p -o main.elf main.o uart.o
```

---

### 4. **Compile and Link in One Step**

To compile and link in one step into an executable `.elf` file:

```bash
avr-gcc -mmcu=<mcu> -o output.elf file.c
```

- `file.c`: C source file.
- `output.elf`: Final output executable.

Example:
```bash
avr-gcc -mmcu=atmega328p -o main.elf main.c
```

---

### 5. **Generate a HEX File for Flashing**

After compiling the `.elf` file, convert it to a `.hex` file (Intel Hex format) for flashing to the microcontroller:

```bash
avr-objcopy -O ihex -R .eeprom output.elf output.hex
```

- `-O ihex`: Output in Intel Hex format.
- `-R .eeprom`: Optionally remove EEPROM section.
- `output.elf`: Input ELF file.
- `output.hex`: Output HEX file.

Example:
```bash
avr-objcopy -O ihex -R .eeprom main.elf main.hex
```

---

### 6. **Flashing the HEX File to the Microcontroller**

To upload the HEX file to the microcontroller, use **avrdude** with a programmer (e.g., USBasp, STK500, etc.):

```bash
avrdude -c <programmer> -p <mcu> -U flash:w:output.hex:i
```

- `-c <programmer>`: Specify the programmer type (e.g., `usbasp`, `usbtiny`).
- `-p <mcu>`: Specify the target microcontroller (e.g., `m328p` for ATmega328P).
- `-U flash:w:output.hex:i`: Write the HEX file to flash memory.

Example:
```bash
avrdude -c usbasp -p m328p -U flash:w:main.hex:i
```

---

### 7. **Common AVR GCC Compiler Flags**

Here are some common flags you might use with AVR GCC:

- `-mmcu=<mcu>`: Set the target microcontroller. This is required for every command. Example: `-mmcu=atmega328p`.
- `-c`: Compile only (do not link).
- `-Wall`: Enable all warnings during compilation.
- `-g`: Generate debugging information.
- `-Os`: Optimize for size (useful for small embedded systems).
- `-D<macro>`: Define a macro for conditional compilation (e.g., `-DDEBUG`).
- `-I<dir>`: Add directory to the list of directories to search for header files.
- `-L<dir>`: Add directory to the list of directories to search for libraries.
- `-std=c99`: Use C99 standard.
- `-funsigned-char`: Treat `char` as unsigned by default (useful for AVR).

Example:
```bash
avr-gcc -mmcu=atmega328p -Wall -Os -g -DDEBUG=1 -o main.elf main.c
```

---

### 8. **Debugging and Optimization**

For debugging with `gdb`, you can use the `-g` flag to include debugging information:

```bash
avr-gcc -mmcu=atmega328p -g -o main.elf main.c
```

For optimizations:
- `-Os`: Optimize for size (important for constrained environments).
- `-O2`: Optimize for speed (general-purpose optimization).
- `-O3`: Maximum optimization (may increase code size).

Example:
```bash
avr-gcc -mmcu=atmega328p -Os -g -o main.elf main.c
```

---

### 9. **Clean Build Example**

If you have multiple object files, you may want to clean and rebuild everything:

```bash
rm *.o main.elf main.hex
avr-gcc -mmcu=atmega328p -o main.elf main.c
avr-objcopy -O ihex -R .eeprom main.elf main.hex
avrdude -c usbasp -p m328p -U flash:w:main.hex:i
```

---

### Summary of Common Commands

1. **Compile C file to object file:**
   ```bash
   avr-gcc -mmcu=atmega328p -c file.c
   ```

2. **Link object files to create ELF:**
   ```bash
   avr-gcc -mmcu=atmega328p -o output.elf file1.o file2.o
   ```

3. **Generate HEX file:**
   ```bash
   avr-objcopy -O ihex -R .eeprom output.elf output.hex
   ```

4. **Flash HEX to microcontroller:**
   ```bash
   avrdude -c usbasp -p m328p -U flash:w:output.hex:i
   ```

These are the primary steps in a typical AVR project flow using GCC.
