#!/bin/bash

g++ keepTracking.cpp -o keepTracking $(pkg-config opencv --cflags --libs) -L/opt/vc/lib -I/use/local/include/ -lraspicam -lraspicam_cv -lmmal -lmmal_core -lmmal_util -lopencv_core -lopencv_highgui
