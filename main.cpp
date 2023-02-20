#include "time_measurement.h"
#include <iostream>

int main() {
    constexpr int SAMPLES = 10;
    constexpr int MIN_SIZE = 20000;
    constexpr int MAX_SIZE = MIN_SIZE * 10;
    const std::string FILENAME = "results.txt";
    Time_measurement test(MIN_SIZE, MAX_SIZE, SAMPLES, FILENAME);

    test.measure(Algorithm::selection_sort, Data_series::random);
    test.measure(Algorithm::selection_sort, Data_series::monotonic_rising);
    test.measure(Algorithm::selection_sort, Data_series::monotonic_falling);
    test.measure(Algorithm::selection_sort, Data_series::constant);

    test.measure(Algorithm::insertion_sort, Data_series::random);
    test.measure(Algorithm::insertion_sort, Data_series::monotonic_rising);
    test.measure(Algorithm::insertion_sort, Data_series::monotonic_falling);
    test.measure(Algorithm::insertion_sort, Data_series::constant);

    test.measure(Algorithm::quicksort_right, Data_series::random);
    test.measure(Algorithm::quicksort_right, Data_series::monotonic_rising);
    test.measure(Algorithm::quicksort_right, Data_series::monotonic_falling);
    test.measure(Algorithm::quicksort_right, Data_series::constant);

    test.measure(Algorithm::quicksort_median_of_three, Data_series::random);
    test.measure(Algorithm::quicksort_median_of_three, Data_series::monotonic_rising);
    test.measure(Algorithm::quicksort_median_of_three, Data_series::monotonic_falling);
    test.measure(Algorithm::quicksort_median_of_three, Data_series::constant);

    test.measure(Algorithm::stl_sort, Data_series::random);
    test.measure(Algorithm::stl_sort, Data_series::monotonic_rising);
    test.measure(Algorithm::stl_sort, Data_series::monotonic_falling);
    test.measure(Algorithm::stl_sort, Data_series::constant);

    return 0;
}