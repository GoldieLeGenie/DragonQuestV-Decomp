#include "main/ceremony/CeremonySetting.hpp"

THUMB ceremony::CeremonySetting::CeremonySetting() : opening_(0), staffrollIndex_(0), nextActMap_(1)
{
}

THUMB ceremony::CeremonySetting::~CeremonySetting()
{
}

THUMB ceremony::CeremonySetting* ceremony::CeremonySetting::getSingleton()
{
    static CeremonySetting s_singleton;
    return &s_singleton;
}
