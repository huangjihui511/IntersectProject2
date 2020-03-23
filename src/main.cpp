#include "intersect.h"
#include <QtWidgets/QApplication>
#include "core.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <set>
#include <string>

int main(int argc, char *argv[])
{
	Core core;
	int result;
	if (argc >= 5) {
		ifstream fin(argv[2]);
		ofstream fout(argv[4]);
		//ifstream fin("input.txt");
		//ofstream fout("output.txt");
		if (!fin) {
			cout << "文件打开失败!" << endl;
			exit(1);
		}
		if (!fout) {
			cout << "文件打开失败!" << endl;
			exit(1);
		}

		core.addGeomrties(&fin);
		//cout << "haha";
		core.intersect();
		if (core.errorInformations.size() > 0) {
			//输入格式有误，不计算交点
			for (int i = 0; i < core.errorInformations.size(); i++) {
				fout << core.errorInformations.at(i) << endl;
			}
		}
		else {
			//输入格式正确，计算交点
			result = core.intersect();
			//几何体重合
			if (core.errorInformations.size() > 0) {
				for (int i = 0; i < core.errorInformations.size(); i++) {
					fout << core.errorInformations.at(i) << endl;
				}
			}
			else {
				fout << result << endl;
			}
		}
		fin.close();
		fout.close();
	}
	else {
		QApplication a(argc, argv);
		intersect w;
		w.show();
		return a.exec();
	}
}
