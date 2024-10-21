#include <iostream>
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