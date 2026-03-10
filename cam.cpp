#include <opencv2/opencv.hpp>
#include <iostream>
#include <chrono>  // 新增：用于获取系统时间
#include <iomanip> // 新增：用于格式化时间 (put_time)
#include <sstream> // 新增：用于拼接字符串

using namespace cv;
using namespace std;

int main()
{
    cout << "Initializing cameras..." << endl;

    VideoCapture cap1(1, CAP_DSHOW);
    VideoCapture cap2(2, CAP_DSHOW);

    if (!cap1.isOpened())
    {
        cerr << "Error: Cannot open Camera 0!" << endl;
        return -1;
    }
    if (!cap2.isOpened())
    {
        cerr << "Error: Cannot open Camera 1!" << endl;
        return -1;
    }

    // 强制降低分辨率到 640x480
    cap1.set(CAP_PROP_FRAME_WIDTH, 640);
    cap1.set(CAP_PROP_FRAME_HEIGHT, 480);
    cap2.set(CAP_PROP_FRAME_WIDTH, 640);
    cap2.set(CAP_PROP_FRAME_HEIGHT, 480);

    Mat frame1, frame2;
    cap1 >> frame1;
    cap2 >> frame2;

    if (frame1.empty() || frame2.empty())
    {
        cerr << "Error: Cameras opened, but frames are empty. Check USB connection." << endl;
        return -1;
    }

    cout << "Cameras successfully connected! Resolution: "
         << frame1.cols << "x" << frame1.rows << endl;

    // ==========================================
    // 核心新增：获取当前时间并生成文件名
    // ==========================================
    auto now = chrono::system_clock::now();
    time_t now_c = chrono::system_clock::to_time_t(now);
    tm *now_tm = localtime(&now_c);

    ostringstream oss;
    // 使用 %Y%m%d%H%M 格式化时间为 年月日时分，例如 202603082334
    oss << put_time(now_tm, "%Y%m%d%H%M") << ".mp4";
    string filename = oss.str();
    // ==========================================

    Size combinedSize(frame1.cols * 2, frame1.rows);
    int fourcc = VideoWriter::fourcc('m', 'p', '4', 'v');

    // 将动态生成的文件名传入 VideoWriter
    VideoWriter writer(filename, fourcc, 30.0, combinedSize);

    if (!writer.isOpened())
    {
        cerr << "Error: Failed to create MP4 file!" << endl;
        return -1;
    }

    // 打印出即将保存的文件名，方便确认
    cout << "Recording to: " << filename << endl;
    cout << "Press 'ESC' on the video window to stop." << endl;

    Mat frame2_resized, combinedFrame;

    while (true)
    {
        cap1 >> frame1;
        cap2 >> frame2;

        if (frame1.empty() || frame2.empty())
        {
            cerr << "Warning: Dropped frame." << endl;
            break;
        }

        if (frame1.size() != frame2.size())
        {
            resize(frame2, frame2_resized, frame1.size());
        }
        else
        {
            frame2_resized = frame2;
        }

        hconcat(frame1, frame2_resized, combinedFrame);

        imshow("Dual Camera Preview", combinedFrame);
        writer.write(combinedFrame);

        if (waitKey(30) == 27)
        {
            cout << "User stopped the recording." << endl;
            break;
        }
    }

    cap1.release();
    cap2.release();
    writer.release();
    destroyAllWindows();

    cout << "Video saved successfully!" << endl;
    return 0;
}