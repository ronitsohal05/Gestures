#include "video_recorder.hpp"
#include "frame_queue.hpp"

#include <opencv2/opencv.hpp>

#include <functional>
#include <atomic>
#include <thread>

int main() {
    FrameQueue frameQueue(10);
    std::atomic<bool> running{true};

    std::thread cameraThread(runCamera, std::ref(frameQueue), std::ref(running));

    while (running) {
        cv::Mat frame = frameQueue.pop();

        cv::imshow("Live", frame);

        if (cv::waitKey(5) >= 0) {
            running = false;
        }
    }

    cameraThread.join();
    return 0;
}