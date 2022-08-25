#ifndef ___objParams___
#define ___objParams___

#include <string>
#include <vector>
#include <fstream>
#include "externals/json.hpp"

class objParams
{
public:
    objParams() : noof(0) { readConfig(); }
    ~objParams() {}
    bool readConfig();
    bool reloadConfig();
    std::string getObjName(int id);
    std::string getMonitProcess(int id);
    std::string getRelatedProcess(int id);
    std::string getSemaphore(int id);
    std::string getRunProcess(int id);
    std::string getRunArvg(int id);
    int getTestFrequency(int id);
    int getNoofObjects();
private:
    std::vector<std::string> objName, monitProcess, runProcess, relatedProcess, runArvg, semaphore;
    std::vector<int> testFrequency;
    int noof;
    nlohmann::json config;
};

#endif /*___objParams___*/