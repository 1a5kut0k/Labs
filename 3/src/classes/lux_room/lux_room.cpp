/*!
    \file
    \brief Файл реализации класса Lux_room

    Данный файл содержит в себе реализацию методов класса Lux_room (Номер люкс)
*/
#include "lux_room.h"

/*!
    Конструктор
    \param tar Суточный тариф проживания
    \param r_n Количество комнат
*/
Lux_room::Lux_room(int tar, int r_n):stay_time{0}, rooms_n{r_n}{
    tariff = tar > 0 ? tar : 0;
    busy = false;
}

/*!
    Занять номер - занять номер посетителем
    \param t Тип номера
    \param day День заселения
    \param month Месяц заселения
    \param year Год заселения
    \param st_time Дни проживания
    \param g_n Количество гостей
*/
void Lux_room::take(int day, int month, int year, int st_time, int g_n){
    if(busy == false){
        busy = true;
        date.tm_mday = day;
        date.tm_mon = month;
        date.tm_year = year - 1900;
        stay_time = st_time < 1 ? 1 : st_time;
        guests_n = g_n > 2 ? 2 : 1;
    }
}

/*!
    Геттер тарифа
    \return Возвращает суточный тариф проживания
*/
int Lux_room::get_tariff(){return tariff;}

/*!
    Геттер количества комнат
    \return Возвращает количество комнат
*/
int Lux_room::get_rooms(){return rooms_n;}

/*!
    Геттер занятых комнат
    \return Возвращает количество занятых комнат
*/
int Lux_room::get_taked_rooms(){return busy == 1 ? rooms_n : 0;}

/*!
    Геттер дней проживания
    \return Возвращает количество дней проживания
*/
int Lux_room::get_stay_time(int num){return stay_time;}

/*!
    Освободить номер
*/
void Lux_room::release(int null){
    if(busy == true){
        busy = false;
        tariff = 0;
        date.tm_mday = 1;
        date.tm_mon = 0;
        date.tm_year = 0;
        stay_time = 0;
        guests_n = 0;
    }
}

/*!
    Состояние номера
    \return Возвращает true если номер занят, false в противном случае
*/
bool Lux_room::state(){
    return busy;
}

/*!
    Информация о номере
    \return Возвращает строку с информацией о номере
*/
std::string Lux_room::info(){
    if(busy == 0){
        return std::string("Lux busy: 0\n");
    }
    return std::format("Lux busy: 1, {}.{}.{}, stay time: {}, tariff: {} guests: {}\n", date.tm_mday, date.tm_mon + 1, date.tm_year + 1900, stay_time, tariff, guests_n);
}

/*!
    Тип номера
    \return Возвращает тип номера
*/
RType Lux_room::type(){
    return RType::Lux;
}
