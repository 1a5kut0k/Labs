/*!
    \file
    \brief Файл реализации класса App

    Данный файл содержит в себе реализацию методов класса App (Приложения)
*/

#include "app.h"

/*!
    Поиск - поиск элемента таблицы по id
    \param i id элемента
    \return Индекс элемента в таблице
*/
int App::search(int i){
    if(i < 0) return -1;
    int l = -1, r = this->data.size();
    while(l < (r - 1)){
        int m = (l + r) / 2;
        if(this->data[m].id == i) return m;
        if(this->data[m].id < i) l = m;
        else r = m;
    }
    if(this->data[r].id == i) return r;
    return -1;
}

/*!
    Создание - создание экземпляра номера
    \param t Тип номера
    \param tar Суточный тариф номера
    \param rooms Количество комнат в номере (используется только для многоместных и люкс номеров)
*/
void App::create(RType t, int tar, int rooms){
    switch(t){
        case RType::Single:
            this->data.add(new Single_room(tar));
            break;
        case RType::Lux:
            this->data.add(new Lux_room(tar, rooms));
            break;
        case RType::Multiple:
            this->data.add(new Multiple_room(tar, rooms));
            break;
        default:
            return;
    }
}

/*!
    Вывод всей таблицы
*/
void App::show(){
    this->data.show();
}

/*!
    Вывод свободных номеров таблицы
*/
void App::info(){
    for(int i = 0; i < this->data.size(); i++){
        if(this->data[i].ptr->state() == false){
            std::cout<<this->data[i].id<<" : "<<*(this->data[i].ptr)<<std::endl;
        }
    }
}

/*!
    Занять номер - занять свободный номер посетителем
    \param t Тип номера
    \param day День заселения
    \param month Месяц заселения
    \param year Год заселения
    \param st_time Дни проживания
    \param g_n Количество гостей (только для номеров типа люкс)
*/
void App::take(RType t, int day, int month, int year, int st_time, int g_n){
    for(int i = 0; i < this->data.size(); i++){
        if((this->data[i].ptr->type() == t) && (this->data[i].ptr->state() == false)){
            this->data[i].ptr->take(day, month, year, st_time, g_n);
            return;
        }
    }
}

/*!
    Освободить номер - освободить определенный номер в таблице
    \param i id номера в таблице
    \param j Индекс посетителя в многоместном номере (только для номеров многоместного типа)
    \return Возвращает плату за проживание
*/
int App::release(int i, int j){
    int pos = search(i);
    if(pos == -1) return 0;
    int tar = this->data[pos].ptr->get_tariff();
    int st_time = this->data[pos].ptr->get_stay_time(j);
    this->data[pos].ptr->release(j);
    return tar * st_time;
}

void App::busy_async(RType t, std::promise<int> f, std::promise<int> s){
    int n = this->data.size();
    int taked_rooms = 0;
    int rooms_n = 0;
    for(int i = 0; i < n; i++){
        if(this->data[i].ptr->type() == t){
            taked_rooms += this->data[i].ptr->get_taked_rooms();
            rooms_n += this->data[i].ptr->get_rooms();
        }
    }
    f.set_value(taked_rooms);
    s.set_value(rooms_n);
}

/*!
    Перегрузка оператора [] - возвращает i-й элемент таблицы
*/
Row<Premises> App::operator [] (int i){
    return this->data[i];
}


/*!
    Занятость таблицы - определяет занятость таблицы
    \return Возвращает занятость таблицы - число от 0 до 1
*/
double App::busy(){
    std::promise<int> size_single_promise, size_lux_promise, size_multiple_promise;
    std::promise<int> taked_single_promise, taked_lux_promise, taked_multiple_promise;
    auto size_single = size_single_promise.get_future();
    auto size_lux = size_lux_promise.get_future();
    auto size_multiple = size_multiple_promise.get_future();
    auto taked_single = taked_single_promise.get_future();
    auto taked_lux = taked_lux_promise.get_future();
    auto taked_multiple = taked_multiple_promise.get_future();

    std::thread single_th(&App::busy_async, this, RType::Single, std::move(taked_single_promise), std::move(size_single_promise));
    std::thread lux_th(&App::busy_async, this, RType::Lux, std::move(taked_lux_promise), std::move(size_lux_promise));
    std::thread multiple_th(&App::busy_async, this, RType::Multiple, std::move(taked_multiple_promise), std::move(size_multiple_promise));

    int size = size_single.get() + size_lux.get() + size_multiple.get();
    int taked = taked_single.get() + taked_lux.get() + taked_multiple.get();
    
    single_th.join();
    lux_th.join();
    multiple_th.join();
    if(size == 0) return 0;
    return (taked / size);
}

double App::busy_sync(){
    int n = this->data.size();
    int taked_rooms = 0;
    int rooms = 0;
    for(int i = 0; i < n; i++){
        taked_rooms += this->data[i].ptr->get_taked_rooms();
        rooms += this->data[i].ptr->get_rooms();
    }
    if(rooms == 0) return 0;
    return (taked_rooms / rooms);
}