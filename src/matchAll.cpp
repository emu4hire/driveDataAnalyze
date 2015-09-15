#include<iostream>
#include<string>
#include<fstream>
#include<cstdlib>
#include<sstream>
#include<vector>

using namespace std;

int main(int argc, char ** argv){

	if(argc < 2){
		cerr<<"Not enough input"<<endl;
		exit(1);
	}

	string filepath = argv[1];
	string captureName, imgDir, snapped, svDir, temp, location;
	string command;

	size_t d = filepath.find_last_of('/');
	captureName = filepath.substr(d, filepath.length());
	imgDir = filepath + "/images/";
	snapped = filepath + "/analysis" + captureName + "_uniquePose.dat";
	svDir = filepath + "/analysis/SVImages/";
	location = filepath + captureName + "_LOCATION.log";

//	command = "./genImgList "+ imgDir;
//	system(command.c_str());

	ifstream imagesList, SVList;
	int n=0;
	int k=0;
	
	temp = imgDir + "img_list.txt";
	imagesList.open(temp.c_str());
	if(!imagesList){
		cerr<<"ERROR OPENING FILE: "<<temp<<endl;
		exit(1);
	}
	
	imagesList >> n;
	string imageNames[n];
	while(!(imagesList.eof())){
		imagesList >> imageNames[k];
		k++;
	}

	imagesList.close();

	temp = svDir + "img_list.txt";
	SVList.open(temp.c_str());
	if(!SVList){
		cerr<<"ERROR OPENING FILE: "<<temp<<endl;
	exit(1);
	}

	SVList >> n;
	string svNames [n];
	int svMax = n;
	
	k=0;
	while(!(SVList.eof())){
		SVList >> svNames[k];
		k++;
	}
	SVList.close();

	for(int ad=0; ad < n; ad++){
		cerr<<svNames[ad]<<endl;
	}

	ifstream in;
	in.open(snapped.c_str());
	if(!in){
		cerr<<"ERROR OPENING FILE: "<<snapped<<endl;
		exit(1);
	}
	
	vector <double> SVLat, SVLon;
	double x;
	
	k=0;
	char buffer[100];
	while(!(in.eof())){
		in >>x;
		SVLat.push_back(x);
		in.getline(buffer, 100, ',');
		in >> x;
		SVLon.push_back(x);
		in.getline(buffer, 100, '\n');

		k++;
	}
	
	in.close();

	bool match;
	int svIncr, imgIncr;
	vector<double> imgLat, imgLon;
	svIncr = 0;
	imgIncr = 0;

	in.open(location.c_str());
	if(!in){
		cerr<<"ERROR OPENING LOCATION FILE"<<endl;
		exit(1);
	}

	while(in){
		in.getline(buffer, 100, ',');
		in >> x;
		imgLat.push_back(x);
		in.getline(buffer, 100,  ',');
		in>>x;
		imgLon.push_back(x);
		in.getline(buffer, 100, '\n');
	}
	in.close();
	
	for(k=0; k<SVLon.size(); k++){
			if(k >= svMax)
				continue;
			int img1;
			temp = svNames[svIncr];
			d = temp.find_last_of('_')+1;
			temp = temp.substr(d, temp.length());
			d = temp.find_last_of('.');
			temp = temp.substr(0, d);
			stringstream(temp) >> img1;
	
			match = (img1 == k);
		
			while(imgLat[imgIncr] == imgLat[imgIncr+1] && imgLon[imgIncr] == imgLon[imgIncr+1]){	
				if(match){
					string img, sv;
					sv = svDir + svNames[svIncr];
					img = imgDir + imageNames[imgIncr];
					cerr<<"Matching "<< sv <<" to "<<img<<endl;
					command = "./featureMatcher " + sv + " " + img;
					system(command.c_str());	
				}
				imgIncr++;
			}
			
			imgIncr++;
			
			if(match){
				svIncr ++;
			}
			
	}

}
