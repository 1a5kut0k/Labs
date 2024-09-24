#include <iostream>
#include <string>
#include <vector>
#include <algorithm> 
#include <cstring>
#include <unordered_map>

struct DataType {
    std::string key;
    std::string type;
};

inline void trim(std::string &);
std::string parseJson(const std::string &, const std::string &);
int getJson(std::string &);
char* parseJson(const char* &, const char* &);
