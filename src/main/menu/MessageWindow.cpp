#pragma ipa file
#include "main/menu/MessageWindow.hpp"
#include "main/dss/UnkDisplay.hpp"
#include "main/menu/UnkMenuTextDisplay.hpp"
#include "main/menu/MenuWindowFrame.hpp"
#include "main/dss/DssUtils.hpp"
#include "main/dss/UnkBgBuffer.hpp"
#include "main/sound/Sound.hpp"
#include <nitro/std.h>
#include "main/menu/UnkMenuDisplays.hpp"
#include "main/text/TextAPI.hpp"

inline UnkTextIterator* MessageWindow::getIterator()
{
    return &iterator_;
}

THUMB MessageWindow::MessageWindow()
{
    windowType_ = 0;
    cursor_ = 0;
    soundSpeed_ = 25;
}

THUMB void MessageWindow::setup(int id)
{
    id_ = id;
    reset();
    setType(2);
    state_ = 0;
    unk_9d4 = 0;
    shake_ = 0;
    shakeCount_ = 0;
    shakeRepeat_ = 0;
    shakeX_ = 0;
    shakeY_ = 0;
    keyWait_ = 0;
    keySound_ = 0;
    unk_9ec = 0;
    unk_9f0 = 0;
    unk_9f4 = 0;
}

THUMB void MessageWindow::update(UnkOamBuffer* main, UnkOamBuffer* sub)
{
    if (shake_) {
        shakeX_ = data_0209aaf0[shakeCount_ / 2];
        shakeY_ = data_0209ab10[shakeCount_ / 2];
        shakeCount_++;
        if (shakeCount_ == 16) {
            shakeRepeat_--;
            if (shakeRepeat_ == 0) {
                shake_ = 0;
            } else {
                shakeCount_ = 0;
            }
        }
    } else {
        shakeX_ = 0;
        shakeY_ = 0;
    }
}

THUMB void MessageWindow::execute(UnkOamBuffer* main, UnkOamBuffer* sub)
{
    executeState();
}

THUMB void MessageWindow::draw(UnkOamBuffer* main, UnkOamBuffer* sub)
{
    if (!enable_) {
        setWindow0Enable(0);
    }
    if (!isDrawable(main, sub) || state_ == 0) {
        return;
    }
    frame_->setPosition(x_ + shakeX_, y_ + shakeY_);
    if (config_->margin_ != 0) {
        frame_->setEnable(1);
    } else {
        frame_->setEnable(0);
        data_02114dd4.frames_.addFrame(0, 192, 256, 192, 0, 15);
    }
    if (namePlate_) {
        namePlate_->setPosition(shakeX_ + (x_ + config_->margin_), shakeY_ + (y_ + config_->margin_ - config_->nameY_) - 4);
        namePlate_->setVisibleCount(-1);
        namePlate_->setEnable(1);
    }
    for (int i = 0; i < lineCount_; i++) {
        UnkMenuTextDisplay* line = lines_[i];
        if (line) {
            if (config_->frameType_ == 1) {
                line->setTranslucent(1);
            } else {
                line->setTranslucent(0);
            }
            line->setPosition(config_->margin_ + (x_ + shakeX_), config_->margin_ + (y_ + shakeY_) + i * lineHeight_ - scroll_);
            line->setEnable(1);
        }
    }
    int type;
    switch (getDisplayPluginType()) {
    case 1:
        type = 0x14;
        break;
    case 2:
        type = 0x11;
        break;
    case 3:
        type = 0x11;
        break;
    default:
        type = 0;
        break;
    }
    if (type) {
        setWindow0Enable(1);
        setWindow0(type, x_ + 2 + shakeX_, y_ - 0xbe + shakeY_, width_ - 4, height_ - 4);
    }
}

THUMB void MessageWindow::setName(const char* name)
{
    char* buf = name_;
    dss::strlen(name);
    MI_CpuFill(0, buf, sizeof(name_));
    STD_CopyString(buf, name);
}

THUMB void MessageWindow::setText(const char* text)
{
    text_[0] = 0;
    appendText(text);
}

THUMB void MessageWindow::appendText(const char* text)
{
    char* buf = text_;
    dss::strlen(text);
    int length = dss::strlen(buf);
    int maxWidth = config_->width_ - config_->margin_ * 2;
    int x = 0;
    setBgTextFontSize(config_->font_);
    UnkUtf8Iterator src;
    src.setText(text);
    UnkUtf8Iterator dst;
    dst.setBuffer(buf + length, sizeof(text_));
    unsigned short c = src.getChar();
    int wordPos = -1;
    int wordLength = -1;
    int line = 0;
    while (c != 0) {
        c = src.getChar();
        src.nextChar();
        if (c == 0x1b) {
            dst.putChar(c);
            c = src.getChar();
            src.nextChar();
            dst.putChar(c);
            c = src.getChar();
            src.nextChar();
        }
        if (c == 0xd) {
            dst.putChar(c);
            c = src.getChar();
            src.nextChar();
        }
        if (c == 0x3221) {
            src.nextChar();
            int count = lineCount_ - line;
            if (line == 0 && x == 0) {
                count = 0;
            }
            for (; count != 0; count--) {
                dst.putChar('\n');
                line++;
            }
            x = 0;
        } else if (c != '\n') {
            int width = drawBgChar(NULL, 0, 0, 0, c);
            dst.putChar(c);
            if (c == ' ' || c == '-' || c == 0x3220) {
                wordPos = src.pos_;
                wordLength = dst.getLength();
            }
            x += width;
            if (x > maxWidth) {
                if (wordPos != -1) {
                    src.pos_ = wordPos;
                    wordPos = -1;
                    dst.truncate(wordLength);
                    wordLength = -1;
                }
                dst.putChar('\n');
                x = 0;
                line++;
            }
        } else {
            dst.putChar(c);
            x = 0;
            line++;
        }
        if (line == lineCount_ && src.getChar() != 0) {
            dst.putChar(0x328a);
            line = 0;
        }
    }
    dst.putChar(0);
}
int data_0209ab10[8] = { -2, 0, 0, 0, -2, 0, 0, 0 };
int data_0209aaf0[8] = { 0, 0, -2, 0, 0, 0, -2, 0 };
static UnkMessageWindowConfig s_config[9] = {
    { 0, 0, 0x138, 128, 72, 8, 16, 16, 3, 8, 1, 0, 12, 12, 4, 2, 1, 1, 0, 0, 0, 0 },
    { 1, 0, 0x138, 256, 72, 8, 16, 16, 3, 8, 1, 0, 12, 12, 4, 2, 1, 1, 0, 0, 1, 0 },
    { 2, 0, 0x138, 256, 72, 8, 16, 16, 3, 8, 1, 0, 12, 12, 4, 2, 1, 1, 0, 0, 1, 0 },
    { 3, 0, 0x138, 256, 72, 8, 0, 0, 4, 4, 1, 0, 10, 10, 4, 2, 1, 100, 30, 40, 0, 0 },
    { 4, 0, 0x140, 256, 70, 8, 16, 16, 2, 8, 1, 1, 10, 10, 4, 2, 1, 100, 0, 0, 0, 0 },
    { 5, 0, 0x138, 256, 72, 8, 0, 0, 4, 4, 1, 0, 12, 12, 2, 2, 1, 100, 30, 40, 0, 0 },
    { 6, 0, 0x140, 256, 70, 8, 16, 16, 2, 8, 1, 1, 12, 12, 2, 2, 1, 100, 0, 0, 0, 0 },
    { 7, 0, 0xf8, 256, 72, 0, 16, 16, 3, 8, 1, 0, 12, 12, 4, 2, 1, 1, 0, 0, 1, 1 },
    { -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 10, 0, 0, 0, 0, 1, 0, 0, 0, 0 },
};

THUMB void MessageWindow::setWindowType(int type)
{
    if (TextAPI::m_lang != 0) {
        if (type == 3) {
            type = 5;
        }
        if (type == 4) {
            type = 6;
        }
    }
    UnkMessageWindowConfig* config = s_config;
    while (config->type_ != -1) {
        if (config->type_ == type) {
            break;
        }
        config++;
    }
    windowType_ = type;
    config_ = config;
    lineCount_ = config->lineCount_;
}

THUMB void MessageWindow::startWindow()
{
    lineCount_ = config_->lineCount_;
    const char* name = name_;
    if (lineCount_ == 4) {
        name = NULL;
    }
    lineHeight_ = config_->fontHeight_ + config_->lineSpace_;
    if (config_->nameX_ == 0) {
        name = NULL;
    }
    int offset;
    if (name) {
        namePlate_ = &data_02114dd4.texts_[3];
        namePlate_->unkfunc_02066fe4(config_->font_, name, 0, 0, 0, 0);
        offset = config_->nameX_ + namePlate_->getTextWidth();
    } else {
        offset = 0;
        namePlate_ = NULL;
    }
    initLines();
    frame_ = &data_02114dd4.windowFrame1_;
    frame_->setNameWidth(offset);
    frame_->setPosition(x_, y_);
    frame_->setFrameType(config_->frameType_);
    frame_->setCursor(0);
    width_ = config_->width_;
    int height = config_->margin_ * 2 - config_->lineSpace_ + lineHeight_ * lineCount_;
    height += config_->unk_24;
    height_ = height;
    frame_->setSize(width_, height_);
    waitLine_ = NULL;
    scroll_ = 0;
    scrollSpeed_ = config_->scrollSpeed_;
    setPosition(config_->x_, config_->y_);
    intervalCursor_ = config_->intervalCursor_ ? 1 : 0;
    lastCursor_ = config_->lastCursor_ ? 1 : 0;
    iterator_.setText(text_);
    state_ = 1;
    shake_ = 0;
    shakeRepeat_ = 0;
    shakeCount_ = 0;
    shakeX_ = 0;
    shakeY_ = 0;
    int repeat = unk_9d4;
    if (repeat) {
        shake_ = 1;
        shakeCount_ = 0;
        shakeRepeat_ = repeat;
        unk_9d4 = 0;
    }
    unk_9f0 = 0;
    unk_9f4 = 0;
    if (unk_9ec) {
        unk_9f0 = unk_9ec;
        unk_9f4 = unk_9ec;
    }
    keyWait_ = 0;
    keySound_ = 0;
    unk_9d0 = 0;
    if (config_->sound_ == 0) {
        sound_ = -1;
    } else {
        sound_ = 0;
    }
    unk_038 = config_->unk_54;
}

THUMB void MessageWindow::updateNameFrame()
{
    lineCount_ = config_->lineCount_;
    const char* name = name_;
    if (lineCount_ == 4) {
        name = NULL;
    }
    lineHeight_ = config_->fontHeight_ + config_->lineSpace_;
    if (config_->nameX_ == 0) {
        name = NULL;
    }
    int offset;
    if (name) {
        namePlate_ = &data_02114dd4.texts_[3];
        namePlate_->unkfunc_02066fe4(config_->font_, name, 0, 0, 1, 0);
        offset = config_->nameX_ + namePlate_->getTextWidth();
    } else {
        offset = 0;
        namePlate_ = NULL;
    }
    frame_ = &data_02114dd4.windowFrame1_;
    frame_->setNameWidth(offset);
    frame_->setPosition(x_, y_);
    frame_->setFrameType(config_->frameType_);
    frame_->setCursor(0);
    width_ = config_->width_;
    int height = config_->margin_ * 2 - config_->lineSpace_ + lineHeight_ * lineCount_;
    height += config_->unk_24;
    height_ = height;
    frame_->setSize(width_, height_);
    setPosition(config_->x_, config_->y_);
}

THUMB void MessageWindow::executeState()
{
    switch (state_) {
    case 0:
        stateIdle();
        break;
    case 1:
        stateNextLine();
        break;
    case 2:
        statePrint();
        break;
    case 3:
        stateScroll();
        break;
    case 4:
        stateWaitKey();
        break;
    case 5:
        stateWaitProg();
        break;
    case 6:
        stateFinish();
        break;
    case 7:
        break;
    }
}

THUMB void MessageWindow::stateIdle()
{
}

THUMB void MessageWindow::stateNextLine()
{
    char buf[0x800];
    int c = getIterator()->getChar();
    if (isEndChar(c)) {
        state_ = 4;
        unk_9c4 = -1;
        return;
    }
    if (c == 0x1b) {
        getIterator()->nextChar();
        c = getIterator()->getChar();
        getIterator()->nextChar();
        if (sound_ != -1) {
            if (c == '0') {
                sound_ = 0;
            }
            if (c == '1') {
                sound_ = 0x12d;
            }
            if (c == '2') {
                sound_ = 0x12e;
            }
            if (c == '3') {
                sound_ = 0x12f;
            }
        }
        if (c == 'A') {
            nextName();
        }
        return;
    }
    if (c == 0x328a) {
        state_ = 4;
        unk_9c4 = -1;
        getIterator()->nextChar();
        if (getIterator()->getChar()) {
            getIterator()->prevChar();
        }
        return;
    }
    if (c == 0x328d) {
        getIterator()->nextChar();
        state_ = 5;
        setWaitProg(1);
        return;
    }
    UnkMenuTextDisplay* line = allocLine();
    if (line == NULL) {
        state_ = 3;
        return;
    }
    if (waitLine_ == NULL) {
        waitLine_ = line;
    }
    UnkUtf8Iterator writer;
    writer.initBuffer(buf, sizeof(buf));
    while (true) {
        c = getIterator()->getChar();
        unsigned char* p = (unsigned char*)iterator_.buf_ + iterator_.pos_;
        if (p[0] == '%') {
            if (p[1] == '3') {
                unk_038 = 1;
                getIterator()->nextChar();
                getIterator()->nextChar();
                continue;
            }
            if (p[1] == '4') {
                unk_038 = 2;
                getIterator()->nextChar();
                getIterator()->nextChar();
                continue;
            }
        }
        if (isEndChar(c) || isControlCode(c)) {
            break;
        }
        if (isNewlineChar(c)) {
            skipNewlines(getIterator());
            break;
        }
        getIterator()->nextChar();
        writer.putChar(c);
    }
    line->unkfunc_02066fe4(config_->font_, buf, 0, 0, 0, unk_038);
    if (unk_038 == 2) {
        unk_038 = 0;
    }
    soundTimer_ = 100;
    state_ = 2;
}

THUMB void MessageWindow::statePrint()
{
    UnkMenuTextDisplay* line = getLastLine();
    if (line->getVisibleCount() != line->getCharCount()) {
        if (unk_9f0 != 0) {
            int limit = line->unk_394;
            if (line->getVisibleCount() < limit) {
                unk_9f0 = 0;
            }
        }
        if (unk_9f0 == 0) {
            line->setVisibleCount(config_->printSpeed_ + line->getVisibleCount());
            int extra = 0;
            if (line->unk_130[line->visibleCount_] == 0x3222) {
                extra = 10;
            }
            wait_ = config_->wait_;
            waitProgFlag_ = config_->unk_4c;
            if (sound_ != 0 && sound_ != -1) {
                if (soundTimer_ > 100) {
                    Sound::sePlay(sound_);
                    soundTimer_ -= 100;
                }
                soundTimer_ += soundSpeed_;
            }
            unk_9f0 = unk_9f4 + extra;
        } else {
            unk_9f0--;
        }
        return;
    }
    if (wait_ == 0) {
        state_ = 1;
        return;
    }
    wait_--;
}

THUMB void MessageWindow::stateScroll()
{
    scroll_ += scrollSpeed_;
    if (scroll_ > lineHeight_) {
        scroll_ = lineHeight_;
    }
    getFirstLine()->clearScrolledLines(scroll_);
    if (scroll_ == lineHeight_) {
        if (waitLine_ == getFirstLine()) {
            waitLine_ = NULL;
        }
        releaseFirstLine();
        scroll_ = 0;
        state_ = 1;
    }
}

THUMB void MessageWindow::stateWaitKey()
{
    if (config_->margin_ != 0 && waitLine_ != getFirstLine()) {
        stateScroll();
        state_ = 4;
        return;
    }
    if (waitProgFlag_) {
        waitProgFlag_--;
        return;
    }
    if (isEndChar(getIterator()->getChar())) {
        keyWait_ = 0;
        keySound_ = 0;
        state_ = 6;
        return;
    }
    if (unk_9c4 == 0) {
        getIterator()->nextChar();
        skipNewlines(getIterator());
        frame_->setCursor(0);
        waitLine_ = NULL;
        keyWait_ = 0;
        keySound_ = 0;
        state_ = 1;
        return;
    }
    if (intervalCursor_) {
        frame_->setCursor(1);
    }
    if (unk_9c4 != -1) {
        unk_9c4--;
    }
    if (keyWait_ == 1) {
        keyWait_ = 0;
        unk_9c4 = 0;
        if (keySound_ == 1) {
            Sound::sePlay(300);
        }
        keySound_ = 0;
    }
}

THUMB void MessageWindow::stateWaitProg()
{
    if (waitProgFlag_) {
        waitProgFlag_--;
        return;
    }
    if (unk_9d0 != 1) {
        state_ = 1;
    }
}

THUMB void MessageWindow::stateFinish()
{
    if (cursor_ == 0 && lastCursor_) {
        frame_->setCursor(1);
    }
    if (cursor_ == 1) {
        frame_->setCursor(1);
    }
    if (cursor_ == -1) {
        frame_->setCursor(0);
    }
    if (keyWait_ == 1) {
        keyWait_ = 0;
        state_ = 7;
        sound_ = -1;
        if (lastCursor_ == 1 && keySound_ == 1) {
            Sound::sePlay(300);
        }
        keySound_ = 0;
    }
}

THUMB void MessageWindow::initLines()
{
    for (int i = 0; i < lineCount_; i++) {
        lines_[i] = NULL;
        freeLines_[i] = &data_02114dd4.texts_[i];
    }
}

THUMB UnkMenuTextDisplay* MessageWindow::allocLine()
{
    for (int i = 0; i < lineCount_; i++) {
        if (freeLines_[i]) {
            UnkMenuTextDisplay* line = freeLines_[i];
            freeLines_[i] = NULL;
            for (int j = 0; j < lineCount_; j++) {
                if (lines_[j] == NULL) {
                    lines_[j] = line;
                    return line;
                }
            }
        }
    }
    return NULL;
}

THUMB UnkMenuTextDisplay* MessageWindow::getFirstLine()
{
    return lines_[0];
}

THUMB UnkMenuTextDisplay* MessageWindow::getLastLine()
{
    UnkMenuTextDisplay* last = NULL;
    for (int i = 0; i < lineCount_; i++) {
        if (lines_[i]) {
            last = lines_[i];
        }
    }
    return last;
}

THUMB void MessageWindow::releaseFirstLine()
{
    UnkMenuTextDisplay* first = lines_[0];
    for (int i = 1; i < lineCount_; i++) {
        lines_[i - 1] = lines_[i];
        lines_[i] = NULL;
    }
    for (int i = 0; i < lineCount_; i++) {
        if (freeLines_[i] == NULL) {
            freeLines_[i] = first;
            return;
        }
    }
}

THUMB int MessageWindow::isEndChar(int c)
{
    if (c == 0) {
        return 1;
    }
    return 0;
}

THUMB int MessageWindow::isNewlineChar(int c)
{
    if (c == '\r') {
        return 1;
    }
    if (c == '\n') {
        return 1;
    }
    return 0;
}

THUMB int MessageWindow::isControlCode(int c)
{
    switch (c) {
    case 0x328a:
    case 0x328b:
    case 0x328c:
    case 0x328d:
    case 0x328e:
    case 0x328f:
    case 0x3290:
        return 1;
    }
    return 0;
}

THUMB void MessageWindow::skipNewlines(UnkTextIterator* it)
{
    while (isNewlineChar(it->getChar())) {
        it->nextChar();
    }
}

THUMB void MessageWindow::openWindow(int type, const char* name, const char* text)
{
    setWindowType(type);
    setName(name);
    setText(text);
    startWindow();
}

THUMB void MessageWindow::addText(const char* text)
{
    appendText(text);
    iterator_.setText(text_);
}

THUMB void MessageWindow::addWaitKey()
{
    addControlCode(0x328a);
}

THUMB void MessageWindow::addWaitProg()
{
    addControlCode(0x328d);
}

THUMB void MessageWindow::addControlCode(int code)
{
    const char* text;
    switch (code) {
    case 0x328a:
        text = "\xe3\x8a\x8a";
        break;
    case 0x328b:
        text = "\xe3\x8a\x8b";
        break;
    case 0x328c:
        text = "\xe3\x8a\x8c";
        break;
    case 0x328d:
        text = "\xe3\x8a\x8d";
        break;
    case 0x328e:
        text = "\xe3\x8a\x8e";
        break;
    case 0x328f:
        text = "\xe3\x8a\x8f";
        break;
    case 0x3290:
        text = "\xe3\x8a\x90";
        break;
    case 0x3221:
        text = "\xe3\x88\xa1";
        break;
    default:
        return;
    }
    appendText(text);
}

THUMB void MessageWindow::clearNames()
{
    nameIndex_ = -1;
    nameCount_ = 0;
    for (int i = 0; i < 32; i++) {
        names_[i][0] = 0;
    }
}

THUMB void MessageWindow::addName(const char* name)
{
    if (nameCount_ != 32) {
        dss::strcpy_s(names_[nameCount_], 0x80, name);
        nameCount_++;
    }
}

THUMB void MessageWindow::nextName()
{
    const char* prev = getCurrentName();
    nameIndex_++;
    const char* next = getCurrentName();
    if (prev == NULL) {
        prev = "";
    }
    if (next == NULL) {
        next = "";
    }
    if (dss::strcmp(prev, next) != 0) {
        setName(next);
        updateNameFrame();
    }
}

THUMB const char* MessageWindow::getCurrentName()
{
    if (nameIndex_ == -1) {
        return NULL;
    }
    if (nameIndex_ >= nameCount_) {
        return NULL;
    }
    return names_[nameIndex_];
}

THUMB void MessageWindow::restart()
{
    state_ = 1;
    waitLine_ = NULL;
    text_[0] = 0;
    if (config_->sound_ == 0) {
        sound_ = -1;
    } else {
        sound_ = 0;
    }
}

THUMB int MessageWindow::isWaitTrigger()
{
    if (state_ == 4) {
        return 1;
    }
    return 0;
}

THUMB int MessageWindow::isFinish()
{
    if (state_ == 6) {
        return 1;
    }
    return 0;
}

THUMB int MessageWindow::isEnd()
{
    if (state_ == 7) {
        return 1;
    }
    return 0;
}

THUMB bool MessageWindow::isWaitProg()
{
    if (state_ == 5) {
        return 1;
    }
    return 0;
}

THUMB void MessageWindow::clearWaitTriggerSE()
{
    keyWait_ = 1;
    keySound_ = 1;
}

THUMB void MessageWindow::clearWaitTriggerNoSE()
{
    keyWait_ = 1;
    keySound_ = 0;
}

THUMB void MessageWindow::setWaitProg(int flag)
{
    unk_9d0 = flag;
}
