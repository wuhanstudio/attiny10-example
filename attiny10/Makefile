PRG			= main
OBJ			= main.o
SRCDIR=src
OBJDIR=obj
OUTDIR=bin

#MCU_TARGET	 = at90s2313
#MCU_TARGET	 = at90s2333
#MCU_TARGET	 = at90s4414
#MCU_TARGET	 = at90s4433
#MCU_TARGET	 = at90s4434
#MCU_TARGET	 = at90s8515
#MCU_TARGET	 = at90s8535
#MCU_TARGET	 = atmega128
#MCU_TARGET	 = atmega1280
#MCU_TARGET	 = atmega1281
#MCU_TARGET	 = atmega1284p
#MCU_TARGET	 = atmega16
#MCU_TARGET	 = atmega163
#MCU_TARGET	 = atmega164p
#MCU_TARGET	 = atmega165
#MCU_TARGET	 = atmega165p
#MCU_TARGET	 = atmega168
#MCU_TARGET	 = atmega169
#MCU_TARGET	 = atmega169p
#MCU_TARGET	 = atmega2560
#MCU_TARGET	 = atmega2561
#MCU_TARGET	 = atmega32
#MCU_TARGET	 = atmega324p
#MCU_TARGET	 = atmega325
#MCU_TARGET	 = atmega3250
#MCU_TARGET	 = atmega329
#MCU_TARGET	 = atmega3290
#MCU_TARGET	 = atmega32u4
#MCU_TARGET	 = atmega48
#MCU_TARGET	 = atmega64
#MCU_TARGET	 = atmega640
#MCU_TARGET	 = atmega644
#MCU_TARGET	 = atmega644p
#MCU_TARGET	 = atmega645
#MCU_TARGET	 = atmega6450
#MCU_TARGET	 = atmega649
#MCU_TARGET	 = atmega6490
#MCU_TARGET	 = atmega8
#MCU_TARGET	 = atmega8515
#MCU_TARGET	 = atmega8535
#MCU_TARGET	 = atmega88
#MCU_TARGET	 = attiny2313
#MCU_TARGET	 = attiny24
#MCU_TARGET	 = attiny25
#MCU_TARGET	 = attiny26
#MCU_TARGET	 = attiny261
#MCU_TARGET	 = attiny44
#MCU_TARGET	 = attiny45
#MCU_TARGET	 = attiny461
#MCU_TARGET	 = attiny84
#MCU_TARGET	 = attiny85
#MCU_TARGET	 = attiny861
MCU_TARGET	 = attiny10

OPTIMIZE	   = -Os -ffunction-sections -fdata-sections -MMD -flto -fno-fat-lto-objects
DEFS		   =
LIBS		   =

# You should not have to change anything below here.
CC			 = avr-gcc
# Override is only needed by avr-lib build system.
override CFLAGS		= -g -Wall $(OPTIMIZE) -mmcu=$(MCU_TARGET) $(DEFS)
override LDFLAGS	= -Wl,-Map,$(OBJDIR)/$(PRG).map
OBJCOPY		= avr-objcopy
OBJDUMP		= avr-objdump

all: directories $(OBJDIR)/$(PRG).elf lst text eeprom usage

directories:
	@mkdir -p $(OBJDIR)
	@mkdir -p $(OUTDIR)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c -o $@ $^  $(LIBS)

$(OBJDIR)/$(PRG).elf: $(OBJDIR)/$(OBJ)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^ $(LIBS)

lst:  $(OBJDIR)/$(PRG).lst
$(OBJDIR)/%.lst: $(OBJDIR)/%.elf
	$(OBJDUMP) -h -S $< > $@

# Rules for building the .text rom images
text: hex bin srec
hex:  $(OUTDIR)/$(PRG).hex
bin:  $(OUTDIR)/$(PRG).bin
srec: $(OBJDIR)/$(PRG).srec

$(OUTDIR)/%.hex: $(OBJDIR)/%.elf
	$(OBJCOPY) -j .text -j .data -O ihex $< $@

$(OBJDIR)/%.srec: $(OBJDIR)/%.elf
	$(OBJCOPY) -j .text -j .data -O srec $< $@

$(OUTDIR)/%.bin: $(OBJDIR)/%.elf
	$(OBJCOPY) -j .text -j .data -O binary $< $@

# Rules for building the .eeprom rom images
eeprom: ehex ebin esrec
ehex:  $(OUTDIR)/$(PRG)_eeprom.hex
ebin:  $(OUTDIR)/$(PRG)_eeprom.bin
esrec: $(OBJDIR)/$(PRG)_eeprom.srec

$(OUTDIR)/%_eeprom.hex: $(OBJDIR)/%.elf
	$(OBJCOPY) -j .eeprom --change-section-lma .eeprom=0 -O ihex $< $@ || { echo empty $@ not generated; exit 0; }

$(OBJDIR)/%_eeprom.srec: $(OBJDIR)/%.elf
	$(OBJCOPY) -j .eeprom --change-section-lma .eeprom=0 -O srec $< $@ || { echo empty $@ not generated; exit 0; }

$(OUTDIR)/%_eeprom.bin: $(OBJDIR)/%.elf
	$(OBJCOPY) -j .eeprom --change-section-lma .eeprom=0 -O binary $< $@ || { echo empty $@ not generated; exit 0; }

usage:
	@echo
	@echo ----------------
	@avr-size -C -x $(OBJDIR)/$(PRG).elf

clean:
	rm -rf bin obj

upload:
	avrdude -p t10 -c usbasp -U flash:w:$(OUTDIR)/$(PRG).hex:i
