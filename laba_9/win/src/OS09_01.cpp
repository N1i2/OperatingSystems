#include <windows.h>
#include <tchar.h>
#include <iostream>
#include <iomanip>

#define UNICODE
#define PATH_TO_FILE L"D:\\Univer\\OS\\laba_9\\OS09_01.txt"

BOOL printFileInfo(LPWSTR fileName);
BOOL printFileTxt(LPWSTR fileName);

int main()
{
    if (!printFileInfo((LPWSTR)PATH_TO_FILE))
    {
        std::wcerr << L"Information error." << std::endl;
        return 1;
    }

    if (!printFileTxt((LPWSTR)PATH_TO_FILE))
    {
        std::wcerr << L"Read error" << std::endl;
        return 1;
    }

    return 0;
}

BOOL printFileInfo(LPWSTR fileName)
{
    WIN32_FILE_ATTRIBUTE_DATA fileInfo;

    if (!GetFileAttributesExW(fileName, GetFileExInfoStandard, &fileInfo))
    {
        std::wcerr << L"Attribute error." << std::endl;
        return FALSE;
    }

    std::wcout << L"Name: " << fileName << std::endl;

    std::wcout << L"Type: ";
    if (fileInfo.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
    {
        std::wcout << L"Directory" << std::endl;
    }
    else
    {
        std::wcout << L"File" << std::endl;
    }

    LARGE_INTEGER fileSize;
    fileSize.LowPart = fileInfo.nFileSizeLow;
    fileSize.HighPart = fileInfo.nFileSizeHigh;
    std::wcout << L"Size: " << fileSize.QuadPart << L" byte" << std::endl;

    FILETIME ftCreate = fileInfo.ftCreationTime;
    SYSTEMTIME stCreate;
    FileTimeToSystemTime(&ftCreate, &stCreate);
    std::wcout << L"Create: "
               << stCreate.wDay << L"/" << stCreate.wMonth << L"/" << stCreate.wYear << L" "
               << stCreate.wHour << L":" << stCreate.wMinute << L":" << stCreate.wSecond << std::endl;

    FILETIME ftWrite = fileInfo.ftLastWriteTime;
    SYSTEMTIME stWrite;
    FileTimeToSystemTime(&ftWrite, &stWrite);
    std::wcout << L"Update: "
               << stWrite.wDay << L"/" << stWrite.wMonth << L"/" << stWrite.wYear << L" "
               << stWrite.wHour << L":" << stWrite.wMinute << L":" << stWrite.wSecond << std::endl;

    return TRUE;
}

BOOL printFileTxt(LPWSTR fileName)
{
    HANDLE hFile = CreateFileW(
        fileName,
        GENERIC_READ,
        0,
        NULL,
        OPEN_EXISTING,
        FILE_ATTRIBUTE_NORMAL,
        NULL);

    if (hFile == INVALID_HANDLE_VALUE)
    {
        std::wcerr << L"Failed to open file." << std::endl;
        return FALSE;
    }

    SetConsoleOutputCP(CP_UTF8);

    LARGE_INTEGER fileSize;
    if (!GetFileSizeEx(hFile, &fileSize))
    {
        std::cerr << "Unable to get file size." << std::endl;
        return false;
    }

    const DWORD bufferSize = static_cast<DWORD>(fileSize.QuadPart);
    char *buffer = new char[bufferSize + 1];
    DWORD bytesRead;
    int count = 1;

    std::wcout << L"Inside File: \n"
               << std::endl;
    std::cout << count << ") ";
    while (ReadFile(hFile, buffer, bufferSize - 1, &bytesRead, NULL) && bytesRead > 0)
    {
        buffer[bytesRead] = '\0';
        // std::cout<< buffer;
        for (char sim : std::string(buffer, bytesRead))
        {
            std::cout << sim;

            if (sim == '\n')
            {
                std::cout << ++count << ") ";
            }
        }
    }

    std::wcout << std::endl;

    CloseHandle(hFile);
    return TRUE;
}