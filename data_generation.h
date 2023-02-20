#ifndef SORTING_DATA_GENERATION_H
#define SORTING_DATA_GENERATION_H

#include <algorithm>
#include <chrono>
#include <random>
#include <vector>

enum class Order {
    rising, falling
};

class Data_generator {
public:
    explicit Data_generator(int max);

    std::vector<int> random_data(size_t size);
    std::vector<int> monotonic_data(size_t size, const Order& order);
    std::vector<int> constant_data(size_t size);

private:
    std::mt19937 m_rng;
    std::uniform_int_distribution<int> m_uid;
};

#endif