#ifndef TRACKCAM_H
#define TRACKCAM

#include <iostream>
#include <opencv2/opencv.hpp>
#include <raspicam/raspicam_cv.h>

class TrackCam(){
	public:
		TrackCam();
		~TrackCam();

		bool init();
		void track();
	private:
		raspicam::RaspiCam_cv* camera;
		void calibration();
		Rect getBound();
};

#endif //TRACKCAM_H
