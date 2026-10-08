#pragma once
#include <chrono>

class Stopwatch {
public:
    Stopwatch() = default;

    void resume() {
        if (!mIsRunning) {
            mStartTime = std::chrono::steady_clock::now();
            mIsRunning = true;
        }
    }

    void stop() {
        if (mIsRunning) {
            mTotalDuration += std::chrono::steady_clock::now() - mStartTime;
            mIsRunning = false;
        }
    }

    void reset() {
        mTotalDuration = std::chrono::steady_clock::duration::zero();
        mIsRunning = false;
    }

    int64_t elapsed_nano() const {
        auto total = mTotalDuration;
        if (mIsRunning) {
            total += std::chrono::steady_clock::now() - mStartTime;
        }
        return std::chrono::duration_cast<std::chrono::nanoseconds>(total).count();
    }

private:
    std::chrono::steady_clock::time_point mStartTime;
    std::chrono::steady_clock::duration mTotalDuration = std::chrono::steady_clock::duration::zero();
    bool mIsRunning = false;
};
