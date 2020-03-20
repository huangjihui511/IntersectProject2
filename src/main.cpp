#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <set>
#include <string>
#include "core.h"
using namespace std;

int main(int argc, char** argv)
{

	Core core;
	int result;
	if (argc == 5) {
		ifstream fin(argv[2]);
		ofstream fout(argv[4]);
		//ifstream fin("input.txt");
		//ofstream fout("output.txt");
		ofstream fpoint("point.txt");
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
		fin.close();
		fout.close();
		fpoint.close();
		fout << result << endl;
	}
	int debug = 1;

	if (debug) {
		core.addGeomrtie("L 0 0 1 1");
		core.addGeomrtie("L 0 0 1 1");
		core.addGeomrtie("L 0 1 1 0");
		core.addGeomrtie("L 0 1 0 1");
		core.addGeomrtie("L 1000000 1 1 0");
		core.addGeomrtie("L -1000000 1 1 0");
		//core.addGeomrtie("S -1 3 2 -1");
		//core.addGeomrtie("L -2 2 3 0");
		//core.addGeomrtie("R -3 0 4 2");
		//core.addGeomrtie("R -3 0 4 2");
		result = core.intersect();
		for (int i = 0; i < core.errorInformations.size(); i++) {
			cout << core.errorInformations[i] << endl;
		}
	}
	cout << result;



}