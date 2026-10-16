#include "video_recorder.hpp"
#include "frame_queue.hpp"

using namespace cv;
using namespace std;

void mirrorFrame(Mat& frame) {
    for (int row = 0; row < frame.rows; ++row) {
        for (int col = 0; col < frame.cols / 2; ++col) {
            Vec3b& leftPixel = frame.at<Vec3b>(row, col);
            Vec3b& rightPixel = frame.at<Vec3b>(row, frame.cols - col - 1);
            swap(leftPixel, rightPixel);
        }
    }
}

int runCamera(FrameQueue& frameQueue, std::atomic<bool>& running) {
    Mat frame;
    // INITIALIZE VIDEOCAPTURE
    VideoCapture cap;
    // open the default camera using default API
    // cap.open(0);
    // OR advance usage: select any API backend
    int deviceID = 0;             // 0 = open default camera
    int apiID = cv::CAP_ANY;      // 0 = autodetect default API
    // open selected camera using selected API
    cap.open(deviceID, apiID);
    // check if we succeeded
    if (!cap.isOpened()) {
        cerr << "ERROR! Unable to open camera\n";
        return -1;
    }

    // GRAB AND WRITE LOOP
    cout << "Start grabbing" << endl
        << "Press any key to terminate" << endl;

    while (running) {

        // wait for a new frame from camera and store it into 'frame'
        bool success = cap.read(frame);

        // check if read succeeded
        if (!success) {
            cerr << "ERROR! cap.read() failed\n";
            break;
        }

        // check if frame is empty
        if (frame.empty()) {
            cerr << "ERROR! blank frame grabbed\n";
            break;
        }
        
        //reflect the frame horizontally to create a mirror effect
        mirrorFrame(frame);

        frameQueue.push(frame.clone());
    }
    // the camera will be deinitialized automatically in VideoCapture destructor
    return 0;
}