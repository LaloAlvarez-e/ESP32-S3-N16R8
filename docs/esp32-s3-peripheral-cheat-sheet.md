# ESP32-S3 Peripheral Inspection Cheat Sheet

This sheet is intentionally narrower than the general GDB cheat sheet. It focuses on the first peripheral blocks and register fields you are most likely to inspect in the ESP-IDF Peripheral View or through raw GDB memory reads.

The values below come from the workspace SVD at `.vscode/svd/esp32s3.svd`.

## Fast Start

- Use `ESP-IDF: Peripheral View` for read-only browsing by peripheral and field name.
- Use the GDB console when you want exact addresses or direct writes.
- Read a register with `x/wx ADDRESS`.
- Read a short block with `x/8wx BASE_ADDRESS`.
- Write a 32-bit register with `set *((volatile uint32_t *)ADDRESS) = VALUE`.

## GPIO

- Base: `0x60004000`
- Inspect first:
  - `OUT` at offset `0x04`: field `DATA_ORIG`
  - `OUT_W1TS` at offset `0x08`: field `OUT_W1TS`
  - `OUT_W1TC` at offset `0x0C`: field `OUT_W1TC`
  - `ENABLE` at offset `0x20`: field `DATA`
  - `ENABLE_W1TS` at offset `0x24`: field `ENABLE_W1TS`
  - `ENABLE_W1TC` at offset `0x28`: field `ENABLE_W1TC`
  - `IN` at offset `0x3C`: field `DATA_NEXT`
  - `STATUS` at offset `0x44`: field `INTERRUPT`
- Typical use:
  - Check whether firmware actually drove a pin high or low.
  - Confirm the output-enable path before blaming routing or pad config.
  - Check interrupt status when GPIO callbacks do not fire.

Example reads:

```text
x/8wx 0x60004000
x/wx 0x60004004
x/wx 0x60004020
x/wx 0x6000403C
```

## IO_MUX

- Base: `0x60009000`
- Inspect first:
  - `PIN_CTRL` at offset `0x00`: fields `CLK_OUT1`, `CLK_OUT2`, `CLK_OUT3`
  - `GPIO<n>` pad register at offset `0x04 + 4 * n` for pads `0..48`
    - fields `MCU_SEL`, `FUN_IE`, `FUN_WPU`, `FUN_WPD`, `FUN_DRV`, `FILTER_EN`, `SLP_SEL`
- Typical use:
  - Confirm the pad function selected for a pin.
  - Check whether pull-up, pull-down, input-enable, or drive strength is fighting your intended behavior.

Example reads:

```text
x/wx 0x60009000
x/wx 0x60009004
x/wx 0x60009008
```

## UART

- `UART0` base: `0x60000000`
- `UART1` base: `0x60010000`
- `UART1` follows the same layout as `UART0`.
- Inspect first:
  - `INT_ST` at offset `0x08`: fields `RXFIFO_FULL_INT_ST`, `TXFIFO_EMPTY_INT_ST`, `RXFIFO_TOUT_INT_ST`, `TX_DONE_INT_ST`
  - `INT_ENA` at offset `0x0C`: fields `RXFIFO_FULL_INT_ENA`, `TXFIFO_EMPTY_INT_ENA`, `RXFIFO_TOUT_INT_ENA`, `TX_DONE_INT_ENA`
  - `CLKDIV` at offset `0x14`: fields `CLKDIV`, `FRAG`
  - `RX_FILT` at offset `0x18`: fields `GLITCH_FILT`, `GLITCH_FILT_EN`
  - `STATUS` at offset `0x1C`: fields `RXFIFO_CNT`, `TXFIFO_CNT`, `RXD`, `TXD`
- Typical use:
  - Check whether the FIFO is filling or draining.
  - Confirm whether baud-rate divider values are sane.
  - Inspect line state before assuming a cable or routing problem.

Example reads:

```text
x/wx 0x60010008
x/wx 0x6001000C
x/wx 0x60010014
x/wx 0x6001001C
```

## I2C

- `I2C0` base: `0x60013000`
- `I2C1` base: `0x60027000`
- `I2C1` follows the same register pattern as `I2C0`.
- Inspect first:
  - `CTR` at offset `0x04`: fields `MS_MODE`, `TRANS_START`, `SDA_FORCE_OUT`, `SCL_FORCE_OUT`, `ARBITRATION_EN`
  - `SR` at offset `0x08`: fields `RESP_REC`, `ARB_LOST`, `BUS_BUSY`, `RXFIFO_CNT`, `TXFIFO_CNT`
  - `FIFO_CONF` at offset `0x18`: fields `RXFIFO_WM_THRHD`, `TXFIFO_WM_THRHD`, `RX_FIFO_RST`, `TX_FIFO_RST`
  - `INT_ENA` at offset `0x28`: fields `RXFIFO_WM_INT_ENA`, `TRANS_COMPLETE_INT_ENA`, `TIME_OUT_INT_ENA`, `NACK_INT_ENA`
  - `INT_STATUS` at offset `0x2C`: fields `RXFIFO_WM_INT_ST`, `TRANS_COMPLETE_INT_ST`, `TIME_OUT_INT_ST`, `NACK_INT_ST`
  - `CLK_CONF` at offset `0x54`: fields `SCLK_DIV_NUM`, `SCLK_DIV_A`, `SCLK_DIV_B`, `SCLK_SEL`
- Typical use:
  - Confirm master mode and whether a transfer was actually started.
  - Check for `BUS_BUSY`, `NACK`, timeout, or arbitration loss before chasing wiring.
  - Verify clock divider configuration after changing bus speed.

Example reads:

```text
x/wx 0x60027004
x/wx 0x60027008
x/wx 0x6002702C
x/wx 0x60027054
```

## SPI

- `SPI2` base: `0x60024000`
- `SPI3` base: `0x60025000`
- `SPI3` follows the same register pattern as `SPI2`.
- Inspect first:
  - `CMD` at offset `0x00`: fields `CONF_BITLEN`, `UPDATE`, `USR`
  - `CTRL` at offset `0x08`: fields `DUMMY_OUT`, `FADDR_DUAL`, `FADDR_QUAD`, `FREAD_QUAD`
- Typical use:
  - Confirm whether a user transaction actually started.
  - Check whether line-width and dummy-cycle related settings match the expected bus mode.

Example reads:

```text
x/wx 0x60025000
x/wx 0x60025008
```

## Timer Group

- `TIMG0` base: `0x6001F000`
- `TIMG1` base: `0x60020000`
- In the SVD, `T%s...` becomes `T0...` or `T1...` per timer instance.
- Inspect first:
  - `T0CONFIG` at offset `0x00`: fields `USE_XTAL`, `ALARM_EN`, `DIVIDER`, `AUTORELOAD`, `INCREASE`, `EN`
  - `T0UPDATE` at offset `0x0C`: field `UPDATE`
  - `T0ALARMLO` at offset `0x10`: field `ALARM_LO`
  - `T0LOADLO` at offset `0x18`: field `LOAD_LO`
  - `T0LOAD` at offset `0x20`: field `LOAD`
  - `WDTCONFIG0` at offset `0x48`: fields including `WDT_PROCPU_RESET_EN`
- Typical use:
  - Check whether the timer is enabled, counting up or down, and auto-reloading.
  - Confirm whether the watchdog is armed and capable of resetting a core.

Example reads:

```text
x/wx 0x60020000
x/wx 0x6002000C
x/wx 0x60020010
x/wx 0x60020048
```

## SYSTIMER

- Base: `0x60023000`
- Inspect first:
  - `CONF` at offset `0x00`: fields `SYSTIMER_CLK_FO`, `TARGET0_WORK_EN`, `TIMER_UNIT0_WORK_EN`, `CLK_EN`
  - `UNIT0_OP` at offset `0x04`: fields `TIMER_UNIT0_VALUE_VALID`, `TIMER_UNIT0_UPDATE`
  - `TARGET0_CONF` at offset `0x34`: fields `TARGET0_PERIOD`, `TARGET0_PERIOD_MODE`, `TARGET0_TIMER_UNIT_SEL`
  - `INT_ENA` at offset `0x64`: fields `TARGET0_INT_ENA`, `TARGET1_INT_ENA`, `TARGET2_INT_ENA`
  - `INT_ST` at offset `0x70`: fields `TARGET0_INT_ST`, `TARGET1_INT_ST`, `TARGET2_INT_ST`
- Typical use:
  - Check whether the system timer units and targets are enabled.
  - Confirm target periodic mode and whether compare interrupts are pending.

Example reads:

```text
x/wx 0x60023000
x/wx 0x60023004
x/wx 0x60023034
x/wx 0x60023070
```

## RTC_CNTL

- Base: `0x60008000`
- Inspect first:
  - `OPTIONS0` at offset `0x00`: fields `SW_STALL_APPCPU_C0`, `SW_STALL_PROCPU_C0`, `SW_APPCPU_RST`, `SW_PROCPU_RST`, `XTL_FORCE_PD`, `XTL_FORCE_PU`, `BBPLL_FORCE_PD`, `BBPLL_FORCE_PU`
- Typical use:
  - Check reset, stall, crystal, and PLL-related control when the chip appears to stick in low-level clock or reset behavior.

Example reads:

```text
x/wx 0x60008000
```

## Matching The View To The Tool

- Use `ESP-IDF: Peripheral View` when you want readable field names and a tree by peripheral.
- Use the GDB console when you want exact addresses, quick comparisons, or direct writes.
- For a live pin problem, the usual first path is `IO_MUX` plus `GPIO`.
- For a serial problem, start with `UARTx STATUS`, `INT_ST`, and `CLKDIV`.
- For an I2C problem, start with `CTR`, `SR`, and `INT_STATUS`.
- For a timer issue, start with `TIMGx T0CONFIG` or `SYSTIMER CONF` and `INT_ST`.
