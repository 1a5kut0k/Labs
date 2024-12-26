/*!
    \file
    \brief Файл реализации класса Interface

    Данный файл содержит в себе реализацию методов класса Interface (Интерфейс)
*/

#include "interface.h"

/*!
    Занять номер
*/
void Interface::take(){
    RType t;
    int c;
    std::cout<<"Введите тип номера\n1. Одноместный\n2. Люкс\n3. Многоместный\n";
    std::cin>>c;
    std::string s("Введите день, месяц, год заселения, количество дней проживания");
    switch(c){
        case 1:
            t = RType::Single;
            break;
        case 2:
            t = RType::Lux;
            s += " и число гостей";
            break;
        case 3:
            t = RType::Multiple;
            s += " и число комнат";
            break;
        default:
            return;
    };
    std::cout<<s<<std::endl;
    int day, month, year, st_time, num = -1;
    std::cin>>day>>month>>year>>st_time;
    if(c != 1) std::cin>>num; 
    app.take(t, day, month, year, st_time, num);
}

/*!
    Освободить номер
*/
void Interface::release(){
    std::cout<<"Введите id"<<std::endl;
    int id;
    std::cin>>id;
    int i = app.search(id);
    int j = -1;
    if(app[i].ptr->type() == RType::Multiple){
        std::cout<<"Введите индекс комнаты"<<std::endl;
        std::cin>>j;
    }
    app.release(i, j);
}

/*!
    Создать номер
*/
void Interface::create(){
    std::cout<<"Введите тип номера\n1. Одноместный\n2. Люкс\n3. Многоместный"<<std::endl;
    int c = 0;
    RType t;
    std::cin>>c;
    switch(c){
        case 1:
            t = RType::Single;
            break;
        case 2:
            t = RType::Lux;
            break;
        case 3:
            t = RType::Multiple;
            break;
        default:
            return;
    }
    std::cout<<"Введите тариф\n";
    int tar;
    std::cin>>tar;
    int rooms = 2;
    if(c != 1){
        std::cout<<"Введите количество комнат\n";
        std::cin>>rooms;
    }
    app.create(t, tar, rooms);
}

/*!
    Запуск меню
*/
void Interface::menu(){
    while(!std::cin.eof()){
        std::cout<<"1. Создать номер\n2. Занять номер\n3. Освободить номер\n4. Вывести все номера\n5. Вывести незанятые номера\n6. Вывести занятость таблицы\n";
        int c = 0;
        while((c < 1) || (c > 6)){
            std::cin>>c;
            if(std::cin.eof()) return;
        }
        switch(c){
            case 1:
                this->create();
                break;
            case 2:
                this->take();
                break;
            case 3:
                this->release();
                break;
            case 4:
                app.show();
                break;
            case 5:
                app.info();
                break;
            case 6:
                std::cout<<app.busy();
                break;
        }
    }
}