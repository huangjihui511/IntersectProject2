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
			cout << "�ļ���ʧ��!" << endl;
			exit(1);
		}
		if (!fout) {
			cout << "�ļ���ʧ��!" << endl;
			exit(1);
		}

		core.addGeomrties(&fin);
		//cout << "haha";
		core.intersect();
		if (core.errorInformations.size() > 0) {
			//�����ʽ���󣬲����㽻��
			for (int i = 0; i < core.errorInformations.size(); i++) {
				fout << core.errorInformations.at(i) << endl;
			}
		}
		else {
			//�����ʽ��ȷ�����㽻��
			result = core.intersect();
			//�������غ�
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
