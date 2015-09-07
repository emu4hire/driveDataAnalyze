#include <iostream>
#include<cstdlib>
#include<fstream>

using namespace std;

int main(int argc, char ** argv){
	
	string filepath;
	string capturename;
	
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
	
	infilename = filepath + "/analysis" + capturename + "_uniquePose.dat";
	outfilename = filepath + "/analysis"+ capturename + "_snapRequest.dat";
	cout<<"    --IN:"<<infilename<<endl;
	cout<<"    --OUT:"<<outfilename<<endl;

	in.open(infilename.c_str());
	out.open(outfilename.c_str(), std::fstream::out);

        if(!in || !out){
                cerr<<"FILE COULD NOT BE OPENED"<<endl;
                exit(1);
        }
	
	out<<"https://roads.googleapis.com/v1/snapToRoads?path=";


	char buffer[100];
	double lat[100], lng[100];
	int i=0;

	do{
		in >> lat[i];
		in.getline(buffer, 100 ,',');
		in >> lng[i];
		in.getline(buffer, 100, '\n');
	
		i++;
	}while(!(in.eof()));

	int k = i;
	i=0;

	out<<lat[i]<<","<<lng[i];
	i++;

	while(i<k-1){
		out<<"|"<<lat[i]<<","<<lng[i];
		i++;
	}

	out<<"&interpolate=true";
	ifstream in_key;
	in_key.open("key.txt");
	char key[100];

	in_key.getline(key, 100, '\n');
	in_key.close();

	out<<"&key="<<key;

	out.close();
	in.close();

	return 0;
}
