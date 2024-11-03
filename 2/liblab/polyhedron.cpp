/*!
    \file
    \brief Файл реализации класса Polyhedron

    Данный файл содержит в себе реализацию методов и операторов класса Polyhedron (Многогранник)
*/

#include "polyhedron.h"

/*!
    (Вспомогательная функция) Нахождение площади треугольника по координатам трёх точек
*/
double square(double x1,double y1,double x2,double y2,double x3,double y3){
    return 0.5*fabs((x2-x3)*(y1-y3) - (x1-x3)*(y2-y3));
}

/*!
    Проверка наличия точки в массиве
    \param a массив точек
    \param b искомая точка
    \return true, если точка есть в массиве, иначе false
*/
bool find(Point *a, int n, Point& b){
    for(int i = 0; i < n; i++){
        if(a[i] == b) return true;
    }
    return false;
}

    /*!
        Конструктор - создание экземпляров класса с инициализацией заданной точкой
        \param p точка для инициализации
    */
    Polyhedron::Polyhedron(Point &p):n(1){
        vertices = new Point[1];
        vertices[0] = p;
    }

    /*!
        Конструктор - создание экземпляров класса с инициализацией заданным массивом точек
        \param n размер массива
        \param vert массив точек
    */
    Polyhedron::Polyhedron(int n, Point *vert){
        this->n = 0;
        vertices = new Point[n];
        for(int i = 0; i < n; i++){
            if(find(vertices, this->n,  vert[i]) == true) continue;
            vertices[this->n].setx(vert[i].getx());
            vertices[this->n].sety(vert[i].gety());
            this->n++;
        }
        if(this->n != 0){
            Point *buff = new Point[this->n];
            std::copy(vertices,vertices + this->n , buff);
            delete[] vertices;
            vertices = buff;
        }
    }

    /*!
        Конструктор копирования - создание экземпляра класса на основе другого экземпляра копированием данных
        \param p троичный вектор
    */
    Polyhedron::Polyhedron(Polyhedron &p){
        n = p.getn();
        vertices = new Point[n];
        std::copy(p.vertices, p.vertices + n, vertices);
    }

    /*!
        Конструктор перемещения - создание экземпляра класса на основе другого экземпляра копированием данных
        \param p троичный вектор
        \throw std::bad_alloc() в случае ошибки выделения памяти
    */
    Polyhedron::Polyhedron(Polyhedron &&p){
        n = p.n;
        vertices = p.vertices;
        p.vertices = NULL;
        p.n = 0;
    }

    /*!
        Геттер - получение текущего количества точек
    */
    int Polyhedron::getn(){
        return n;
    }

    /*!
        Нахождение центра тяжести многогранника
        \return точка, являющаяся центром тяжести
    */
    Point Polyhedron::center(){
	    double xm = 0, ym = 0;
		std::for_each(vertices, vertices + this->n, [&](Point &v){
			xm += v.getx();
			ym += v.gety();
		});
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
        return Point{xc, yc};
    }
    /*!
        Поворот всего многогранника против часовой стрелки вокруг заданной точки на угол, кратный 90 градусов
        \param o точка, вокруг которой выполняется поворот
        \param phi число раз, которое нужно повернуть на 90 градусов
    */
    void Polyhedron::rotate(const Point& o, int phi){
        phi %= 4;
        phi = 4 - phi;
        std::for_each(vertices, vertices + n, [&](Point &v){
            v = v - o;
            for(int j = 0; j < phi; j++) v.rotate();
            v = v + o;
        });
    }

    /*!
        Перегрузка оператора '+=' - добавление точки к многограннику
        \param p точка, которая добавляется многогранник
    */
    Polyhedron& Polyhedron::operator += (Point& p){
        if(find(vertices, n, p) == false){
            n++;
            Point *buff = new Point[n];
            std::copy(vertices, vertices + n - 1, buff);
            buff[n - 1] = p;
            delete[] vertices;
            vertices = buff;
        }
        return *this;
    }

    /*!
        Перегрузка оператора '[]' - получение i-того элемента в массиве точек
        \param i индекс точки для возвращения
        \throw std::out_of_range() при выходе за размеры массива
    */
    Point& Polyhedron::operator [] (int i){
        if(i >= n)
            throw std::out_of_range("Range out of index");
        return vertices[i];
    }

    /*!
        Перегрузка оператора копирующего присваивания '='
        \param p многогранник, из которого копируются данные
    */
    Polyhedron& Polyhedron::operator = (Polyhedron &p){
        delete[] vertices;
        n = p.getn();
        vertices = new Point[n];
        std::copy(p.vertices, p.vertices + n ,vertices);
        return *this;
    }

    /*!
        Перегрузка оператора перемещающего присваивания '='
        \param p многогранник, из которого перемещаются данные
    */
    Polyhedron& Polyhedron::operator = (Polyhedron &&p){
        delete[] vertices;
        n = p.getn();
        vertices = p.vertices;
        p.vertices = NULL;
        p.n = 0;
        return *this;
    }

    /*!
        Функция сдвига многогранника на вектор, построенный из центра координат в заданную точку
        \param p искомая точка
    */
    void Polyhedron::shift(Point& p){
        std::for_each(vertices, vertices + n, [&](Point &v){
            v = v + p;
        });
    }

    Polyhedron::~Polyhedron(){
        delete[] vertices;
        n = 0;
        vertices = NULL;
    }

/*!
    Перегрузка оператора << - вывод точек многогранника
    \param stream выходной поток
    \param p многогранник
    \return Полученный выходной поток с выведенным многогранником
*/
std::ostream& operator <<(std::ostream& stream, Polyhedron& p){
    for(int i = 0; i < p.getn(); i++){
        stream << p[i] << std::endl;
    }
    return stream;
}

/*!
    Перегрузка оператора >> - ввод точек многогранника
    \param stream входной поток
    \param p многогранник
    \return Полученный входной поток с введенным многогранником
*/
std::istream& operator >>(std::istream& stream, Polyhedron& p){
    int n = 0;
    stream >> n;
    Point *vert = new Point[n];
    for(int i = 0; i < n; i++){
        stream >> vert[i];
    }
    p = Polyhedron(n, vert);
    delete[] vert;
    return stream;
}