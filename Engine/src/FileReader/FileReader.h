#pragma once

#include "Core/CoreApi.h"
#include "Core/Types.h"

class FileReader
{
public:
    static string GetCurrentDir()
    {
        char* directoryBuffer = new char[MAX_PATH + 1];
        GetCurrentDirectoryA(MAX_PATH, directoryBuffer);
        return (string)directoryBuffer;
    }

    static string GetDataFromCurrentDir(string relativePath, string dataName)
    {
        HANDLE fileHandle;
        string fullPath = GetCurrentDir() + "\\" + relativePath + "\\" + dataName;

        bool bIsFileOk;
        DWORD countByte;

        fileHandle = CreateFileA(fullPath.c_str(),GENERIC_READ,FILE_SHARE_READ, nullptr,OPEN_ALWAYS,
                        FILE_ATTRIBUTE_READONLY, nullptr);

        const DWORD fileSize = GetFileSize(fileHandle, nullptr);

        char* stringFile = new char[fileSize + 1];
        stringFile[fileSize] = {'\0'};

        try
        {
            if(bIsFileOk = ReadFile(fileHandle, stringFile, fileSize, &countByte, nullptr))
            {
                return string(stringFile);
            }
            else
            {
                throw "Unexpected file or path.";
            }
        }
        catch (const string exception)
        {
            printf("Error: %s", (char*)&exception);
            return nullptr;
        }
    }
};
