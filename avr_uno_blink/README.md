# avr_uno_blink

Minimal Arduino Uno (ATmega328P) blink example running under QEMU.

## What it does

- Toggles PB5 (the on-board LED pin on a real Uno)
- Prints `LED: ON` / `LED: OFF` over UART at 9600 baud
- Runs entirely in QEMU — no hardware required

## Build & run

```sh
make            # builds blink.elf and blink.hex
make run        # runs under qemu-system-avr (Ctrl+C to stop)
make debug      # runs with instruction/interrupt tracing to trace.log
```

## Requirements

- `avr-gcc`, `avr-objcopy` (provided by `gcc-avr` / `binutils-avr`)
- `qemu-system-avr` (QEMU 10.2+)

## QEMU invocation

```sh
qemu-system-avr -M uno -bios blink.elf -nographic -serial mon:stdio -no-reboot
```

**Key notes:**
- Must use `-bios blink.elf` (not `.hex`) — Intel HEX triggers a segfault in QEMU's debug thread
- `-nographic` / `-display none` avoids a Gdk seat assertion on headless hosts
- Runs under TCG (software emulation) — no `/dev/kvm` needed

## Example output

```
LED: ON
LED: OFF
LED: ON
LED: OFF
...
```

## Files

| File | Description |
|------|-------------|
| `blink.c` | Firmware source |
| `Makefile` | Build and run targets |