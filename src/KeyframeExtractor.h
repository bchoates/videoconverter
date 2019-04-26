/* 
 * Keyframe Extractor Class
 */
#ifndef KEYFRAME_EXTRACTOR
#define KEYFRAME_EXTRACTOR

#include <string>
#include <vector>

class KeyframeExtractor {
public:
	KeyframeExtractor(const std::string& filePath = "");

	bool Open();
	bool Open(const std::string& filePath);
	bool Close();
	bool GetNextFrame(std::string& framePath, std::string& timestamp);

private:
	std::string videoPath;
	int frameIndex;
	std::vector<std::string> framePaths;
	std::vector<std::string> timeStamps;
};

#endif
