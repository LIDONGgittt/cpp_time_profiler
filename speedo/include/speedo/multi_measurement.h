#ifndef MULTI_MEASUREMENT_H
#define MULTI_MEASUREMENT_H MULTI_MEASUREMENT_H

#include "speedo/single_measurement.h"


/// Saves the statistics of multiple execution time measurements that have the
/// same start checkpoint and the same end checkpoint.
class MultiMeasurement
{
protected:
    std::size_t hash_;
    std::string start_file_;
    std::string start_function_;
    int start_line_;
    std::string end_file_;
    std::string end_function_;
    int end_line_;
    int count_;
    boost::chrono::microseconds overall_duration_;

public:
    MultiMeasurement()
        : hash_(0),
          count_(0),
          overall_duration_(0)
    {
    }


    /// Adds a measurement to the vector of measurements.
    bool add(const SingleMeasurement& measurement)
    {
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
        // as the other measurements in the vector.
        if (hash_ != measurement.get_hash()) 
            return false;

        count_++;
        overall_duration_ += measurement.get_duration();

        return true;
    }


    /// Returns the number of measurements.
    int count() const
    {
        return count_;
    }
    
    
    /// Computes the overall duration of all measurements.
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


    std::size_t get_hash() const
    {
        return hash_;
    }


    std::string get_start_file() const
    {
        return start_file_;
    }


    std::string get_start_function() const
    {
        return start_function_;
    }


    int get_start_line() const
    {
        return start_line_;
    }


    std::string get_end_file() const
    {
        return end_file_;
    }


    std::string get_end_function() const
    {
        return end_function_;
    }

    
    int get_end_line() const
    {
        return end_line_;
    }
};


#endif

