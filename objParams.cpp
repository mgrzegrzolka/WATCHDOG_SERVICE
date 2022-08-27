#include "objParams.h"
#include <iostream>

bool objParams::readConfig()
{
#ifdef DEBUG_MODE
    std::ifstream sFile("settings.json");
#else
    std::ifstream sFile("c:\\wd\\settings.json");
#endif
    if(sFile) {
     printf("The configuration file has been loaded \n");
     config = nlohmann::json::parse(sFile);
    } else return false;
    
    for (nlohmann::json& el : config["config"]) {
        objName.push_back(el["ObjName"].get<std::string>());
        runProcess.push_back(el["RunProcess"].get<std::string>());
        runArvg.push_back(el["RunArvg"].get<std::string>());
        semaphore.push_back(el["Semaphore"].get<std::string>());
        testFrequency.push_back(el["TestFrequency"].get<int>());
        monitProcess.push_back(el["MonitProcess"].get<std::string>());
        relatedProcess.push_back(el["RelatedProcess"].get<std::string>());
        noof++;
    }
    
    return true;
}
bool objParams::reloadConfig()
{
    return true;
}

std::string objParams::getObjName(int id)
{
    return objName[id];
}

std::string objParams::getMonitProcess(int id)
{
    return monitProcess[id];
}

std::string objParams::getRelatedProcess(int id)
{
    return relatedProcess[id];
}

std::string objParams::getRunProcess(int id)
{
    return runProcess[id];
}

std::string objParams::getRunArvg(int id)
{
    return runArvg[id];
}

std::string objParams::getSemaphore(int id)
{
    return semaphore[id];
}

int objParams::getTestFrequency(int id)
{
    return testFrequency[id];
}

 int objParams::getNoofObjects()
 {
    return noof;
 }