#ifndef PRINTER_H
#define PRINTER_H PRINTER_H

#include <iomanip>
#include <sstream>
#include "speedo/multi_measurement.h"


/// Prints the statistics of the given measurements to the console.
class Printer
{
private:
    /// Measurements whose statistics to print.
    std::vector<MultiMeasurement> measurements_;

    /// Width of the output lines.
    static const int line_width         = 80;

    /// Width of the column indicating the file of a checkpoint.
    static const int file_header_width  = 30;

    /// Width of the column indicating the line of a checkpoint.
    static const int line_header_width  = 10;

    /// Width of the column indicating the count of a measurement.
    static const int count_header_width = 10;

    /// Width of the column indicating the duration of a measurement.
    static const int time_header_width  = 30;


public:
    /// Add a measurement whose statistics will be printed when print()
    /// is called.
    void add(const MultiMeasurement& measurement)
    {
        measurements_.push_back(measurement);
    }


    /// Prints the statistics of the given measurements.
    void print() const
    {
        print_title();
        print_header();

        for (int i = 0; i < measurements_.size(); i++)
        {
            print(measurements_[i]);
            print_hline((i < measurements_.size()-1) ? '-' : '#');
        }
    }


private:
    /// Prints a horizontal line consisting of the given character.
    static void print_hline(char fill = '#')
    {
        std::cerr << std::setfill(fill) << std::setw(line_width) << fill << std::endl;
    }


    /// Prints a heading.
    static void print_title()
    {
        const std::string title(" PROFILING WITH SPEEDO ");

        const char fill = '#';
        std::cerr << std::setfill(fill)
                  << std::setw(line_width) << fill << std::endl
                  << std::setw((line_width-title.length()) / 2) << fill << title
                  << (title.length() % 2 > 0 ? std::string(&fill) : "")
                  << std::setw((line_width-title.length()) / 2) << fill << std::endl
                  << std::setw(line_width) << fill << std::endl;
    }


    /// Prints the headers of all columns.
    static void print_header()
    {
        std::cerr << std::setfill(' ')
                  << std::setw(file_header_width)  << std::left << "File"
                  << std::setw(line_header_width)  << std::left << "|  Line"
                  << std::setw(count_header_width) << std::left << "|  Hits"
                  << "|" << std::setw(time_header_width-1) << std::right << "Average duration [us]"
                  << std::endl;

        print_hline('=');
    }


    /// Prints two rows for each measurement.
    static void print(const MultiMeasurement& measurement)
    {
        // Print where the measurement started.
        const std::string file_start(crop_path(measurement.get_start().get_file()));
        std::cerr << std::setfill(' ')
                  << std::setw(file_header_width) << std::left  << file_start
                  << "|" << std::setw(line_header_width-1)  << std::right
                  << measurement.get_start().get_line()
                  << "|" << std::setw(count_header_width-1) << std::right << " "
                  << "|" << std::endl;

        // Print where the measurement ended and how long it took.
        std::string file_end(crop_path(measurement.get_end().get_file()));
        if (file_start == file_end)
            file_end.clear();
        std::cerr << std::setw(file_header_width) << std::left  << file_end
                  << "|" << std::setw(line_header_width-1)  << std::right
                  << measurement.get_end().get_line()
                  << "|" << std::setw(count_header_width-1) << std::right
                  << measurement.count()
                  << "|" << std::setw(time_header_width-1)  << std::right
                  << insert_separators(measurement.get_average_duration().count())
                  << std::endl;
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
