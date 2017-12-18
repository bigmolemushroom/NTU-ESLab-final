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

void TrackCam::calibration(){}

void TrackCam::track(){
	Mat im, im_hsv_inv, im_mask;
	Rect bound = getBound();
	vector<Point> locations;
	int x_ave = 0;
	int y_ave = 0;
	int x_pre = -1;
	int y_pre = -1;
	int pix_num = 0;
	while(true){
		//Catch a frame
		camera->grab();
		camera->retrieve(im);

		//Crop it
		im = im(bound);

		//Get the red part
		cvtColor(~im, im_hsv_inv, COLOR_BGR2HSV);
		inRange(im_hsv_inv, Scalar(80, 90, 70), Scalar(100, 255, 255), im_mask);

		//Locate the center of the signal
		findNonZero(im_mask, locations);
		if(!locations.empty()){
			pix_num = locations.size();
			x_ave = y_ave = 0;
			for(int i=0; i<pix_num; ++i){
				x_ave += locations[i].x;
				y_ave += locations[i].y;
			}
			x_ave /= pix_num;
			y_ave /= pix_num;
		}
		else x_pre = y_pre = -1;
		
		// Print the center of the signal
		if(x_ave == -1) cout<<"\r(---, ---)"<<flush;
		else cout<<"\r("<<x_ave<<", "<<y_ave<<")"<<flush;

		if(x_ave != -1 && x_pre != -1){
			line(im_track, Point(x_pre, y_pre), Point(x_ave, y_ave), Scalar(0, 255, 0), 5);
	}
}

Rect TrackCam::getBound(){
	int x_start = min(veretx[0].x, vertex[3].x);
	int y_start = min(vertex[0].y, vertex[1].y);
	int x_len = max(vertex[1].x - vertex[0].x, vertex[2].x - vertex[3].x);
	int y_len = max(vertex[3].y - vertex[0].y, vertex[2].y - vertex[1].y);
	
	return Rect(x_start, y_start, x_len, y_len);
}

		
