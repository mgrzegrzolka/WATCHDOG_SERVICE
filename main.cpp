#include <iostream>
#include <windows.h>
#include <cstdio>
#include <tlhelp32.h>
#include <codecvt>
#include <vector>
#include "objParams.h"
#include "monitObject.h"
#include <tchar.h>

int main( int argc, char * argv[ ] )
{

    objParams *params = new objParams;
    std::vector<monitObject*> mObjects;
    for(int i = 0; i < params->getNoofObjects(); i++) {
        std::cout << "NOOF:" << i << "\n";
        mObjects.push_back(new monitObject(params, i));
    }

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