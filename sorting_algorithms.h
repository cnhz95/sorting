#ifndef SORTING_SORTING_ALGORITHMS_H
#define SORTING_SORTING_ALGORITHMS_H

#include <algorithm>

template<typename FwdIt>
void selection_sort(FwdIt first, FwdIt last) {
    for (FwdIt it = first; it != last; it++) {
        FwdIt selection = std::min_element(it, last);
        std::iter_swap(it, selection);
    }
}

template<typename FwdIt>
void insertion_sort(FwdIt first, FwdIt last) {
    for (FwdIt it = first; it != last; it++) {
        FwdIt insertion = std::upper_bound(first, it, *it);
        std::rotate(insertion, it, std::next(it));
    }
}

template<typename FwdIt>
FwdIt median_of_three(FwdIt first, FwdIt last) {
    FwdIt mid = first + (std::distance(first, last) >> 1);
    if (*last < *first) {
        std::iter_swap(last, first);
    }
    if (*mid < *first) {
        std::iter_swap(mid, first);
    }
    if (*last < *mid) {
        std::iter_swap(last, mid);
    }
    return mid;
}

template<typename FwdIt>
FwdIt partition(FwdIt first, FwdIt last, FwdIt pivot) {
    FwdIt p = first;
    for (FwdIt i = first; i != last; i++) {
        if (*i < *pivot) {
            std::iter_swap(i, p++);
        }
    }
    std::iter_swap(pivot, p);
    return p;
}

template<typename FwdIt>
void quicksort_right(FwdIt first, FwdIt last) {
    if (first != last) { // Empty
        FwdIt pivot = partition(first, std::prev(last), std::prev(last));
        quicksort_right(first, pivot);
        quicksort_right(std::next(pivot), last);
    }
}

template<typename FwdIt>
void quicksort_median_of_three(FwdIt first, FwdIt last) {
    if (first != last) {
        FwdIt median = median_of_three(first, std::prev(last));
        FwdIt pivot = partition(first, std::prev(last), median);
        quicksort_median_of_three(first, pivot);
        quicksort_median_of_three(std::next(pivot), last);
    }
}

#endif