#include "../premises/premises.h"
#include <ctime>
#include <string>

class Single_room : private Premises{
private:
    tm date;
    int stay_time;
    int tariff;
public:
    Single_room();
    void take(int, int, int, int, int);
    void release();
    virtual std::string info();
    virtual std::string type();
}