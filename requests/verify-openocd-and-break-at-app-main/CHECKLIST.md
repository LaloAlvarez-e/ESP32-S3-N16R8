# Checklist

- [x] Create the request folder and required tracking files.
- [x] Attempt OpenOCD start with the repository wrapper.
- [ ] Resolve the Windows USB-JTAG access failure and confirm the OpenOCD listener on `localhost:3333`.
- [ ] Connect GDB and verify a break at `app_main`.
- [x] Record the interim outcome and update the tracker.

## Notes

- Windows enumerates the ESP32-S3 native USB debug device as `USB JTAG/serial debug unit` plus `COM8`, but OpenOCD fails with `LIBUSB_ERROR_ACCESS` when trying to open the JTAG interface.
