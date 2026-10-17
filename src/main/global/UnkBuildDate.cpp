#include "main/global/UnkBuildDate.hpp"
#include <string.h>

THUMB UnkBuildDate::UnkBuildDate()
{
    date_ = "Oct 24 2008";
    strcpy(time_, "21:40:29");
    strcpy(dateString_, "Oct 24 2008");
}
