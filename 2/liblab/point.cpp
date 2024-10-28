/*!
    \file
    \brief Файл реализации класса Point

    Данный файл содержит в себе реализацию методов и операторов класса Point (Точка)
*/

#include "point.h"

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
        Перегрузка оператора копирующего присваивания '='
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