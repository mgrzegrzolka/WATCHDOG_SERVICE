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
    monitObject(objParams *pObjects, int p_id);
    ~monitObject() {}
    void checkAllConditions();
    bool isProcessRunning();
    bool startProcess();

    static wchar_t *monitObject::convertCharWchar_t(char *c) 
    {
        const size_t cSize = strlen(c)+1;
        wchar_t* wc = new wchar_t[cSize];
        mbstowcs(wc, c, cSize);

        return wc;
    }
private:
    std::string objName, monitProcess, runProcess, argv, semaphore;
    int testFrequency, state, id;
};

#endif /* ___monitObject___ */