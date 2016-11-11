## Speedo

A simple and lightweight CPU execution time profiler for single-threaded 
C++ programs

### What it does

Speedo measures the CPU execution times elapsed between checkpoints in the code.
You set the checkpoints. Checkpoints can be hit one or several times.

This is the output of the sample program you find in 
`speedo/src/speedo_test.cpp`:
```
################################################################################
############################# PROFILED WITH SPEEDO #############################
################################################################################
File                          | Line |    Count |  Average [us] |   Overall [us]
================================================================================
speedo_test.cpp               |     9|          |               |
                              |    11|         1|     53,224,780|     53,224,780
--------------------------------------------------------------------------------
speedo_test.cpp               |    22|          |               |
                              |    22| 1,999,999|              7|     14,276,117
--------------------------------------------------------------------------------
speedo_test.cpp               |    22|          |               |
                              |    26|         1|            296|            296
--------------------------------------------------------------------------------
speedo_test.cpp               |    11|          |               |
                              |    29|         1|             31|             31
--------------------------------------------------------------------------------
speedo_test.cpp               |    26|          |               |
                              |     9|         1|             17|             17
--------------------------------------------------------------------------------
speedo_test.cpp               |    20|          |               |
                              |    22|         1|              3|              3
################################################################################
```

### How to install it

Speedo is a header-only library. To use it, simply copy the header files onto 
your computer and include `speedo.h` in your code.

### How to use it

Measurement points are added by inserting 3 underscores `___` or 3 Xs `xxx` in 
the code.

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

You find an example program in `speedo/src/speedo_test.cpp`.

### Note

Speedo is not thread-safe. It is designed to be used with single-threaded 
programs.

