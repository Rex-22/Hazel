#ifndef IO_H
#define IO_H

namespace Hazel {

    struct FileData
    {
        char* Data;
        u32   Size;
    };
    
    class Io
    {
    public:
        static FileData LoadFile(const char* filePath);
        static b32 WriteToFile(const char* filePath, const char* data, b32 overwrite = false);
    };
}
#endif /* IO_H */
