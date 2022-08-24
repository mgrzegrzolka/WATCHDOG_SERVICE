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

#include "objParams.h"

class monitObject
{
public:
    monitObject(objParams *pObjects, int p_id);
    ~monitObject() {}
    bool checkAllConditions();
    bool isProcessRunning();
    bool startProcess();
    void doAction();

    static wchar_t *monitObject::convertCharWchar_t(char *c) 
    {
        const size_t cSize = strlen(c)+1;
        wchar_t* wc = new wchar_t[cSize];
        mbstowcs(wc, c, cSize);

        return wc;
    }
private:
    std::string objName, monitProcess, runProcess, argv, semaphore;
    int state, id, monitProcessState;
    double testFrequency;
    std::chrono::system_clock::time_point lastTest;
};

#endif /* ___monitObject___ */