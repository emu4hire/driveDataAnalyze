#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/video/video.hpp>
#include <iostream>
#include <cstdlib>
#include <string>

using namespace cv;
using namespace std;

int main(int argc, char ** argv){

        if (argc < 3){
                cerr<<"Not enough input"<<endl;
                exit(1);
        }
        
        string f = argv[1];
        Mat im1 = imread(f.c_str());
        f = argv[2];
        Mat im2 = imread(f.c_str());

        Mat im1_gray, im2_gray;
        cvtColor(im1, im1_gray, CV_BGR2GRAY);
        cvtColor(im2, im2_gray, CV_BGR2GRAY);

        const int warp_mode = MOTION_HOMOGRAPHY;
        
        Mat warp_matrix;

        warp_matrix = Mat :: eye(3,3, CV_32F);

        int number_of_iterations = 5000;
        
        double termination_eps = 1e-10;

        TermCriteria criteria (TermCriteria :: COUNT + TermCriteria::EPS, 
                                number_of_iterations, termination_eps);

        cerr<<"BOop"<<endl;
        findTransformECC(
                        im1_gray,
                        im2_gray,
                        warp_matrix,
                        warp_mode,
                        criteria
                        );

        Mat im2_aligned;

        cerr<<"Bap"<<endl;
        warpPerspective(im2, im2_aligned, warp_matrix, im1.size(), 
                        INTER_LINEAR + WARP_INVERSE_MAP);


        imshow("im1", im1);
        imshow("im2", im2);
        imshow("algined", im2_aligned);
        
        imwrite("./config/aligned.jpg", im2_aligned);
        waitKey(0);
}
