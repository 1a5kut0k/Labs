/*!
    \file
    \brief Файл реализации класса Lux_room

    Данный файл содержит в себе реализацию методов класса Lux_room (Номер люкс)
*/

#include "single_room.h"

/*!
    Конструктор
    \param tar Суточный тариф проживания
*/
Single_room::Single_room(int tar = 0):busy{false}, stay_time{0}{
    tariff = tar < 0 ? 0 : tar;
}

/*!
    Занять номер - занять номер посетителем
    \param t Тип номера
    \param day День заселения
    \param month Месяц заселения
    \param year Год заселения
    \param st_time Дни проживания
*/
void Single_room::take(int day = 1, int month = 0, int year = 1900, int st_time = 0, int null = 1){
    if(busy == false){
        busy = true;
        date.mday = day;
        date.mon = month;
        date.year = year - 1900;
        stay_time = st_time > 0 ? st_time : 1;
    }
}

/*!
    Геттер тарифа
    \return Возвращает суточный тариф проживания
*/
int Single_room::get_tariff(){return tariff;}

/*!
    Геттер дней проживания
    \return Возвращает количество дней проживания
*/
int Single_room::get_stay_time(int num){return stay_time;}

/*!
    Освободить номер
*/
void Single_room::release(int null = 0){
    if(busy == true){
        busy = false;
        tariff = 0;
        date.mday = 1;
        date.mon = 0;
        date.year = 0;
        stay_time = 0;
    }
}

/*!
    Геттер количества комнат
    \return Возвращает количество комнат
*/
int Single_room::get_rooms(){return 1;}

/*!
    Геттер занятых комнат
    \return Возвращает количество занятых комнат
*/
int Single_room::get_taked_rooms(){return busy;}

/*!
    Информация о номере
    \return Возвращает строку с информацией о номере
*/
std::string Single_room::info(){
    if(busy == 0){
        return std::string("Single busy: 0\n");
    }
    return format("Single busy: 1\nday: {}\nmonth: {}\nyear: {}\nstay time: {}\ntariff: {}\n", date.mday, date.mon + 1, date.year + 1900, stay_time, tariff);
}

/*!
    Состояние номера
    \return Возвращает true если номер занят, false в противном случае
*/
bool Single_room::state(){
    return busy;
}

/*!
    Тип номера
    \return Возвращает тип номера
*/
RType Single_room::type(){
    return RType::Single;
}

/*!
    Перегрузка оператора вывода (<<)
*/
std::ostream& operator << (std::ostream &os, const Premises &r){
    return os << r.info();
}