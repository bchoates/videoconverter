/*
 * Frame Processing class
 */

#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <fstream>

bool FrameToCSV(cv::Mat frame);
bool FrameToGrid(cv::Mat frame);
bool GridToMedian();
bool MedianToCSV(std::string& csvString);
