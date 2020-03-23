//#ifdef DLL3_EXPORTS
//#define DLL3_API __declspec(dllexport)
//#else
//#define DLL3_API __declspec(dllimport)
//#endif
#define DLL3_API __declspec(dllexport)

#pragma once
#ifndef INTERSECT_H
#define INTERSECT_H

#include<set>
#include<string>


#define MAX_LENGTH 99999999;
using namespace std;

enum DLL3_API GType { L, C, S, R};
const double eps = 1e-7;

class DLL3_API Point : public pair<double, double> {
public:
	Point() {}
	Point(double x, double y);
	Point operator - (const Point& p);
	bool operator ==(const Point& p) const;
	void operator=(const Point& point);
	Point operator/(const double& d);
	bool operator<(const Point& p) const;
	//	return first == p.first ? second < p.second : first < p.first;
	//	return dcmp(first - p.first)==0 ? dcmp(second - p.second) < 0 : dcmp(first - p.first) < 0;
	//}
};

class DLL3_API Line {
public:
	double a;
	double b;
	double c;
	GType type;
	Point e;
	Point p1;
	Point p2;

	Line() {
		a = 0;
		b = 0;
		c = 0;
		type = L;
	}
	Line(Point source, Point target, GType type);

	int getIntersection_ll(set<Point>* intersections, Line l1, Line l2);
	void operator=(const Line& line);
};

class DLL3_API Circle {
public:
	Point c;
	double r;
	
	Circle() {
		r = 0;
	}
	Circle(Point c, double r);
	void operator=(const Circle& circle);
	int getIntersection_cc(set<Point>* intersections, Circle c1, Circle c2);
};

struct DLL3_API Geometry {
	GType Gflag;
	//string name;
	union {
		Line lObj;
		Circle cObj;
	};

	Geometry(Line l);

	Geometry(Circle c);

	void getObj(Line& obj);

	void getObj(Circle& obj);

	void operator=(const Geometry& g);
};

class DLL3_API Core {
public:
	set<Point> intersections;
	vector<Geometry> geomrties;
	vector<string> errorInformations;
	int isValid = 1;
	void addGeomrties(ifstream *fin);
	void addGeomrtie(string text);
	int intersect();
	int addError(string input);
};

DLL3_API int dcmp(double x);
DLL3_API int getIntersection_cl(set<Point>* intersections, Circle c, Line l);
DLL3_API GType char2type(char c);
DLL3_API string type2char(GType type);
DLL3_API int checkError(string input);
DLL3_API int checkRange(string input);
DLL3_API int checkCoincide(string input);
DLL3_API string errorinformation(string input);
DLL3_API string point2str(Point p);
DLL3_API string getName(Geometry g);
#endif