<h1 align="center">🐚 Minishell: Building a Custom Bash</h1>

<p align="center">
  A <strong>Unix shell clone</strong> implemented from scratch — capable of parsing, interpreting, and executing user commands using <code>execve</code>, with full support for built-in commands, pipes, redirections, and signal handling.
</p>

<hr/>

<h2>📌 Project Summary</h2>
<p>
  A small Bash-like shell that interprets and executes commands via <code>execve</code>, handles user input, built-ins, environment variables, piping, redirection, and return handling — all in compliance with POSIX behavior.
</p>

<h2>✅ Key Features</h2>
<ul>
  <li>🔄 <strong>Built-in commands</strong>: <code>cd</code>, <code>echo</code>, <code>pwd</code>, <code>exit</code>, <code>export</code>, <code>unset</code></li>
  <li>📦 <strong>Environment variable</strong> parsing and export</li>
  <li>🔧 <strong>Command parsing</strong> with quote handling and variable expansion</li>
  <li>➰ <strong>Pipes</strong>: chaining commands with <code>|</code></li>
  <li>📂 <strong>Redirection</strong>: input <code>&lt;</code>, output <code>&gt;</code>, append <code>&gt;&gt;</code>, and heredocs <code>&lt;&lt;</code></li>
  <li>⚙️ <strong>Command execution</strong> with <code>execve</code></li>
  <li>🚫 <strong>Signal handling</strong> for Ctrl+C and Ctrl+\</li>
  <li>🧠 <strong>Memory-safe</strong>: handles leaks and frees all resources properly</li>
</ul>

<h2>🛠️ Under the Hood</h2>
<ul>
  <li><strong>Parser</strong>: Tokenizes input and builds command structures</li>
  <li><strong>Executor</strong>: Manages forks and <code>execve</code> calls</li>
  <li><strong>Built-in Dispatcher</strong>: Detects and handles built-in commands internally</li>
  <li><strong>Environment Manager</strong>: Maintains shell variables and updates</li>
  <li><strong>Signal System</strong>: Gracefully manages signals (SIGINT, SIGQUIT)</li>
</ul>


<p align="center">🧑‍💻 Built from scratch with low-level system programming in C</p>
