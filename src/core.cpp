#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <set>
#include <string>
#include "core.h"
using namespace std;

int dcmp(double x);
double sqr(double x);
double dot(Point a, Point b);
double length(Point a);
bool onCircle(Point p, Circle c);
bool onLine(Line l, Point p);
double disLine(Point p, Line l);
Point vbase(Circle c, Line l);
Point prxy(Circle c, Line l);
int getIntersection_cl(set<Point>* intersections, Circle c, Line l);

Point::Point(double x, double y) {
	first = x;
	second = y;
}
Point Point::operator - (const Point& p) {
	return Point(first - p.first, second - p.second);
}
bool Point::operator ==(const Point& p)const {
	return dcmp(first - p.first) == 0 && dcmp(second - p.second) == 0;
}
void Point::operator=(const Point& point) {
	first = point.first;
	second = point.second;
}
Point Point::operator/(const double& d) {
	return Point(first / d, second / d);
}
bool Point::operator<(const Point& p)const {
	return dcmp(first - p.first) == 0 ? dcmp(second - p.second) < 0 : dcmp(first - p.first) < 0;
}

Line::Line(Point src, Point dst, GType t) {
	a = src.second - dst.second;
	b = dst.first - src.first;
	c = src.first * dst.second - dst.first * src.second;
	type = t;
	p1 = src;
	p2 = dst;
	e = (p2 - p1) / length(p2 - p1);

}
void Line::operator=(const Line& line) {
	a = line.a;
	b = line.b;
	c = line.c;
	e = line.e;
	p1 = line.p1;
	p2 = line.p2;
	type = line.type;
}
int Line::getIntersection_ll(set<Point>* intersections, Line l1, Line l2) {
	double D = l1.a * l2.b - l2.a * l1.b;
	if (D == 0) return 0;
	Point p = { (l1.b * l2.c - l2.b * l1.c) / D, (l2.a * l1.c - l1.a * l2.c) / D };
	//p.first = (float)p.first;
	//p.second = (float)p.second;

	if (onLine(l1, p) && onLine(l2, p)) {
		intersections->insert(p);
	}
	return 1;
}

void Circle::operator=(const Circle& circle) {
	c.first = circle.c.first;
	c.second = circle.c.second;
	r = circle.r;
}
int Circle::getIntersection_cc(set<Point>* intersections, Circle c1, Circle c2) {
	double r1 = c1.r, r2 = c2.r;
	double x1 = c1.c.first, x2 = c2.c.first, y1 = c1.c.second, y2 = c2.c.second;
	double d = length(c1.c - c2.c);		//dist of circle center

	if (dcmp(fabs(r1 - r2) - d) > 0) return -1;
	if (dcmp(r1 + r2 - d) < 0) return 0;

	double d2 = sqr(d);	//d*d
	double a = 2 * r1 * (x1 - x2);
	double b = 2 * r1 * (y1 - y2);
	double c = r2 * r2 - r1 * r1 - d * d;
	double p = a * a + b * b;
	double q = -2 * a * c;
	double r = c * c - b * b;

	double cosa, sina, cosb, sinb;
	//one intersection
	if (dcmp(d - (r1 + r2)) == 0 || dcmp(d - fabs(r1 - r2)) == 0) {
		cosa = -q / p / 2;													//被除数 p = a2 + b2 > 0
		sina = sqrt(1 - sqr(cosa));
		Point p(x1 + c1.r * cosa, y1 + c1.r * sina);
		if (!onCircle(p, c2)) p.second = y1 - c1.r * sina;
		//p.first = (float)p.first;
		//p.second = (float)p.second;
		intersections->insert(p);
		return 1;
	}
	//two intersections
	double delta = sqrt(q * q - 4 * p * r);
	cosa = (delta - q) / p / 2;
	cosb = (-delta - q) / p / 2;
	sina = sqrt(1 - sqr(cosa));
	sinb = sqrt(1 - sqr(cosb));
	Point p1(x1 + c1.r * cosa, y1 + c1.r * sina);
	Point p2(x1 + c1.r * cosb, y1 + c1.r * sinb);
	if (!onCircle(p1, c2)) p1.second = y1 - c1.r * sina;
	if (!onCircle(p2, c2)) p2.second = y1 - c1.r * sinb;
	if (p1 == p2) p1.second = y1 - c1.r * sina;
	//p1.first = (float)p1.first;
	//p1.second = (float)p1.second;
	//p2.first = (float)p2.first;
	//p2.second = (float)p2.second;
	intersections->insert(p1);
	intersections->insert(p2);
	return 2;
}

int dcmp(double x) {
	if (fabs(x) < eps) return 0;
	return x < 0 ? -1 : 1;
}

double sqr(double x) {		//平方
	return x * x;
}

double dot(Point a, Point b) {	//内积
	return a.first * b.first + a.second * b.second;
}

double length(Point a) {	//向量长度
	return sqrt(dot(a, a));
}

bool onCircle(Point p, Circle c) {
	return dcmp(dot(p - c.c, p - c.c) - sqr(c.r)) == 0;
}

bool onLine(Line l, Point p)
{
	switch (l.type)
	{
	case L: return true;
	case R: {
		//return ((p.first - l.p1.first)/(l.p2.first - l.p1.first) >= 0
		//	&& (p.second - l.p1.second) / (l.p2.second - l.p1.second) >= 0);
		return ((p.first - l.p1.first) * (l.p2.first - l.p1.first) >= 0);
	}
	case S: {
		//return (length(l.p1 - p) + length(l.p2 - p) == length(l.p1 - l.p2));
		return ((p.first - l.p1.first) * (l.p2.first - p.first) >= 0);
	}
	default:
		break;
	}
	return false;
}

double disLine(Point p, Line l) {		//点到直线距离
	double a = l.a, b = l.b, c = l.c;
	double x = p.first, y = p.second;
	return fabs(a * x + b * y + c) / sqrt(a * a + b * b);	//a,b不同时为0
}

Point vbase(Circle c, Line l) {	//向量base
	double r = c.r;
	double base = sqrt(r * r - sqr(disLine(c.c, l)));
	return Point(l.e.first * base, l.e.second * base);
}

Point prxy(Circle c, Line l) {
	Point A = l.p1;
	Point B = l.p2;
	Point O = c.c;
	Point AB = B - A;
	Point AO = O - A;
	double L = dot(AB, AO) / length(AB);
	Point Apr(l.e.first * L, l.e.second * L);
	return Point(A.first + Apr.first, A.second + Apr.second);
}

int getIntersection_cl(set<Point>* intersections, Circle c, Line l) {
	if (dcmp(disLine(c.c, l) - c.r) > 0) { return 0; }
	Point Base = vbase(c, l);
	Point pr = prxy(c, l);
	Point inter1 = { Base.first + pr.first, Base.second + pr.second };
	Point inter2 = { pr.first - Base.first, pr.second - Base.second };
	//inter1.first = (float)inter1.first;
	//inter1.second = (float)inter1.second;
	//inter2.first = (float)inter2.first;
	//inter2.second = (float)inter2.second;
	if (inter1 == inter2) {
		if (onLine(l, inter1)) {
			intersections->insert(inter1);
			return 1;
		}
		return 0;
	}
	else {
		int interN = 0;
		if (onLine(l, inter1)) {
			intersections->insert(inter1);
			interN++;
		}
		if (onLine(l, inter2)) {
			intersections->insert(inter2);
			interN++;
		}
		return interN;
	}
}



void Core::addGeomrties(ifstream *fin)
{
	char buffer[256];
	int n;
	fin->getline(buffer, 255);
	n = stoi(buffer);
	while (n--) {
		fin->getline(buffer, sizeof(buffer));
		addGeomrtie(buffer);
	}
}

void Core::addGeomrtie(string buffer)
{
	char type;
	stringstream text(buffer);
	text >> type;
	switch (type)
	{
	case 'L':
	case 'R':
	case 'S': {
		double x1, y1, x2, y2;
		text >> x1 >> y1 >> x2 >> y2;
		geomrties.push_back(Line(Point(x1, y1), Point(x2, y2),char2type(type)));
		break;
	}
	case 'C': {
		double x, y, r;
		text >> x >> y >> r;
		geomrties.push_back(Circle(Point(x, y), r));
		break;
	}
	default:
		break;
	}
}

GType char2type(char c) {
	switch(c)
	{
		case 'L': return L;
		case 'R': return R;
		case 'S': return S;
		case 'C': return C;
	}
}

int Core::intersect()
{
	for (int i = 0; i < (int)(geomrties.size()); i++) {
		for (int j = 0; j < i; j++) {
			if (geomrties[i].Gflag == L && geomrties[j].Gflag == L) {
				Line l1, l2;
				geomrties[i].getObj(l1);
				geomrties[j].getObj(l2);
				l1.getIntersection_ll(&intersections, l1, l2);
			}
			else if (geomrties[i].Gflag == C && geomrties[j].Gflag == C) {
				Circle c1, c2;
				geomrties[i].getObj(c1);
				geomrties[j].getObj(c2);
				c1.getIntersection_cc(&intersections, c1, c2);
			}
			else if (geomrties[i].Gflag == C && geomrties[j].Gflag == L) {
				Line line;
				Circle circle;
				geomrties[i].getObj(circle);
				geomrties[j].getObj(line);
				getIntersection_cl(&intersections, circle, line);
			}
			else if (geomrties[i].Gflag == L && geomrties[j].Gflag == C) {
				Line line;
				Circle circle;
				geomrties[i].getObj(line);
				geomrties[j].getObj(circle);
				getIntersection_cl(&intersections, circle, line);
			}
			else {
				cout << "几何体类型错误" << endl;
			}
		}
	}
	return intersections.size();
}
