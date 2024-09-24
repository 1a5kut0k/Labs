#include "liblab.h"

inline void ltrim(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) {
        return !std::isspace(ch);
    }));
}

inline void rtrim(std::string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch) {
        return !std::isspace(ch);
    }).base(), s.end());
}

inline void trim(std::string &s) {
    rtrim(s);
    ltrim(s);
}

bool islong(std::string &str){
    std::string::size_type s;
    try{
        std::stol(str, &s);
    }
    catch (std::invalid_argument){
        return false;
    }
    if(str.length() == s) return true;
    return false;
}

bool isdouble(std::string &str){
    std::string::size_type s;
    std::cout<<str<<std::endl;
    try{
        std::stod(str, &s);
    }
    catch (std::invalid_argument){
        return false;
    }
    if(str.length() <= s) return true;
    return false;
}

std::string parseJson(const std::string &name, const std::string &json) {
    std::vector<DataType> data;
    std::string currentKey;
    std::string currentValue;
    bool inKey = true;
    bool inString = false;
    if(json[0] != '{' && json[json.length() - 1] != '}'){
        throw std::runtime_error("Invalid Syntax");
    }
    for (char c : json) {
        if (c == '"') {
            if(inKey)
                inString = !inString;
            if(inString && !inKey)
                currentValue.push_back('"');
        } else if (c == ':') {
            inKey = false;
            inString = !inString;
        } else if (c == ',') {
            trim(currentKey);
            trim(currentValue);
            if (inString) {
                inString = false;
            }
            if (currentValue == "true" || currentValue == "false") {
                data.push_back({currentKey, "bool"});
            } else if (currentValue == "null") {
                data.push_back({currentKey, "void*"});
            } else if (isdouble(currentValue)){
                data.push_back({currentKey, "double"});
            } else if (islong(currentValue)) {
                data.push_back({currentKey, "long"});
            } else if ((std::count(currentValue.begin(),currentValue.end(), '"') == 2) && (currentValue[0] == '"') && (currentValue[currentValue.length() - 1] == '"')){
                data.push_back({currentKey, "char*"});
            }
            else{
                throw std::runtime_error("Invalid Syntax");
            }
            currentKey.clear();
            currentValue.clear();
            inKey = true;
            inString = false;
        } else if (inString) {
            if (inKey) {
                currentKey += c;
            } else {
                currentValue += c;
            }
        }
    }
    trim(currentKey);
    trim(currentValue);
    if (!currentKey.empty() && !currentValue.empty()) {
        if (currentValue == "true" || currentValue == "false") {
            data.push_back({currentKey, "bool"});
        } else if (currentValue == "null") {
             data.push_back({currentKey, "void*"});
        } else if (isdouble(currentValue)){
            data.push_back({currentKey, "double"});
        } else if (islong(currentValue)) {
            data.push_back({currentKey, "long"});
        } else if ((std::count(currentValue.begin(),currentValue.end(), '"') == 2) && (currentValue[0] == '"') && (currentValue[currentValue.length() - 1] == '"')){
            data.push_back({currentKey, "char*"});
        }
        else{
            throw std::runtime_error("Invalid Syntax");
        }
    }
    std::string res("struct ");
    res.append(name);
    res.append(" {\n");
    for(const auto &d : data){
        res.push_back('\t');
        res.append(d.type);
        res.push_back(' ');
        res.append(d.key);
        res.append(";\n");
    }
    res.push_back('}');
    return res;
}

char* parseJson(const char* &name, const char* &json){
    std::string n(name);
    std::string js(json);
    std::string r = parseJson(name, json);
    char *res = new char[r.length() - 1];
    std::strcpy(res, r.c_str());
    return res;
}

int getJson(std::string &json){
    std::getline(std::cin, json, '}');
    if(std::cin.eof()){
        return EOF;
    }
    return 0;
}