set(DRV_SRC
    acmp.c
    adc.c
    bpwm.c
    canfd.c
    clk.c
    crc.c
    dac.c
    fmc.c
    gpio.c
    i2c.c
    llsi.c
    pdma.c
    pwm.c
    retarget.c
    spi.c
    sys.c
    timer.c
    uart.c
    usci_i2c.c
    usci_spi.c
    usci_uart.c
    wdt.c
    wwdt.c
)


add_library(standard_driver ${DRV_SRC})
