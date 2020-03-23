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
	argc = 5;
	if (argc == 6) {
		//ifstream fin(argv[2]);
		//ofstream fout(argv[4]);
		ifstream fin("input.txt");
		ofstream fout("output.txt");
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
		if (core.errorInformations.size() > 0) {
			//输入格式有误，不计算交点
			for (int i = 0; i < core.errorInformations.size(); i++) {
				fout << core.errorInformations[i] << endl;
			}
		}
		else {
			//输入格式正确，计算交点
			result = core.intersect();
			//几何体重合
			if (core.errorInformations.size() > 0) {
				for (int i = 0; i < core.errorInformations.size(); i++) {
					fout << core.errorInformations[i] << endl;
				}
			}
			else {
				fout << result << endl;
			}
		}
		fin.close();
		fout.close();
		fpoint.close();
	}
	int debug = 1;

	if (debug) {
		core.addGeomrtie("L 0 0 1 1");
		core.addGeomrtie("L 0 0 1 1");
		core.addGeomrtie("L 0 1 1 0");
		//core.addGeomrtie("L 0 1 0 1");
		core.addGeomrtie("L 1 1 1 0");
		core.addGeomrtie("L 1 2 1 0");
		//core.addGeomrtie("L 1000000 1 1 0");
		//core.addGeomrtie("L -1000000 1 1 0");
		//core.addGeomrtie("S -1 3 2 -1");
		//core.addGeomrtie("L -2 2 3 0");
		core.addGeomrtie("R -3 0 4 2");
		core.addGeomrtie("R -3 0 4 2");
		core.addGeomrtie("C -3 0 4");
		core.addGeomrtie("C -3 0 4");
		result = core.intersect();
		for (int i = 0; i < core.errorInformations.size(); i++) {
			cout << core.errorInformations[i] << endl;
		}
	}
	cout << result;



}