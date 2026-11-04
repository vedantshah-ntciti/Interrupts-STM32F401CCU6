
CC      = arm-none-eabi-gcc
OBJCOPY = arm-none-eabi-objcopy
SIZE    = arm-none-eabi-size

BUILD = build
TARGET = $(BUILD)/blink

CFLAGS = -mcpu=cortex-m4 -mthumb \
         -Os -g \
         -ffreestanding -fno-builtin \
         -ffunction-sections -fdata-sections \
         -Wall -Wextra \
         -DSTM32F401xC

LDFLAGS = -T linker.ld \
          -nostdlib \
          -Wl,--gc-sections \
          -Wl,--build-id=none \
          -Wl,-Map=$(TARGET).map

OBJECTS = $(BUILD)/main.o $(BUILD)/startup.o

all: $(TARGET).bin

$(BUILD):
	mkdir -p $(BUILD)

$(BUILD)/main.o: main.c | $(BUILD)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD)/startup.o: startup.S | $(BUILD)
	$(CC) $(CFLAGS) -c $< -o $@

$(TARGET).elf: $(OBJECTS) linker.ld
	$(CC) $(CFLAGS) $(LDFLAGS) $(OBJECTS) -lgcc -o $@
	$(SIZE) $@

$(TARGET).bin: $(TARGET).elf
	$(OBJCOPY) -O binary $< $@

clean:
	rm -rf $(BUILD)

.PHONY: all clean

