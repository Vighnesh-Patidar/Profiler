# CPU and Memory Usage Monitor

This is a terminal-based system resource monitor implemented in C++. It reads from the `/proc` filesystem on Linux to display per-process CPU and memory usage in real-time.

## Features

- Displays process name, PID, CPU usage percentage, and memory usage (in MB)
- Refreshes output at a fixed interval (default: 500ms)
- Parses `/proc/[pid]/stat` for CPU and memory metrics
- Modular code structure with `CPU_Usage` and `MEM_Usage` classes

## Project Structure

```
├── include/             # Public headers
│   ├── cpu.hpp
│   └── memory.hpp
├── src/                 # Source files
│   ├── cpu.cpp
│   ├── memory.cpp
│   └── main.cpp
├── obj/                 # Intermediate object files (.o)
├── bin/                 # Final compiled binaries (e.g. profiler)
├── Makefile             # Build script
└── README.md            # Project documentation
```

## Build Instructions

1. Ensure you have a Linux system with `g++` installed.
2. Run the following command from the project root:

    make

This will build the project and place object files in the `bin/` directory.

## Usage

After building, run the monitor:

    ./bin/profiler

The application will continuously display an updated table of running processes with their CPU and memory usage.

## Notes

- Memory usage is reported as resident set size (RSS) in megabytes.
- CPU usage is computed by comparing deltas across intervals for each process.
- Tested on Linux kernels with standard `/proc` layout.

## License

This project is provided for educational and diagnostic purposes. No explicit license is declared.