# Made by decomp-kit (dk new). Build settings live in dk.json; dk writes config.mk.
include config.mk

SPLAT_CFG := config/main.yaml
LD_SCRIPT := linker/main.ld
LD_SYMS   := config/linker_syms.txt
WARM_LIST := config/warm_files.txt
BUILD     := build
ELF       := $(BUILD)/main.elf
OUT_EXE   := $(BUILD)/$(EXE)

AS      := mipsel-none-elf-as
LD      := mipsel-none-elf-ld
OBJCOPY := mipsel-none-elf-objcopy

ASM_SRCS := $(shell find asm -name '*.s' -not -path '*/nonmatchings/*' -not -path '*/matchings/*' 2>/dev/null)
C_SRCS   := $(shell find src -name '*.c' 2>/dev/null)
BIN_SRCS := $(shell find assets -name '*.bin' 2>/dev/null)
OBJS     := $(ASM_SRCS:%=$(BUILD)/%.o) $(C_SRCS:%=$(BUILD)/%.o) $(BIN_SRCS:%=$(BUILD)/%.o)
# Files tools/cc.sh compiles warm (see there). A file put on the list compiles again; one
# taken off does too, through the .d file its warm build wrote.
WARM_SRCS := $(shell sed 's/\#.*//' $(WARM_LIST) 2>/dev/null)
# Files tools/cc.sh compiles with an EE GCC (Sony's libraries), the same way.
GCC_LIST  := config/gcc_files.txt
GCC_SRCS  := $(shell sed 's/\#.*//' $(GCC_LIST) 2>/dev/null | awk '{ print $$1 }')

.PHONY: all build check split clean
all: check

split:
	@rm -rf asm $(BUILD) $(LD_SCRIPT) linker/undefined_*_auto.txt
	@mkdir -p $(BUILD)
	@python3 -m splat split $(SPLAT_CFG) > $(BUILD)/split.log 2>&1 || { tail -20 $(BUILD)/split.log; exit 1; }
	@if [ -f tools/fix_asm.py ]; then python3 tools/fix_asm.py; fi

build:
	@[ -f $(LD_SCRIPT) ] || $(MAKE) --no-print-directory split
	@$(MAKE) --no-print-directory $(OUT_EXE)

check: build
	@echo "$(TARGET_SHA)  $(OUT_EXE)" | sha1sum -c --quiet - && echo "OK: $(OUT_EXE) matches the original"

$(BUILD)/%.s.o: %.s
	@mkdir -p $(dir $@)
	@$(AS) $(AS_FLAGS) -I. -Iinclude -o $@ $<

# Through the assembler (not ld -b binary) so its ABI flags match every other object.
$(BUILD)/%.bin.o: %.bin
	@mkdir -p $(dir $@)
	@printf '.section .data\n.incbin "%s"\n' $< > $@.s
	@$(AS) $(AS_FLAGS) -o $@ $@.s

$(BUILD)/%.c.o: %.c
	@mkdir -p $(dir $@)
	@tools/cc.sh $< $@

$(WARM_SRCS:%=$(BUILD)/%.o): $(WARM_LIST)
$(GCC_SRCS:%=$(BUILD)/%.o): $(GCC_LIST)

$(ELF): $(OBJS) $(LD_SCRIPT) $(LD_SYMS)
	@$(LD) -EL -T $(LD_SCRIPT) -T linker/undefined_syms_auto.txt -T linker/undefined_funcs_auto.txt \
		-T $(LD_SYMS) -Map $(BUILD)/main.map -o $@

$(OUT_EXE): $(ELF)
	@$(OBJCOPY) -O binary $< $@

clean:
	rm -rf $(BUILD)

-include $(C_SRCS:%=$(BUILD)/%.o.d)
