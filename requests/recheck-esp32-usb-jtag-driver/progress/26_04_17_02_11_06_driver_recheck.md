# Progress Entry

## Completed Work

- Queried current connected PnP devices for `VID_303A&PID_1001`.
- Confirmed three present nodes: the USB composite parent, `MI_00` serial, and `MI_02` USB JTAG.
- Verified driver bindings with `pnputil` and PowerShell.

## Findings

- `USB\VID_303A&PID_1001&MI_00` is the COM interface and uses Microsoft `usbser.inf`.
- `USB\VID_303A&PID_1001&MI_02` is the `USB JTAG/serial debug unit` interface and uses `WinUSB` through libwdi INF `oem108.inf` (`usb_jtag_debug_unit.inf`).
- This means the expected debug-class binding is already present.

## Result

- The driver itself is not obviously wrong anymore.
- The prior OpenOCD `LIBUSB_ERROR_ACCESS` is more consistent with host-side access contention, stale device state, or another USB-level access restriction.