// This program runs the DistancePPG algorithm
// Importing Requisite Headers

#include <opencv2/imgproc.hpp> 
#include <opencv2/core.hpp>
#include <opencv2/objdetect.hpp>
#include <opencv2/highgui.hpp>
#include <chrono>
#include <iostream>


int main(int argc, char *argv[]){

	std::cout<<"Program has started\n";
	cv::String file_name = "./inputs/UID003_EID002_original.avi";

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
