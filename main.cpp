#include <iostream>
#include <vector>
#include <memory>
#include "objParams.h"
#include "monitObject.h"
#include <spdlog/spdlog.h>
#include <spdlog/sinks/rotating_file_sink.h>
#include <spdlog/sinks/stdout_sinks.h>
#include <spdlog/sinks/stdout_color_sinks.h>


int main( int argc, char * argv[ ] )
{

    std::vector<spdlog::sink_ptr> sinks;
    std::shared_ptr<spdlog::sinks::stdout_color_sink_mt> stdout_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
    sinks.push_back(stdout_sink);

#ifdef DEBUG_MODE
    sinks.push_back(std::make_shared<spdlog::sinks::rotating_file_sink_mt>("log\\wd_log.log", 1048576 * 5, 5));
#else
    sinks.push_back(std::make_shared<spdlog::sinks::rotating_file_sink_mt>("c:\\wd\\log\\wd_log.log", 1048576 * 5, 5));
#endif
    auto logger = std::make_shared<spdlog::logger>("wd_log", begin(sinks), end(sinks));
    
    objParams *params = new objParams;
    std::vector<monitObject*> mObjects;
    for(int i = 0; i < params->getNoofObjects(); i++) {
        mObjects.push_back(new monitObject(params, i));
    }
    logger->info("Number of monit objects: {}", mObjects.size());

    do {
        for(monitObject* ob : mObjects) {
            if(ob->checkAllConditions()) {
                ob->doAction();
            }
        }
        Sleep(100);
    } while(true);

    return 0;
}