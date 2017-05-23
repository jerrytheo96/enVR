#include "Capture.hpp"

using namespace enVR;

/*
 * capture_images - Captures images sequentially from each of the
 * cameras attached and returns an std::map that associates each image
 * with the camera attached.
 *
 * Parameters:
 *   None
 *
 * Returns:
 *   frame_map := Associates the cube face with
 *     the captured image.
 */

frame_map capture_images()
{
	using std::string;
	std::map<string, cv::Mat> frames;
	std::vector<string> cams {"front", "left", "right", "back",  "top"};

	// For unit buffering.
	std::cout.setf(std::ios::unitbuf);
	
	cv::Mat frame;
	for (int i=0; i < cams.size(); i++) {
		std::cout << ":: Capturing image from camera " << i << " ... ";
		cv::VideoCapture cap(i+1);
		cap.set(CV_CAP_PROP_FRAME_WIDTH, DIM);
		cap.set(CV_CAP_PROP_FRAME_HEIGHT, DIM);
		cap >> frame;
		frames[cams[i] = frame.clone();
		std::cout << "done." << std::endl;
	}

	std::cout.unsetf(std::ios::unitbuf);
	
	return frames;
}


/*
 * save_frames - Saves each frame as a jpg file.
 *
 * Parameters:
 *   frame_map frames := Each entry is the cube
 *     face and it's corresponding frame.
 *
 * Returns:
 *   None
 */
void save_frames(frame_map frames)
{
	for (auto it = frames.begin(); it != frames.end(); ++it)
		cv::imwrite("img/" + it->first + ".jpg", it->second);
}


/*
 * read_frames - Reads each frame from a jpg file.
 *
 * Returns:
 *   frame_map frames := Each entry is the cube
 *     face and it's corresponding frame.
 */
frame_map read_frames()
{
	frame_map frames;
	std::vector<string> cams {"front", "left", "right", "back", "top"};	
	for (auto it = cams.begin(); it != cams.end(); ++it) {
		cv::Mat frame = cv::imread("img/" + (*it) + ".jpg");
	}
}