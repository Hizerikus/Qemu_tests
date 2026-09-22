# Qemu_tests

A playground for learning QEMU AVR emulation.

## Project structure

```
avr_uno_blink/
├── blink.c     # Minimal ATmega328P firmware (toggles PB5, prints over UART)
└── Makefile    # Build + run targets
```

## Tooling present

- `qemu-system-avr` (QEMU 10.2.1) — machines: uno (ATmega328P), duemilanove (ATmega168),
  mega (ATmega1280), mega2560 (ATmega2560)
- `avr-gcc` 14.3.0, `avr-objcopy`, `avr-objdump`, `avr-size`
- No `/dev/kvm` here, so emulation runs under TCG (software).

## Running the blink sketch

```sh
cd avr_uno_blink
make            # blink.c -> blink.elf + blink.hex
make run        # boot blink.elf under qemu-system-avr (Ctrl+C to stop)
make debug      # run with instruction/interrupt tracing to trace.log
```

QEMU is invoked headless (`-nographic`, `-serial mon:stdio`) so the virtual
ATmega's UART prints to your terminal. PB5 toggles every 500 ms and each
transition is reported over the serial line.

### Key findings

- **Use `-bios blink.elf`**, not `-bios blink.hex` — the Intel HEX file triggers
  a segfault in QEMU's debug thread (`cpu_handle_guest_debug`), while the ELF
  loads and runs correctly.
- `-nographic` / `-display none` required on this host: QEMU's default
  GTK/SDL display triggers a Gdk seat assertion before it even starts.
- TCG emulates CPU *logic*, not real-world timing or electrical behavior.

## Example output

```
LED: ON
LED: OFF
LED: ON
LED: OFF
...
```