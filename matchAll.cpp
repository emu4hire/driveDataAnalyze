#include<iostream>
#include<string>
#include<fstream>
#include<cstdlib>

using namespace std;

int main(int argc, char ** argv){

	if(argc < 2){
		cerr<<"Not enough input"<<endl;
		exit(1);
	}

	string filepath = argv[1];
	string captureName, imgDir, snapped, svDir, temp;
	string command;

	size_t d = filepath.find_last_of('/');
	captureName = filepath.substr(d, filepath.length());
	imgDir = filepath + "/images/";
	snapped = filepath + "/analysis" + captureName + "_snappedPose.dat";
	svDir = filepath + "/analysis/SVImages/";

	cerr<<imgDir<<endl<<snapped<<endl<<svDir<<endl;

	command = "./genImgList "+ imgDir;
	system(command.c_str());

	ifstream imagesList, SVList;
	int n=0;
	int k=0;
	
	temp = imgDir + "img_list.txt";
	imagesList.open(temp.c_str());
	imagesList >> n;
	string imageNames[n];
	
	while(imagesList){
		imageNames[k];
		k++;
	}

	imgDir.close();

	temp = svDir + "img_list.txt";
	SVList.open(temp.c_str());
	SVList >> n;
	string svName [n];
	
	k=0;
	while(SVList){
		svNames[k];
		k++;
	}
	SVList.close();

	istream in;
	in.open(snapped.c_str());
	int j=0;
	in >> j;
	double SVLat[j], SVLon[j];
	
	k=0;
	char buffer[100];
	while(in){
		in >> svLat[k];
		in >> svLon[k];
		in.getline(buffer, 100, '\n');
		k++;
	}
	
	in.close();
	
	for(k=0; k<n; k++){
		int img1, img2;
		if(k != 0){
			temp = svNames[k];
			d = temp.find_last_of('_')+1;
			temp.substr(d, temp.length());
			d = temp.find_last_of('.');
			temp.substr(0, d);
			stringstream(temp) >> img1;

			temp = svNames[k+1];
                        d = temp.find_last_of('_')+1;
                        temp.substr(d, temp.length());
                        d = temp.find_last_of('.');
                        temp.substr(0, d);
                        stringstream(temp) >> img2;

			cerr<<img1<<" "<<img2<<endl;
		}

		if(k !=0 && img2 - img1 != 1){
			do{		
				//set lat, lon
				//throw out rest
	
			}while(lat == svLat[k] && long =svLon[k]);
			
			//match on this and the next sv image;

		}

		}
		
		else{
			int i=0;
			do{
				//set lat, lon
				//match on this and the next sv image	
							
				i++;
			}while(lat == SVLat[k] && lon = SVLon[k]);
		}
	}

}
