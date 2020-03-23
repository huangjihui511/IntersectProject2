#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <set>
#include <string>
#include "core.h"
#pragma comment(lib,"core.lib")
using namespace std;

int main(int argc, char** argv)
{

	Core core;
	int result;
	//argc = 5;
	if (argc == 5) {
		//ifstream fin(argv[2]);
		//ofstream fout(argv[4]);
		ifstream fin("input.txt");
		ofstream fout("output.txt");
		if (!fin) {
			cout << "文件打开失败!" << endl;
			exit(1);
		}
		if (!fout) {
			cout << "文件打开失败!" << endl;
			exit(1);
		}
		core.addGeomrties(&fin);
		result = core.intersect();
		fout << result << endl;
		fin.close();
		fout.close();
	}
	int debug = 1;

	if (debug) {
		core.addGeomrtie("C 3 3 3");
		core.addGeomrtie("S 2 4 3 2");
		core.addGeomrtie("L -1 4 5 2");
		core.addGeomrtie("R 2 5 -1 2");
		result = core.intersect();
		set<Point>::iterator iter;
		for (iter = core.intersections.begin(); iter != core.intersections.end(); iter++) {
			cout << "(" << iter->first << "," << iter->second << ")" << endl;
		}
	}
	cout << result;
}