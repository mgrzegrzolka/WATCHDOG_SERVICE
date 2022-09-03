#ifndef ___objParams___
#define ___objParams___

#include <string>
#include <vector>
#include <fstream>
#include <json.hpp>
#include <spdlog/spdlog.h>
#include <chrono>
#include <ctime>
#include <iostream>

#define READ_AGAIN_CONFIG_TIME 60
class objParams
{
public:
    objParams() : noof(0)
    { 
        std::chrono::system_clock::time_point controlTime, lastTest;
        while(1) {
            std::chrono::system_clock::time_point controlTime = std::chrono::system_clock::now();
            std::chrono::duration<double> elapsed_seconds = controlTime - lastTest;
            if(elapsed_seconds.count() > READ_AGAIN_CONFIG_TIME) {
                if(readConfig()) break;
                lastTest = std::chrono::system_clock::now();
            }
            Sleep(100);
        }
    }
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