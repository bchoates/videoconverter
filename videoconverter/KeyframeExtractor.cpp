/*
 * Keyframe Extractor Class
 */

#include <KeyframeExtractor.h>

bool KeyframeExtractor::KeyframeExtractor() {
	fp = "";
}

bool KeyframeExtractor::KeyframeExtractor(const std::string& filePath) {
	fp = filePath;
}

bool KeyframeExtractor::Open() {
	return vc.open(fp);
}

bool KeyframeExtractor::Open(const std::string& filePath) {
	fp = filePath;
	return Open();
}

bool KeyframeExtractor::Close() {
	vc.release();
	return true;
}

bool KeyframeExtractor::GetNextFrame() {
	return vc.read(cf);
}

cv::Mat* KeyframeExtractor::CurrentFrame() {
	return cf;
}
