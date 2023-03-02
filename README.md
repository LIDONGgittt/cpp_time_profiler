Modified from https://github.com/acschaefer/profiler.git @[acschaefer](https://github.com/acschaefer)

## C++ Time Profiler

A simple and lightweight CPU execution time profiler for **single-threaded**
C++ programs

### What it does

Measures the CPU execution times elapsed between checkpoints. Checkpoints can be added to anywhere and can be hit multiple times.

### How to install it

Requirement:
- C++ 17 or higher

This is a header-only library. Simply include the header file `time_profiler.h` in your projects and you are good to go.


### How to use it

Measurement points are added by inserting `PROFILER_HOOK()` to target lines. The macro can work with or without semicolon ';'.

The profiler prints the statistics on the console when being destroyed.
The statistics can also be printed by calling `TimeProfiler::print_statistics()`.

Profiling is enabled by default. It can be globally disabled by defining USE_PROFILER to 0:
```c
#define USE_PROFILER 0
```

Define USE_PROFILER to 1 to enable the profiler:
```c
#define USE_PROFILER 1
```

You can find an example program in `src/time_profiler_test.cpp`.

### Note

The profiler is not thread-safe. It is designed to be used with single-threaded programs.


Sample output from `src/time_profiler_test.cpp`:
```
========================================================================================================================
File                          |Function                                | Line |    Count |  Average [us] |   Overall [us]
========================================================================================================================
time_profiler_test.cpp        |function                                |     8|          |               |
                              |function                                |    11|         1|      3,094,796|      3,094,796
------------------------------------------------------------------------------------------------------------------------
time_profiler_test.cpp        |main                                    |    23|          |               |
                              |main                                    |    23| 1,999,999|              1|      2,187,379
------------------------------------------------------------------------------------------------------------------------
time_profiler_test.cpp        |main                                    |    23|          |               |
                              |main                                    |    29|         1|             20|             20
------------------------------------------------------------------------------------------------------------------------
time_profiler_test.cpp        |function                                |    11|          |               |
                              |main                                    |    32|         1|             17|             17
------------------------------------------------------------------------------------------------------------------------
time_profiler_test.cpp        |main                                    |    29|          |               |
                              |function                                |     8|         1|              5|              5
------------------------------------------------------------------------------------------------------------------------
time_profiler_test.cpp        |main                                    |    19|          |               |
                              |main                                    |    23|         1|              4|              4
########################################################################################################################
```


