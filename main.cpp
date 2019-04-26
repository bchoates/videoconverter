/*
 * Uses the videoconversion library to process and 
 * convert a video file to a csv file.
 */
#include "src/VideoConverter.h"

int main() {
	std::string testVideo = "./data/ranggyu.mp4";
	std::string csvPath = "test.csv";

	if (0 != ConvertVideo(testVideo, csvPath, 3, 3))
		fprintf(stderr, "good convert failed\n");
}
