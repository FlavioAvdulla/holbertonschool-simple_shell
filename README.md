# Simple Shell
## Table of Contents

- Introduction
- Features
- Getting Started
- Installation
- Usage
- Examples
- File Structure
- Limitations
- Development
- Coding Style
- Testing
- Authors
- License

## Introduction

Simple Shell is a minimalist UNIX command-line interpreter built as a project to understand the core concepts of operating systems, process creation, and execution. The shell reads commands from the user, executes them, and then displays the output. This project replicates the most fundamental behaviors of popular shells like bash but with a simplified design and limited functionality.

## Features

- Prompt Display: Shows a custom prompt (#cisfun$) waiting for user input.
- Command Execution: Executes single-word commands using their full path (e.g., /bin/ls).
- Error Handling: Displays an error message if a command cannot be found or executed.
- EOF Handling: Gracefully handles end-of-file (Ctrl+D) to exit the shell.
- Process Management: Uses fork and execve for process creation and execution.

## Getting Started
## Installation

To use the Simple Shell, you need to clone the repository and compile the source code. Follow these steps:

**1.** Clone the repository:

```
git clone https://github.com/<your-username>/holbertonschool-simple_shell.git
```

**2.** Navigate to the project directory:

```
cd holbertonschool-simple_shell
```

**3.** Compile the source files:

```
gcc -o hsh -Wall -Werror -Wextra -pedantic -std=gnu89 *.c
```

Replace <your-username> with your GitHub username.

## Usage

Once compiled, you can start the shell by running:

```
./hsh
```

This will launch the Simple Shell, displaying the prompt #cisfun$. You can type commands, which the shell will execute.

## Examples

Listing files:

```
#cisfun$ /bin/ls
file1  file2  simple_shell.c  hsh
```

**2.** Printing the current directory:

```
    #cisfun$ /bin/pwd
    /home/user/holbertonschool-simple_shell
```

**3.** Exiting the shell:
- Press Ctrl+D to exit.

## File Structure

Here's an overview of the key files in this project:

**'README.md'**: Detailed information about the project.

**'man_1_simple_shell'**: Manual page for the Simple Shell.

**'AUTHORS'**: List of contributors to the project.

**'simple_shell.'**: Main source file containing the shell's core logic.

**'.c' and '*.h'**: Other source and header files that make up the Simple Shell.

## Limitations

While this shell provides basic functionality, it has several limitations:

- No Argument Handling: Commands cannot take additional arguments (e.g., ls -l will not work).
- No Environment Variable Handling: Commands like echo $PATH are not supported.
- No Built-in Commands: Commands like cd, exit, or env are not implemented.
- No Advanced Features: Piping (|), redirection (>, <), and background execution (&) are not supported.
- Full Paths Required: Commands must be entered with their full path (e.g., /bin/ls).

## Development
**Coding Style**

The project follows the GNU C coding style with strict adherence to:

- Compiler Flags: -Wall -Werror -Wextra -pedantic -std=gnu89
- Indentation: 4 spaces, no tabs.
- Comments: Use C-style block comments (/* */) and ensure code is well-documented.

**Testing**

Testing is crucial to ensure that the shell behaves as expected. You can manually test the shell by running different commands and verifying the output. Consider testing edge cases like:

- Empty input
- Non-existent commands
- Executing the shell within itself (recursion)
- Handling of EOF and signals (e.g., Ctrl+C)

## Authors

This project is a collaborative effort by:

- [Flavio Avdulla](https://github.com/FlavioAvdulla)
- [Stilian Saka](https://github.com/StilianSaka)

For a complete list of contributors, please refer to the AUTHORS file.
## License

This project is licensed under the MIT License. See the LICENSE file for more details.

This **README.md** is more comprehensive, providing users and developers with detailed information about the project, its limitations, and how to get started.