#include "monitObject.h"

monitObject::monitObject(objParams *pObjects, int p_id) : id(p_id), state(0), monitProcessState(0)
{
    objName = pObjects->getObjName(p_id);
    monitProcess = pObjects->getMonitProcess(p_id);
    runProcess = pObjects->getRunProcess(p_id);
    argv = pObjects->getRunArvg(p_id);
    testFrequency = pObjects->getTestFrequency(p_id);
    semaphore = pObjects->getSemaphore(p_id);
    lastTest = std::chrono::system_clock::now();
}

bool monitObject::checkAllConditions()
{
    std::chrono::system_clock::time_point controlTime = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = controlTime-lastTest;
    if(elapsed_seconds.count() > testFrequency) {
        
        if(isProcessRunning()) monitProcessState = 1;

        lastTest = std::chrono::system_clock::now();
        return true;
    }
    return false;
}

bool monitObject::isProcessRunning()
{
    bool exists = false;
    PROCESSENTRY32 entry;
    entry.dwSize = sizeof(PROCESSENTRY32);
    
    std::wstring widestr = std::wstring(monitProcess.begin(), monitProcess.end());
    const wchar_t* processName = widestr.c_str();

    HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);
    wchar_t *pName = 0;
    if (Process32First(snapshot, &entry)) {
        while (Process32Next(snapshot, &entry)) {
            pName = convertCharWchar_t(entry.szExeFile);
            if (!wcsicmp(pName, processName)) {
                exists = true;
            }
            delete[] pName;
            pName = 0;
        }
    }

    CloseHandle(snapshot);

    return exists;
}

bool monitObject::startProcess()
{
    return true;
}

void monitObject::doAction()
{
    if(!monitProcessState) {
        std::ifstream infile(runProcess);
        if(infile.good()) {
            std::cout << "Run file exist !!!" << "\n";
        } else {
            std::cout << "Run file not exist !!!" << "\n";
        }

    }
                //system("C:\\Program Files\\Program.exe");
}