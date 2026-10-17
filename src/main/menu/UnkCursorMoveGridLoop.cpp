#include "main/menu/UnkCursorMoveGridLoop.hpp"
#include "globaldefs.h"

THUMB void UnkCursorMoveBase::setupBase()
{
    w_ = 0;
    h_ = 0;
    count_ = 0;
    pageNo_ = 0;
}

THUMB void UnkCursorMoveBase::setXY(int w, int h)
{
    w_ = w;
    h_ = h;
}

THUMB void UnkCursorMoveBase::setMaxCount(int count)
{
    count_ = count;
}

THUMB int UnkCursorMoveBase::getPageNo()
{
    return pageNo_;
}

THUMB void UnkCursorMoveBase::setPageNo(int pageNo)
{
    pageNo_ = pageNo;
}

THUMB int UnkCursorMoveBase::getPageMaxCount()
{
    return (count_ - 1) / (w_ * h_) + 1;
}

THUMB int UnkCursorMoveBase::pageNext(int index)
{
    int max = getPageMaxCount();
    pageNo_++;
    pageNo_ = (pageNo_ < max) ? pageNo_ : 0;
    int count = getCountInPage();
    if (index >= count) {
        index = (count - 1) / w_;
        index *= w_;
    }
    return index;
}

THUMB int UnkCursorMoveBase::pageBack(int index)
{
    int max = getPageMaxCount();
    pageNo_--;
    pageNo_ = (pageNo_ < 0) ? (short)(max - 1) : pageNo_;
    int count = getCountInPage();
    if (index >= count) {
        index = count - 1;
    }
    return index;
}

THUMB int UnkCursorMoveBase::getIndex(int index)
{
    return index + pageNo_ * w_ * h_;
}

THUMB int UnkCursorMoveBase::getMaxCountInPage()
{
    return w_ * h_;
}

THUMB int UnkCursorMoveBase::getCountInPage()
{
    int last = getPageMaxCount() - 1;
    if (pageNo_ != last) {
        return getMaxCountInPage();
    }
    last = getPageMaxCount() - 1;
    int n = getMaxCountInPage();
    return count_ - n * last;
}

THUMB int UnkCursorMoveGridLoop::inputRight(int index)
{
    if (getCountInPage() == 0) {
        return 0;
    }
    pageNext(index);
    int result = index / w_;
    result *= w_;
    int count = getCountInPage();
    if (result >= count) {
        result = (count - 1) / w_;
        result *= w_;
    }
    return result;
}

THUMB int UnkCursorMoveGridLoop::inputLeft(int index)
{
    if (getCountInPage() == 0) {
        return 0;
    }
    pageBack(index);
    int result = (index / w_ + 1) * w_ - 1;
    int count = getCountInPage();
    if (result >= count) {
        result = count - 1;
    }
    return result;
}

THUMB int UnkCursorMoveGridLoop::inputDown(int index)
{
    if (getCountInPage() == 0) {
        return 0;
    }
    return index % w_;
}

THUMB int UnkCursorMoveGridLoop::inputUp(int index)
{
    if (getCountInPage() == 0) {
        return 0;
    }
    int count = getCountInPage();
    int page = count / w_;
    int result = index % w_ + page * w_;
    if (result >= count) {
        result -= w_;
    }
    return result;
}

THUMB void UnkCursorMoveGridLoop::setup(int w, int h, int count)
{
    setXY(w, h);
    setMaxCount(count);
}
