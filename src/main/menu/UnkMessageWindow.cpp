#pragma ipa file
#include "main/menu/UnkMessageWindow.hpp"
#include "main/dss/UnkDisplay.hpp"
#include "main/menu/UnkMenuTextDisplay.hpp"
#include "main/menu/UnkMenuWindowFrame.hpp"
#include "main/dss/DssUtils.hpp"
#include "main/dss/UnkBgBuffer.hpp"
#include "main/sound/Sound.hpp"
#include <nitro/std.h>
#include "main/menu/UnkMenuDisplays.hpp"
#include "main/text/TextAPI.hpp"

inline UnkTextIterator* UnkMessageWindow::getIterator()
{
    return &iterator_;
}

THUMB UnkMessageWindow::UnkMessageWindow()
{
    windowType_ = 0;
    cursor_ = 0;
    soundSpeed_ = 25;
}

THUMB void UnkMessageWindow::setup(int id)
{
    id_ = id;
    unkfunc_020646c8();
    unkfunc_0206477c(2);
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

THUMB void UnkMessageWindow::update(UnkOamBuffer* main, UnkOamBuffer* sub)
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

THUMB void UnkMessageWindow::execute(UnkOamBuffer* main, UnkOamBuffer* sub)
{
    unkfunc_02066288();
}

THUMB void UnkMessageWindow::draw(UnkOamBuffer* main, UnkOamBuffer* sub)
{
    if (!enable_) {
        unkfunc_0204d068(0);
    }
    if (!unkfunc_02064730(main, sub) || state_ == 0) {
        return;
    }
    frame_->unkfunc_0206478c(x_ + shakeX_, y_ + shakeY_);
    if (config_->margin_ != 0) {
        frame_->unkfunc_02064780(1);
    } else {
        frame_->unkfunc_02064780(0);
        data_02114dd4.frames_.unkfunc_02064270(0, 192, 256, 192, 0, 15);
    }
    if (namePlate_) {
        namePlate_->unkfunc_0206478c(shakeX_ + (x_ + config_->margin_), shakeY_ + (y_ + config_->margin_ - config_->nameY_) - 4);
        namePlate_->unkfunc_02067180(-1);
        namePlate_->unkfunc_02064780(1);
    }
    for (int i = 0; i < lineCount_; i++) {
        UnkMenuTextDisplay* line = lines_[i];
        if (line) {
            if (config_->frameType_ == 1) {
                line->unkfunc_02067268(1);
            } else {
                line->unkfunc_02067268(0);
            }
            line->unkfunc_0206478c(config_->margin_ + (x_ + shakeX_), config_->margin_ + (y_ + shakeY_) + i * lineHeight_ - scroll_);
            line->unkfunc_02064780(1);
        }
    }
    int type;
    switch (unkfunc_0204d0b8()) {
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
        unkfunc_0204d068(1);
        unkfunc_0204d080(type, x_ + 2 + shakeX_, y_ - 0xbe + shakeY_, width_ - 4, height_ - 4);
    }
}

THUMB void UnkMessageWindow::unkfunc_02065e0c(const char* name)
{
    char* buf = name_;
    dss::strlen(name);
    MI_CpuFill(0, buf, sizeof(name_));
    STD_CopyString(buf, name);
}

THUMB void UnkMessageWindow::unkfunc_02065e30(const char* text)
{
    text_[0] = 0;
    unkfunc_02065e40(text);
}

THUMB void UnkMessageWindow::unkfunc_02065e40(const char* text)
{
    char* buf = text_;
    dss::strlen(text);
    int length = dss::strlen(buf);
    int maxWidth = config_->width_ - config_->margin_ * 2;
    int x = 0;
    unkfunc_0204e478(config_->font_);
    UnkUtf8Iterator src;
    src.unkfunc_0204a800(text);
    UnkUtf8Iterator dst;
    dst.unkfunc_0204a814(buf + length, sizeof(text_));
    unsigned short c = src.unkfunc_0204a990();
    int wordPos = -1;
    int wordLength = -1;
    int line = 0;
    while (c != 0) {
        c = src.unkfunc_0204a990();
        src.unkfunc_0204a9ec();
        if (c == 0x1b) {
            dst.unkfunc_0204a9a0(c);
            c = src.unkfunc_0204a990();
            src.unkfunc_0204a9ec();
            dst.unkfunc_0204a9a0(c);
            c = src.unkfunc_0204a990();
            src.unkfunc_0204a9ec();
        }
        if (c == 0xd) {
            dst.unkfunc_0204a9a0(c);
            c = src.unkfunc_0204a990();
            src.unkfunc_0204a9ec();
        }
        if (c == 0x3221) {
            src.unkfunc_0204a9ec();
            int count = lineCount_ - line;
            if (line == 0 && x == 0) {
                count = 0;
            }
            for (; count != 0; count--) {
                dst.unkfunc_0204a9a0('\n');
                line++;
            }
            x = 0;
        } else if (c != '\n') {
            int width = unkfunc_0204e1a0(NULL, 0, 0, 0, c);
            dst.unkfunc_0204a9a0(c);
            if (c == ' ' || c == '-' || c == 0x3220) {
                wordPos = src.pos_;
                wordLength = dst.unkfunc_0204a864();
            }
            x += width;
            if (x > maxWidth) {
                if (wordPos != -1) {
                    src.pos_ = wordPos;
                    wordPos = -1;
                    dst.unkfunc_0204a880(wordLength);
                    wordLength = -1;
                }
                dst.unkfunc_0204a9a0('\n');
                x = 0;
                line++;
            }
        } else {
            dst.unkfunc_0204a9a0(c);
            x = 0;
            line++;
        }
        if (line == lineCount_ && src.unkfunc_0204a990() != 0) {
            dst.unkfunc_0204a9a0(0x328a);
            line = 0;
        }
    }
    dst.unkfunc_0204a9a0(0);
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

THUMB void UnkMessageWindow::unkfunc_02065fe0(int type)
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

THUMB void UnkMessageWindow::unkfunc_02066028()
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
        offset = config_->nameX_ + namePlate_->unkfunc_020671e0();
    } else {
        offset = 0;
        namePlate_ = NULL;
    }
    unkfunc_02066834();
    frame_ = &data_02114dd4.windowFrame1_;
    frame_->unkfunc_0206529c(offset);
    frame_->unkfunc_0206478c(x_, y_);
    frame_->unkfunc_020652c4(config_->frameType_);
    frame_->unkfunc_020652a8(0);
    width_ = config_->width_;
    int height = config_->margin_ * 2 - config_->lineSpace_ + lineHeight_ * lineCount_;
    height += config_->unk_24;
    height_ = height;
    frame_->unkfunc_02064794(width_, height_);
    waitLine_ = NULL;
    scroll_ = 0;
    scrollSpeed_ = config_->scrollSpeed_;
    unkfunc_0206478c(config_->x_, config_->y_);
    intervalCursor_ = config_->intervalCursor_ ? 1 : 0;
    lastCursor_ = config_->lastCursor_ ? 1 : 0;
    iterator_.unkfunc_0204a800(text_);
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

THUMB void UnkMessageWindow::unkfunc_020661cc()
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
        offset = config_->nameX_ + namePlate_->unkfunc_020671e0();
    } else {
        offset = 0;
        namePlate_ = NULL;
    }
    frame_ = &data_02114dd4.windowFrame1_;
    frame_->unkfunc_0206529c(offset);
    frame_->unkfunc_0206478c(x_, y_);
    frame_->unkfunc_020652c4(config_->frameType_);
    frame_->unkfunc_020652a8(0);
    width_ = config_->width_;
    int height = config_->margin_ * 2 - config_->lineSpace_ + lineHeight_ * lineCount_;
    height += config_->unk_24;
    height_ = height;
    frame_->unkfunc_02064794(width_, height_);
    unkfunc_0206478c(config_->x_, config_->y_);
}

THUMB void UnkMessageWindow::unkfunc_02066288()
{
    switch (state_) {
    case 0:
        unkfunc_020662dc();
        break;
    case 1:
        unkfunc_020662e0();
        break;
    case 2:
        unkfunc_0206653c();
        break;
    case 3:
        unkfunc_0206662c();
        break;
    case 4:
        unkfunc_0206668c();
        break;
    case 5:
        unkfunc_02066788();
        break;
    case 6:
        unkfunc_020667ac();
        break;
    case 7:
        break;
    }
}

THUMB void UnkMessageWindow::unkfunc_020662dc()
{
}

THUMB void UnkMessageWindow::unkfunc_020662e0()
{
    char buf[0x800];
    int c = getIterator()->unkfunc_0204a990();
    if (unkfunc_02066918(c)) {
        state_ = 4;
        unk_9c4 = -1;
        return;
    }
    if (c == 0x1b) {
        getIterator()->unkfunc_0204a9ec();
        c = getIterator()->unkfunc_0204a990();
        getIterator()->unkfunc_0204a9ec();
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
            unkfunc_02066ad0();
        }
        return;
    }
    if (c == 0x328a) {
        state_ = 4;
        unk_9c4 = -1;
        getIterator()->unkfunc_0204a9ec();
        if (getIterator()->unkfunc_0204a990()) {
            getIterator()->unkfunc_0204aa18();
        }
        return;
    }
    if (c == 0x328d) {
        getIterator()->unkfunc_0204a9ec();
        state_ = 5;
        unkfunc_02066be8(1);
        return;
    }
    UnkMenuTextDisplay* line = unkfunc_02066864();
    if (line == NULL) {
        state_ = 3;
        return;
    }
    if (waitLine_ == NULL) {
        waitLine_ = line;
    }
    UnkUtf8Iterator writer;
    writer.unkfunc_0204a828(buf, sizeof(buf));
    while (true) {
        c = getIterator()->unkfunc_0204a990();
        unsigned char* p = (unsigned char*)iterator_.buf_ + iterator_.pos_;
        if (p[0] == '%') {
            if (p[1] == '3') {
                unk_038 = 1;
                getIterator()->unkfunc_0204a9ec();
                getIterator()->unkfunc_0204a9ec();
                continue;
            }
            if (p[1] == '4') {
                unk_038 = 2;
                getIterator()->unkfunc_0204a9ec();
                getIterator()->unkfunc_0204a9ec();
                continue;
            }
        }
        if (unkfunc_02066918(c) || unkfunc_02066938(c)) {
            break;
        }
        if (unkfunc_02066924(c)) {
            unkfunc_02066968(getIterator());
            break;
        }
        getIterator()->unkfunc_0204a9ec();
        writer.unkfunc_0204a9a0(c);
    }
    line->unkfunc_02066fe4(config_->font_, buf, 0, 0, 0, unk_038);
    if (unk_038 == 2) {
        unk_038 = 0;
    }
    soundTimer_ = 100;
    state_ = 2;
}

THUMB void UnkMessageWindow::unkfunc_0206653c()
{
    UnkMenuTextDisplay* line = unkfunc_020668b0();
    if (line->unkfunc_020671d0() != line->unkfunc_020671d8()) {
        if (unk_9f0 != 0) {
            int limit = line->unk_394;
            if (line->unkfunc_020671d0() < limit) {
                unk_9f0 = 0;
            }
        }
        if (unk_9f0 == 0) {
            line->unkfunc_02067180(config_->printSpeed_ + line->unkfunc_020671d0());
            int extra = 0;
            if (line->unk_130[line->visibleCount_] == 0x3222) {
                extra = 10;
            }
            wait_ = config_->wait_;
            unk_9cc = config_->unk_4c;
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

THUMB void UnkMessageWindow::unkfunc_0206662c()
{
    scroll_ += scrollSpeed_;
    if (scroll_ > lineHeight_) {
        scroll_ = lineHeight_;
    }
    unkfunc_020668ac()->unkfunc_020671e8(scroll_);
    if (scroll_ == lineHeight_) {
        if (waitLine_ == unkfunc_020668ac()) {
            waitLine_ = NULL;
        }
        unkfunc_020668d4();
        scroll_ = 0;
        state_ = 1;
    }
}

THUMB void UnkMessageWindow::unkfunc_0206668c()
{
    if (config_->margin_ != 0 && waitLine_ != unkfunc_020668ac()) {
        unkfunc_0206662c();
        state_ = 4;
        return;
    }
    if (unk_9cc) {
        unk_9cc--;
        return;
    }
    if (unkfunc_02066918(getIterator()->unkfunc_0204a990())) {
        keyWait_ = 0;
        keySound_ = 0;
        state_ = 6;
        return;
    }
    if (unk_9c4 == 0) {
        getIterator()->unkfunc_0204a9ec();
        unkfunc_02066968(getIterator());
        frame_->unkfunc_020652a8(0);
        waitLine_ = NULL;
        keyWait_ = 0;
        keySound_ = 0;
        state_ = 1;
        return;
    }
    if (intervalCursor_) {
        frame_->unkfunc_020652a8(1);
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

THUMB void UnkMessageWindow::unkfunc_02066788()
{
    if (unk_9cc) {
        unk_9cc--;
        return;
    }
    if (unk_9d0 != 1) {
        state_ = 1;
    }
}

THUMB void UnkMessageWindow::unkfunc_020667ac()
{
    if (cursor_ == 0 && lastCursor_) {
        frame_->unkfunc_020652a8(1);
    }
    if (cursor_ == 1) {
        frame_->unkfunc_020652a8(1);
    }
    if (cursor_ == -1) {
        frame_->unkfunc_020652a8(0);
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

THUMB void UnkMessageWindow::unkfunc_02066834()
{
    for (int i = 0; i < lineCount_; i++) {
        lines_[i] = NULL;
        freeLines_[i] = &data_02114dd4.texts_[i];
    }
}

THUMB UnkMenuTextDisplay* UnkMessageWindow::unkfunc_02066864()
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

THUMB UnkMenuTextDisplay* UnkMessageWindow::unkfunc_020668ac()
{
    return lines_[0];
}

THUMB UnkMenuTextDisplay* UnkMessageWindow::unkfunc_020668b0()
{
    UnkMenuTextDisplay* last = NULL;
    for (int i = 0; i < lineCount_; i++) {
        if (lines_[i]) {
            last = lines_[i];
        }
    }
    return last;
}

THUMB void UnkMessageWindow::unkfunc_020668d4()
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

THUMB int UnkMessageWindow::unkfunc_02066918(int c)
{
    if (c == 0) {
        return 1;
    }
    return 0;
}

THUMB int UnkMessageWindow::unkfunc_02066924(int c)
{
    if (c == '\r') {
        return 1;
    }
    if (c == '\n') {
        return 1;
    }
    return 0;
}

THUMB int UnkMessageWindow::unkfunc_02066938(int c)
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

THUMB void UnkMessageWindow::unkfunc_02066968(UnkTextIterator* it)
{
    while (unkfunc_02066924(it->unkfunc_0204a990())) {
        it->unkfunc_0204a9ec();
    }
}

THUMB void UnkMessageWindow::unkfunc_020669a0(int type, const char* name, const char* text)
{
    unkfunc_02065fe0(type);
    unkfunc_02065e0c(name);
    unkfunc_02065e30(text);
    unkfunc_02066028();
}

THUMB void UnkMessageWindow::unkfunc_020669c4(const char* text)
{
    unkfunc_02065e40(text);
    iterator_.unkfunc_0204a800(text_);
}

THUMB void UnkMessageWindow::unkfunc_020669e0()
{
    unkfunc_02066a00(0x328a);
}

THUMB void UnkMessageWindow::unkfunc_020669f0()
{
    unkfunc_02066a00(0x328d);
}

THUMB void UnkMessageWindow::unkfunc_02066a00(int code)
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
    unkfunc_02065e40(text);
}

THUMB void UnkMessageWindow::unkfunc_02066a7c()
{
    nameIndex_ = -1;
    nameCount_ = 0;
    for (int i = 0; i < 32; i++) {
        names_[i][0] = 0;
    }
}

THUMB void UnkMessageWindow::unkfunc_02066aa4(const char* name)
{
    if (nameCount_ != 32) {
        dss::strcpy_s(names_[nameCount_], 0x80, name);
        nameCount_++;
    }
}

THUMB void UnkMessageWindow::unkfunc_02066ad0()
{
    const char* prev = unkfunc_02066b1c();
    nameIndex_++;
    const char* next = unkfunc_02066b1c();
    if (prev == NULL) {
        prev = "";
    }
    if (next == NULL) {
        next = "";
    }
    if (dss::strcmp(prev, next) != 0) {
        unkfunc_02065e0c(next);
        unkfunc_020661cc();
    }
}

THUMB const char* UnkMessageWindow::unkfunc_02066b1c()
{
    if (nameIndex_ == -1) {
        return NULL;
    }
    if (nameIndex_ >= nameCount_) {
        return NULL;
    }
    return names_[nameIndex_];
}

THUMB void UnkMessageWindow::unkfunc_02066b48()
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

THUMB int UnkMessageWindow::unkfunc_02066b74()
{
    if (state_ == 4) {
        return 1;
    }
    return 0;
}

THUMB int UnkMessageWindow::unkfunc_02066b88()
{
    if (state_ == 6) {
        return 1;
    }
    return 0;
}

THUMB int UnkMessageWindow::unkfunc_02066b9c()
{
    if (state_ == 7) {
        return 1;
    }
    return 0;
}

THUMB bool UnkMessageWindow::unkfunc_02066bb0()
{
    if (state_ == 5) {
        return 1;
    }
    return 0;
}

THUMB void UnkMessageWindow::unkfunc_02066bc4()
{
    keyWait_ = 1;
    keySound_ = 1;
}

THUMB void UnkMessageWindow::unkfunc_02066bd4()
{
    keyWait_ = 1;
    keySound_ = 0;
}

THUMB void UnkMessageWindow::unkfunc_02066be8(int flag)
{
    unk_9d0 = flag;
}
