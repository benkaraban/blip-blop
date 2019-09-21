#pragma once

#include <numeric>
#include <vector>

template <class T>
class MovingAverage {
   private:
    std::vector<T> hist_;
    int idx_;

   public:
    MovingAverage(int hist_size) : hist_(hist_size, 0), idx_(0) {}

    void Add(T val) {
        hist_[idx_] = val;
        idx_ = (idx_ + 1) % hist_.size();
    }

    T average() const {
        return std::accumulate(hist_.begin(), hist_.end(), 0);
    }
};
