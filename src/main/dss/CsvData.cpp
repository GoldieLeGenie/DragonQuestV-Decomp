#include "main/dss/CsvData.hpp"
#include "main/dss/DssUtils.hpp"
#include "main/dss/UnkMemory.hpp"

THUMB void CsvRow::unkfunc_020521e0()
{
    for (int i = 0; i < 8; i++) {
        column_[i] = -1;
    }
}

THUMB void CsvRow::unkfunc_020521f0(int index, int offset)
{
    column_[index] = offset;
}

THUMB short CsvRow::unkfunc_020521f8(int index)
{
    return column_[index];
}

THUMB CsvData::CsvData() : text_(0)
{
}

THUMB CsvData::~CsvData()
{
}

THUMB void CsvData::unkfunc_02052224(const char* filename, int a)
{
    data_.setup(filename, a, 1);
    text_ = (char*)data_.getAddr();
    size_ = data_.getSize();
}

THUMB void CsvData::unkfunc_02052248(const char* filename, int a)
{
    unkfunc_02052224(filename, a);
    row_ = (CsvRow*)dssAlloc(&data_020fd24c, 0x3840, -0x20);
    for (int i = 0; i < 0x384; i++) {
        row_[i].unkfunc_020521e0();
    }
    int pos = 0;
    int row = 0;
    int column = 0;
    row_[row].unkfunc_020521f0(column, pos);
    char* text = text_;
    do {
        if (text[pos] == ',') {
            text[pos] = 0;
            pos++;
            column++;
            row_[row].unkfunc_020521f0(column, pos);
        } else if (text[pos] == '\r' && text[pos + 1] == '\n') {
            text[pos] = 0;
            text[pos + 1] = 0;
            pos += 2;
            row++;
            column = 0;
            row_[row].unkfunc_020521f0(column, pos);
        } else {
            pos++;
        }
    } while (pos < size_);
    CsvRow* rows = (CsvRow*)dssAlloc(&data_020fd24c, row * sizeof(CsvRow), 0x20);
    dss::memcpy(rows, row_, row * sizeof(CsvRow));
    dssFree(&data_020fd24c, row_);
    row_ = rows;
    rowCount_ = row;
}

THUMB char* CsvData::unkfunc_02052314(int row, int column)
{
    if (rowCount_ <= row) {
        return 0;
    }
    if (row_[row].unkfunc_020521f8(column) == -1) {
        return 0;
    }
    return text_ + row_[row].unkfunc_020521f8(column);
}
