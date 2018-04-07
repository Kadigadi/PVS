BUILD_HOME=../../..
include $(BUILD_HOME)/src/Makefile.include

LIB = libstm_spl.a

all: $(LIB) lib-copy

DEFS += -DUSE_STDPERIPH_DRIVER -DSTM32F40_41xxx

SRCS = misc.c stm32f4xx_cryp_des.c stm32f4xx_dma.c stm32f4xx_hash.c stm32f4xx_pwr.c stm32f4xx_spi.c \
       stm32f4xx_adc.c stm32f4xx_cryp_tdes.c stm32f4xx_exti.c stm32f4xx_hash_md5.c stm32f4xx_rcc.c \
       stm32f4xx_syscfg.c stm32f4xx_can.c stm32f4xx_dac.c stm32f4xx_flash.c stm32f4xx_hash_sha1.c \
       stm32f4xx_rng.c stm32f4xx_tim.c stm32f4xx_crc.c stm32f4xx_dbgmcu.c stm32f4xx_i2c.c \
       stm32f4xx_rtc.c stm32f4xx_usart.c stm32f4xx_cryp_aes.c stm32f4xx_dcmi.c \
       stm32f4xx_fsmc.c stm32f4xx_iwdg.c stm32f4xx_sai.c stm32f4xx_wwdg.c \
       stm32f4xx_cryp.c stm32f4xx_dma2d.c stm32f4xx_gpio.c stm32f4xx_ltdc.c stm32f4xx_sdio.c

OBJS=${SRCS:.c=.o}

$(LIB): $(OBJS)
	$(AR) r $@ $(OBJS)

lib-copy: $(LIB)
	cp -f $(LIB) $(BUILD_HOME)/lib/
