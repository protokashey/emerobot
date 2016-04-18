/* -*- Mode: C; c-basic-offset: 4; -*-
 *
 * EMEROBOT, A WHOLE POOL OF CREATED BOT PROCESS INSTANCES
 *
 * ### Programmed by kashey@protonmail.com,
 * ### source code published under terms of GPLv3 license.
 *
 */

#include <stdio.h>
#include <string.h>


#include "emerobots.h"



Emerobots::Emerobots ()
{
    bots      = NULL;
    bots_tail = NULL;
    nbots     = 0;
}


Emerobots::~Emerobots()
{
    Emerobot *c, *n;

    for ( c=bots; c; c=n )
    {
	n = c->next;

	delete c;
    }
}

int  Emerobots::Push ( Emerobot * bot )
{
    int id;

    Lock();

    bot->AssignRoot (this);

    if (bots)
    {
	bots_tail->next = bot;
	bots_tail       = bot;
    }
    else
	bots = bots_tail = bot;

    ++ nbots;

    id = nbots;
    bot->AssignID (id);

    Unlock();

    return id;
}






Emerobots Bots;

