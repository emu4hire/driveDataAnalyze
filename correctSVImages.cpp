#include<iostream>
#include <fstream>
#include<cstdlib>
#include<string>
#include <vector>
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

using namespace std;
using namespace cv;

int main (int argc, char ** argv){

	if(argc<2){
		cerr<<"Not enough input"<<endl;
		exit(1);
	}

	string filepath= argv[1];
	string listname= filepath + "img_list.txt";
	ifstream in;
	
	
	in.open(listname.c_str());

	if(!in){
		cerr<<"FILE Opening Problem"<<endl;
		exit(1);
	}

	string s;
	int n;
	vector <string> filenames;

	in>>n;
	while(in){
		in >> s;
		filenames.push_back(s);
	}

	in.close();

	Mat img, compare, ideal, color;

	string fullImgName;
	vector <string> toWrite;
	
	compare = imread("./config/no_imagery.jpg");
	ideal = imread( "./config/ideal.jpg");

	Vec3b pixel;
	Vec4f outLine_ideal, outLine;
	vector<Point> points_ideal;

	int threshV[6];
	ifstream in_thresh;
	in_thresh.open("./config/threshold_values.txt");

	if(!in_thresh){
		cerr<<"ERROR Opening threshold config file"<<endl;
		exit(1);
	}
	
	int w=0;
	do{
		in_thresh >> threshV[w];
		w++;
	}while(w <6);

	in_thresh.close();
	cvtColor(ideal, color, CV_BGR2HSV, 3);
	
	for(int i=0; i<color.rows; i++){
		for(int j=0; j<color.cols;j++){
			pixel = color.at<Vec3b>(Point(j,i));
			if( (i > ( 2* color.rows / 3 )) && (j > color.cols/3 &&  j <(2* color.rows /3))
			&& (pixel[0] > threshV[0] && pixel[0] < threshV[1]) 
			&& (pixel[1] > threshV[2] && pixel[1] < threshV[3] ) 
			&& (pixel[2] > threshV[4] && pixel[2] < threshV[5] ))
				points_ideal.push_back(Point(j,i));
				
		}

	}

	fitLine(points_ideal, outLine_ideal, CV_DIST_FAIR, 0, 0.01, 0.01);
	
	double m = max(color.rows, color.cols);
	Point Cp1, Cp2;

	Cp1.x = outLine_ideal[2] - m*outLine_ideal[0];
	Cp1.y = outLine_ideal[3] - m*outLine_ideal[1];
	Cp2.x = outLine_ideal[2] + m*outLine_ideal[0];
	Cp2.y = outLine_ideal[3] + m*outLine_ideal[1];

	line(ideal, Cp1, Cp2, Scalar(0, 0, 255), 3, CV_AA, 0);
	
        for(int k=0; k < points_ideal.size(); k++){
 	       circle(ideal, points_ideal[k], 1, Scalar(255, 0, 0), -1,CV_AA, 0);
        }

	

	imwrite("test.jpg", ideal);

	for(int i=0; i< filenames.size()-1; i++){
		fullImgName = filepath+filenames[i];
		img = imread(fullImgName.c_str());
		if(!img.data){
			cerr<<"ERROR READING IMAGE"<<endl;
			continue;
		}
		
		//IF No imagery, delete.
		Scalar ssum = sum(img - compare);
		if((ssum[0] == 0) && (ssum[1] == 0) && (ssum[2]== 0)){
			string command = "rm -f " + fullImgName;
			cerr<<"Deleting " <<filenames[i]<<endl;
			system(command.c_str());
		}
	
		else{
			vector<Point> points;

			outLine[0]=outLine[1]=outLine[2]=outLine[3]=0;

			cvtColor(img, color, CV_BGR2HSV, 3);

		        for(int x=0; x<color.rows; x++){
                		for(int y=0; y<color.cols;y++){
		                        pixel = color.at<Vec3b>(Point(y,x));
                		        if( (x > ( 2* color.rows / 3 )) && (y > color.cols/3 &&  y <(2* color.rows /3))
		                        && (pixel[0] > threshV[0] && pixel[0] < threshV[1])
		                        && (pixel[1] > threshV[2] && pixel[1] < threshV[3] )
		                        && (pixel[2] > threshV[4] && pixel[2] < threshV[5] ))
                		                points.push_back(Point(y,x));

		                }		

		        }	

			cerr<<"NUMBER OF POINTS "<<points.size()<<endl;
			if(points.size() > 0){
				fitLine(points, outLine, CV_DIST_FAIR, 0, 0.01, 0.01);
			}


		        m = max(color.rows, color.cols);

		        Cp1.x = outLine[2] - m*outLine[0];
        		Cp1.y = outLine[3] - m*outLine[1];
		        Cp2.x = outLine[2] + m*outLine[0];
		        Cp2.y = outLine[3] + m*outLine[1];

		        line(ideal, Cp1, Cp2, Scalar(0, 0, 255), 3, CV_AA, 0);

		        for(int k=0; k < points.size(); k++){
		               circle(img, points[k], 1, Scalar(255, 0, 0), -1,CV_AA, 0);
		        }

			imwrite(fullImgName.c_str(), img);
			

			toWrite.push_back(filenames[i]);
			
		}
		

	

		//IF no line, generate new wget with 90 degree rotation

		//IF tilted left, generate new wget with 30 + degree rotation
	
		//If tilted right, generate new wget with 30 - degree rotation

		//otherwise good, ignore for future sweeps

	}

	ofstream out;
	out.open(listname.c_str());
	out<< toWrite.size();
	for(int i=0; i<toWrite.size(); i++){
		out << endl<<toWrite[i];
	}

	out.close();
	
	//write new file for nth sweep.

	
}
