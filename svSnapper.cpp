#include<iostream>
#include<cstdlib>

using namespace std;

int main(int argc, char ** argv){
	
	string filepath;

	if(argc < 2){
		cerr<<"NOT ENOUGH INPUT"<<endl;
		exit(1);
	}

	filepath = argv[1];
	cout<<filepath<<endl;



}
