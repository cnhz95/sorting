#include "data_generation.h"

Data_generator::Data_generator(int max)	: m_uid(0, max),
    m_rng((uint32_t)std::chrono::steady_clock::now().time_since_epoch().count()) {}

std::vector<int> Data_generator::random_data(size_t size) {
    std::vector<int> data(size);
    for (int& elem : data) {
        elem = m_uid(m_rng);
    }
    return data;
}

std::vector<int> Data_generator::monotonic_data(size_t size, const Order& order) {
    std::vector<int> data(size);
    for (size_t i = 0; i < size; i++) {
        data[i] = i << 1;
    }
    if (order == Order::falling) {
        std::reverse(data.begin(), data.end());
    }
    return data;
}

std::vector<int> Data_generator::constant_data(size_t size) {
    std::vector<int> data(size);
    const int VAL = m_uid(m_rng);
    std::for_each(data.begin(), data.end(), [VAL](int& elem) -> void {
        elem = VAL;
    });
    return data;
}