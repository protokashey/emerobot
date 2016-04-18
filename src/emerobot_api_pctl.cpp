/* -*- Mode: C; c-basic-offset: 4; -*-
 *
 * EMEROBOT, JAVASCRIPT API IMPLEMENTATION, PROCESS CONTROL FUNCTIONS
 *
 * ### Programmed by kashey@protonmail.com,
 * ### source code published under terms of GPLv3 license.
 *
 */


#include <stdlib.h>
#include <unistd.h>


#include "emerobot.h"




static duk_ret_t API__sleep ( duk_context * ctx )
{
    double        dur = duk_require_number ( ctx, 0 );

    if ( dur < 0.0 )                      dur = 0.0;
    if ( dur > 3600.0 * 24 * 365 * 100 )  dur = 3600.0 * 24 * 365 * 100;

    if ( dur > 3600 )
    {
	unsigned int  Dur = dur + 0.5;
	sleep (Dur);
    }
    else
    {
	unsigned int  Dur = dur * 1000000.0 + 0.5;
	usleep (Dur);
    }

    return 0;
}

static duk_ret_t API__settitle ( duk_context * ctx )
{
    duk_size_t    len;
    const char *  new_title = duk_require_lstring ( ctx, 0, &len );

    Bot->SetTitle (new_title);

    return 0;
}



void Emerobot::InstallAPI_pctl()
{
    duk_push_c_function ( ctx, API__sleep, 1 );
    duk_put_prop_string ( ctx, -2, "sleep");

    duk_push_c_function ( ctx, API__settitle, 1 );
    duk_put_prop_string ( ctx, -2, "settitle" );
}


