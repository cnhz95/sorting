#ifndef SORTING_TIME_MEASUREMENT_H
#define SORTING_TIME_MEASUREMENT_H

#include "data_generation.h"
#include "sorting_algorithms.h"
#include <chrono>
#include <functional>
#include <fstream>

enum class Algorithm {
    selection_sort, insertion_sort, quicksort_right, quicksort_median_of_three, stl_sort
};

enum class Data_series {
    random, monotonic_rising, monotonic_falling, constant
};

struct Result {
    int size;
    double mean;
    double std_dev;
};

class Time_measurement {
public:
    Time_measurement(int min, int max, int samples, const std::string& filename);
    void measure(const Algorithm& sorting, const Data_series& series);

private:
    double mean();
    double stdev();
    void export_data(const Algorithm& sorting, const Data_series& series);

    int m_min_size;
    int m_max_size;
    int m_sample_size;
    int m_total_intervals;
    double m_mean_calc{};

    std::ofstream m_file;
    Data_generator m_generator;
    std::vector<int> m_data;
    std::vector<double> m_times;
    std::vector<Result> m_results;

    std::chrono::time_point<std::chrono::steady_clock> m_start;
    std::chrono::time_point<std::chrono::steady_clock> m_end;
    std::chrono::duration<double> m_duration{};
    std::vector<int>::iterator m_low;
    std::vector<int>::iterator m_high;
};

#endif