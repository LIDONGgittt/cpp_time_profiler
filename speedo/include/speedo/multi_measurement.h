#ifndef MULTI_MEASUREMENT_H
#define MULTI_MEASUREMENT_H MULTI_MEASUREMENT_H

#include "speedo/single_measurement.h"


/// Saves the statistics of multiple execution time measurements that have the
/// same start checkpoint and the same end checkpoint.
class MultiMeasurement
{
protected:
    /// Hash that uniquely identifies the combination of start checkpoint and
    /// end checkpoint. 
    std::size_t hash_;

    /// Name of the file where the start checkpoint resides.
    std::string start_file_;

    /// Name of the function where the start checkpoint resides.
    std::string start_function_;

    /// Number of the line where the start checkpoint resides.
    int start_line_;

    /// Name of the file where the end checkpoint resides.
    std::string end_file_;

    /// Name of the function where the end checkpoint resides.
    std::string end_function_;

    /// Number of the line where the end checkpoint resides.
    int end_line_;

    /// Number of single measurements collected by this object.
    int count_;

    /// Sum of the durations of all measurements collected by this object.
    boost::chrono::microseconds overall_duration_;

public:
    /// Default constructor.
    /// Initializes the member variables to 0.
    MultiMeasurement()
        : hash_(0),
          start_line_(0),
          end_line_(0),
          count_(0),
          overall_duration_(0)
    {
    }


    /// Collects a measurement.
    /// \return \c true if the hash of the measurement matches the hash of 
    /// the measurements collected so far.
    bool add(const SingleMeasurement& measurement)
    {
        // If no measurement has been collected so far, define the member
        // variables.
        if (hash_ == 0)
        {
            hash_           = measurement.get_hash();
            start_file_     = measurement.get_start_checkpoint().get_file();
            start_function_ = measurement.get_start_checkpoint().get_function();
            start_line_     = measurement.get_start_checkpoint().get_line();
            end_file_       = measurement.get_end_checkpoint().get_file();
            end_function_   = measurement.get_end_checkpoint().get_function();
            end_line_       = measurement.get_end_checkpoint().get_line();
        }

        // Check if the measurement starts and ends at the same checkpoints
        // as the other measurements that have been collected.
        if (hash_ != measurement.get_hash()) 
            return false;

        // Update the statistics.
        count_++;
        overall_duration_ += measurement.get_duration();

        return true;
    }


    /// Returns the number of measurements.
    int count() const
    {
        return count_;
    }
    
    
    /// Returns the overall duration of all measurements.
    /// Unit: [us].
    boost::chrono::microseconds get_overall_duration() const
    {
        return overall_duration_;
    }


    /// Computes the average duration of all measurements.
    /// Unit: [us].
    boost::chrono::microseconds get_average_duration() const
    {
        boost::chrono::microseconds average_duration(overall_duration_);
        
        if (count_ > 0)
            average_duration /= count_;
        
        return average_duration;
    }
    
    
    /// Compares measurements based on their overall time consumption.
    bool operator<(const MultiMeasurement& rhs) const
    {
        return get_overall_duration() < rhs.get_overall_duration();
    }


    /// Returns the hash of the measurements collected so far.
    /// If no measurements have been collected, 0 is returned.
    std::size_t get_hash() const
    {
        return hash_;
    }


    /// Returns the file where the start checkpoint resides.
    std::string get_start_file() const
    {
        return start_file_;
    }


    /// Returns the function where the start checkpoint resides.
    std::string get_start_function() const
    {
        return start_function_;
    }


    /// Returns the number of the line where the start checkpoint resides.
    int get_start_line() const
    {
        return start_line_;
    }


    /// Returns the file where the end checkpoint resides.
    std::string get_end_file() const
    {
        return end_file_;
    }


    /// Returns the function where the end checkpoint resides.
    std::string get_end_function() const
    {
        return end_function_;
    }

    
    /// Returns the number of the line where the end checkpoint resides.
    int get_end_line() const
    {
        return end_line_;
    }
};


#endif

