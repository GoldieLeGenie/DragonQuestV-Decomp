#pragma ipa file
#include "main/object/DSSACharacter.hpp"
#include "main/dss/UnkArchive.hpp"
#include <printf.h>

static UnkDSSAStream s_stream;
static char s_format[0x20];
static DataObject s_dataObject[2];

ARM DSSACharacter::DSSACharacter()
{
    flag_.clear();
    currentAnimationIndex_ = 0;
}

ARM DSSACharacter::~DSSACharacter()
{
}

ARM void DSSACharacter::setupFromData(DataObject* texture, DataObject* animation)
{
    TextureObject* textureObject = (TextureObject*)texture->getAddr();
    textureObject->loadToVram(1);
    unk_034 = 1;
    unkfunc_020524c8(textureObject, animation);
}

ARM void DSSACharacter::unkfunc_020524c8(TextureObject* texture, DataObject* animation)
{
    flag_.clear();
    unk_ae4 = texture;
    palette_.loadFromTexture(texture, 0);
    dataObject_ = animation;
    currentAnimationIndex_ = -1;
    for (int i = 0; i < getArchiveFileCount(dataObject_->getAddr()); i++) {
        if (isEnable(i)) {
            if (currentAnimationIndex_ == -1) {
                currentAnimationIndex_ = i;
                firstAnimationIndex_ = i;
            }
            dssaObject_[i].setup(getArchiveFile(dataObject_->getAddr(), i));
            dssaObject_[i].setTexture(unk_ae4);
            dssaObject_[i].setPalette(&palette_);
        }
    }
}

ARM void DSSACharacter::setupStream(TextureObject* texture, const char* format, int count)
{
    char filename[0x20];
    flag_.clear();
    unk_ae4 = texture;
    palette_.loadFromTexture(texture, 0);
    flag_.set(0x40);
    dss::strcpy(s_format, format);
    sprintf(filename, s_format, 0);
    s_dataObject[0].setup(filename, 0, 0);
    dssaObject_[0].setup(s_dataObject[0].getAddr());
    dssaObject_[0].setTexture(unk_ae4);
    dssaObject_[0].setPalette(&palette_);
    sprintf(filename, s_format, 1);
    s_dataObject[1].setup(filename, 0, 0);
    dssaObject_[1].setup(s_dataObject[1].getAddr());
    dssaObject_[1].setTexture(unk_ae4);
    dssaObject_[1].setPalette(&palette_);
    s_stream.unk_08 = 0;
    s_stream.unk_00 = 2;
    s_stream.unk_04 = count;
    currentAnimationIndex_ = 0;
    firstAnimationIndex_ = 0;
    nextAnimationIndex_ = -1;
}

ARM void DSSACharacter::cleanup()
{
    palette_.freeVram();
    if (unk_034 != 0) {
        unk_ae4->freeVram();
    }
    for (int i = 0; i < 17; i++) {
        if (dssaObject_[i].isEnable()) {
            dssaObject_[i].cleanup();
        }
    }
    if (flag_.check(0x40)) {
        flag_.remove(0x40);
        s_dataObject[0].cleanup();
        s_dataObject[1].cleanup();
    }
    unk_034 = 0;
    dataObject_ = 0;
}

ARM void DSSACharacter::updateStream()
{
    char filename[0x20];
    if (!flag_.check(0x40)) {
        return;
    }
    if (s_stream.unk_00 > s_stream.unk_04) {
        return;
    }
    if (!dssaObject_[s_stream.unk_08].isEnd()) {
        return;
    }
    if (s_stream.unk_00 < s_stream.unk_04) {
        sprintf(filename, s_format, s_stream.unk_00);
        s_dataObject[s_stream.unk_08].cleanup();
        s_dataObject[s_stream.unk_08].setup(filename, 0, 0);
    }
    currentAnimationIndex_ = s_stream.unk_08 = s_stream.unk_08 == 0 ? 1 : 0;
    dssaObject_[s_stream.unk_08].cleanup();
    dssaObject_[s_stream.unk_08].setup(s_dataObject[s_stream.unk_08].getAddr());
    dssaObject_[s_stream.unk_08].setTexture(unk_ae4);
    dssaObject_[s_stream.unk_08].setPalette(&palette_);
    s_stream.unk_00++;
}

ARM void DSSACharacter::draw()
{
    dssaObject_[currentAnimationIndex_].setPosition(position_);
    dssaObject_[currentAnimationIndex_].draw();
    dssaObject_[currentAnimationIndex_].execute();
    updateStream();
    if (nextAnimationIndex_ != -1 && dssaObject_[currentAnimationIndex_].isEnd()) {
        start(nextAnimationIndex_, 0);
        if (flag_.check(0x20)) {
            dssaObject_[nextAnimationIndex_].setAlpha(dss::Fix32(0L));
        }
    }
    if (flag_.check(1)) {
        dss::Fix32 alpha(0x1f - flagCount_);
        alpha /= 0x1f;
        dssaObject_[currentAnimationIndex_].setAlpha(alpha);
        flagCount_++;
        flagCount_ = dss::clamp<int>(flagCount_, 0, 0x1f);
        if (flagCount_ == 0x1f) {
            flagCount_ = 0;
            flag_.remove(1);
            dssaObject_[currentAnimationIndex_].setAlpha(dss::Fix32(0L));
        }
    }
    if (flag_.check(8)) {
        dss::Fix32 alpha(flagCount_);
        alpha /= 0x1f;
        dssaObject_[currentAnimationIndex_].setAlpha(alpha);
        flagCount_++;
        flagCount_ = dss::clamp<int>(flagCount_, 0, 0x1f);
        if (flagCount_ == 0x1f) {
            flagCount_ = 0;
            flag_.remove(8);
            dssaObject_[currentAnimationIndex_].setAlpha(dss::Fix32(0x1000));
        }
    }
    if (flag_.check(2)) {
        if (flagCount_ & 4) {
            dssaObject_[flagIndex_].setAlpha(dss::Fix32(0L));
            dssaObject_[firstAnimationIndex_].setAlpha(dss::Fix32(0L));
        } else {
            dssaObject_[flagIndex_].setAlpha(dss::Fix32(0x1000));
            dssaObject_[firstAnimationIndex_].setAlpha(dss::Fix32(0x1000));
        }
        if (++flagCount_ == 0x19) {
            dssaObject_[flagIndex_].setAlpha(dss::Fix32(0x1000));
            dssaObject_[firstAnimationIndex_].setAlpha(dss::Fix32(0x1000));
            flagCount_ = 0;
            flag_.remove(2);
        }
    }
    if (flag_.check(4)) {
        if (flagCount_ & 4) {
            dssaObject_[flagIndex_].setAlpha(dss::Fix32(0L));
            dssaObject_[firstAnimationIndex_].setAlpha(dss::Fix32(0L));
        } else {
            dssaObject_[flagIndex_].setAlpha(dss::Fix32(0x1000));
            dssaObject_[firstAnimationIndex_].setAlpha(dss::Fix32(0x1000));
        }
        if (++flagCount_ >= 0x18) {
            flagCount_ = 0;
            flag_.remove(4);
            dssaObject_[flagIndex_].setAlpha(dss::Fix32(0x1000));
            dssaObject_[firstAnimationIndex_].setAlpha(dss::Fix32(0L));
            currentAnimationIndex_ = firstAnimationIndex_;
        }
    }
}

ARM bool DSSACharacter::start(int index, int loop)
{
    if (index == 0x1e) {
        return true;
    }
    if (index == 0x22) {
        specialIndex_ = 0x22;
        flag_.set(4);
        flagCount_ = 0;
        flagIndex_ = currentAnimationIndex_;
        return true;
    }
    if (index == 0x23) {
        specialIndex_ = 0x23;
        flag_.set(2);
        flagIndex_ = currentAnimationIndex_;
        flagCount_ = 0;
        return true;
    }
    if (index == 0x24) {
        specialIndex_ = 0x24;
        dssaObject_[currentAnimationIndex_].setAlpha(dss::Fix32(0));
        return true;
    }
    if (index == 0x26) {
        specialIndex_ = 0x26;
        dssaObject_[currentAnimationIndex_].setAlpha(dss::Fix32(0));
        dssaObject_[nextAnimationIndex_].setAlpha(dss::Fix32(0));
        return true;
    }
    if (index == 0x25) {
        specialIndex_ = 0x25;
        dssaObject_[currentAnimationIndex_].setAlpha(dss::Fix32(0x1000));
        return true;
    }
    if (index == 0x1f) {
        specialIndex_ = 0x1f;
        flag_.set(1);
        flagCount_ = 0;
        return true;
    }
    if (index == 0x20) {
        specialIndex_ = 0x20;
        flag_.set(8);
        flagCount_ = 0;
        return true;
    }
    if (index == 0x21) {
        specialIndex_ = 0x21;
        dssaObject_[currentAnimationIndex_].setAlpha(dss::Fix32(0));
        return true;
    }
    if (!isEnable(index)) {
        return false;
    }
    if (specialIndex_ == 0x20 && flagCount_ > 0x18 && currentAnimationIndex_ == 0) {
        dssaObject_[currentAnimationIndex_].setAlpha(dss::Fix32(0x1000));
    }
    currentAnimationIndex_ = index;
    nextAnimationIndex_ = !loop ? firstAnimationIndex_ : -1;
    dssaObject_[currentAnimationIndex_].start(0);
    return true;
}

ARM void DSSACharacter::setAlpha(int alpha)
{
    dss::Fix32 trans;
    trans.value = (alpha << 12) / 31;
    dssaObject_[currentAnimationIndex_].setAlpha(trans);
}

ARM bool DSSACharacter::isEnable(int index)
{
    if (dataObject_ == 0) {
        return false;
    }
    if (getArchiveFileSize(dataObject_->getAddr(), index) != 0) {
        return true;
    }
    return false;
}

ARM int DSSACharacter::getCurrentFrame()
{
    return dssaObject_[currentAnimationIndex_].frame_;
}

ARM int DSSACharacter::getMaxFrame()
{
    return dssaObject_[currentAnimationIndex_].dssaData_.frame_;
}

ARM dss::Fix32Vector3 DSSACharacter::getNullPosition(int index, int no)
{
    return dssaObject_[index].getNullPosition(no);
}

ARM void DSSACharacter::setCurrentFrame(int index, int frame)
{
    dssaObject_[index].setCurrentFrame(frame);
}

ARM void DSSACharacter::setScale(dss::Fix32 scale)
{
    for (int i = 0; i < 17; i++) {
        dssaObject_[i].setScale(scale);
    }
}

ARM void DSSACharacter::setCameraType(DSSAObjectWithCamera::CameraType type)
{
    for (int i = 0; i < 17; i++) {
        dssaObject_[i].type_ = type;
    }
}

ARM void DSSACharacter::pause(int flag)
{
    for (int i = 0; i < 17; i++) {
        dssaObject_[i].pause(flag);
    }
}
