🐚 Minishell: Building a Custom Bash
A Unix shell clone implemented from scratch — capable of parsing, interpreting, and executing user commands in a terminal-like environment.

📌 Project Summary
A small Bash-like shell that interprets and executes commands using execve, handles input parsing, built-ins, environment variables, pipes, redirections, and error management — following POSIX standards.

✅ Key Features
🔄 Built-in commands like cd, echo, pwd, exit, export, unset

📦 Environment variable support and manipulation

🔧 Command parsing: handles quotes, escape sequences, and expansions

➰ Pipes: support for chaining commands with |

📂 Redirection: input <, output >, append >>, and here-documents <<

⚙️ Execution of external binaries via execve

🚫 Signal handling: Ctrl+C, Ctrl+\ for graceful interruption

🧠 Memory management: handles leaks and frees resources on exit
