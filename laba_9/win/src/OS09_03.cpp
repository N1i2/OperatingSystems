#include <windows.h>
#include <tchar.h>
#include <iostream>
#include <string>
#include <vector>

#define UNICODE
#define PATH_TO_FILE L"D:\\Univer\\OS\\laba_9\\OS09_01.txt"

BOOL delRowFileTxt(LPWSTR fileName, DWORD row);
BOOL insRowFileTxt(LPWSTR fileName, LPWSTR str, int row);
std::vector<std::wstring> readLines(LPWSTR fileName);
BOOL writeLine(LPWSTR fileName, std::vector<std::wstring> lines);

int main()
{
    int rowsToDelete[] = {0, -1, 5, 7};
    const wchar_t* insertedStr = L"Inserte ";

    for (int row : rowsToDelete)
    {
        size_t len = wcslen(insertedStr) + 20;
        LPWSTR resultStr = new wchar_t[len];
        swprintf(resultStr, len, L"%s%d", insertedStr, row);

        if (!insRowFileTxt((LPWSTR)PATH_TO_FILE, resultStr, row))
        {
            std::wcout << L"Error: row " << row << L" not exist" << std::endl;
            continue;
        }
    }

    return 0;
}

std::vector<std::wstring> readLines(LPWSTR fileName)
{
    HANDLE hFile = CreateFileW(
        fileName,
        GENERIC_READ,
        FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE,
        NULL,
        OPEN_EXISTING,
        FILE_ATTRIBUTE_NORMAL,
        NULL);

    if (hFile == INVALID_HANDLE_VALUE)
    {
        std::wcerr << L"Failed to open file to read." << std::endl;
    }

    DWORD fileSize = GetFileSize(hFile, NULL);
    if (fileSize == INVALID_FILE_SIZE)
    {
        std::wcerr << L"Failed size." << std::endl;
        CloseHandle(hFile);
    }

    char *buffer = new char[fileSize + 1];
    DWORD bytesRead;
    if (!ReadFile(hFile, buffer, fileSize, &bytesRead, NULL) || bytesRead != fileSize)
    {
        std::wcerr << L"Failed read." << std::endl;
        delete[] buffer;
        CloseHandle(hFile);
    }
    buffer[fileSize] = '\0';

    std::vector<std::wstring> lines;
    wchar_t wideBuffer[4096];
    MultiByteToWideChar(CP_UTF8, 0, buffer, -1, wideBuffer, 4096);

    std::wstring currentLine;
    for (int i = 0; wideBuffer[i] != L'\0'; ++i)
    {
        if (wideBuffer[i] == L'\n')
        {
            if (!currentLine.empty())
            {
                lines.push_back(currentLine);
                currentLine.clear();
            }
        }
        else
        {
            currentLine += wideBuffer[i];
        }
    }

    if (!currentLine.empty())
    {
        lines.push_back(currentLine);
    }

    delete[] buffer;

    CloseHandle(hFile);

    return lines;
}

BOOL writeLine(LPWSTR fileName, std::vector<std::wstring> lines)
{
    HANDLE hFile = CreateFileW(
        fileName,
        GENERIC_WRITE,
        FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE,
        NULL,
        CREATE_ALWAYS,
        FILE_ATTRIBUTE_NORMAL,
        NULL);

    if (hFile == INVALID_HANDLE_VALUE)
    {
        std::wcerr << L"Failed to create file. Error code: " << GetLastError() << std::endl;
        return FALSE;
    }

    for (const auto &line : lines)
    {
        int utf8Size = WideCharToMultiByte(CP_UTF8, 0, line.c_str(), -1, NULL, 0, NULL, NULL);
        std::vector<char> utf8Line(utf8Size);
        WideCharToMultiByte(CP_UTF8, 0, line.c_str(), -1, utf8Line.data(), utf8Size, NULL, NULL);

        DWORD bytesWritten;
        WriteFile(hFile, utf8Line.data(), utf8Line.size() - 1, &bytesWritten, NULL);
        WriteFile(hFile, "\r\n", 2, &bytesWritten, NULL);
    }

    CloseHandle(hFile);

    return TRUE;
}

BOOL delRowFileTxt(LPWSTR fileName, DWORD row)
{
    std::vector<std::wstring> lines = readLines(fileName);

    if (row < 1 || row > lines.size())
    {
        std::wcerr << L"String " << row << L" out of range." << std::endl;
        return FALSE;
    }

    lines.erase(lines.begin() + row - 1);

    if (!writeLine(fileName, lines))
    {
        std::cout << "Error write file" << std::endl;
        return FALSE;
    }

    return TRUE;
}

BOOL insRowFileTxt(LPWSTR fileName, LPWSTR str, int row)
{
    std::vector<std::wstring> lines = readLines(fileName);

    if (row == 0)
    {
        lines.insert(lines.begin(), str);
    }
    else if (row == -1)
    {
        lines.push_back(str);
    }
    else if (row > 0 && row <= static_cast<int>(lines.size() + 1))
    {
        lines.insert(lines.begin() + (row - 1), str);
    }
    else
    {
        std::wcerr << L"Invalid row index: " << row << std::endl;
        return FALSE;
    }

    if (!writeLine(fileName, lines))
    {
        std::cout << "Error write file" << std::endl;
        return FALSE;
    }

    return TRUE;
}