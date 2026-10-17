#include "main/debug/UnkDebugPrint.hpp"
#include "main/dss/DssCore.hpp"

int data_020f325c;
int data_020f3258;
int data_020f3260;

ARM void unkfunc_02043430(const char* title)
{
    data_020f6f9c.unkfunc_0204b00c(0, 0, 0x20, 0x30);
    if (data_020f325c != 0) {
        unkfunc_0204348c(0, 0, title);
    }
}

ARM void unkfunc_0204348c(int x, int y, const char* str)
{
    if (data_020f325c != 0) {
        data_020f6f9c.unkfunc_0204b04c(x, y, str);
    }
}

ARM void unkfunc_020434c8(int x, int y, const char* fmt, ...)
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
    unkfunc_0204348c(x, y, out);
}
