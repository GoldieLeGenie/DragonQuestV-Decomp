#include "main/text/TextAPI.hpp"

inline void MessageMacro::stateStackPush(int state)
{
    stateStackPos_++;
    stateStack_[stateStackPos_] = state;
}

THUMB void MessageMacro::initialize(char* dst, int size, const char* src)
{
    dst_ = dst;
    size_ = size;
    src_ = src;
    stateStackPos_ = 0;
    stateStack_[stateStackPos_] = 1;
    stateNow_ = 0;
    stateStackPos_++;
    stateStack_[stateStackPos_] = 1;
}

THUMB void MessageMacro::processMessage(char* dst, int size, const char* src)
{
    initialize(dst, size, src);
    while (1) {
        int ch = *(const unsigned char*)src_++;
        if (ch == 0) {
            break;
        }
        if (ch != '%') {
            if (stateStack_[stateStackPos_] == 1) {
                *dst_++ = ch;
            }
            continue;
        }
        ch = *(const unsigned char*)src_++;
        if (ch >= 'A' && ch <= 'S') {
            int v1 = (*(const unsigned char*)src_++ - '0') * 100;
            int v2 = (*(const unsigned char*)src_++ - '0') * 10;
            int v3 = *(const unsigned char*)src_++ - '0';
            int vn = v1 + v2 + v3;
            int id = *(const unsigned char*)src_++ - '0';
            switch (ch) {
                case 'A':
                    judgeState(MST_MALE, vn, id);
                    break;
                case 'B':
                    judgeState(MST_FEMALE, vn, id);
                    break;
                case 'C':
                    judgeState(MST_NEUTER, vn, id);
                    break;
                case 'D':
                    judgeState(MST_SOLO, vn, id);
                    break;
                case 'E':
                    judgeState(MST_PROPER, vn, id);
                    break;
                case 'F':
                    judgeState(MST_VOWEL, vn, id);
                    break;
                case 'G':
                    judgeState(MST_VOWEL_FR, vn, id);
                    break;
                case 'H':
                    judgeState(MST_SINGLE, vn, id);
                    break;
                case 'I':
                    judgeState(MST_SINGLE_FR, vn, id);
                    break;
                case 'J':
                    judgeState(MST_LASTLETTER_S, vn, id);
                    break;
                case 'K':
                    judgeState(MST_LASTLETTER_S_DE, vn, id);
                    break;
                case 'L':
                    judgeState(MST_SISTER, vn, id);
                    break;
                case 'M':
                    judgeState(MST_PLRNOUN, vn, id);
                    break;
                case 'N':
                    judgeState(MST_ACTTGT, vn, id);
                    break;
                case 'O':
                    judgeState(MST_LEADER, vn, id);
                    break;
                case 'P':
                    judgeState(MST_PLUS, vn, id);
                    break;
                case 'Q':
                    judgeState(MST_TALKER, vn, id);
                    break;
                case 'R':
                    judgeState(MST_ALLMEMBER, vn, id);
                    break;
                case 'S':
                    judgeState(MST_BOOL, vn, id);
                    break;
                default:
                    judgeState(MST_NULL, vn, id);
                    break;
            }
        } else if (ch >= 'X' && ch <= 'Z') {
            switch (ch) {
                case 'X':
                    processIF();
                    break;
                case 'Y':
                    processELSE();
                    break;
                case 'Z':
                    processENDIF();
                    break;
            }
        } else {
            if (stateStack_[stateStackPos_] == 1) {
                *dst_++ = '%';
            }
            if (stateStack_[stateStackPos_] == 1) {
                *dst_++ = ch;
            }
        }
    }
    *dst_++ = 0;
}

THUMB void MessageMacro::judgeState(MACRO_STAT mask, int def, int array_index_no)
{
    stateNow_ = (g_text_env.macro_getMacroStat(def, array_index_no) & mask) ? 1 : 0;
}

THUMB void MessageMacro::processIF()
{
    if (stateStack_[stateStackPos_] == 0) {
        stateNow_ = 0;
    }
    stateStackPush(stateNow_);
}

THUMB void MessageMacro::processELSE()
{
    if (stateStackPos_ == 0) {
        return;
    }
    if (stateStack_[stateStackPos_ - 1] == 0) {
        stateStack_[stateStackPos_] = 0;
        return;
    }
    if (stateStack_[stateStackPos_] == 1) {
        stateStack_[stateStackPos_] = 0;
    } else {
        stateStack_[stateStackPos_] = 1;
    }
}

THUMB void MessageMacro::processENDIF()
{
    if (stateStackPos_ != 0) {
        stateStackPos_--;
    }
}
