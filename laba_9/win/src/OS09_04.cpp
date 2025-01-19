#include <windows.h>
#include <iostream>
#include <vector>
#include <string>
#include <shlwapi.h>

#define UNICODE
#define PATH_TO_FILE L"D:\\Univer\\OS\\laba_9\\OS09_01.txt"

BOOL printWatchRowFileTxt(LPWSTR fileName, DWORD mlsec);
std::vector<std::wstring> readLines(LPWSTR fileName);

int main()
{
	DWORD watchTime = 30000;

	if (!printWatchRowFileTxt((LPWSTR)PATH_TO_FILE, watchTime))
	{
		std::wcerr << L"Failed to watch file." << std::endl;
		return 1;
	}

	return 0;
}

void RemoveFileSpec(LPWSTR path) {
    size_t len = wcslen(path);
    for (size_t i = len; i > 0; --i) {
        if (path[i - 1] == L'\\') {
            path[i - 1] = L'\0'; 
            break;
        }
    }
}

BOOL printWatchRowFileTxt(LPWSTR fileName, DWORD mlsec)
{
	WCHAR directory[MAX_PATH];
	wcscpy_s(directory, fileName);
	RemoveFileSpec(directory);

	HANDLE hDir = CreateFileW(
		directory,
		FILE_LIST_DIRECTORY,
		FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE,
		NULL,
		OPEN_EXISTING,
		FILE_FLAG_BACKUP_SEMANTICS,
		NULL);

	if (hDir == INVALID_HANDLE_VALUE)
	{
		std::wcerr << L"Failed to open directory. Error: " << GetLastError() << std::endl;
		return FALSE;
	}
	DWORD previousLineCount = readLines(fileName).size();
	std::wcout << L"Initial line count: " << previousLineCount << std::endl;

	BYTE buffer[1024];
	DWORD bytesReturned;
	DWORD startTime = GetTickCount();

	while (GetTickCount() - startTime < mlsec)
	{
		if (ReadDirectoryChangesW(
				hDir,
				buffer,
				sizeof(buffer),
				FALSE,
				FILE_NOTIFY_CHANGE_LAST_WRITE,
				&bytesReturned,
				NULL,
				NULL))
		{

			DWORD currentLineCount = readLines(fileName).size();
			if (currentLineCount != previousLineCount)
			{
				std::wcout << L"Line count changed: " << currentLineCount << L" lines" << std::endl;
				previousLineCount = currentLineCount;
			}
		}
		else
		{
			std::wcerr << L"Failed to monitor directory. Error: " << GetLastError() << std::endl;
			CloseHandle(hDir);
			return FALSE;
		}
	}

	CloseHandle(hDir);
	return TRUE;
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
		std::wcerr << L"Failed to open file for reading. Error: " << GetLastError() << std::endl;
	}

	DWORD fileSize = GetFileSize(hFile, NULL);
	if (fileSize == INVALID_FILE_SIZE)
	{
		std::wcerr << L"Failed to get file size. Error: " << GetLastError() << std::endl;
		CloseHandle(hFile);
	}

	char *buffer = new char[fileSize + 1];
	DWORD bytesRead;
	if (!ReadFile(hFile, buffer, fileSize, &bytesRead, NULL) || bytesRead != fileSize)
	{
		std::wcerr << L"Failed to read file. Error: " << GetLastError() << std::endl;
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