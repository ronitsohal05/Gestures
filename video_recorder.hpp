#include <opencv2/opencv.hpp>
#include <iostream>
#include <stdio.h>
#include "frame_queue.hpp"


void flipHorizontal(cv::Mat& image);
int runCamera(FrameQueue& frameQueue, std::atomic<bool>& running);