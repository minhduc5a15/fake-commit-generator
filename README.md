# Fake Commits :)

**Idea:** [here](https://www.facebook.com/share/p/1DfZuG5suj/)

---

## Description

This project generates fake commits with random dates within a specified range. The main purpose is to "beautify" your GitHub contribution graph.

## Requirements

- A C++ compiler supporting C++17 or later.
- Boost Libraries (specifically `boost::date_time`).
- Git installed on your system.

## Setup

1. Install Boost:
   ```bash
   sudo apt install libboost-all-dev
   ```

2. Clone this repository:
   ```bash
   git clone https://github.com/minhduc5a15/fake-commit-generator
   cd fake-commit-generator
   ```

3. Compile the program:
   ```bash
   g++ -std=c++17 -o main main.cpp -lboost_system -lboost_filesystem
   ```

## Usage

1. Ensure you are inside a Git repository. If not, initialize one:
   ```bash
   git init
   ```

2. Run the program:
   ```bash
   ./main
   ```

3. Enter the number of commits you want to generate when prompted.

## Example

```bash
$ ./main
Number of commits to generate: 50
Checking Git repository...
Creating commit: 2019-01-15
Creating commit: 2020-03-21
...
Done! Pushing changes...
```

## Notes

- The program automatically pushes the commits to the remote repository after generation.
- If the current directory is not a Git repository, the program will prompt you to initialize one.
