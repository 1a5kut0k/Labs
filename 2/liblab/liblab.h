#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

class Point{
private:
    double x, y;
public:
    Point(double, double);
    Point(double [2]);
    double getx();
    double gety();
    void setx(const double);
    void sety(const double);
    double dist(const Point &b);
    void rotate();
    Point operator + (const Point&) const;
    Point operator - (const Point&) const;
    Point operator / (const Point&) const;
    Point& operator = (const Point&);
    bool operator ==(const Point&);
};
std::ostream& operator <<(std::ostream&, Point&);
std::istream& operator >>(std::istream&, Point&);

class Polyhedron{
private:
    int n = 0;
    Point *vertices;
public:
    Polyhedron(Point p);
    Polyhedron(int n, const Point *vert);
    Polyhedron(const Polyhedron &p);
    Polyhedron(Polyhedron &&p);
    int getn();
    Point center();
    void rotate(const Point& o, int phi);
    Polyhedron& operator += (const Point& p);
    Point& operator [] (int i);
    Polyhedron& operator = (const Polyhedron &p);
    Polyhedron& operator = (Polyhedron &&p);
    void shift(const Point& a);
    ~Polyhedron();
};
std::ostream& operator <<(std::ostream& stream, Polyhedron& p);
std::istream& operator >>(std::istream& stream, Polyhedron& p);
