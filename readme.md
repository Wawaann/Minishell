# Project Name

## Description

This project is a custom implementation of a shell (or a specific component). It is designed to interact with the operating system, manage processes, and handle built-in commands, such as `cd`, `echo`, and environment variable manipulation. The shell is built from scratch using C, and it provides an understanding of how shells handle command execution, process management, and environment variables.

## Features

- Custom implementation of a shell that supports basic commands like `cd`, `echo`, `pwd`, and more.
- Handling of special cases like `$?`, `$$`, and other environment variables.
- Supports basic piping and redirection.
- 101% validation score in the project.

## How to Compile

To compile the project, follow these steps:

1. Clone the repository to your local machine:
   ```bash
   git clone https://github.com/Wawaann/Minishell.git
   cd Minishell

2. Install the `readline` library if it is not already installed:
    ```bash
    sudo apt-get install libreadline-dev
    ```

3. Compile the project using the provided `Makefile`:
    ```bash
    make
    ```

4. Run the compiled executable:
    ```bash
    ./minishell
    ```

## How to Use

Once compiled, you can execute the shell by running the executable. You can then enter commands as you would in a regular shell environment.

Example usage:
```bash
./minishell
$ echo Hello, World!
Hello, World!
$ cd /path/to/directory
$ echo $PWD
/path/to/directory
$ exit
```

## Validation
The project has been successfully validated with 101% of the tests passed. This includes various edge cases and feature implementation checks.

## Authors
- **Wawaann**
- **CedricM11**