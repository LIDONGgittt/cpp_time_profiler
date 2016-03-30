#ifndef SPEEDO_H
#define SPEEDO_H SPEEDO_H

// Activates profiling.
#define PROFILE 1

#if PROFILE > 0
    #define ___ Speedo::tick(__FILE__, __LINE__, __FUNCTION__);
#else
    #define ___
#endif

#include <vector>
#include <map>
#include <list>
#include "speedo/printer.h"


/// Simple execution time profiler.
///
/// The profiler is implemented as a singleton.
/// Measurement points are added by inserting 3 underscores \c ___
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
    /// Computes and prints the collected statistics and saves them to a 
    /// log file: \c $HOME/.speedo/log.
    ~Speedo()
    {
        print_statistics();
        save_log();
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
    
    
    /// Returns a sorted list of the measurements that were made.
    /// The measurements are sorted with respect to the overall execution time
    /// in descending order.
    static std::list<MultiMeasurement> sort_measurements()
    {
        // Create a map that contains all measurements arranged by the hashes
        // of their file-line pairs.
        std::map<std::size_t, MultiMeasurement> measurement_map;

        // Iterate over all checkpoints collected and sort them into the map.
        for (int i = 1; i < get_instance().checkpoints_.size(); i++)
        {
            SingleMeasurement single_measurement(
                                            get_instance().checkpoints_[i-1],
                                            get_instance().checkpoints_[i]);
            std::size_t hash = single_measurement.get_hash();
            if (measurement_map.count(hash) <= 0)
            {
                MultiMeasurement multi_measurement;
                multi_measurement.add(single_measurement);
                measurement_map[hash] = multi_measurement;
            }
            else
                measurement_map[hash].add(single_measurement);
        }
        
        // Copy the map elements into a list that can be sorted.
        std::list<MultiMeasurement> measurement_list;
        std::map<std::size_t, MultiMeasurement>::const_iterator mit;
        for (mit = measurement_map.begin(); mit != measurement_map.end(); mit++)
            measurement_list.push_back(mit->second);
            
        // Sort the measurements based on their overall execution times,
        // starting with the largest value.
        measurement_list.sort();
        measurement_list.reverse();
        
        return measurement_list;
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
        // Print the sorted list of all measurements.
        Printer printer;
        printer.add(sort_measurements());

        printer.print();
    }
    
    
    /// Saves a log file with the statistics under \c $HOME/.speedo/log.
    static void save_log()
    {
        Printer printer;
        printer.add(sort_measurements());
        
        printer.save_log();
    }
};


#endif
