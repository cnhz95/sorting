#include "time_measurement.h"
#include <iostream>
#include <iomanip>
#include <numeric>
#include <cmath>

Time_measurement::Time_measurement(int min, int max, int samples, const std::string& filename)
    : m_min_size(min), m_max_size(max), m_sample_size(samples), m_file(filename), m_total_intervals(min / 200), m_generator(max) {}

void Time_measurement::measure(const Algorithm& sorting, const Data_series& series) {
    for (int size = m_min_size; size <= m_max_size; size += m_min_size) {
        for (int sample = 0; sample < m_sample_size; sample++) {
            switch (series) {
                case Data_series::random:
                    m_data = m_generator.random_data(size);
                    break;
                case Data_series::monotonic_rising:
                    m_data = m_generator.monotonic_data(size, Order::rising);
                    break;
                case Data_series::monotonic_falling:
                    m_data = m_generator.monotonic_data(size, Order::falling);
                    break;
                case Data_series::constant:
                    m_data = m_generator.constant_data(size);
                    break;
            }
            int intervals_left = m_total_intervals;
            const int interval_size = size / m_total_intervals;
            switch (sorting) {
                case Algorithm::selection_sort:
                    m_start = std::chrono::steady_clock::now();
                    for (m_low = m_data.begin(), m_high = m_low + interval_size; --intervals_left; m_low = m_high, m_high += interval_size) {
                        selection_sort(m_low, m_high);
                    }
                    m_end = std::chrono::steady_clock::now();
                    break;
                case Algorithm::insertion_sort:
                    if (series == Data_series::constant) {
                        m_start = std::chrono::steady_clock::now();
                        insertion_sort(m_data.begin(), m_data.end());
                        m_end = std::chrono::steady_clock::now();
                    }
                    else {
                        m_start = std::chrono::steady_clock::now();
                        for (m_low = m_data.begin(), m_high = m_low + interval_size; --intervals_left; m_low = m_high, m_high += interval_size) {
                            insertion_sort(m_low, m_high);
                        }
                        m_end = std::chrono::steady_clock::now();
                    }
                    break;
                case Algorithm::quicksort_right:
                    if (series == Data_series::random) {
                        m_start = std::chrono::steady_clock::now();
                        quicksort_right(m_data.begin(), m_data.end());
                        m_end = std::chrono::steady_clock::now();
                    }
                    else {
                        m_start = std::chrono::steady_clock::now();
                        for (m_low = m_data.begin(), m_high = m_low + interval_size; --intervals_left; m_low = m_high, m_high += interval_size) {
                            quicksort_right(m_low, m_high);
                        }
                        m_end = std::chrono::steady_clock::now();
                    }
                    break;
                case Algorithm::quicksort_median_of_three:
                    if (series == Data_series::constant) {
                        m_start = std::chrono::steady_clock::now();
                        for (m_low = m_data.begin(), m_high = m_low + interval_size; --intervals_left; m_low = m_high, m_high += interval_size) {
                            quicksort_median_of_three(m_low, m_high);
                        }
                        m_end = std::chrono::steady_clock::now();
                    }
                    else {
                        m_start = std::chrono::steady_clock::now();
                        quicksort_median_of_three(m_data.begin(), m_data.end());
                        m_end = std::chrono::steady_clock::now();
                    }
                    break;
                case Algorithm::stl_sort:
                    m_start = std::chrono::steady_clock::now();
                    std::sort(m_data.begin(), m_data.end());
                    m_end = std::chrono::steady_clock::now();
                    break;
            }
            m_duration = m_end - m_start;
            m_times.push_back(m_duration.count());
        }
        m_results.push_back({ size, mean(), std_dev() });
        m_times.clear();
    }
    export_data(sorting, series);
    m_results.clear();
}

double Time_measurement::mean() {
    return m_mean_calc = std::accumulate(m_times.begin(), m_times.end(), 0.0) / m_sample_size;
}

double Time_measurement::std_dev() {
    double square_sum = std::accumulate(m_times.begin(), m_times.end(), 0.0, [=](double sum, const double x) -> double {
        return sum += std::pow(x - m_mean_calc, 2);
    });
    return std::sqrt(1.0 / (m_sample_size - 1) * square_sum);
}

void Time_measurement::export_data(const Algorithm& sorting, const Data_series& series) {
    if (!m_file) {
        std::cerr << "The output file couldn't be opened!\n";
        return;
    }
    switch (sorting) {
        case Algorithm::selection_sort:
            m_file << "Selection sort ";
            break;
        case Algorithm::insertion_sort:
            m_file << "Insertion sort ";
            break;
        case Algorithm::quicksort_right:
            m_file << "Quicksort right element ";
            break;
        case Algorithm::quicksort_median_of_three:
            m_file << "Quicksort median of three ";
            break;
        case Algorithm::stl_sort:
            m_file << "STL sort ";
            break;
    }
    switch (series) {
        case Data_series::random:
            m_file << "[Random]\n";
            break;
        case Data_series::monotonic_rising:
            m_file << "[Monotonic rising]\n";
            break;
        case Data_series::monotonic_falling:
            m_file << "[Monotonic falling]\n";
            break;
        case Data_series::constant:
            m_file << "[Constant]\n";
            break;
    }
    m_file << "N\t\tT[s]\t\tStdev[s]\tSamples\n";
    std::for_each(m_results.begin(), m_results.end(), [&](const Result& elem) -> void {
        m_file << std::setprecision(5) << std::fixed << elem.size << "\t\t"
               << elem.mean << "\t\t" << elem.std_dev << "\t\t" << m_sample_size << '\n';
    });
    m_file << '\n';
}