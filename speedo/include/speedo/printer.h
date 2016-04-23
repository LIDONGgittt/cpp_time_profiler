#ifndef PRINTER_H
#define PRINTER_H PRINTER_H

#include <string>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <list>

#include <boost/filesystem.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/date_time/posix_time/posix_time_io.hpp>

#include "speedo/multi_measurement.h"


/// Prints the statistics of the given measurements to the console.
class Printer
{
private:
    /// Measurements whose statistics to print.
    std::vector<MultiMeasurement> measurements_;

    /// Width of the output lines.
    static const int line_width              = 80;

    /// Width of the column indicating the file of a checkpoint.
    static const int file_col_width          = 30;

    /// Width of the column indicating the line of a checkpoint.
    static const int line_col_width          =  6;

    /// Width of the column indicating the count of a measurement.
    static const int count_col_width         = 10;

    /// Width of the column indicating the average duration of a measurement.
    static const int avg_duration_col_width  = 15;

    /// Width of the column indicating the overall duration of a measurement.
    static const int ovr_duration_col_width  = 15;


public:
    /// Adds a measurement whose statistics will be printed when print()
    /// is called.
    void add(const MultiMeasurement& measurement)
    {
        measurements_.push_back(measurement);
    }


    /// Adds a list of measurements whose statistics will be printed when
    /// print() is called.
    void add(const std::list<MultiMeasurement>& measurements)
    {
        std::list<MultiMeasurement>::const_iterator lit;
        for (lit = measurements.begin(); lit != measurements.end(); lit++)
            add(*lit);
    }


    /// Prints the statistics of the given measurements.
    void print() const
    {
        std::cerr << create_table();
    }


    /// Creates a table that shows the statistics of the given measurements.
    std::string create_table() const
    {
        // If no measurements are given, return an empty string.
        if (measurements_.size() <= 0)
            return std::string();

        std::stringstream stream;
        stream << create_title() << create_header();

        for (int i = 0; i < measurements_.size(); i++)
        {
            stream << create_entry(measurements_[i]);
            stream << create_hline((i < measurements_.size()-1) ? '-' : '#');
        }

        return stream.str();
    }


    /// Saves the current profiling information to \c $HOME/.speedo/log.
    void save_log() const
    {
        // If no measurements are given, abort.
        if (measurements_.size() <= 0)
            return;

        // Create the folder name.
        std::stringstream folder_name;
        folder_name << getenv("HOME") << "/.speedo/log";
        boost::filesystem::path folder_path(folder_name.str());

        // Create the folder.
        boost::filesystem::create_directories(folder_path);

        // Create the name of the log file from the current date and time.
        std::stringstream file_name;
        boost::posix_time::time_facet* facet(
                        new boost::posix_time::time_facet("%Y%m%d-%H%M%S"));
        file_name.imbue(std::locale(file_name.getloc(), facet));
        file_name << boost::posix_time::second_clock::local_time() << ".log";

        // Save the log file.
        std::ofstream logfile;
        logfile.open(std::string(boost::filesystem::canonical(folder_path).string()
                                 + "/" + file_name.str()).c_str());
        logfile << create_table();
        logfile.close();
    }


private:
    /// Generates a string containing a horizontal line
    /// consisting of the given character.
    static std::string create_hline(char fill = '#')
    {
        std::stringstream stream;
        stream << std::setfill(fill) << std::setw(line_width) << fill << std::endl;
        return stream.str();
    }


    /// Generates a string containing the profiler's heading.
    static std::string create_title()
    {
        const std::string title(" PROFILING WITH SPEEDO ");

        const char fill = '#';
        std::stringstream stream;
        stream << std::setfill(fill)
               << std::setw(line_width) << fill << std::endl
               << std::setw((line_width-title.length()) / 2) << fill << title
               << (title.length() % 2 > 0 ? std::string(1, fill) : "")
               << std::setw((line_width-title.length()) / 2) << fill << std::endl
               << std::setw(line_width) << fill << std::endl;

        return stream.str();
    }


    /// Generates a string with the headers of all columns.
    static std::string create_header()
    {
        std::stringstream stream;
        stream << std::setfill(' ')
               << std::setw(file_col_width)         << std::left
               << "File"                            << "|"
               << std::setw(line_col_width)         << std::right
               << "Line "                           << "|"
               << std::setw(count_col_width)        << std::right
               << "Count "                          << "|"
               << std::setw(avg_duration_col_width) << std::right
               << "Average [us] "                   << "|"
               << std::setw(ovr_duration_col_width) << std::right
               << "Overall [us]"
               << std::endl
               << create_hline('=');

        return stream.str();
    }


    /// Generates a table entry for the given measurement.
    static std::string create_entry(const MultiMeasurement& measurement)
    {
        // Create a line indicating where the measurement started.
        const std::string file_start(crop_path(measurement.get_start_file()));
        std::stringstream stream;
        stream << std::setfill(' ')
               << std::setw(file_col_width)          << std::left
               << file_start                         << "|"
               << std::setw(line_col_width)          << std::right
               << measurement.get_start_line()       << "|"
               << std::setw(count_col_width)         << std::right
               << " "                                << "|"
               << std::setw(avg_duration_col_width)  << std::right
               << " "                                << "|"
               << std::endl;

        // Show the file name in the second line only if it
        // is a different file.
        std::string file_end(crop_path(measurement.get_end_file()));
        if (file_start == file_end)
            file_end.clear();

        // Create a line indicating where the measurement ended
        // and how long it took.
        stream << std::setfill(' ')
               << std::setw(file_col_width)                  << std::left
               << file_end                                   << "|"
               << std::setw(line_col_width)                  << std::right
               << measurement.get_end_line()                 << "|"
               << std::setw(count_col_width)                 << std::right
               << measurement.count()                        << "|"
               << std::setw(avg_duration_col_width)          << std::right
               << insert_separators(measurement.get_average_duration().count()) << "|"
               << std::setw(ovr_duration_col_width)          << std::right
               << insert_separators(measurement.get_overall_duration().count())
               << std::endl;

        return stream.str();
    }


    /// Cuts the given file path after the last slash and returns the file name.
    static std::string crop_path(const std::string& file_name)
    {
        std::size_t slash_position = file_name.find_last_of("/\\");
        return file_name.substr(slash_position + 1);
    }


    /// Inserts thousands separators into the given number.
    static std::string insert_separators(long int n)
    {
        std::stringstream stream;
        stream << n;
        const std::string n_str = stream.str();

        stream.str("");
        for (int pos = 0; pos < n_str.length(); pos++)
        {
            stream << n_str.at(pos);

            if ((n_str.length()-1-pos) >= 3
                && (n_str.length()-1-pos) % 3 == 0)
                stream << ",";
        }

        return stream.str();
    }
};


#endif
