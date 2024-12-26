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
void App::create(RType t, int tar, int rooms = 2){
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
void App::take(RType t, int day = 1, int month = 0, int year = 1900, int st_time = 0, int g_n = -1){
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
int App::release(int i, int j = -1){
    int pos = search(i);
    if(pos == -1) return 0;
    int tar = this->data[pos].ptr->get_tariff();
    int st_time = this->data[pos].ptr->get_stay_time(j);
    this->data[pos].ptr->release(j);
    return tar * st_time;
}

void App::busy_async(RType t, std::promise<int> f, std::promise<int> s){
    int n = this->data.size();
    int free_rooms = 0;
    int rooms_n = 0;
    for(int i = 0; i < n; i++){
        if(this->data[i].ptr->type() == t){
            rooms_n++;
            if(this->data[i].ptr->state() == false){
                if(t == RType::Multiple)
                    free_rooms += (this->data[i].ptr->get_rooms() - this->data[i].ptr->get_taked_rooms());
                else
                    free_rooms++;
            }
        }
    }
    f.set_value(free_rooms);
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
    std::promise<int> free_single_promise, free_lux_promise, free_multiple_promise;
    auto size_single = size_single_promise.get_future();
    auto size_lux = size_lux_promise.get_future();
    auto size_multiple = size_multiple_promise.get_future();
    auto free_single = free_single_promise.get_future();
    auto free_lux = free_lux_promise.get_future();
    auto free_multiple = free_multiple_promise.get_future();

    std::thread single_th(&App::busy_async, this, RType::Single, free_single_promise, size_single_promise);
    std::thread lux_th(&App::busy_async, RType::Lux, std::move(free_lux_promise), std::move(size_lux_promise));
    std::thread multiple_th(&App::busy_async, RType::Multiple, std::move(free_multiple_promise), std::move(size_multiple_promise));

    int size = size_single.get() + size_lux.get() + size_multiple.get();
    int free_rooms = free_single.get() + free_lux.get() + free_multiple.get();
    
    single_th.join();
    lux_th.join();
    multiple_th.join();
    if(size == 0) return 0;
    return (1 - free_rooms / size);
}