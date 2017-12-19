#ifndef TRACKCAM_H
#define TRACKCAM

#include <iostream>
#include <opencv2/opencv.hpp>
#include <raspicam/raspicam_cv.h>

using namespace cv;

class TrackCam{
	public:
		~TrackCam();

		bool init();
		void track();
	private:
		//Private Variables
		raspicam::RaspiCam_Cv* camera;
		int x[4], y[4];	//Observed positions of the screen's vertices
		int width, height;	//Screen size
		int bx0, bx1, bx2, by0, by1, by2;

		//Private functions
		void setVertex();
		void setParam();
		void calibration(int, int, float, float);
		Rect getBound();
};

#endif //TRACKCAM_H
