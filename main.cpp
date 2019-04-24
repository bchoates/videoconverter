/*
 * main.cpp
 */
#include "videoconverter/FrameProcessor.h"
#include "videoconverter/KeyframeExtractor.h"

bool WriteToCSV(ofstream f, const std::string& v) {
	if (!f.is_open())
		return false;
	f << v.c_str();
	return true;
}

int main(int argc, char* argv[]) {
	KeyframeExtractor Ke("vid.mp4");
	if (!Ke.open()) {
		fprintf(stderr, "Failed to open video\n");
		return 1;
	}

	ofstream csvFile("vid.csv");
	if (!csvFile.is_open()) {
		fprintf(stderr, "Failed to open csv file\n");
		return 1;
	}

	std::string csvString = "";

	while (Ke.GetNextFrame()) {
		if (!FrameToCSV(Ke.CurrentFrame(), csvString)) {
			fprintf(stderr, "Failed to process frame\n");
			break;
		}
		if (!WriteToCSV(csvFile, csvString)) {
			fprintf(stderr, "Failed to write csv\n");
			break;
		}
	}

	csvFile.close();
	return 0;
}
