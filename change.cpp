/*************************************************************************
    > File Name: change.cpp
    > Author: ghost_lzw
    > Mail: lanzongwei@gmail.com 
    > Created Time: Tue May 19 11:28:38 2020
 ************************************************************************/

#include<iostream>
#include<fstream>
#include<io.h>
using namespace std;

char base = 0xFF;

int main(){

	string path = "./*.dat";
	_finddata_t fileinfo;
	long handle = _findfirst(path.data(), &fileinfo);
	if (handle == -1) return -1;
	do {
		string info(fileinfo.name);
		ifstream fin(info.data(), std::ifstream::binary);
		char head;
		fin.read(&head, sizeof head);
		char diff = head ^ base;
		ofstream fout((info.substr(0, info.length() - 4) + ".jpg").data(), std::ofstream::binary);
		do {
			head ^= diff;
			fout.write(reinterpret_cast<char*>(&head), sizeof(head));
		} while (fin.read(&head, sizeof head));
	} while (!_findnext(handle, &fileinfo));

	_findclose(handle);
	
	return 0;
}
