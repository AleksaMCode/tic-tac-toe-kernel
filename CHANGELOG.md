# Changelog

All notable changes to this project are documented in this file.

## [0.2.0] - 2026-02-25

### Added
- Post-game end menu with four options:
  - `1` Play another game
  - `2` Reset scoreboard and play again
  - `3` Show scoreboard and return to menu
  - `4` Show final scoreboard and shutdown
- Runtime scoreboard reset support without rebooting:
  - Resets total games, draws, and wins for both sides
  - Preserves username and selected difficulty
- Kernel shutdown routine integrated into game flow:
  - Selecting `No` on the initial prompt now shuts down the VM
  - Quit option from end menu also triggers shutdown
  - QEMU/Bochs ACPI poweroff ports supported
- Root `Makefile` for build/run/test/format workflow:
  - `make`, `make kernel`, `make iso`, `make run`, `make test`, `make format`, `make clean`
- Unit testing setup under `tests/` using Unity:
- GitHub workflows:
  - Unit test workflow execution in CI
  - Code style workflow that fails if formatting is not compliant

### Changed
- README updated with:
  - New game flow and end-menu behavior
  - Makefile-first build instructions


## [0.1.0] - Initial release

### Added
- Bootable x86 Tic Tac Toe kernel with GRUB.
- Core kernel components:
  - Boot/multiboot entry
  - GDT/IDT setup
  - Interrupt and timer handling
  - VGA monitor output and keyboard input
- Tic Tac Toe gameplay in kernel space:
  - Username entry
  - Difficulty selection (`EASY`, `HARD`)
  - Turn-based game loop with win/draw detection
  - "AI" move logic with minimax on hard difficulty
- Session scoreboard tracking for games, wins, and draws.
- Shell scripts for building and running in QEMU.
