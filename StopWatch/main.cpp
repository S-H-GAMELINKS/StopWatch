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

//Using Boost Library
#include <boost/timer/timer.hpp>

// Set Software Title
constexpr const char* WindowName = "Stop Watch";

// Draw Start & Stop
bool DrawButton(cv::Mat frame, bool timable, boost::timer::cpu_timer& timer) {

	if (cvui::button(frame, 40, 100, "Start")) {
		if (timable == false) {
			timer.start();
			timable = true;
		}
	}

	if (cvui::button(frame, 100, 100, "Pause")) {
		if (timable != false) {
			timer.stop();
			timable = false;
		}
		else {
			timer.resume();
			timable = true;
		}
	}

	if (cvui::button(frame, 160, 100, "Stop")) {
		if (timable != false) {
			timer.stop();
			timable = false;
		}
	}

	return timable;
}

int main(int argc, const char *argv[]) {

	// Create a frame where components will be rendered to.
	cv::Mat frame = cv::Mat(180, 280, CV_8UC3);

	// Init cvui and tell it to create a OpenCV window, i.e. cv::namedWindow(WINDOW_NAME).
	cvui::init(WindowName);

	boost::timer::cpu_timer timer;

	std::int32_t hours = 0, minitues = 0, seconds = 0;

	bool timable = false;

	timer.stop();

	while (true) {

		// Fill the frame with a nice color
		frame = cv::Scalar(49, 52, 49);

		seconds = std::stoi(timer.format(0, "%w"));

		minitues = (seconds % 60 == 0) ? seconds / 60 : minitues;

		hours = (minitues % 60 == 0) ? minitues / 60 : hours;

		cvui::printf(frame, 20, 40, "%s hours %s minitues %s seconds",
							std::to_string(hours).c_str(),
							std::to_string(minitues - hours * 60).c_str(),
							std::to_string(seconds - minitues * 60).c_str());

		// Draw Button
		timable = DrawButton(frame, timable, timer);

		// Update cvui stuff and show everything on the screen
		cvui::imshow(WindowName, frame);

		// Exit to ESC Key!
		if (cv::waitKey(20) == 27) {
			break;
		}
	}

	return 0;
}

