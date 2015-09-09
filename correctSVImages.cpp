#include<iostream>
<<<<<<< HEAD
#include<fstream>
#include <string>
#include <cstdlib>
#include <vector>
=======
#include<cstdlib>
#include<string>
>>>>>>> 0baebfab7672d4ad70a90b5ea225c95d89a81fee
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

using namespace std;
using namespace cv;

<<<<<<< HEAD
int main(int argc, char ** argv){

	if(argc < 2){
		cerr<<"Not enough input"<<endl;
		exit(1);
	}

	string filepath= argv[1];

	ifstream in;
	in.open(filepath.c_str());

	if(!in){
		cerr<<"FILE INPUT BAD"<<endl;
		exit(1);
	}

	string s;
	vector <string> filenames;

	while(in){
		in>>s;
		cout<<s<<endl;
	}	

	
	
	return 0;
=======
int main (int argc, char ** argv){

	return 0;

>>>>>>> 0baebfab7672d4ad70a90b5ea225c95d89a81fee
}
