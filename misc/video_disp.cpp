// This program opens a camera and writes its frame rate
// Importing Requisite Headers

#include <opencv2/imgproc.hpp> 
#include <opencv2/core.hpp>
#include <opencv2/objdetect.hpp>
#include <opencv2/highgui.hpp>
#include <chrono>
#include <iostream>


int main(int argc, char *argv[]){
	std::cout<<"Program has started\n";

	cv::VideoCapture cam(0);

	if(cam.isOpened()){               // Checking Camera is Opened
		std::cout<<"Feed Live\n";
		cv::Mat frame;

		while(1){
			auto start = std::chrono::steady_clock::now( );
			cam.read(frame);

			cv::imshow("Frame",frame);
			auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>( std::chrono::steady_clock::now( ) - start );

			std::cout << "Frame Rate: " << 1000.0/elapsed.count() << std::endl;


			if (cv::waitKey(1) >=0)
				break;
		}

	}
	return 0;
}


