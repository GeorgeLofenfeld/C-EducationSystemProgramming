#include <stdio.h>
#include <windows.h>
#include <fileapi.h>
#include <string.h>
#include <tchar.h>

int main()
{
    WIN32_FIND_DATA fd;
    wchar_t path[256] = L"D:\\Рабочий Стол\\Колледж\\Уч. практика Си УП.01\\pr_r_2\\*";
    HANDLE Handle = FindFirstFile(path, &fd);
    printf("\nOpen dir: %ls\n", path);
    if (Handle != NULL) {
        while (FindNextFile(Handle, &fd))
        {
            printf("\nChecking file: %ls\n", fd.cFileName);
            if ( (fd.nFileSizeLow == 0) && 
                (fd.nFileSizeHigh == 0) && 
                (fd.dwFileAttributes != FILE_ATTRIBUTE_DIRECTORY) && 
                (fd.dwFileAttributes != FILE_ATTRIBUTE_DEVICE)) {
                for (int i = 0; i < sizeof(fd.cFileName); i++) {
                    if (fd.cFileName[i] == '~') {
                        printf("Deleted file: %ls\n", fd.cFileName);
                        DeleteFile(fd.cFileName);
                        break;
                    }
                }
            }
        }
    } else _tprintf(_T("%d"),GetLastError());
    return 0;
}

