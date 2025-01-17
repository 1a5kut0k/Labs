/*!
    \file
    \brief Файл реализации класса Multiple_room

    Данный файл содержит в себе реализацию методов класса Multiple_room (Многоместный номер)
*/

#include "multiple_room.h"

/*!
    Конструктор
    \param tar Суточный тариф проживания
    \param m_n Количество комнат
*/
Multiple_room::Multiple_room(int tar, int m_n):taked_rooms{0}{
    rooms = m_n > 4 ? 4 : m_n;
    rooms = rooms < 2 ? 2 : rooms;
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
*/
void Multiple_room::take(int day, int month, int year, int st_time, int null){
    if(busy == false){
        busy = true;
        if(date_arr.size() < rooms){
            tm d;
            d.tm_mday = day;
            d.tm_mon = month;
            d.tm_year = year - 1900;
            date_arr.push_back(d);
            if(st_time < 1) st_time = 1;
            stay_time_arr.push_back(st_time);
            taked_rooms++;
        }
    }
}

/*!
    Геттер тарифа
    \return Возвращает суточный тариф проживания
*/
int Multiple_room::get_tariff(){return tariff;}

/*!
    Геттер дней проживания определенного гостя
    \param i Индекс комнаты гостя
    \return Возвращает количество дней проживания
*/
int Multiple_room::get_stay_time(int i){
    if(i == -1) i = date_arr.size() - 1;
    if((i < 0) || (i >= date_arr.size())) return -1;
    return stay_time_arr[i];
};

/*!
    Освободить комнату определенного гостя
    \param i Индекс комнаты гостя
*/
void Multiple_room::release(int i){
    if(i < -1) return;
    if(busy == true){
        if(i < date_arr.size()){
            if(i == -1){
                i = date_arr.size() - 1;
            }
            date_arr.erase(date_arr.begin() + i);
            stay_time_arr.erase(stay_time_arr.begin() + i);
            if(date_arr.size() == 0) busy = 0;
            taked_rooms--;
        }
    }
}

/*!
    Состояние номера
    \return Возвращает true если номер полностью занят, false в противном случае
*/
bool Multiple_room::state(){
    return (taked_rooms == rooms);
}

/*!
    Геттер занятых комнат
    \return Возвращает количество занятых комнат
*/
int Multiple_room::get_taked_rooms(){
    return taked_rooms;
}

/*!
    Геттер количества комнат
    \return Возвращает количество комнат
*/
int Multiple_room::get_rooms(){
    return rooms;
}

/*!
    Информация о номере
    \return Возвращает строку с информацией о номере
*/
std::string Multiple_room::info(){
    if(busy == false){
        return std::string("Multiple busy: 0\n");
    }
    std::string res = std::format("Multiple busy: 1, taked_rooms: {}\n", date_arr.size());
    for(int i = 0; i < date_arr.size(); i++){
        res = res + std::format("\t{}: {}.{}.{}, stay time: {}, tariff: {}\n", i, date_arr[i].tm_mday, date_arr[i].tm_mon + 1, date_arr[i].tm_year + 1900, stay_time_arr[i], tariff);
    }
    return res;
}

/*!
    Тип номера
    \return Возвращает тип номера
*/
RType Multiple_room::type(){
    return RType::Multiple;
}
