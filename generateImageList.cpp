#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <sstream>
#include <algorithm>
#include <vector>

using namespace std;

bool sort_names (string i, string j);

int main(int argc, char ** argv){

	if(argc < 1){
		cerr<<"Not enough arguments"<<endl;
		exit(1);
	}

	string filepath = argv[1];
	
	cout<<filepath<<endl;

	string img_filepath = filepath + "img_list.txt";

	string command = "ls -1 " + filepath + "|wc -l >" + img_filepath + " && ls " +filepath + ">>" + img_filepath;
	system(command.c_str());

	ifstream in;
	ofstream out;

	in.open(img_filepath.c_str());

	int n;
	in >> n;

	vector <string> v;
	string temp;
	
	for(int i=0; i < (n-1); i++){
		in >> temp;
		v.push_back(temp);
	}
	in.close();

	sort(v.begin(), v.end(), sort_names); 

	out.open(img_filepath.c_str());
	out << (n-1);

	for(int i = 0; i < v.size(); i++){
		out<<endl;
		out <<v[i];
	}

	return 0;
}


bool sort_names (string i, string j){

	int i_num, j_num;
	size_t i_, j_, idot, jdot;
	string itemp, jtemp;
	i_ = i.find_last_of("_") + 1;
	j_ = i.find_last_of("_") + 1;
	
	itemp = i.substr(i_);
	jtemp= j.substr(j_);
	

	idot = itemp.find_last_of('j') - 1;
	jdot = jtemp.find_last_of('j') - 1;

	itemp = itemp.substr(0, idot);
	jtemp = jtemp.substr(0, jdot);

	stringstream(itemp)>> i_num;
	stringstream(jtemp)>>j_num;
	
	return (i_num < j_num);
}
