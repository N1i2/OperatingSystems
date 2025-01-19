#include <windows.h>
#include <vector>
#include <string>
#include <iostream>

#define UNICODE
#define PATH_TO_FILE L"D:\\Univer\\OS\\laba_9\\OS09_01.txt"

BOOL delRowFileTxt(LPWSTR fileName, DWORD row);

int main()
{
    DWORD rowsToDelete[] = {1, 3, 8, 10};

    for (DWORD row : rowsToDelete)
    {
        if (!delRowFileTxt((LPWSTR)PATH_TO_FILE, row))
        {
            std::wcout << L"Error: row " << row << L" not exist" << std::endl;
        }
    }

    return 0;
}

BOOL delRowFileTxt(LPWSTR fileName, DWORD row)
{
    HANDLE hFile = CreateFileW(fileName, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (hFile == INVALID_HANDLE_VALUE)
    {
        return FALSE;
    }

    DWORD fileSize = GetFileSize(hFile, NULL);
    if (fileSize == INVALID_FILE_SIZE)
    {
        CloseHandle(hFile);
        return FALSE;
    }

    std::vector<char> buffer(fileSize);
    DWORD bytesRead;
    if (!ReadFile(hFile, buffer.data(), fileSize, &bytesRead, NULL) || bytesRead != fileSize)
    {
        CloseHandle(hFile);
        return FALSE;
    }
    CloseHandle(hFile);

    std::vector<std::string> lines;
    std::string line;
    for (size_t i = 0; i < buffer.size(); ++i)
    {
        if (buffer[i] == '\n')
        {
            lines.push_back(line);
            line.clear();
        }
        else if (buffer[i] != '\r')
        {
            line += buffer[i];
        }
    }
    if (!line.empty())
    {
        lines.push_back(line);
    }

    if (row > 0 && row <= lines.size())
    {
        lines.erase(lines.begin() + row - 1);
    }
    else
    {
        return FALSE;
    }

    hFile = CreateFileW(fileName, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    if (hFile == INVALID_HANDLE_VALUE)
    {
        return FALSE;
    }

    for (int i = 0; i < lines.size(); i++)
    {
        DWORD bytesWritten;
        std::string lineWithNewline = lines[i] + "\r";

        if(i != lines.size() - 1)
        {
            lineWithNewline += "\n";
        }

        if (!WriteFile(hFile, lineWithNewline.c_str(), lineWithNewline.size(), &bytesWritten, NULL) || bytesWritten != lineWithNewline.size())
        {
            CloseHandle(hFile);
            return FALSE;
        }
    }

    CloseHandle(hFile);
    return TRUE;
}