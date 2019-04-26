/*
 * Keyframe Extractor Class
 */

#include <fstream>
#include <sstream>
#include <filesystem>
#include "KeyframeExtractor.h"

#define KEYFRAME_NAME "keyframe-%05d.png"
#define TIMESTAMP_FILENAME "timestamps.txt"
#define TIMESTAMP_PREFIX "pkt_pts_time="

KeyframeExtractor::KeyframeExtractor(const std::string& filePath) {
	videoPath = filePath;
	frameIndex = 0;
}

bool KeyframeExtractor::Open(const std::string& filePath) {
	videoPath = filePath;
	return Open();
}

bool KeyframeExtractor::Open() {
	if ("" == videoPath)
		return false;

	const char* cmdFrames = "ffmpeg.exe -hide_banner -loglevel panic -skip_frame nokey -i ";
	const char* optFrames = " -vsync 0 -r 30 -f image2 ";

	std::ostringstream sFrame;
	sFrame << cmdFrames << videoPath << optFrames << KEYFRAME_NAME;
	std::string strCmd = sFrame.str();
	if (std::system(strCmd.c_str())) { //Should be replaced by a library call
		return false;
	}

	const char* cmdTs = "ffprobe.exe -hide_banner -loglevel panic -select_streams v -skip_frame nokey -show_frames -show_entries frame=pkt_pts_time -of default=noprint_wrappers=1 ";
	const char* optTs = " > ";

	std::ostringstream sTs;
	sTs << cmdTs << videoPath << optTs << TIMESTAMP_FILENAME;
	strCmd = sTs.str();
	if (std::system(strCmd.c_str())) { //Should be replaced by a library call
		return false;
	}

	std::ifstream fileTs(TIMESTAMP_FILENAME, std::ios::in);
	if (!fileTs.is_open())
		return false;

	frameIndex = 0;
	char buf[24];
	memset(buf, 0, sizeof(buf));
	int frameCount = 0;

	while (frameCount > -1) { //To prevent looping forever. May prevent reading all frames
		if (0 > snprintf(buf, sizeof(buf), KEYFRAME_NAME, ++frameCount))
			return false;
		std::string framePath = buf;
		if (std::filesystem::exists(framePath)) {
			std::string timestamp = "";
			std::getline(fileTs, timestamp);
			if ("" == timestamp)
				break;

			timeStamps.push_back(timestamp.substr(sizeof(TIMESTAMP_PREFIX) - 1));
			framePaths.push_back(framePath);
		}
		else
			break;
	}

	return true;
}

bool KeyframeExtractor::Close() {
	for (auto it = framePaths.begin(); it != framePaths.end(); ) {
		if (!std::filesystem::remove((*it)))
			return false;
		it = framePaths.erase(it);
	}
	return true;
}

bool KeyframeExtractor::GetNextFrame(std::string& framePath, std::string& timestamp) {
	if (frameIndex >= framePaths.size() || 0 > frameIndex) {
		frameIndex = -1;
		return false;
	}
	framePath = framePaths[frameIndex];
	timestamp = timeStamps[frameIndex++];
	return true;
}
