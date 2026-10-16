#include "frame_queue.hpp"

FrameQueue::FrameQueue(std::size_t maxSize)
    : maxSize_(maxSize) {
}

void FrameQueue::push(cv::Mat frame) {
    {
        std::lock_guard<std::mutex> lock(mutex);

        if (frames.size() >= maxSize) {
            frames.pop();
        }

        frames.push(frame);
    }

    condition.notify_one();
}

cv::Mat FrameQueue::pop() {
    {
        std::lock_guard<std::mutex> lock(mutex);

        while (frames.empty()) {
            condition.wait(lock);
        }

        cv::Mat frame = frames.front();
        frames.pop();
        return frame;
    }
}