#include <iostream>
#include <algorithm>
#include <cmath>
#include "point.h"

class Polyhedron{
private:
    int n = 0;
    Point *vertices;
public:
    Polyhedron(Point &p);
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
