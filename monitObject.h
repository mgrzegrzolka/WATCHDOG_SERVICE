#ifndef ___monitObject___
#define ___monitObject___

#include <string>
#include <chrono>
#include <ctime>  
#include <windows.h>
#include <cstdio>
#include <tlhelp32.h>
#include <codecvt>
#include "objParams.h"

class monitObject
{
public:
    monitObject(objParams *pObjects) {}
    ~monitObject() {}
    void checkAllConditions();
    bool isProcessRunning(const wchar_t *processName);
    bool runProcess();

private:
    std::string monitProcess, runProcess, argv;
    int testFrequency, state;
};

#endif /* ___monitObject___ */