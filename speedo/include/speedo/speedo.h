#ifndef SPEEDO_H
#define SPEEDO_H SPEEDO_H

// Activates profiling.
#define PROFILE 1

#if PROFILE > 0
    #define ___ Speedo::tick(__FILE__, __LINE__, __FUNCTION__);
#else
    #define ___
#endif

#include <map>
#include "speedo/printer.h"


/// Simple execution time profiler.
///
/// The profiler is implemented as a singleton.
/// Measurement points are added by inserting \c ___
/// at the start of a line of code.
/// The profiler prints its statistics on the console when being destroyed.
/// The statistics can also be printed by calling Speedo::print_statistics().
///
/// \note Profiling can be deactivated by simply adding
/// \code
/// #define PROFILE 0
/// \endcode
/// to the source file.
///
/// \note This class is not thread-safe.
class Speedo
{
private:
    /// All checkpoints collected during program execution.
    std::vector<Checkpoint> checkpoints_;


private:
    /// Default constructor.
    /// Inaccessible from outside the class.
    Speedo()
    {
    }


    /// Destructor.
    /// Computes and prints the collected statistics.
    ~Speedo()
    {
        print_statistics();
    }


    /// Copy constructor.
    /// Inaccessible from outside the class.
    Speedo(const Speedo& speedo);


    /// Assignment operator.
    /// Inaccessible from outside the class.
    Speedo& operator=(const Speedo& speedo);


    /// Returns the singleton instance of the profiler.
    static Speedo& get_instance()
    {
        // Create the single instance of this class.
        static Speedo speedo;
        return speedo;
    }


public:
    /// Adds a measurement.
    static void tick(const std::string& file, int line, const std::string& function)
    {
        // Add the measurement point.
        get_instance().checkpoints_.push_back(Checkpoint(file, line, function));
    }


    /// Prints the statistics.
    static void print_statistics()
    {
        // Create a map that contains all measurements arranged by the hashes
        // of their file-line pairs.
        std::map<std::size_t, MultiMeasurement> measurements;

        // Iterate over all checkpoints collected and sort them into the map.
        for (int i = 1; i < get_instance().checkpoints_.size(); i++)
        {
            SingleMeasurement single_measurement(
                                            get_instance().checkpoints_[i-1],
                                            get_instance().checkpoints_[i]);
            std::size_t hash = single_measurement.get_hash();
            if (measurements.count(hash) <= 0)
            {
                MultiMeasurement multi_measurement;
                multi_measurement.add(single_measurement);
                measurements[hash] = multi_measurement;
            }
            else
                measurements[hash].add(single_measurement);
        }

        // Iterate over the map and print all measurements.
        Printer printer;
        std::map<std::size_t, MultiMeasurement>::iterator it;
        for (it = measurements.begin(); it != measurements.end(); it++)
            printer.add(it->second);

        printer.print();
    }
};


#endif
