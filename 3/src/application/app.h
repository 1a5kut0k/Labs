#include "../classes/lux_room/lux_room.h"
#include "../classes/multiple_room/multiple_room.h"
#include "../classes/single_room/single_room.h"
#include "../classes/table/table.h"
#include "../classes/premises/premises.h"
#include <future>

class App{
private:
    Table<Premises> data;
    void busy_async(RType, std::promise <int>, std::promise <int>);
public:
    int search(int);
    App(){data = Table <Premises>();}
    void take(RType, int, int, int, int, int);
    int release(int, int);
    void info();
    void show();
    double busy();
    void create(RType, int, int);
    Row<Premises> operator [] (int);
};
