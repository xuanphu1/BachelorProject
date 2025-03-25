# Directories
PRO_DIR := .

DRIVER_DIR := $(PRO_DIR)/Component
OUTPUT_DIR := $(PRO_DIR)/Output
LINKER_DIR := $(PRO_DIR)/main/stm32f103xx_Linker.ld
PROJ_NAME  := STM32_RUN

# Compiler and linker
CC = arm-none-eabi-gcc
OBJCOPY = arm-none-eabi-objcopy
CFLAGS = -mcpu=cortex-m3 -mthumb -Wall -O3 \
         -ffunction-sections -fdata-sections -fstack-usage --specs=nano.specs
LDFLAGS = -T $(LINKER_DIR) -nostartfiles -lc -lgcc -lnosys \
          -Wl,--gc-sections -Wl,-Map=$(OUTPUT_DIR)/firmware.map,--cref
# Create output directory if it doesn't exist
$(shell mkdir -p $(OUTPUT_DIR))

# Find all subdirectories in Component for include paths
SUB_DIRS := $(wildcard $(DRIVER_DIR)/*)
INCLUDE_DIRS := $(foreach dir, $(SUB_DIRS), -I$(dir))
CFLAGS += $(INCLUDE_DIRS)

# Get all .c files from main directory and subdirectories
SRCS := $(wildcard $(PRO_DIR)/*/*.c) $(wildcard $(DRIVER_DIR)/*/*.c)
# Convert .c file paths to .o files in Output directory
OBJS := $(patsubst $(PRO_DIR)/%.c, $(OUTPUT_DIR)/%.o, $(SRCS))

# Define output files
TARGET_ELF := $(OUTPUT_DIR)/${PROJ_NAME}.elf
TARGET_HEX := $(OUTPUT_DIR)/${PROJ_NAME}.hex

# Default rule: build everything
all: $(TARGET_HEX)

# Single rule to compile source files into object files
$(OUTPUT_DIR)/%.o: $(PRO_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

# Link object files into an ELF file
$(TARGET_ELF): $(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) $(OBJS) -o $@

# Convert ELF file to HEX format
$(TARGET_HEX): $(TARGET_ELF)
	$(OBJCOPY) -O ihex $< $@

.PHONY: run
run:
	$(PRO_DIR)/debug/ST-LINKUtility/ST-LINK_CLI.exe -ME
	$(PRO_DIR)/debug/ST-LINKUtility/ST-LINK_CLI.exe -p "$(OUTPUT_DIR)/$(PROJ_NAME).hex" 0x08000000
	# Đọc dữ liệu từ RAM (không dùng grep để xem toàn bộ log)
	$(PRO_DIR)/debug/ST-LINKUtility/ST-LINK_CLI.exe -r32 0x20000000 4 | tee $(OUTPUT_DIR)/debug.log


# Clean all generated files
clean:
	rm -rf $(OUTPUT_DIR)

.PHONY: all clean