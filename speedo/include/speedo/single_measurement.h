#ifndef SINGLE_MEASUREMENT_H
#define SINGLE_MEASUREMENT_H SINGLE_MEASUREMENT_H

// Boost hash generation.
#include <boost/functional/hash.hpp>

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


    /// Returns a hash value that maps the file and line values of both
    /// the start and the end measurement to a string.
    /// This hash uniquely identifies every combination of two checkpoints.
    std::size_t get_hash() const
    {
        boost::hash<std::string> hash;
        return hash(start_checkpoint_.get_file_line()
                    + end_checkpoint_.get_file_line());
    }


    /// Get the time that expired between the start checkpoint and the
    /// end checkpoint.
    /// Unit: [us].
    boost::chrono::microseconds get_duration() const
    {
        return boost::chrono::duration_cast<boost::chrono::microseconds>(
                                        end_checkpoint_.get_time_point()
                                        - start_checkpoint_.get_time_point());
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

