#include "main/debug/UnkDebugPrint.hpp"
#include "main/dss/DssCore.hpp"

int data_020f325c;
int data_020f3258;
int data_020f3260;

ARM void clearDebugConsole(const char* title)
{
    data_020f6f9c.clearRect(0, 0, 0x20, 0x30);
    if (data_020f325c != 0) {
        debugConsolePrint(0, 0, title);
    }
}

ARM void debugConsolePrint(int x, int y, const char* str)
{
    if (data_020f325c != 0) {
        data_020f6f9c.printf(x, y, str);
    }
}

ARM void debugConsolePrintfIfEnabled(int x, int y, const char* fmt, ...)
{
    char out[0x21];
    char buf[0x200];
    va_list args;
    if (data_020f325c == 0) {
        return;
    }
    va_start(args, fmt);
    func_020873dc(buf, 0x1fe, fmt, args);
    int i = 0;
    while (buf[i] != '\0') {
        if (buf[i] < ' ') {
            out[i] = ' ';
        } else {
            out[i] = buf[i];
        }
        i++;
        if (i == 0x20) {
            break;
        }
    }
    out[i] = '\0';
    debugConsolePrint(x, y, out);
}
