#pragma once
#ifndef INTERSECT_H
#define INTERSECT_H

#include<set>

using namespace std;

enum GType { L, C };
const double eps = 1e-7;

class Point : public pair<double, double> {
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

class Line {
public:
	double a;
	double b;
	double c;
	Point e;
	Point p1;
	Point p2;

	Line() {
		a = 0;
		b = 0;
		c = 0;
	}
	Line(Point source, Point target);
	int getIntersection_ll(set<Point>* intersections, Line l1, Line l2);
	void operator=(const Line& line);
};

class Circle {
public:
	Point c;
	double r;

	Circle() {
		r = 0;
	}
	Circle(Point c, double r) :c(c), r(r) {}
	void operator=(const Circle& circle);
	int getIntersection_cc(set<Point>* intersections, Circle c1, Circle c2);
};

struct Geometry {
	GType Gflag;
	union {
		Line lObj;
		Circle cObj;
	};

	Geometry(Line l) {
		Gflag = L;
		lObj = l;
	}

	Geometry(Circle c) {
		Gflag = C;
		cObj = c;
	}

	void getObj(Line& obj) {
		if (Gflag == L) {
			obj = lObj;
		}
	}

	void getObj(Circle& obj) {
		if (Gflag == C) {
			obj = cObj;
		}
	}
};

class Core {

public:
	set<Point> intersections;
	vector<Geometry> geomrties;
	void addGeomrties(ifstream *fin);
	void addGeomrtie(string text);
	int intersect();
};

int dcmp(double x);
int getIntersection_cl(set<Point>* intersections, Circle c, Line l);
#endif