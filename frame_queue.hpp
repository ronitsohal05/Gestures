#pragma once

#include <opencv2/opencv.hpp>
#include <queue>
#include <mutex>
#include <condition_variable>

class FrameQueue {
    public:
        explicit FrameQueue(std::size_t maxSize);

        void push(cv::Mat frame);
        cv::Mat pop();

    private:
        std::queue<cv::Mat> frames;
        std::size_t maxSize;

        std::mutex mutex;
        std::condition_variable condition;
};