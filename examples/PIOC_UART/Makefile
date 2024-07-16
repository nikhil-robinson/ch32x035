TOOLCHAIN_PREFIX := /opt/gcc-riscv/RISC-V_Embedded_GCC12/bin/riscv-none-elf

SDK_PATH := ../../sdk


APP_C_SRCS += \
  ./src/main.c \
  ./src/ch32x035_it.c \
  ./src/system_ch32x035.c



SDK_Peripheral_C_SRCS += \
  $(SDK_PATH)/Peripheral/ch32x035_dbgmcu.c \
  $(SDK_PATH)/Peripheral/ch32x035_misc.c \
  $(SDK_PATH)/Peripheral/ch32x035_rcc.c \
  $(SDK_PATH)/Peripheral/ch32x035_usart.c \
  $(SDK_PATH)/Peripheral/ch32x035_gpio.c \
  

SDK_CORE_C_SRCS += \
  $(SDK_PATH)/Core/core_riscv.c

SDK_DEBUG_C_SRCS += \
	$(SDK_PATH)/Debug/debug.c

SDK_STARTUP_S_UPPER_SRCS += \
  $(SDK_PATH)/Startup/startup_ch32x035.S 

C_SRCS := \
  $(APP_C_SRCS) \
  $(SDK_Peripheral_C_SRCS) \
  $(SDK_CORE_C_SRCS) \
  $(SDK_DEBUG_C_SRCS)

S_UPPER_SRCS := \
  $(SDK_STARTUP_S_UPPER_SRCS)

OBJS := \
  $(patsubst ./src/%.c,obj/src/%.o,$(APP_C_SRCS)) \
  $(patsubst $(SDK_PATH)/%.c,obj/sdk/%.o,$(SDK_Peripheral_C_SRCS)) \
  $(patsubst $(SDK_PATH)/%.c,obj/sdk/%.o,$(SDK_CORE_C_SRCS)) \
    $(patsubst $(SDK_PATH)/%.c,obj/sdk/%.o,$(SDK_DEBUG_C_SRCS)) \
  $(patsubst $(SDK_PATH)/%.S,obj/sdk/%.o,$(SDK_STARTUP_S_UPPER_SRCS))

MAKEFILE_DEPS := \
  $(foreach obj,$(OBJS),$(patsubst %.o,%.d,$(obj)))


LIBS := 

SECONDARY_FLASH := main.hex
SECONDARY_LIST := main.lst
SECONDARY_SIZE := main.siz


CFLAGS_COMMON := \
  -march=rv32imacxw \
  -mabi=ilp32 \
  -msmall-data-limit=8 \
  -msave-restore \
  -Os \
  -fmessage-length=0 \
  -fsigned-char \
  -ffunction-sections \
  -fdata-sections \
  -fno-common \
  -Wunused \
  -Wuninitialized \
  -g
  

.PHONY: all
all: main.elf secondary-outputs

.PHONY: clean
clean:
	-rm -rf $(OBJS) $(MAKEFILE_DEPS) $(SECONDARY_FLASH) $(SECONDARY_LIST) main.elf main.map ./obj

.PHONY: secondary-outputs
secondary-outputs: $(SECONDARY_FLASH) $(SECONDARY_LIST) $(SECONDARY_SIZE)

main.elf: $(OBJS)
	${TOOLCHAIN_PREFIX}-g++ \
	    $(CFLAGS_COMMON) \
	    -T "./Ld/Link.ld" \
	    -nostartfiles \
	    -Xlinker \
	    --gc-sections \
	    -Wl,-Map,"main.map" \
	    -Lobj \
	    --specs=nano.specs \
	    --specs=nosys.specs \
	    -o "main.elf" \
	    $(OBJS) \
	    $(LIBS)

%.hex: %.elf
	@ ${TOOLCHAIN_PREFIX}-objcopy -O ihex "$<"  "$@"

%.lst: %.elf
	@ ${TOOLCHAIN_PREFIX}-objdump --all-headers --demangle --disassemble -M xw "$<" > "$@"

%.siz: %.elf
	@ ${TOOLCHAIN_PREFIX}-size --format=berkeley "$<"





obj/src/%.o: ./src/%.c
	@ mkdir --parents $(dir $@)
	@ ${TOOLCHAIN_PREFIX}-gcc \
	    $(CFLAGS_COMMON) \
	    -I"src/include" \
	    -I"$(SDK_PATH)/Peripheral/inc" \
	    -I"$(SDK_PATH)/Core" \
		-I"$(SDK_PATH)/Debug" \
	    -std=gnu99 \
	    -MMD \
	    -MP \
	    -MF"$(@:%.o=%.d)" \
	    -MT"$(@)" \
	    -c \
	    -o "$@" "$<"

obj/sdk/%.o: $(SDK_PATH)/%.c
	@ mkdir --parents $(dir $@)
	@ ${TOOLCHAIN_PREFIX}-gcc \
	    $(CFLAGS_COMMON) \
	    -DDEBUG=1 \
	    -I"src/include" \
	    -I"$(SDK_PATH)/Peripheral/inc" \
	    -I"$(SDK_PATH)/Core" \
		-I"$(SDK_PATH)/Debug" \
	    -std=gnu99 \
	    -MMD \
	    -MP \
	    -MF"$(@:%.o=%.d)" \
	    -MT"$(@)" \
	    -c \
	    -o "$@" "$<"

obj/sdk/%.o: $(SDK_PATH)/%.S
	@ mkdir --parents $(dir $@)
	@ ${TOOLCHAIN_PREFIX}-gcc \
	    $(CFLAGS_COMMON) \
	    -x assembler \
	    -MMD \
	    -MP \
	    -MF"$(@:%.o=%.d)" \
	    -MT"$(@)" \
	    -c \
	    -o "$@" "$<"

f: clean all  
	wchisp flash ./main.elf

flash: main.elf
	wchisp flash ./main.elf
