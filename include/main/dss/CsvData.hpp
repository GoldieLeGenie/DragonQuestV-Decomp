#pragma once
#include <globaldefs.h>
#include "main/data/DataObject.hpp"

struct CsvRow {
    short column_[8];                           // 0x00

    void clear();
    void setColumn(int index, int offset);
    short getColumn(int index);
};

struct CsvData {
    char* text_;                                // 0x00
    unsigned int size_;                         // 0x04
    CsvRow* row_;                               // 0x08
    unsigned int rowCount_;                     // 0x0C
    DataObject data_;                           // 0x10

    CsvData();
    ~CsvData();
    void loadText(const char* filename, int a);
    void load(const char* filename, int a);
    char* getText(int row, int column);
};
