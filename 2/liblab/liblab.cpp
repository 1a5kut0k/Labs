#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

class Point{
private:
    double x, y;
public:
    Point(double nx = 0, double ny = 0):x(nx), y(ny){};
    Point(double cord[2]):x(cord[0]), y(cord[1]){};
    double getx(){return x;}
    double gety(){return y;}
    void setx(const double nx){x = nx;}
    void sety(const double ny){y = ny;}
    double dist(Point b){
        return std::sqrt(pow((x - b.x), 2) + pow((y - b.y), 2));
    }
    void rotate(){
        if(x * y > 0){
            y *= -1;
        }
        else if (x * y < 0){
            x *= -1;
        }
        x, y = y, x;
    }
    Point operator + (const Point& p) const{
        return Point{x + p.x, y + p.y};
    }
    Point operator - (const Point& p) const{
        return Point{x - p.x, y - p.y};
    }
    Point operator / (const int d) const{
        return Point{x / d, y / d};
    }
    Point& operator=(const Point& right) {
        if (this == &right) {return *this;}
        x = right.x;
        y = right.y;
        return *this;
    }
    bool operator ==(Point right) {
        return (x == right.getx() && y == right.gety());
    }
};

std::ostream& operator <<(std::ostream& stream, Point& p){
    stream << "(" << p.getx() << ", " << p.gety() << ")" << std::endl;
    return stream;
}

std::istream& operator >>(std::istream& stream, Point& p){
    double x, y;
    stream >> x >> y;
    p.setx(x);
    p.sety(y);
    return stream;
}

double square(double x1,double y1,double x2,double y2,double x3,double y3){
    return 0.5*fabs((x2-x3)*(y1-y3) - (x1-x3)*(y2-y3));
}

bool find(Point *a, int size, Point b){
    for(int i = 0; i < size; i++){
        if(a[i] == b) return true;
    }
    return false;
}

class Polyhedron{
private:
    int n = 0;
    Point *vertices;
public:
    Polyhedron(Point p):n(1){
        vertices = new Point[1];
        vertices[0] = p;
    }
    Polyhedron(int n, Point vert[]){
        this->n = 0;
        vertices = new Point[n];
        for(int i = 0; i < n; i++){
            if(find(vertices, this->n, vert[i]) == true) continue;
            vertices[this->n] = vert[i];
            this->n++;
        }
        if(this->n != 0){
            Point *buff = new Point[this->n];
            for(int i = 0; i < this->n; i++){
                buff[i] = vertices[i];
            }
            delete[] vertices;
            vertices = buff;
        }
    }
    Polyhedron(Polyhedron p){
        n = p.getn();
        vertices = new Point[n];
        for(int i = 0; i < n; i++){
            vertices[i] = p[i];
        }
    }
    Polyhedron(Polyhedron &&p){
        n = p.n;
        vertices = p.vertices;
        p.vertices = NULL;
        p.n = 0;
    }
    int getn(){
        return n;
    }
    Point center(){
	    double xm = 0, ym = 0;
		for(int i = 0; i < n; i++){
			xm += vertices[i].getx();
			ym += vertices[i].gety();
		}
		xm /= n; ym /= n; 
		double s = 0;
		double xc = 0, yc = 0;
		for(int i = 0; i < n; i++){
			double s1 = square(xm, ym, vertices[i].getx(), vertices[i].gety(), vertices[(i+1)%n].getx(), vertices[(i+1)%n].gety());
			xc += s1 * (xm + vertices[i].getx() + vertices[(i+1)%n].getx())/3;
			yc += s1 * (ym + vertices[i].gety() + vertices[(i+1)%n].gety())/3;
			s += s1;
		}
		xc /= s; yc /= s;
        return Point(xc, yc);
    }
    void rotate(Point o, int phi){
        if(phi % 90 != 0) return;
        if(phi % 360 == 0) return;
        phi = 360 - (phi % 360);
        for(int i = 0; i < n; i++){
            vertices[i] = vertices[i] - o;
            for(int j = 0; j < (phi / 90); j++) vertices[i].rotate();
            vertices[i] = vertices[i] + o;
        }
    }
    Polyhedron& operator += (const Point& p){
        if(find(vertices, n, p) == false){
            n++;
            Point *buff = new Point[n];
            for(int i = 0; i < (n - 1); i++){
                buff[i] = vertices[i];
            }
            buff[n - 1] = p;
            delete[] vertices;
            vertices = buff;
        }
        return *this;
    }
    Point& operator [] (int i){
        if(i > n)
            throw std::__throw_out_of_range;
        return vertices[i];
    }

    Polyhedron& operator = (Polyhedron p){
        delete[] vertices;
        n = p.getn();
        vertices = new Point[n];
        for(int i = 0; i < this->n; i++){
            vertices[i] = p[i];
        }
        return *this;
    }
    Polyhedron& operator = (Polyhedron &&p){
        delete[] vertices;
        n = p.getn();
        vertices = p.vertices;
        p.vertices = NULL;
        p.n = 0;
        return *this;
    }
    void shift(Point a){
        for(int i = 0; i < n; i++){
            vertices[i] = vertices[i] + a;
        }
    }
    ~Polyhedron(){
        delete[] vertices;
        n = 0;
        vertices = NULL;
    }
};

std::ostream& operator <<(std::ostream& stream, Polyhedron& p){
    for(int i = 0; i < p.getn(); i++){
        stream << p[i] << std::endl;
    }
    return stream;
}

std::istream& operator >>(std::istream& stream, Polyhedron& p){
    int n;
    stream >> n;
    p.n = 0;
    p.vertices = new Point[n];
    for(int i = 0; i < n; i++){
        Point a;
        stream >> a;
        if(find(p.vertices, p.n, a) == true) continue;
        p.vertices[p.n] = a;
        p.n++;
    }
    if(p.n != 0){
        Point *buff = new Point[p.n];
        for(int i = 0; i < p.n; i++){
            buff[i] = p.vertices[i];
        }
        delete[] p.vertices;
        p.vertices = buff;
    }
    return stream
}