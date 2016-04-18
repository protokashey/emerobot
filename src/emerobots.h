/* -*- Mode: C; c-basic-offset: 4; -*-
 *
 * EMEROBOT, A WHOLE POOL OF CREATED BOT PROCESS INSTANCES
 *
 * ### Programmed by kashey@protonmail.com,
 * ### source code published under terms of GPLv3 license.
 *
 */

#ifndef EMEROBOTS_H_INCLUDED
#define EMEROBOTS_H_INCLUDED


#include <boost/thread/mutex.hpp>

#include "emerobot.h"


class Emerobots
{
 public:
    Emerobots();
    ~Emerobots();

    boost::mutex   Mutex;
    void           Lock()   { Mutex.lock();   }
    void           Unlock() { Mutex.unlock(); }

    Emerobot     * bots;
    Emerobot     * bots_tail;
    int            nbots;

    int            Push ( Emerobot * bot );
};


extern Emerobots   Bots;



#endif

