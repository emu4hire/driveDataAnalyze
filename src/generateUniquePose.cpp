#include <iostream>
#include<cstdlib>
#include<fstream>
#include <iomanip>

using namespace std;

int main(int argc, char ** argv){
	
	string filepath;
	string capturename;
        int pres = 10;
	
	if(argc < 2){
		cerr<<"Bad input. Please input a fully qualified filename of a DriveData folder"<<endl;
		exit(1);
	}

	else{
		filepath = argv[1];;
	}

	size_t found = filepath.find_last_of("/");
        capturename = filepath.substr(found, filepath.length());

	ifstream in;
	ofstream out;

	string infilename;
	string outfilename;
	string foldercreate = "mkdir " + filepath + "/analysis";
	
	system(foldercreate.c_str());
	
	infilename = filepath + capturename + "_LOCATION.log";
	outfilename = filepath + "/analysis"+ capturename + "_uniquePose.dat";
	cout<<"    --IN:"<<infilename<<endl;
	cout<<"    --OUT:"<<outfilename<<endl;

	in.open(infilename.c_str());
	out.open(outfilename.c_str(), std::fstream::out);

        if(!in || !out){
                cerr<<"FILE COULD NOT BE OPENED"<<endl;
                exit(1);
        }

	char buffer[100];
	double lat, lng, last_lat, last_lng;
	int orient, orient_sum;
	int count = 1;

	do{
		in.getline(buffer, 100 ,',');
		in >> lat;
		in.getline(buffer, 100 ,',');
		in >> lng;
		in.getline(buffer, 100, ',');
		in.getline(buffer, 100, ',');
		in>>orient;	
		in.getline(buffer, 100, '\n');

		if(lat != last_lat || lng != last_lng){
			out<<setprecision(pres)<< lat<<" , "<<setprecision(pres)<<lng<<" , "<<orient_sum/count<<endl;
			last_lat = lat;
			last_lng = lng;
			orient_sum = 0;
			count =1;
			
		}
		else{
			orient_sum += orient;
			count++;

		}
	
	}while(!(in.eof()));

	out.close();
	in.close();

	return 0;
}
