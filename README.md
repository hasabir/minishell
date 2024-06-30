# Minishell

Minishell is a simple shell that mimics the functionalities of Bash. This project aims to provide a basic understanding of how shells work, including process creation and management, file descriptors, and command execution in Unix-like operating systems.

---

## Features
- **Prompt Display**: Shows a prompt while waiting for a new command.
- **Command History**: Maintains a history of executed commands.
- **Executable Search and Execution**: Locates and executes the correct executable based on the `PATH` variable or using a relative/absolute path.
- **Built-in Commands**:
  - `echo` with `-n` option
  - `cd` with relative or absolute paths
  - `pwd` with no options
  - `export` with no options
  - `unset` with no options
  - `env` with no options or arguments
  - `exit` with no options
- **Redirections**:
  - `<` for input redirection.
  - `>` for output redirection.
  - `<<` for here-document functionality.
  - `>>` for output redirection in append mode.
- **Piping**: Supports piping (`|`) to pass output from one command as input to another.
- **Environment Variables**: Expands environment variables (`$VAR`) and special parameter (`$?`).
- **Special Character Handling**:
  - Single quotes (`'`) to prevent meta-character interpretation.
  - Double quotes (`"`) to prevent meta-character interpretation except for `$`.
  - Control characters (`ctrl-C`, `ctrl-D`, `ctrl-\`) with behavior similar to Bash.

---
## Compilation

To compile Minishell, use the provided Makefile. The Makefile includes the following rules:
- `all`: Compile the source files.
- `clean`: Remove object files.
- `fclean`: Remove all generated files.
- `re`: Recompile the project.
- `bonus`: Compile bonus features (if applicable).

---
## Programming Languages:
<p align="left">
  <img src="https://raw.githubusercontent.com/devicons/devicon/master/icons/c/c-original.svg" alt="C" width="40" height="40"/>
</p>

---

## Authors

- [hasabir](https://github.com/hasabir)
- [nidalamine](https://github.com/nidalamine)

---

## Acknowledgments

- [GNU Bash Manual](https://www.gnu.org/savannah-checkouts/gnu/bash/manual/)
- [42 School](https://42.fr/)

---
