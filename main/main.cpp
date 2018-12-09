// This program runs the DistancePPG algorithm
// Importing Requisite Headers

#include <opencv2/imgproc.hpp> 
#include <opencv2/core.hpp>
#include <opencv2/objdetect.hpp>
#include <opencv2/highgui.hpp>
#include <chrono>
#include <iostream>

const float sampling_rate = 30; // Sampling Rate

struct params_tracker // Structure to keep track of tracker parameters
{
	float Fs, spatialSigma, lcutoff, hcutoff;
	bool MOTION, smoothTrack, spatialFilter;
	cv::String motionAlgo;
	int numKLT, smoothSize, trackerStep, ROISize;

	params_tracker() {
		Fs = sampling_rate; // Sampling Rate
		MOTION=1; //true, is Motion present?
		motionAlgo = "rigid"; //Motion algorithm handling
		numKLT = 200; // No of features
		smoothTrack = 1; // smoothening
		smoothSize = 30;
		trackerStep = 1; // assume no significant motion
		ROISize = 20; // Each ROI is 20 x 20 block
		spatialFilter = 1;
		lcutoff = 0.5; // 0.5 Hz
		hcutoff = 5; // 5 Hz
	}

};


struct param_regionMRC // Structure to keep track of MRC algorithm
{
	bool DEBUG, overlapPPGMaxRatio;
	float Fs, goodnessThreshold, HRbandwidth;
	int window, overlap, amplThresh;

	param_regionMRC() {
		DEBUG = 1; // Debug mode
		Fs = sampling_rate;
		window = 10; // 10-second graph for PPG estimation
		overlap = window/2;
		overlapPPGMaxRatio = 0; //false
		goodnessThreshold = 0.5;
		HRbandwidth = 0.2;
		amplThresh = 8;
	}
};


int main(int argc, char *argv[]){

	std::cout<<"Program has started\n";
	cv::String file_name = "./inputs/UID003_EID002_original.avi";
	params_tracker pa1;

	std::cout << pa1.trackerStep << std::endl;
	std::cout << pa1.ROISize << std::endl;
	std::cout << pa1.smoothTrack << std::endl;

	cv::VideoCapture cam(file_name);

	if(cam.isOpened()){               // Checking Camera/File is Opened
		std::cout<<"Feed/File Live\n";
		cv::Mat frame;

		while(1){
			auto start = std::chrono::steady_clock::now( );
			cam.read(frame);

			if (frame.empty())
				break;

			cv::imshow("Frame",frame);
			auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>( std::chrono::steady_clock::now( ) - start );


			if (cv::waitKey(1) >=0)
				break;
		}

	}
	return 0;
}
