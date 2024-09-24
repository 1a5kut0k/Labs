#include "liblab/liblab.h"

int main() {
    std::string json;
    std::string name;
    std::string res;
    int op = 0;
    while(op == 0){
        std::cout<<"Введите название структуры:"<<std::endl;
        getline(std::cin, name);
        if(std::cin.eof()) break;
        trim(name);
        std::cout<<"Введите json:"<<std::endl;
        if(getJson(json) == EOF) break;
        trim(json);
        try{
            res = parseJson(name, json);
            std::cout<<res<<std::endl;
        }
        catch(std::runtime_error){
            std::cout<<"Неверный ввод"<<std::endl;
        }
        name.clear();
        json.clear();
        res.clear();
    }
    return 0;
}