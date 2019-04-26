/*
 * Frame Processing Class
 */
#ifndef FRAME_PROCESSOR
#define FRAME_PROCESSOR

#include <fstream>
#include <list>
#include <opencv2/opencv.hpp>

class FrameProcessor {
public:
	FrameProcessor(std::string path = "", int height = 1, int width = 1);
	bool FrameToGray(std::string path = "");
	bool GrayToGrid(int height = 0, int width = 0);
	std::string* FrameProcessor::GridToCSV(const std::string& timeStamp);

private:
	std::string framePath;
	cv::Mat grayFrame;
	int gridCols;
	int gridRows;
	std::list<cv::Mat> gridList;
};

#endif
