//
//  UntilTool.cpp
//  HelpAnimal
//
//  Created by lly on 14-7-31.
//
//

#include "UntilTool.h"

long UntilTool::getCurrentTime()
{
    struct cc_timeval tv;
    CCTime::gettimeofdayCocos2d(&tv, NULL);
    return tv.tv_sec * 1000 + tv.tv_usec / 1000;
}