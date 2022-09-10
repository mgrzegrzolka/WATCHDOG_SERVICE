#include "monitObject.h"

monitObject::monitObject(objParams *pObjects, int p_id) : id(p_id), state(0), monitProcessState(0), relatedProcessState(0)
{
    objName = pObjects->getObjName(p_id);
    monitProcess = pObjects->getMonitProcess(p_id);
    relatedProcess = pObjects->getRelatedProcess(p_id);
    runProcess = pObjects->getRunProcess(p_id);
    runArgv = pObjects->getRunArvg(p_id);
    testFrequency = pObjects->getTestFrequency(p_id);
    semaphore = pObjects->getSemaphore(p_id);
    lastTest = std::chrono::system_clock::now();
}

bool monitObject::checkAllConditions()
{
    monitProcessState = 0;
    relatedProcessState = 0;
    std::chrono::system_clock::time_point controlTime = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = controlTime - lastTest;
    if(elapsed_seconds.count() > testFrequency) {
        spdlog::get("wd_log")->info("[checkAllConditions] check each of conditions.");
        if(isProcessRunning(monitProcess)) monitProcessState = 1;
        spdlog::get("wd_log")->info("   [checkAllConditions][monitProcess][{}]", monitProcessState);
        if(isProcessRunning(relatedProcess)) relatedProcessState = 1;
        spdlog::get("wd_log")->info("   [checkAllConditions][relatedProcess][{}]", relatedProcess);
        lastTest = std::chrono::system_clock::now();
        return true;
    }
    return false;
}

bool monitObject::isProcessRunning(std::string m_monitProcess)
{
    bool exists = false;
    PROCESSENTRY32 entry;
    entry.dwSize = sizeof(PROCESSENTRY32);
    
    std::wstring widestr = std::wstring(m_monitProcess.begin(), m_monitProcess.end());
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
    if(!monitProcessState && relatedProcessState) {
        std::ifstream infile(runProcess);
        if(infile.good()) {
            spdlog::get("wd_log")->info("[runProcess] File exist. Start process.");
            startup(runProcess.c_str(), runArgv);
        } else spdlog::get("wd_log")->error("[runProcess] File not exist!");

    }
               
}

void monitObject::startup(LPCSTR lpApplicationName, std::vector<std::string> argv)
{
    // additional information
    STARTUPINFOA si;
    PROCESS_INFORMATION pi;

    // set the size of the structures
    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));

    // start the program up
    CreateProcessA
    (
        lpApplicationName,   // the path
        "",                // Command line
        NULL,                   // Process handle not inheritable
        NULL,                   // Thread handle not inheritable
        FALSE,                  // Set handle inheritance to FALSE
        NULL,     // Opens file in a separate console
        NULL,           // Use parent's environment block
        NULL,           // Use parent's starting directory 
        &si,            // Pointer to STARTUPINFO structure
        &pi           // Pointer to PROCESS_INFORMATION structure
    );
        // Close process and thread handles. 
        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);
}