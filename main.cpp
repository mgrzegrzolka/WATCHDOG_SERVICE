#include <iostream>
#include <windows.h>
#include <cstdio>
#include <tlhelp32.h>
#include <codecvt>
#include "objParams.h"

SERVICE_STATUS_HANDLE g_hStatus;
SERVICE_STATUS g_Status;

DWORD CALLBACK SvcHandlerEx( DWORD dwControl, DWORD dwEventType, LPVOID lpEventData, LPVOID lpContext )
{
    switch( dwControl )
    {
    case SERVICE_CONTROL_PAUSE:
        g_Status.dwCurrentState = SERVICE_PAUSED;
        break;
    case SERVICE_CONTROL_CONTINUE:
        g_Status.dwCurrentState = SERVICE_RUNNING;
        break;
    case SERVICE_CONTROL_STOP:
    case SERVICE_CONTROL_SHUTDOWN:
        g_Status.dwCurrentState = SERVICE_STOPPED;
        break;
    }
    SetServiceStatus( g_hStatus, & g_Status );
    return NO_ERROR;
}

VOID CALLBACK ServiceMain( DWORD dwArgc, LPTSTR * lpszArgv )
{
    g_Status.dwServiceType = SERVICE_WIN32_OWN_PROCESS;
    g_Status.dwCurrentState = SERVICE_RUNNING;
    g_Status.dwControlsAccepted = SERVICE_ACCEPT_PAUSE_CONTINUE | SERVICE_ACCEPT_STOP |
    SERVICE_ACCEPT_SHUTDOWN;
    g_Status.dwWin32ExitCode = NO_ERROR;
    g_Status.dwServiceSpecificExitCode = 0;
    g_Status.dwCheckPoint = 0;
    g_Status.dwWaitHint = 0;
    g_hStatus = RegisterServiceCtrlHandlerEx( "TestService", SvcHandlerEx, 0 );
    SetServiceStatus( g_hStatus, & g_Status );
}

wchar_t *convertCharWchar_t(char *c) 
{
    const size_t cSize = strlen(c)+1;
    wchar_t* wc = new wchar_t[cSize];
    mbstowcs(wc, c, cSize);

    return wc;
}

bool IsProcessRunning(const wchar_t *processName)
{
    bool exists = false;
    PROCESSENTRY32 entry;
    entry.dwSize = sizeof(PROCESSENTRY32);

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

int main( int argc, char * argv[ ] )
{
    //SERVICE_TABLE_ENTRY svc[ ] =
    //{
    //    { "TestService", ServiceMain },
    //    { NULL, NULL }
    //};
    //StartServiceCtrlDispatcher( svc );
    objParams params;
    const wchar_t pName[] = L"Code.exe";

    if (IsProcessRunning(pName)) {
        printf("Exist\n");
    } else {
        printf("Not exist\n");
    }
    
    return 0;
}