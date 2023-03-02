#ifndef CHECKPOINT_H
#define CHECKPOINT_H CHECKPOINT_H

// Boost timing.
// #include <boost/chrono.hpp>
#include <chrono>

// String streams.
#include <sstream>


/// Checkpoint used for measuring execution time. 
/// Objects of this class store all information necessary to identify 
/// a checkpoint: 
///  * the file where the checkpoint resides,
///  * the line where the checkpoint resides,
///  * the point in time when the checkpoint was hit.
class Checkpoint
{
protected:
    /// Name of the file the checkpoint resides in.
    std::string file_;

    /// Number of the line the checkpoint resides in.
    int line_;

    /// Name of the function the checkpoint resides in.
    std::string function_;

    /// Time stamp of the checkpoint.
    std::chrono::system_clock::time_point time_point_;


public:
    /// Constructor.
    /// Initializes the member variables.
    Checkpoint(const std::string& file, int line, const std::string& function)
        : file_(file),
          line_(line),
          function_(function),
          time_point_(std::chrono::system_clock::now())
    {
    }


    /// Compares the file and line of two checkpoints.
    bool operator==(const Checkpoint& rhs) const
    {
        return (file_ == rhs.file_ && line_ == rhs.line_);
    }


    /// Returns a string that contains the file and line of the checkpoint.
    /// Format: \c <file>:<line>.
    std::string get_file_line() const
    {
        std::stringstream stream;
        stream << file_ << ":" << line_;
        return stream.str();
    }


    /// Get the time the checkpoint was captured.
    std::chrono::system_clock::time_point get_time_point() const
    {
        return time_point_;
    }


    /// Get the file the checkpoint resides in.
    std::string get_file() const
    {
        return file_;
    }


    /// Get the line the checkpoint resides in.
    int get_line() const
    {
        return line_;
    }


    /// Get the function the checkpoint resides in.
    std::string get_function() const
    {
        return function_;
    }
};


#endif

