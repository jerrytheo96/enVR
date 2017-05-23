#include "enVRConsts.hpp"
#include "Capture.hpp"
#include "Generate.hpp"
#include "Viewer.hpp"

#include <iostream>

const double lthresh = -1e100;
const double uthresh =  1e100;

int main(int argc, char* argv[])
{
	using std::cout;
	using std::endl;
	using std::cin;

	unsigned char choice;

	cout << endl;
	
	cout << "Welcome to enVR" << endl;
	cout << "---------------" << endl;
	
	cout << endl;

	cout << "Developed by:" << endl;
	cout << "  Abhijit J. Theophilus  (abhitheo96@gmail.com)" << endl;
	cout << "  Abhishek Surbhat       (abhishek.surbhat@gmail.com)" << endl;
	
	cout << endl;
	
	cout << "Cameras attached: 6" << endl;
	cout << ":: Proceed to capture images? [y/n] ";
	cin  >> choice;

	cout.setf(std::ios::unitbuf);

	enVR::frame_map frames;
	if (choice == 'y') {
		cout << ":: Ignoring camera 1." << endl;
		cout << ":: Capturing images." << endl;
		frames = enVR::capture_images();
		cout << ":: Captures complete." << endl;
		cout << ":: Saving frames to img ... ";
		enVR::save_frames(frames);
		cout << "done." << endl;
	} else {
		cout << ":: Retrieving images from img ... ";
		frames = enVR::read_frames();
		cout << "done." << endl;
	}

	cout << ":: Extrapolating projections to 3 dimensions ... ";
	enVR::point_map pmap;
	for (auto it = enVR::faces.begin(); it != enVR::faces.end(); ++it) {
		pmap[(*it)] = enVR::extrapolate_projection(frames[(*it)], (*it),
												   lthresh, uthresh);
	}
	cout << "done." << endl;

	cout << ":: Constructing 3D image ... ";
	enVR::point_set img3d = enVR::construct_3d_image(pmap);
	cout << "done." << endl;

	cout << ":: Initializing OpenGL viewer ... ";
	enVR::init_viewer(&argc, argv);
	cout << "done." << endl;

	cout << ":: Reached target: Viewer." << endl;
	enVR::view_3d_image(img3d);
}
