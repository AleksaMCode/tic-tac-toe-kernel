# Unit Tests (Unity)

This repository now uses the Unity framework for C unit tests under `tests/`.

## Layout

- `tests/unity/` - Unity framework (Git submodule)
- `tests/test_runner.c` - Unity runner entrypoint
- `tests/test_sanity.c` - Sanity test to validate runner setup
- `tests/test_tictactoe.c` - Unit tests for `src/tictactoe.c` logic
- `tests/test_common.c` - Unit tests for `src/common.c` string/memory wrappers
- `tests/test_stubs.c` - Host stubs for kernel-only dependencies
- `tests/Makefile` - Local test build/run entrypoint

## First-time setup

If you cloned this repository fresh, initialize submodules:

```bash
git submodule update --init --recursive
```

## Run tests

From repository root:

```bash
make -C tests
```

Or from `tests/`:

```bash
make
```

Current coverage includes:

- board initialization and game reset behavior
- free-space/winner detection helpers
- minimax move selection via `getComputerMoveAI`
- scoreboard reset behavior
- common utility functions (`strcmp`, `strcpy`, `strcat`, `malloc`)
