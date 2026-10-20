#include "main/sound/UnkNnsSound.hpp"
#include "nnsys/snd.hpp"

int data_02101570[2];
int data_0209a370 = 0x7f;

THUMB UnkSoundHandle::UnkSoundHandle()
{
    volumeSys_ = 0x7f;
    volume_ = 0x7f;
    seArc_ = 0;
    seIndex_ = 0;
    sePlaying_ = 0;
    bgm_[0] = 0;
    bgm_[1] = 0;
    active_[0] = 0;
    active_[1] = 0;
}

THUMB UnkSoundHandle::~UnkSoundHandle()
{
}

THUMB void UnkSoundHandle::init(int a)
{
    current_ = 0;
    pause_ = 0;
    func_0207b51c(&handle_[0]);
    func_0207b51c(&handle_[1]);
    unk_14 = a;
}

THUMB void UnkSoundHandle::playBgm(int bgm, int sub)
{
    if (pause_ != 0 && sub == 0) {
        if (active_[0] == 0) {
            bgm_[0] = -1;
        }
        if (active_[1] == 0) {
            bgm_[1] = -1;
        }
        if (bgm != bgm_[0]) {
            stopAll(15);
            func_0207b384();
        }
    }
    prev_ = current_;
    if (sub == 0) {
        current_ = 0;
        if (pause_ != 0) {
            setPause(0);
            applyVolume();
            return;
        }
        func_0207ceac(&handle_[current_], bgm);
    } else {
        if (sub != 0) {
            setPause(1);
        }
        current_ = 1;
        func_0207ceac(&handle_[current_], bgm);
    }
    bgm_[current_] = bgm;
    active_[current_] = 1;
    func_0207b578(&handle_[current_], data_0209a370);
    applyVolume();
}

THUMB void UnkSoundHandle::stopBgm(int fade)
{
    if (current_ == 0) {
        pause_ = 0;
    }
    func_0207b504(&handle_[current_], fade);
    active_[current_] = 0;
}

THUMB int UnkSoundHandle::isBgmPlaying()
{
    if (isPaused()) {
        if (func_0207b534(bgm_[1])) {
            return 1;
        }
    } else {
        int playing0 = func_0207b534(bgm_[0]);
        int playing1 = func_0207b534(bgm_[1]);
        if (playing0 || playing1) {
            return 1;
        }
    }
    return 0;
}

THUMB int UnkSoundHandle::isBgmStopped()
{
    if (isPaused()) {
        if (func_0207b534(bgm_[1]) == 0) {
            return 1;
        }
    }
    if (func_0207b534(bgm_[0]) == 0 && func_0207b534(bgm_[1]) == 0) {
        return 1;
    }
    return 0;
}

THUMB void UnkSoundHandle::setPause(int pause)
{
    pause_ = pause;
    func_0207b510(&handle_[current_], pause);
}

THUMB int UnkSoundHandle::isPaused()
{
    return pause_;
}

THUMB void UnkSoundHandle::stopAll(int fade)
{
    func_0207b504(&handle_[0], 0);
    func_0207b504(&handle_[1], 0);
    active_[0] = 0;
    active_[1] = 0;
    pause_ = 0;
    current_ = 0;
}

THUMB void UnkSoundHandle::playSe(int seqArc, int index)
{
    func_0207b504(&handle_[current_], 0);
    int mode = 0;
    int player = 9;
    int priority = -1;
    int mute = 0xff00;
    if (index == 300) {
        mode = 1;
        priority = 50;
    }
    if (index == 402) {
        player = 9;
        mode = 1;
        priority = 127;
        mute = 0xc000;
    }
    if (index == 404) {
        player = 9;
        mode = 1;
        priority = 100;
    }
    if (index == 405) {
        player = 9;
        mode = 1;
        priority = 100;
    }
    if (index == 406) {
        player = 9;
        mode = 1;
        priority = 120;
    }
    if (index == 407) {
        player = 9;
        mode = 1;
        priority = 120;
    }
    if (index == 520) {
        player = 9;
        mode = 1;
        priority = 120;
    }
    if (index == 521) {
        player = 9;
        mode = 1;
        priority = 120;
    }
    if (index == 306) {
        player = 9;
        mode = 1;
        priority = 127;
    }
    if (index == 501) {
        player = 9;
        mode = 1;
        priority = 127;
    }
    if (index == 1100) {
        player = 10;
        mode = 2;
        priority = 127;
    }
    if (mode == 0) {
        func_0207ced8(&handle_[current_], seqArc, index);
    }
    if (mode == 1) {
        func_0207cf2c(&handle_[current_], player, -1, priority, seqArc, index);
        func_0207b59c(&handle_[current_], 0xffff, mute);
    }
    if (mode == 2) {
        func_0207cf2c(&handle_[current_], player, -1, priority, seqArc, index);
    }
    seArc_ = seqArc;
    seIndex_ = index;
    sePlaying_ = 1;
}

THUMB int UnkSoundHandle::isSe(int seqArc, int index)
{
    if (seArc_ != seqArc) {
        return 0;
    }
    return seIndex_ == index;
}

THUMB void UnkSoundHandle::stopSe(int fade)
{
    func_0207b504(&handle_[current_], fade);
    seArc_ = -1;
    seIndex_ = -1;
    sePlaying_ = 0;
}

THUMB int UnkSoundHandle::isSePlaying()
{
    if (func_0207b5e0(&handle_[current_]) != 0) {
        return 1;
    }
    return sePlaying_ == 1;
}

THUMB void UnkSoundHandle::setVolume(int volume)
{
    volume_ = volume;
    func_0207b568(&handle_[current_], volume);
}

THUMB void UnkSoundHandle::applyVolume()
{
    func_0207b568(&handle_[current_], volumeSys_ * volume_ / 127);
}

THUMB UnkNnsSound::UnkNnsSound()
{
    unk_a8 = 0;
}

THUMB UnkNnsSound::~UnkNnsSound()
{
}

THUMB void UnkNnsSound::init(void* file, void* memory, int size, int group)
{
    unk_b4 = 0;
    bgm_ = 0;
    subBgm_ = -1;
    file_ = file;
    group_ = group;
    memory_ = memory;
    size_ = size - 0x3e800;
    heap_[0] = func_0207c5fc(memory_, size_);
    heap_[1] = func_0207c5fc((unsigned char*)memory_ + size_, 0xc800);
    heap_[2] = func_0207c5fc((unsigned char*)memory_ + (size_ + 0xc800), 0x32000);
    loadArchive();
}

THUMB void UnkNnsSound::loadArchive()
{
    func_0207c658(heap_[0]);
    func_0207c658(heap_[1]);
    func_0207c658(heap_[2]);
    func_0207c0c8(arc_, file_, heap_[0], 0);
    func_0207ce50(0);
    if (group_ != 0) {
        func_0207d0a0(20, heap_[0]);
    }
    func_0207be8c(3);
    func_0207b480(0, 5);
    func_0207b480(1, 5);
    func_0207b480(2, 1);
    func_0207b480(3, 1);
    func_0207b480(4, 5);
    func_0207b480(5, 5);
    func_0207b480(6, 5);
    func_0207b480(7, 2);
    func_0207b480(8, 5);
    func_0207b480(9, 2);
    func_0207b494(9, 0xff00);
    func_0207b480(10, 1);
    func_0207b494(10, 0x3c00);
    saved_ = 0;
}

THUMB void UnkNnsSound::update()
{
    func_0207b384();
}

THUMB void UnkNnsSound::loadBgm(int bgm, int sub)
{
    if (saved_ == 0) {
        heapState_[0] = func_0207c70c(heap_[0]);
        heapState_[1] = func_0207c70c(heap_[1]);
        heapState_[2] = func_0207c70c(heap_[2]);
        saved_ = 1;
    }
    if (sub == 0) {
        if (bgm != bgm_) {
            unk_b4 = 0;
        }
        if (unk_b4 != 0) {
            func_0207c740(heap_[0], state_);
            func_0207c740(heap_[2], heapState_[2]);
            loadBank(bgm, heap_[0]);
            loadWaveArc(bgm, heap_[2]);
            unk_b4 = 0;
            bgm_ = bgm;
            return;
        }
        int main = (bgm < 101 || bgm > 120);
        if (main) {
            func_0207c740(heap_[0], heapState_[0]);
            func_0207c740(heap_[2], heapState_[2]);
            loadSeq(bgm, heap_[0]);
            loadBank(bgm, heap_[0]);
            state_ = func_0207c70c(heap_[0]);
            loadWaveArc(bgm, heap_[2]);
            unk_b4 = 0;
            bgm_ = bgm;
            return;
        }
        loadSeq(bgm, heap_[1]);
        loadBank(bgm, heap_[1]);
        loadWaveArc(bgm, heap_[1]);
        subBgm_ = bgm;
        return;
    }
    func_0207c740(heap_[1], heapState_[1]);
    func_0207c740(heap_[2], heapState_[2]);
    loadSeq(bgm, heap_[1]);
    loadBank(bgm, heap_[1]);
    state_ = func_0207c70c(heap_[1]);
    loadWaveArc(bgm, heap_[2]);
    unk_b4 = 1;
    subBgm_ = -1;
}

THUMB void UnkNnsSound::preload(int a, int b)
{
    func_0207c844(a, heap_[0]);
    func_0207c860(b, heap_[0]);
}

THUMB int UnkNnsSound::loadSeq(int no, void* heap)
{
    return func_0207c87c(no, 1, heap);
}

THUMB int UnkNnsSound::loadBank(int no, void* heap)
{
    return func_0207c87c(no, 2, heap);
}

THUMB int UnkNnsSound::loadWaveArc(int no, void* heap)
{
    return func_0207c87c(no, 4, heap);
}

THUMB UnkSoundMember::UnkSoundMember()
{
}

THUMB UnkSoundMember::~UnkSoundMember()
{
}

THUMB void UnkSoundMember::init()
{
    func_0207d280(this);
}

THUMB void UnkSoundMember::play(int no)
{
    func_0207d244(this, no, 0);
    func_0207d270(this, data_0209a374);
}

THUMB void UnkSoundMember::stop(int value)
{
    func_0207d260(this, value);
}

THUMB int UnkSoundMember::isPlaying()
{
    if (func_0207d29c(this) != 0) {
        return 1;
    }
    return 0;
}

UnkNnsSound data_02101584;
int data_0209a374 = 0x7f;
