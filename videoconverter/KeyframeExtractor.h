/* 
 * Keyframe Extractor Class
 */

#include <opencv2/opencv.hpp>

class KeyframeExtractor {
public:
	KeyframeExtractor();
	KeyframeExtractor(const std::string& filePath);

	bool Open(const std::string& filePath = "");
	bool Close();
	bool GetNextFrame();
	cv::Mat* CurrentFrame();

private:
	std::string fp;
	cv::VideoCapture vc;
	cv::Mat* cf;
};
