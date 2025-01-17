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
Single_room::Single_room(int tar):stay_time{0}{
    tariff = tar < 0 ? 0 : tar;
    busy = false;
}

/*!
    Занять номер - занять номер посетителем
    \param t Тип номера
    \param day День заселения
    \param month Месяц заселения
    \param year Год заселения
    \param st_time Дни проживания
*/
void Single_room::take(int day, int month, int year, int st_time, int null){
    if(busy == false){
        busy = true;
        date.tm_mday = day;
        date.tm_mon = month;
        date.tm_year = year - 1900;
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
void Single_room::release(int null){
    if(busy == true){
        busy = false;
        tariff = 0;
        date.tm_mday = 1;
        date.tm_mon = 0;
        date.tm_year = 0;
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
    return std::format("Single busy: 1\nday: {}\nmonth: {}\nyear: {}\nstay time: {}\ntariff: {}\n", date.tm_mday, date.tm_mon + 1, date.tm_year + 1900, stay_time, tariff);
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
std::ostream& operator << (std::ostream &os, Premises &r){
    return os << r.info();
}