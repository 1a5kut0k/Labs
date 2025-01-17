#ifndef PREM 
#define PREM

#include <string>
#include <iostream>
//#include <fmt/core.h>
#include <format>
enum RType {Lux, Single, Multiple};

class Premises{
protected:
    bool busy;
public:
    Premises(){};
    virtual bool state() = 0;
    virtual void take(int = 1, int = 0, int = 1900, int = 0, int = 1) = 0;
    virtual void release(int = -1) = 0;
    virtual RType type() = 0;
    virtual std::string info() = 0;
    virtual int get_tariff() = 0;
    virtual int get_stay_time(int = 0) = 0;
    virtual int get_rooms() = 0;
    virtual int get_taked_rooms() = 0;
};
std::ostream& operator << (std::ostream &, Premises &);

#endif