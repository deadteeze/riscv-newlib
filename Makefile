PREFIX = riscv-none-elf-
CC = $(PREFIX)gcc
AS = $(PREFIX)as
LD = $(PREFIX)ld
OBJCOPY = $(PREFIX)objcopy

CFLAGS = -march=rv64imac_zicsr -mabi=lp64 -mcmodel=medany -specs=nosys.specs -O2 -g -Wall
LDFLAGS = -T link.ld -nostartfiles

SRCS = main.c uart.c syscalls.c
ASRCS = startup.S
OBJS = $(SRCS:.c=.o) $(ASRCS:.S=.o)

ELF = firmware.elf
BIN = firmware.bin

all: $(BIN)

$(ELF): $(OBJS) link.ld
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $(OBJS)

$(BIN): $(ELF)
	$(OBJCOPY) -O binary $< $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

%.o: %.S
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(ELF) $(BIN) qemu_debug.log

run: $(BIN)
	qemu-system-riscv64 -machine virt -m 256M -nographic -bios none -kernel $(BIN)