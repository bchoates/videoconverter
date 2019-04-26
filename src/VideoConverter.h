/*
 * Video Converter 
 */
#include <fstream>
#include "FrameProcessor.h"
#include "KeyframeExtractor.h"

std::string* FrameToCSV(const std::string& framePath, const std::string& ts, int height, int width) {
	FrameProcessor fp;
	if (!fp.FrameToGray(framePath)) {
		fprintf(stdout, "Failed to convert frame to gray\n");
		return nullptr;
	}

	if (!fp.GrayToGrid(height, width)) {
		fprintf(stdout, "Failed to convert gray to grid\n");
		return nullptr;
	}

	std::string* csvString = fp.GridToCSV(ts);
	if (nullptr == csvString) {
		fprintf(stdout, "Failed to convert grid to csv\n");
	}

	return csvString;
}

bool WriteToCSV(const std::string& csv, std::ofstream& f) {
	if (!f.is_open())
		return false;
	f << csv.c_str();
	return true;
}

int ConvertVideo(const std::string& videoPath, const std::string& csvPath, int height, int width) {
	int err = 0;
	KeyframeExtractor ke(videoPath);
	if (!ke.Open()) {
		fprintf(stderr, "Failed to open video\n");
		err = 1;
		return err;
	}

	std::ofstream csvFile(csvPath);
	if (!csvFile.is_open()) {
		fprintf(stderr, "Failed to open csv file\n");
		err = 2;
		return err;
	}

	std::string framePath = "";
	std::string* csvString = nullptr;
	std::string timeStamp = "";

	while (ke.GetNextFrame(framePath, timeStamp)) {
		csvString = FrameToCSV(framePath, timeStamp, height, width);
		if (nullptr == csvString) {
			err = 3;
			break;
		}

		if (!WriteToCSV(*csvString, csvFile)) {
			err = 4;
			break;
		}
	}

	csvFile.close();
	return err;
}