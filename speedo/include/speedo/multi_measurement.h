#ifndef MULTI_MEASUREMENT_H
#define MULTI_MEASUREMENT_H MULTI_MEASUREMENT_H

#include <vector>
#include "speedo/single_measurement.h"


/// Stores multiple execution time measurements and calculates their
/// average execution time.
class MultiMeasurement
{
protected:
    /// Vector containing single measurements that all started and ended
    /// at the same set of checkpoints.
    std::vector<SingleMeasurement> measurements_;


public:
    /// Adds a measurement to the vector of measurements.
    bool add(const SingleMeasurement& measurement)
    {
        // Check if the measurement starts and ends at the same checkpoints
        // as the other measurements in the vector.
        if (measurements_.size() > 0)
            if (measurement.get_hash() != measurements_[0].get_hash())
                return false;

        measurements_.push_back(measurement);
        return true;
    }


    /// Returns the checkpoint where the measurements started.
    Checkpoint get_start() const
    {
        if (measurements_.size() <= 0)
            return Checkpoint();

        return measurements_[0].get_start_checkpoint();
    }


    /// Returns the checkpoint where the measurements ended.
    Checkpoint get_end() const
    {
        if (measurements_.size() <= 0)
            return Checkpoint();

        return measurements_[0].get_end_checkpoint();
    }


    /// Returns the number of measurements.
    int count() const
    {
        return measurements_.size();
    }
    
    
    /// Computes the overall duration of all measurements.
    /// Unit: [µs].
    boost::chrono::microseconds get_overall_duration() const
    {
        boost::chrono::microseconds overall_duration(0);
        for (int i = 0; i < measurements_.size(); i++)
            overall_duration += measurements_[i].get_duration();
            
        return overall_duration;
    }


    /// Computes the average time of all measurements.
    /// Unit: [µs].
    boost::chrono::microseconds get_average_duration() const
    {
        boost::chrono::microseconds average_duration(get_overall_duration());
        
        if (measurements_.size() > 0)
            average_duration /= measurements_.size();
        
        return average_duration;
    }
    
    
    /// Compares measurements based on their overall time consumption.
    bool operator<(const MultiMeasurement& rhs) const
    {
        return get_overall_duration() < rhs.get_overall_duration();
    }
};


#endif
