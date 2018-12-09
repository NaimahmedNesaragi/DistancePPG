// This program detects faces in an image

// Importing Requisite Headers

#include <opencv2/imgproc.hpp> 
#include <opencv2/core.hpp>
#include <opencv2/objdetect.hpp>
#include <opencv2/highgui.hpp>
#include <chrono>
#include <iostream>

cv::String face_cascade_name = "/Users/$USER/opencv-3.4.3/data/haarcascades/haarcascade_frontalface_alt.xml";


int main(int argc, char *argv[]){
	std::cout<<"Program has started\n";

	cv::VideoCapture cam(0);

	if(cam.isOpened()){               // Checking Camera is Opened
		std::cout<<"Feed Live\n";
		cv::Mat frame,frame_gray;
		//cv::String face_cascade_name = "haarcascade_frontalface_alt.xml";
		std::vector<cv::Rect> faces;

		// Viola-Jones Face Detector	
		cv::CascadeClassifier face_cascade; //::CascadeClassifier("haarcascade_frontalface_default.xml");
		face_cascade.load(face_cascade_name);

		while(1){
			auto start = std::chrono::steady_clock::now( );
			cam.read(frame);
			cv::cvtColor(frame,frame_gray,cv::COLOR_BGR2GRAY);
			
			// Detect Faces
			face_cascade.detectMultiScale( frame_gray, faces, 1.1, 2, 0|cv::CASCADE_SCALE_IMAGE, cv::Size(30, 30) );
			// Draw Rectangles
			for(int i = 0; i < faces.size(); i++){
				cv::rectangle(frame,cv::Point(faces[i].x,faces[i].y),cv::Point(faces[i].x + faces[i].width,faces[i].y + faces[i].height),cv::Scalar(0,255,0));
			}


			cv::imshow("Frame",frame);
			auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>( std::chrono::steady_clock::now( ) - start );

			std::cout << "Frame Rate: " << 1000.0/elapsed.count() << std::endl;


			if (cv::waitKey(3)>=0)
				break;
		}

	}
	return 0;
}


