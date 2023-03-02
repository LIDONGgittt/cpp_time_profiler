#ifndef SINGLE_MEASUREMENT_H
#define SINGLE_MEASUREMENT_H SINGLE_MEASUREMENT_H

#include <functional>
#include <chrono>

// Checkpoint class.
#include "speedo/checkpoint.h"


/// Measurement of the execution time that passed between two checkpoints.
class SingleMeasurement
{
protected:
    /// Start of the measurement.
    Checkpoint start_checkpoint_;

    /// End of the measurement.
    Checkpoint end_checkpoint_;


public:
    /// Constructor.
    SingleMeasurement(const Checkpoint& start_checkpoint,
                      const Checkpoint& end_checkpoint)
        : start_checkpoint_(start_checkpoint),
          end_checkpoint_(end_checkpoint)
    {
    }


    /// Returns a hash value that is generated from the file and line values 
    /// of both the start and the end measurement.
    /// Thus, this hash uniquely identifies every combination 
    /// of two checkpoints.
    std::size_t get_hash() const
    {
        std::hash<std::string> hash;
        return hash(start_checkpoint_.get_file_line()
                    + end_checkpoint_.get_file_line());
    }


    /// Get the time that expired between the start checkpoint and the
    /// end checkpoint.
    /// Unit: [us].
    std::chrono::microseconds get_duration() const
    {
        return std::chrono::duration_cast<std::chrono::microseconds>(
         end_checkpoint_.get_time_point() - start_checkpoint_.get_time_point());
    }


    /// Returns the checkpoint where the measurement of execution time started.
    Checkpoint get_start_checkpoint() const
    {
        return start_checkpoint_;
    }


    /// Returns the checkpoint where the measurement of execution time ended.
    Checkpoint get_end_checkpoint() const
    {
        return end_checkpoint_;
    }
};


#endif

