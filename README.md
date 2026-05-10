
# C-Shell

This project is a lightweight, custom shell implementation written in C. It demonstrates the core mechanics of a command-line interface, including process management, environment variable handling, and command dispatching via a lookup table.

Made this while exploring how `fork()` and `exec()` work, and this is done with 0 AI. (except this readme)

---

## Features

* **Built-in Commands:** Native support for common operations (`cd`, `pwd`, `echo`, `type`, `exit`).
* **System Integration:** Automatically searches the system `PATH` to execute external binaries.
* **Process Management:** Uses `fork`, `execvp`, and `wait` to handle external program execution safely.
* **Lookup Table Architecture:** Uses a function-pointer-based dispatch system, making it trivial to add new built-in commands.

---

## Supported Commands

### Built-ins

* `echo [args]`: Prints text to the standard output.
* `pwd`: Displays the current absolute working directory.
* `cd [path]`: Changes the current directory. Supports `~` for the home directory.
* `type [command]`: Identifies if a command is a shell built-in or an external binary (providing the file path).
* `exit`: Terminate the shell session.

### External Commands

Any command not found in the built-in lookup table (e.g., `ls`, `grep`, `cat`, `gcc`) is searched for in the directories listed in your environment's `PATH`. If found, the shell spawns a child process to execute it.

---

## How It Works

The shell operates on a standard **REPL** (Read-Eval-Print Loop) cycle:

1. **Read:** Captures user input via `fgets` and strips the newline.
2. **Eval:**
* Tokenizes the string into an argument array.
* Checks the `LookupTable` for a matching internal function.
* If no match is found, it forks a new process to execute the command as an external program.


3. **Print:** Output is directed to `stdout`.
4. **Loop:** Returns to the prompt until `exit` is called.

---

## Technical Details

### Dependencies

* Standard C Library (`stdio`, `stdlib`, `string`)
* POSIX API (`unistd`, `sys/wait`)

### Memory Management

The shell dynamically allocates memory for command strings to handle varying input lengths and ensures all allocated memory is freed before the next prompt, preventing leaks during long-running sessions.

---

## Getting Started

### Compilation

Use any standard C compiler (like `gcc` or `clang`):

```bash
gcc -o cshell main.c

```

### Running the Shell

```bash
./cshell

```

Once inside, you will see the `$ ` prompt. You can then run commands like:

```bash
$ echo hello world
$ pwd
$ type ls
$ cd /tmp

```

---

## Future Roadmap

* Support for I/O redirection (`>` and `<`).
* Command piping (`|`).
* Background process execution (`&`).
* Support for quoted strings (e.g., `echo "hello world"` as a single argument).
