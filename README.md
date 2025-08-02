# 🐚 Mini Shell

A Lightweight Unix-style mini shell written in C, designed to replicate basic shell functionality!

---

## 📸 Screenshot
![Mini-Shell Screenshot](screenshot.png)

---

## ✅ Features
- **Command Execution:**
    Run standard Unix commands with arguments. 
    Example: echo hello world, ls -l

- **Builtin Commands:**
    Supports 'cd', 'exit', and 'help'.

- **Input/Output Redirection:**
    Use '<' and '>' to redirect stdin and stdout. 
    Example: sort < unsorted.txt > sorted.txt

- **Pipelines:**
    Chain commands using pipe operator '|'.
    Example: ls | grep .c | sort

- **Coloured Prompts:**
    Custom bold-coloured 'mini-shell>' prompt with colour-coded error messages for better UX.
    
- **Modular Design:**
    Seperated functions into clean C modules: 
    parse_line, run_command, etc.

---

## 🛠️ Compilation & Usage
1. make
2. ./mini-shell

---

## 📚 Future Improvements
- **Background Execution:** Manage background jobs (&)
- **Tab Completion:** Autocomplete commands and filenames for better UX
- **Signal Handling:** Handle signals such as SIGINT and SIGSTP