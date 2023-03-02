#ifndef SPEEDO_H
#define SPEEDO_H SPEEDO_H

// Activate profiling if the user did not explicitly deactivate it.
#ifndef PROFILE
    #define PROFILE 1
#endif

// Define the placeholders for setting checkpoints.
#define xxx Speedo::tick(__FILE__, __LINE__, __FUNCTION__);
#define ___ Speedo::tick(__FILE__, __LINE__, __FUNCTION__);

#include <deque>
#include <map>
#include <list>
#include "speedo/printer.h"

/// Simple CPU execution time profiler.
///
/// Measurement points are added by inserting three underscores \c ___ or three X \c xxx in the code.
/// The profiler prints its statistics on the console when being destroyed.
/// The statistics can also be printed by calling Speedo::print_statistics().
///
/// \note Profiling is enabled by default. It can be globally disabled
/// by simply adding
/// \code
/// #define PROFILE 0
/// \endcode
/// to the source file before including \c speedo.h.
/// \code
/// #define PROFILE 1
/// \endcode enables profiling again.
///
/// \note This class is not thread-safe. It is designed to be used with 
/// single-threaded programs.
class Speedo
{
private:
    std::deque<Checkpoint> checkpoints_;
    std::map<std::size_t, MultiMeasurement> measurement_map_; 

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
        // Copy the elements of the measurement map into a list 
        // that can be sorted.
        std::list<MultiMeasurement> measurement_list;
        std::map<std::size_t, MultiMeasurement>& measurement_map
            = get_instance().measurement_map_;
        std::map<std::size_t, MultiMeasurement>::const_iterator mit;
        for (mit = measurement_map.begin(); 
             mit != measurement_map.end(); 
             mit++)
        {
            measurement_list.push_back(mit->second);
        }

        // Sort the measurements based on their overall execution times,
        // starting with the largest value.
        measurement_list.sort();
        measurement_list.reverse();

        return measurement_list;
    }


public:
    /// Adds a measurement.
    static void tick(
                const std::string& file, int line, const std::string& function)
    {
        // If profiling is deactivated, abort.
        #if PROFILE <= 0
            return;
        #endif

        // Add the measurement point.
        std::deque<Checkpoint>& checkpoints = get_instance().checkpoints_;
        checkpoints.push_back(Checkpoint(file, line, function));
        
        if (checkpoints.size() >= 2)
        {
            SingleMeasurement measurement(checkpoints[0], checkpoints[1]);
            get_instance().measurement_map_[measurement.get_hash()].add(
                                                                measurement);
            checkpoints.pop_front();    
        }
    }


    /// Prints the statistics.
    static void print_statistics()
    {
        // If profiling is deactivated, abort.
        #if PROFILE <= 0
            return;
        #endif

        // Print the sorted list of all measurements.
        Printer printer;
        printer.add(sort_measurements());

        printer.print();
    }


    /// Saves a log file with the statistics under \c $HOME/.speedo/log.
    static void save_log()
    {
        // If profiling is deactivated, abort.
        #if PROFILE <= 0
            return;
        #endif

        Printer printer;
        printer.add(sort_measurements());

        printer.save_log();
    }
};


#endif
