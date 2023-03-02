Modified from https://github.com/acschaefer/profiler.git @[acschaefer](https://github.com/acschaefer)

## C++ Time

A simple and lightweight CPU execution time profiler for **single-threaded**
C++ programs

### What it does

Measures the CPU execution times elapsed between checkpoints in the code.
You set the checkpoints. Checkpoints can be hit one or several times.

This is the output of the sample program you find in 
`src/cpp_time_profiler.cpp`:
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

### How to install it

This is a header-only library. To use it, simply copy the header files into your projects and include it.

### How to use it

Measurement points are added by inserting `PROFILER_HOOK()` in target lines. Can work with or without semicolomn ';'.

The profiler prints its statistics on the console when being destroyed.
The statistics can also be printed by calling `TimeProfiler::print_statistics()`.

Profiling is enabled by default. It can be globally disabled by simply adding
```c
#define PROFILE 0
```
to the source file before including time_profiler.h.
To enable profiling again, write
```c
#define PROFILE 1
```
before including time_profiler.h.

You find an example program in `src/time_profiler_test.cpp`.

### Note

The profiler is not thread-safe. It is designed to be used with single-threaded programs.

