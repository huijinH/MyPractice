#include "mainwindow.h"
#include <QApplication>

#include <opencv2/opencv.hpp>

using namespace cv;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    cv::Mat img = imread("E:\\MyGitHub\\MyPractice\\TestOpencv\\images\\sky1.jpg");
    namedWindow("Qt OpenCV Test");
    imshow("Qt OpenCV Test", img);

    return a.exec();
}
