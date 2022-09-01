#ifndef ___monitObject___
#define ___monitObject___

#include <iostream>
#include <string>
#include <chrono>
#include <ctime>  
#include <windows.h>
#include <cstdio>
#include <tlhelp32.h>
#include <codecvt>
#include <chrono>
#include <ctime>
#include <fstream>
#include <spdlog/spdlog.h>

#include "objParams.h"

class monitObject
{
public:
    monitObject(objParams *pObjects, int p_id);
    ~monitObject() {}
    bool checkAllConditions();
    bool isProcessRunning(std::string m_monitProcess);
    bool startProcess();
    void doAction();
    void startup(LPCSTR lpApplicationName);

    static wchar_t *monitObject::convertCharWchar_t(char *c) 
    {
        const size_t cSize = strlen(c)+1;
        wchar_t* wc = new wchar_t[cSize];
        mbstowcs(wc, c, cSize);

        return wc;
    }
private:
    std::string objName, monitProcess, relatedProcess, runProcess, argv, semaphore;
    int state, id, monitProcessState, relatedProcessState;
    double testFrequency;
    std::chrono::system_clock::time_point lastTest;
};

#endif /* ___monitObject___ */