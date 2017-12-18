#include <iostream>
#include <algorithm>
#include <opencv2/opencv.hpp>
#include <raspicam/raspicam_cv.h>
#include "trackCam.h"

using namespace std;
using namespace cv;

TrackCam::~TrackCam(){
	if(camera->open())
		camera.release();
}

bool TrackCam::init(){
	*camera = raspicam::RaspiCam_cv();
	if(!camera->open()){
		cout<<"Camera failed!"<<endl;
		return False;
	}
}

void TrackCam::track(){
	while(True){
	}
}

Rect TrackCam::getBound(){
	int x_start = min(veretx[0].x, vertex[3].x);
	int y_start = min(vertex[0].y, vertex[1].y);
	int x_len = max(vertex[1].x - vertex[0].x, vertex[2].x - vertex[3].x);
	int y_len = max(vertex[3].y - vertex[0].y, vertex[2].y - vertex[1].y);
	
	return Rect(x_start, y_start, x_len, y_len);
}

		
