# minishell

This is the first project team.

A simple Unix shell project (42 school style) implemented in C.

<img src="/subject/image.png" with=600>

## Overview

This repository contains a small shell implementation with parsing, expansion, execution, and builtin commands.

Directory layout (important folders):

- `builtins/` - implementations of shell builtins (cd, echo, env, exit, export, pwd, unset)
- `execution/` - command execution, redirection, heredoc, and signals
- `parsing/` - lexer, parser, tokenization, and quote/expansion handling
- `libft/` - small helper library used across the project

## Requirements

- POSIX-compatible system (Linux, macOS)
- GCC (or other C compiler)
- make

## Build

From the project root:

```sh
make
```

This should produce the shell executable (commonly named `minishell`). If your Makefile uses different targets, use those accordingly (e.g. `make all`).

## Run

Start the shell from the project root:

```sh
./minishell
```

Use Ctrl+C / Ctrl+D as appropriate to exit or interrupt.

## Cleaning

Common Makefile targets:

```sh
make clean
make fclean
make re
```

