#ifndef ___objParams___
#define ___objParams___

#include <string>
#include <vector>
#include <fstream>
#include "externals/json.hpp"

class objParams
{
public:
    objParams() { readConfig(); }
    ~objParams() {}
    bool readConfig();
    bool reloadConfig();
    std::string getObjName(int id);
    std::string getRunProcess(int id);
    std::string getRunArvg(int id);
    std::string getSemaphore(int id);
    int getTestFrequency(int id);
private:
    std::vector<std::string> objName, runProcess, runArvg, semaphore;
    std::vector<int> testFrequency;
    nlohmann::json config;
};

#endif /*___objParams___*/