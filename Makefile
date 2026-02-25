CC              = gcc
AS              = nasm
LD              = ld

SRC_DIR         = src
BUILD_DIR       = build
INCLUDE_DIR     = $(SRC_DIR)/include

CFLAGS_KERNEL   = -m32 -nostdlib -Wall -O -fstrength-reduce -fomit-frame-pointer \
                  -finline-functions -nostdinc -fno-stack-protector -fno-builtin \
                  -I$(INCLUDE_DIR)
ASFLAGS         = -f elf32
LDFLAGS_KERNEL  = -m elf_i386 -T $(SRC_DIR)/link.ld

KERNEL_NAME     = kernel.bin
ISO_NAME        = KernelXO.iso

KERNEL_ASM      = boot.s gdt.s interrupt.s allocate.s
KERNEL_C        = descriptor_tables.c common.c main.c monitor.c isr.c timer.c kb.c tictactoe.c

KERNEL_OBJECTS  = $(addprefix $(BUILD_DIR)/, $(KERNEL_ASM:.s=.o) $(KERNEL_C:.c=.o))

# Link order must match multiboot entry (boot.o first) and dependencies
LINK_ORDER      = boot main common monitor descriptor_tables gdt timer isr interrupt kb tictactoe allocate
LINK_OBJECTS    = $(addprefix $(BUILD_DIR)/, $(addsuffix .o, $(LINK_ORDER)))

.PHONY: all kernel iso run test format clean

all: iso

format:
	find $(SRC_DIR) \( -iname '*.h' -o -iname '*.c' \) -exec clang-format --style=Google -i {} +

kernel: $(BUILD_DIR) $(KERNEL_OBJECTS)
	$(LD) $(LDFLAGS_KERNEL) -o $(KERNEL_NAME) $(LINK_OBJECTS)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.s
	$(AS) $(ASFLAGS) $< -o $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS_KERNEL) -c $< -o $@

iso: kernel
	cp $(KERNEL_NAME) isodir/boot/$(KERNEL_NAME)
	grub-mkrescue -o $(ISO_NAME) isodir

run: iso
	qemu-system-x86_64 -cdrom $(ISO_NAME)

test:
	$(MAKE) -C tests

clean:
	rm -rf $(BUILD_DIR)
	rm -f $(KERNEL_NAME)
	rm -f $(ISO_NAME)
	$(MAKE) -C tests clean 2>/dev/null || true
