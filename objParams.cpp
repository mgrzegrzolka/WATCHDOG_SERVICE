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
        spdlog::get("wd_log")->info("The configuration file has been loaded.");
        config = nlohmann::json::parse(sFile);
    } else { 
        spdlog::get("wd_log")->error("Error to reading config file.");
        return false;
    }
    spdlog::get("wd_log")->info("Start reading configurations -------------------------------- ");
    for (nlohmann::json& el : config["config"]) {
        objName.push_back(el["ObjName"].get<std::string>());
        runProcess.push_back(el["RunProcess"].get<std::string>());
        nlohmann::json arvg_data = el["RunArvg"];
        std::vector<std::string> v_arvg;
        for(auto &a : arvg_data) {
            v_arvg.push_back(a);
        }
        runArvg.push_back(v_arvg);
        semaphore.push_back(el["Semaphore"].get<std::string>());
        testFrequency.push_back(el["TestFrequency"].get<int>());
        monitProcess.push_back(el["MonitProcess"].get<std::string>());
        relatedProcess.push_back(el["RelatedProcess"].get<std::string>());
        noof++;
        spdlog::get("wd_log")->info("   Object --------{}--------", objName.size());
        spdlog::get("wd_log")->info("       [ObjName][{}] - [RunProcess][{}]", objName.back(), runProcess.back());
        spdlog::get("wd_log")->info("       [semaphore][{}]", semaphore.back());
        spdlog::get("wd_log")->info("       [runArvg][{}]", v_arvg.size());
        for(auto &a : runArvg.back()) {
            spdlog::get("wd_log")->info("           [arvg][{}]", a);
        }
        spdlog::get("wd_log")->info("       [monitProcess][{}]", monitProcess.back());
        spdlog::get("wd_log")->info("       [relatedProcess][{}]", relatedProcess.back());
    }
    spdlog::get("wd_log")->info("Reading configurations completed -------------------------------- ");
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

std::vector<std::string> objParams::getRunArvg(int id)
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