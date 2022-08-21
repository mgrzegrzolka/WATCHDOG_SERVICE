#include <string>
#include <chrono>
#include <ctime>  
#include <windows.h>
#include <cstdio>
#include <tlhelp32.h>
#include <codecvt>

class monitObject
{
public:
    monitObject(Params *pObject) {}
    ~monitObject() {}
    void checkAllConditions();
    bool isProcessRunning(const wchar_t *processName);
    bool runProcess();

private:
    std::string monitProcess, argv;
    int testFrequency, state;
};