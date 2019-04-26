/*
 * Frame Processing function definitions
 */

#include <stdio.h>
#include "FrameProcessor.h"

FrameProcessor::FrameProcessor(std::string path, int cols, int rows) {
	framePath = path;
	gridCols = cols;
	gridRows = rows;
}

bool FrameProcessor::FrameToGray(std::string path) {
	if ("" != path) {
		framePath = path;
	}
	if ("" == framePath)
		return false;

	cv::Mat frame;
	frame = cv::imread(framePath, cv::IMREAD_COLOR);
	if (!frame.data)
		return false;

	cv::cvtColor(frame, grayFrame, cv::COLOR_BGR2GRAY);
	return true;
}

bool FrameProcessor::GrayToGrid(int cols, int rows) {
	if (rows)
		gridRows = rows;
	if (cols)
		gridCols = cols;

	if (gridRows < 1 || gridCols < 1)
		return false;

	int rowSpan = grayFrame.rows / gridRows;
	int colSpan = grayFrame.cols / gridCols;
	for (int row = 0; row < grayFrame.rows; row += rowSpan) {
		for (int col = 0; col < grayFrame.cols; col += colSpan) {
			cv::Mat cell = grayFrame(
				cv::Range(row, cv::min(row + rowSpan, grayFrame.rows)),
				cv::Range(col, cv::min(col + colSpan, grayFrame.cols))).clone();
			gridList.push_back(cell);
		}
	}
	return true;
}

std::string* FrameProcessor::GridToCSV(const std::string& timeStamp) {
	std::string* csvString = new std::string(timeStamp);
	int median = 0;
	for (auto i : gridList) {
		int val = 0;
		for (int row = 0; row < i.rows; row++) {
			for (int col = 0; col < i.cols; col++) {
				val += (int)i.at<uchar>(row, col);
			}
		}
		median = val / (i.rows * i.cols);
		csvString->append("," + std::to_string(median));
	}
	csvString->append("\n");
	return csvString;
}
