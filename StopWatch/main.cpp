// Stop Watch
// coding by S.H. (GAMELINKS)
// This source code license is MIT, see the license

// include openCV
#include <opencv2/opencv.hpp>

// One (and only one) of your C++ files must define CVUI_IMPLEMENTATION
// before the inclusion of cvui.h to ensure its implementaiton is compiled.
#define CVUI_IMPLEMENTATION
#include "cvui.h"

// Hide Console Window
#pragma comment(linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"")

// Set Software Title
constexpr const char* WindowName = "Stop Watch";

// Draw Start & Stop
bool DrawButton(cv::Mat frame, bool timable) {

	if (timable == false && cvui::button(frame, 80, 100, "Start")) {
		return true;
	}

	if (timable != false && cvui::button(frame, 140, 100, "Stop")) {
		return false;
	}

	return (timable == false) ? false : true;
}

int main(int argc, const char *argv[]) {

	// Create a frame where components will be rendered to.
	cv::Mat frame = cv::Mat(180, 280, CV_8UC3);

	// Init cvui and tell it to create a OpenCV window, i.e. cv::namedWindow(WINDOW_NAME).
	cvui::init(WindowName);

	std::int32_t time = 0;

	bool timable = false;

	while (true) {
		// Fill the frame with a nice color
		frame = cv::Scalar(49, 52, 49);

		cvui::printf(frame, 20, 40, "Past Time is %d", time);

		if (timable == true)
			time++;

		// Draw Button
		timable = DrawButton(frame, timable);

		// Update cvui stuff and show everything on the screen
		cvui::imshow(WindowName, frame);

		// Exit to ESC Key!
		if (cv::waitKey(20) == 27) {
			break;
		}
	}

	return 0;
}

