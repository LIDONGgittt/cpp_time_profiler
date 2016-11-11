## Speedo

A simple CPU execution time profiler for C++

### What it does

Speedo measures the CPU execution times elapsed between checkpoints in the code.
You set the checkpoints. Checkpoints can be hit one or several times.

### How to install it

Speedo is header-only. To use it, simply copy the header files and include speedo.h in your code.

### How to use it

Measurement points are added by inserting 3 underscores `___` or 3 Xs `xxx` in the code.

The profiler prints its statistics on the console when being destroyed.
The statistics can also be printed by calling `Speedo::print_statistics()`.

Profiling is enabled by default. It can be globally disabled by simply adding
```c
#define PROFILE 0
```
to the source file before including speedo.h.
To enable profiling again, write
```c
#define PROFILE 1
```
before including speedo.h.

### Note

Speedo is not thread-safe. It is designed to be used with single-threaded programs.
