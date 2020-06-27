#include "hzpch.h"
#include "Hazel/Core/Io.h"

#include <windows.h>
#include <tchar.h>
#include <stdio.h>
#include <strsafe.h>

namespace Hazel
{
    FileData Io::LoadFile(const char* filePath)
    {
        HANDLE hFile;
        LARGE_INTEGER fileSize;
        FileData fileData = {};

        hFile = CreateFileA(filePath, // file to open
                            GENERIC_READ, // open for reading
                            FILE_SHARE_READ, // share for reading
                            NULL, // default security
                            OPEN_EXISTING, // existing file only
                            FILE_ATTRIBUTE_NORMAL, // normal file
                            0); // no attr. template


        if (hFile == INVALID_HANDLE_VALUE)
        {
            HZ_CORE_WARN("FILEIO (Windows): [{0}] Unable to open file", filePath);
            return fileData;
        }
        HZ_CORE_TRACE("FILEIO (Windows): [{0}] File opend", filePath);

        if (!GetFileSizeEx(hFile, &fileSize))
        {
            HZ_CORE_ERROR("FILEIO (Windows): [{0}] Invalid file size (ErrorCode:0x{1:x})", filePath, GetLastError());
            return fileData;
        }
        fileData.Data = (char*)malloc(fileSize.QuadPart * sizeof(char));

        // Read one character less than the buffer size to save room for
        // the terminating NULL character. 
        if (ReadFile(
                hFile,
                fileData.Data,
                fileSize.QuadPart,
                (LPDWORD)&fileData.Size,
                0)
            == FALSE)
        {
            HZ_CORE_ERROR("FILEIO (Windows): [{0}] Unable to read from file (ErrorCode=0x{1:x})", filePath,
                          GetLastError());
            CloseHandle(hFile);
            return fileData;
        }

        if (fileData.Size != fileSize.QuadPart)
            HZ_CORE_WARN("FILEIO (Windows): [{0}] File partially loaded", filePath);
        else
            HZ_CORE_INFO("FILEIO (Windows): [{0}] File loaded successfully", filePath);

        fileData.Data[fileData.Size] = '\0'; // NULL character

        CloseHandle(hFile);
        return fileData;
    }

    b32 Io::WriteToFile(const char* filePath, const char* data, b32 overwrite)
    {
        HANDLE hFile;
        DWORD bytesToWrite = (DWORD)strlen(data);
        DWORD bytesWritten = 0;

        hFile = CreateFileA(filePath, // name of the write
                            GENERIC_WRITE, // open for writing
                            0, // do not share
                            NULL, // default security
                            overwrite ? CREATE_ALWAYS : CREATE_NEW, // create new file only
                            FILE_ATTRIBUTE_NORMAL, // normal file
                            0); // no attr. template

        if (hFile == INVALID_HANDLE_VALUE)
        {
            HZ_CORE_WARN("FILEIO (Windows): [{0}] Unable to open file for writing", filePath);
            return false;
        }

        if (WriteFile(
                hFile,
                data,
                bytesToWrite,
                &bytesWritten,
                0)
            == FALSE)
        {
            HZ_CORE_WARN("FILEIO (Windows): [{0}] Unable to write to file", filePath);
        }
        else
        {
            if (bytesWritten == bytesToWrite)
            {
                HZ_CORE_TRACE("FILEIO (Windows): [{0}] Wrote {1:d} bytes successfully.", filePath, bytesWritten);
            }
            else
            {
                HZ_CORE_WARN("FILEIO (Windows): [{0}] {1:d} bytes not writtent to file!");
            }
        }

        CloseHandle(hFile);
        return true;
    }
}
