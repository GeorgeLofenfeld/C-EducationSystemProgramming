/*
Удалить обычные файлы (regular file), имя которых содержит символ ~ в случае, если длина их равна 0.
Выполните с учетом того, что файлы ищутся не только в текущем каталоге,
но и во всех его подкаталогах (любой степени вложенности).
Обратите внимание на то, что существуют фиктивные каталоги . и .. в каждом каталоге
(их надо игнорировать, иначе произойдет зацикливание).
 */

#pragma warning(disable : 4996)

#include <stdio.h>
#include <windows.h>
#include <fileapi.h>
#include <string.h>
#include <tchar.h>
#include<locale.h>

void ErrorExit(LPCTSTR lpszFunction)
{
    LPVOID lpMsgBuf;
    DWORD dw = GetLastError();
    FormatMessage(
        FORMAT_MESSAGE_ALLOCATE_BUFFER |
        FORMAT_MESSAGE_FROM_SYSTEM |
        FORMAT_MESSAGE_IGNORE_INSERTS,
        NULL,
        dw,
        MAKELANGID(LANG_ENGLISH, SUBLANG_DEFAULT),
        (LPTSTR)&lpMsgBuf,
        0, NULL);
    _tprintf(_T("\n%s\n"), lpMsgBuf);
}

int list_file(TCHAR* dirname) {
    WIN32_FIND_DATA fd;
    TCHAR* new_path[258] = { 0 };
    _tcscat(new_path, dirname);
    _tcscat(new_path, _T("\\*"));
    HANDLE Handle = FindFirstFile(new_path, &fd);
    if (Handle != NULL) {
        while (FindNextFile(Handle, &fd))
        {
            printf("\nChecking file: %ls\n", fd.cFileName);
            TCHAR path_to_current_file[256] = { 0 };
            _tcscat(path_to_current_file, dirname);
            _tcscat(path_to_current_file, _T("\\"));
            _tcscat(path_to_current_file, fd.cFileName);
            if ((fd.nFileSizeLow == 0) &&
                (fd.nFileSizeHigh == 0) &&
                (fd.dwFileAttributes != FILE_ATTRIBUTE_DIRECTORY) &&
                (fd.dwFileAttributes != FILE_ATTRIBUTE_DEVICE)) {
                for (int i = 0; i < sizeof(fd.cFileName); i++) {
                    if (fd.cFileName[i] == _T('~')) {
                        _tprintf(_T("Deleted file: %s\n"), fd.cFileName);
                        _tprintf(_T("\nPath to deleted file: %s\n"), dirname);
                        if (DeleteFile(path_to_current_file)) {
                            break;
                        }
                        else ErrorExit(_T("File deleting error"));

                    }
                }
            }
            else if (((fd.dwFileAttributes == FILE_ATTRIBUTE_DIRECTORY && strcmp(fd.cFileName, ".")) != 0) &&
                (strcmp(fd.cFileName, "..") != 0)) {
                printf(_T("\nOpen directory: %s\n"), fd.cFileName);
                TCHAR path[256] = { 0 };
                _tcscat(path, dirname);
                _tcscat(path, _T("\\"));
                _tcscat(path, fd.cFileName);
                list_file(path);
            }
        };
        if (GetLastError() != ERROR_NO_MORE_FILES)
            ErrorExit(_T("ERROR: Next file not found"));
    }
    else ErrorExit(_T("Find first file error"));
}

int main()
{
    setlocale(LC_ALL,"");
    list_file(_T("D:\\desktop\\Колледж\\Уч. практика Си УП.01\\pr_r_3_2\\temp"));
    return 0;
}

