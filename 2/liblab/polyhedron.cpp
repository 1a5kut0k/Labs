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
            std::copy(vertices.begin(),vertices.end() ,std::back_inserter(buff));
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
        std::copy(p.vertices.begin(), p.vertices.end(),std::back_inserter(vertices));
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
        std::for_each(vertices.begin(), vertices.end(), [&](const Point &v){
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
            std::copy(vertices.begin(), vertices.end(),std::back_inserter(vertices));
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
        std::copy(p.vertices.begin(),p.vertices.end() ,std::back_inserter(vertices));
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
    std::for_each(p.vertices.begin(), p.vertices.end(), [&](const Polyhedron& x){stream << x << std::endl;})
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
        std::copy(p.vertices.begin(),p.vertices.end() ,std::back_inserter(buff));
        delete[] p.vertices;
        p.vertices = buff;
    }
    return stream
}