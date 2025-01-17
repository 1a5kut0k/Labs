#include "../classes/lux_room/lux_room.h"
#include "../classes/multiple_room/multiple_room.h"
#include "../classes/single_room/single_room.h"
#include "../classes/table/table.h"
#include "../classes/premises/premises.h"
#include <future>
#include <thread>
#include <pthread.h>

class App{
private:
    Table<Premises> data;
    void busy_async(RType, std::promise <int>, std::promise <int>);
public:
    int search(int);
    App(){data = Table <Premises>();}
    void take(RType, int = 1, int = 0, int = 1900, int = 0, int = -1);
    int release(int, int = -1);
    void info();
    void show();
    double busy();
    double busy_sync();
    void create(RType, int, int = 2);
    Row<Premises> operator [] (int);
};
