CC = arm-none-eabi-gcc
BIN := RTOSDemo.axf

BUILD_DIR := build

# Kernel dir points to FreeRTOS directory. FREERTOS_DIR environemt variable
# must be set
KERNEL_DIR := $(FREERTOS_DIR)/Source

# Take current Makefile absolute path
mkfile_path := $(abspath $(lastword $(MAKEFILE_LIST)))
CURRENT_DIR := $(patsubst %/,%,$(dir $(mkfile_path)))

SOURCE_FILES += init/startup.c  syscall.c main.c
SOURCE_FILES += $(KERNEL_DIR)/portable/GCC/ARM_CM3/port.c
SOURCE_FILES += $(KERNEL_DIR)/tasks.c
SOURCE_FILES += $(KERNEL_DIR)/list.c
SOURCE_FILES += $(KERNEL_DIR)/queue.c
SOURCE_FILES += $(KERNEL_DIR)/timers.c
SOURCE_FILES += $(KERNEL_DIR)/event_groups.c
SOURCE_FILES += ${KERNEL_DIR}/portable/MemMang/heap_3.c

INCLUDE_DIRS += -I$(FREERTOS_DIR)/Demo/CORTEX_M3_MPS2_QEMU_GCC
INCLUDE_DIRS += -I$(FREERTOS_DIR)/Demo/CORTEX_M3_MPS2_QEMU_GCC/CMSIS
INCLUDE_DIRS += -I$(KERNEL_DIR)/include
INCLUDE_DIRS += -I$(KERNEL_DIR)/portable/GCC/ARM_CM3

ifeq ($(FULL_DEMO), 1)
    SOURCE_FILES += main_full.c
    SOURCE_FILES += $(KERNEL_DIR)/stream_buffer.c
    SOURCE_FILES += ${FREERTOS_DIR}/Demo/Common/Minimal/AbortDelay.c
    SOURCE_FILES += ${FREERTOS_DIR}/Demo/Common/Minimal/BlockQ.c
    SOURCE_FILES += ${FREERTOS_DIR}/Demo/Common/Minimal/blocktim.c
    SOURCE_FILES += ${FREERTOS_DIR}/Demo/Common/Minimal/countsem.c
    SOURCE_FILES += ${FREERTOS_DIR}/Demo/Common/Minimal/death.c
    SOURCE_FILES += ${FREERTOS_DIR}/Demo/Common/Minimal/dynamic.c
    SOURCE_FILES += ${FREERTOS_DIR}/Demo/Common/Minimal/EventGroupsDemo.c
    SOURCE_FILES += ${FREERTOS_DIR}/Demo/Common/Minimal/flop.c
    SOURCE_FILES += ${FREERTOS_DIR}/Demo/Common/Minimal/GenQTest.c
    SOURCE_FILES += ${FREERTOS_DIR}/Demo/Common/Minimal/integer.c
    SOURCE_FILES += ${FREERTOS_DIR}/Demo/Common/Minimal/IntSemTest.c
    SOURCE_FILES += ${FREERTOS_DIR}/Demo/Common/Minimal/MessageBufferAMP.c
    SOURCE_FILES += ${FREERTOS_DIR}/Demo/Common/Minimal/MessageBufferDemo.c
    SOURCE_FILES += ${FREERTOS_DIR}/Demo/Common/Minimal/PollQ.c
    SOURCE_FILES += ${FREERTOS_DIR}/Demo/Common/Minimal/QPeek.c
    SOURCE_FILES += ${FREERTOS_DIR}/Demo/Common/Minimal/QueueOverwrite.c
    SOURCE_FILES += ${FREERTOS_DIR}/Demo/Common/Minimal/QueueSet.c
    SOURCE_FILES += ${FREERTOS_DIR}/Demo/Common/Minimal/QueueSetPolling.c
    SOURCE_FILES += ${FREERTOS_DIR}/Demo/Common/Minimal/recmutex.c
    SOURCE_FILES += ${FREERTOS_DIR}/Demo/Common/Minimal/semtest.c
    SOURCE_FILES += ${FREERTOS_DIR}/Demo/Common/Minimal/StaticAllocation.c
    SOURCE_FILES += ${FREERTOS_DIR}/Demo/Common/Minimal/StreamBufferDemo.c
    SOURCE_FILES += ${FREERTOS_DIR}/Demo/Common/Minimal/StreamBufferInterrupt.c
    SOURCE_FILES += ${FREERTOS_DIR}/Demo/Common/Minimal/TaskNotify.c
    SOURCE_FILES += ${FREERTOS_DIR}/Demo/Common/Minimal/TimerDemo.c
    SOURCE_FILES += ${FREERTOS_DIR}/Demo/Common/Full/print.c

    INCLUDE_DIRS += -I$(FREERTOS_DIR)/Demo/Common/include
    INCLUDE_DIRS += -I${FREERTOS_PLUS_DIR}/Source/FreeRTOS-Plus-Trace/Include/

    CFLAGS := -DmainCREATE_FULL_DEMO_ONLY=1
else
    SOURCE_FILES += main_blinky.c

    CFLAGS := -DmainCREATE_SIMPLE_BLINKY_DEMO_ONLY=1
endif

DEFINES :=  -DQEMU_SOC_MPS2 -DHEAP3

LDFLAGS = -T ./scripts/mps2_m3.ld

ifeq ($(PICOLIBC), 1)
    LDFLAGS += -lc
    CFLAGS += -specs=picolibc.specs --oslib=semihost -DPICOLIBC_INTEGER_PRINTF_SCANF -DPICOLIBC_TLS --include picolibc.h
else
    LDFLAGS += -lc -lrdimon
    CFLAGS +=  -specs=nano.specs --specs=rdimon.specs --include newlib.h
endif

LDFLAGS += -Xlinker -Map=${BUILD_DIR}/output.map
LDFLAGS += -Wl,--gc-sections

CFLAGS += -nostartfiles
CFLAGS += -mthumb
CFLAGS += -mcpu=cortex-m3
CFLAGS += -Wno-error=implicit-function-declaration
CFLAGS += -Wno-builtin-declaration-mismatch -Werror
CFLAGS += -Wall -Wextra
CFLAGS += -ffunction-sections -fdata-sections

ifeq ($(DEBUG), 1)
    CFLAGS += -ggdb3 -Og
else
    CFLAGS += -O3
endif

CFLAGS += -fstrict-aliasing -Wstrict-aliasing -Wno-error=address-of-packed-member

OBJ_FILES := $(SOURCE_FILES:%.c=$(BUILD_DIR)/%.o)

CPPFLAGS += $(DEFINES)
CFLAGS += $(INCLUDE_DIRS)

.PHONY: clean

$(BUILD_DIR)/$(BIN) : $(OBJ_FILES)
	$(CC) $(CFLAGS) $(LDFLAGS) $+ -o $(@)

%.d: %.c
	@set -e; rm -f $@; \
	$(CC) -M $(CPPFLAGS) $< > $@.$$$$; \
	sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
	rm -f $@.$$$$

INCLUDES := $(SOURCE_FILES:%.c=$(BUILD_DIR)/%.d)
-include $(INCLUDES)

${BUILD_DIR}/%.o : %.c Makefile
	-mkdir -p $(@D)
	$(CC) $(CFLAGS) $(CPPFLAGS) -MMD -c $< -o $@

clean:
	-rm -rf build
