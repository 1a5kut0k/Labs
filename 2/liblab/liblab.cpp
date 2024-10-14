/*!
    \file
    \brief Файл реализации классов Point и Polyhedron

    Данный файл содержит в себе реализацию методов и операторов класса Point (Точка) и Polyhedron (Многогранник)
*/

#include "liblab.h"

/*!
    Простой класс точки
*/
class Point{
public:
    /*!
        Конструктор - создание экземпляра класса с инициализацией заданными координатами
        \param x первая координата
        \param y вторая координата
    */
    Point(double nx = 0, double ny = 0):x(nx), y(ny){};

    /*!
        Конструктор - создание экземпляра класса с инициализацией заданным массивом координат
        \param cord массив состоящий из 2-х координат
    */
    Point(double cord[2]):x(cord[0]), y(cord[1]){};

    /*!
        Геттер - получение текущего значения поля x
    */
    double getx(){return x;}

    /*!
        Геттер - получение текущего значения поля y
    */
    double gety(){return y;}

    /*!
        Сеттер - установление нового значения для поля x
        \param nx новое значение для x
    */
    void setx(const double nx){x = nx;}

    /*!
        Сеттер - установление нового значения для поля x
        \param ny новое значение для y
    */
    void sety(const double ny){y = ny;}

    /*!
        Расстояние до точки - вычисление расстояния до заданной точки
        \param p точка, до которой вычисляется расстояние
    */
    double dist(const Point &p){
        return std::sqrt(pow((x - p.x), 2) + pow((y - p.y), 2));
    }

    /*!
        Поворот - поворот точки относительно центра координат по часовой стрелке на 90 градусов
    */
    void rotate(){
        if(x * y > 0){
            y *= -1;
        }
        else if (x * y < 0){
            x *= -1;
        }
        x, y = y, x;
    }

    /*!
        Перегрузка оператора '+' - покоординатное сложение двух точек
        \param p точка
        \return Результат в виде новой точки
    */
    Point operator + (const Point& p) const{
        return Point{x + p.x, y + p.y};
    }

    /*!
        Перегрузка оператора '-' - покоординатная разность двух точек
        \param p точка
        \return Результат в виде новой точки
    */
    Point operator - (const Point& p) const{
        return Point{x - p.x, y - p.y};
    }

    /*!
        Перегрузка оператора '/' - покоординатное деление точки на число
        \param p целое число
        \return Результат в виде новой точки
        \throw std::invalid_argument при делении на 0
    */
    Point operator / (const int d) const{
        if(d == 0)
            throw std::invalid_argument();
        return Point{x / d, y / d};
    }

    /*!
        Перегрузка оператора коирующего присваивания '='
        \param right точка, из которого копируются данные
    */
    Point& operator = (const Point& right) {
        if (this == &right) {return *this;}
        x = right.x;
        y = right.y;
        return *this;
    }

    /*!
        Перегрузка оператора '==' - покоординатное сравнение двух точек
        \param right точка, с которой сравнивать
    */
    bool operator ==(const Point &right) {
        return (x == right.getx() && y == right.gety());
    }
};

/*!
    Перегрузка оператора << - вывод точки в выходной поток
    \param stream выходной поток
    \param p точка
    \return Полученный выходной поток с выведенной точкой
*/
std::ostream& operator <<(std::ostream& stream, Point& p){
    stream << "(" << p.getx() << ", " << p.gety() << ")";
    return stream;
}

/*!
    Перегрузка оператора >> - ввод точки из входного потока
    \param stream входной поток
    \param p точка
    \return Полученный входной поток с введенной точкой
*/
std::istream& operator >>(std::istream& stream, Point& p){
    double x, y;
    stream >> x >> y;
    p.setx(x);
    p.sety(y);
    return stream;
}

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
bool find(const Point *a, const Point& b){
    if(std::any_of(a.begin(), a.end(), [&](const Point &x){return x == b;})) return true;
    return false;
}

/*!
    Сложный класс точки
*/
class Polyhedron{
public:

    /*!
        Конструктор - создание экземпляров класса с инициализацией заданной точкой
        \param p точка для инициализации
        \throw std::bad_alloc() в случае ошибки выделения памяти
    */
    Polyhedron(Point &p):n(1){
        try
            vertices = new Point[1];
        catch const std::&bad_alloc()
            throw std::bad_alloc();
        vertices[0] = p;
    }

    /*!
        Конструктор - создание экземпляров класса с инициализацией заданным массивом точек
        \param n размер массива
        \param vert массив точек
        \throw std::bad_alloc() в случае ошибки выделения памяти
    */
    Polyhedron(int n, const Point *vert){
        this->n = 0;
        try
            vertices = new Point[n];
        catch const std::&bad_alloc()
            throw std::bad_alloc();
        for(int i = 0; i < n; i++){
            if(find(vertices, vert[i]) == true) continue;
            vertices[this->n] = vert[i];
            this->n++;
        }
        if(this->n != 0){
            try
                Point *buff = new Point[this->n];
            catch const std::&bad_alloc()
                throw std::bad_alloc();
            for(int i = 0; i < this->n; i++){
                buff[i] = vertices[i];
            }
            delete[] vertices;
            vertices = buff;
        }
    }

    /*!
        Конструктор копирования - создание экземпляра класса на основе другого экземпляра копированием данных
        \param p троичный вектор
        \throw std::bad_alloc() в случае ошибки выделения памяти
    */
    Polyhedron(const Polyhedron &p){
        n = p.getn();
        try
            vertices = new Point[n];
        catch const std::&bad_alloc()
            throw std::bad_alloc();
        for(int i = 0; i < n; i++){
            vertices[i] = p[i];
        }
    }

    /*!
        Конструктор перемещения - создание экземпляра класса на основе другого экземпляра копированием данных
        \param p троичный вектор
        \throw std::bad_alloc() в случае ошибки выделения памяти
    */
    Polyhedron(Polyhedron &&p){
        n = p.n;
        vertices = p.vertices;
        p.vertices = NULL;
        p.n = 0;
    }

    /*!
        Геттер - получение текущего количества точек
    */
    int getn(){
        return n;
    }

    /*!
        Нахождение центра тяжести многогранника
        \return точка, являющаяся центром тяжести
    */
    Point center(){
	    double xm = 0, ym = 0;
		std::for_each(vertices.begin(), vertices.end(), [&](const Point &v){
			xm += v.getx();
			ym += v.gety();
		})
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
    /*!
        Поворот всего многогранника против часовой стрелки вокруг заданной точки на угол, кратный 90 градусов
        \param o точка, вокруг которой выполняется поворот
        \param phi число раз, которое нужно повернуть на 90 градусов
    */
    void rotate(const Point& o, int phi){
        phi %= 4;
        phi = 4 - phi;
        std::for_each(vertices.begin(), vertices.end(), [&](const Point &v){{
            v = v - o;
            for(int j = 0; j < phi; j++) v.rotate();
            v = v + o;
        });
    }

    /*!
        Перегрузка оператора '+=' - добавление точки к многограннику
        \param p точка, которая добавляется многогранник
    */
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

    /*!
        Перегрузка оператора '[]' - получение i-того элемента в массиве точек
        \param i индекс точки для возвращения
        \throw std::__throw_out_of_range() при выходе за размеры массива
    */
    Point& operator [] (int i){
        if(i >= n)
            throw std::__throw_out_of_range();
        return vertices[i];
    }

    /*!
        Перегрузка оператора копирующего присваивания '='
        \param p многогранник, из которого копируются данные
    */
    Polyhedron& operator = (const Polyhedron &p){
        delete[] vertices;
        n = p.getn();
        vertices = new Point[n];
        for(int i = 0; i < this->n; i++){
            vertices[i] = p[i];
        }
        return *this;
    }

    /*!
        Перегрузка оператора перемещающего присваивания '='
        \param p многогранник, из которого перемещаются данные
    */
    Polyhedron& operator = (Polyhedron &&p){
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
    void shift(const Point& p){
        std::for_each(vertices.begin(), vertices.end(), [&](const Point &v){
            v = v + p;
        });
    }

    ~Polyhedron(){
        delete[] vertices;
        n = 0;
        vertices = NULL;
    }
};

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