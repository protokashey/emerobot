/* -*- Mode: C; c-basic-offset: 4; -*-
 *
 * EMEROBOT, BOT PROCESS INSTANCE
 *
 * ### Programmed by kashey@protonmail.com,
 * ### source code published under terms of GPLv3 license.
 *
 */

#include <stdio.h>
#include <string.h>
#include <assert.h>


#include "emerobot.h"
#include "emerobots.h"


__thread Emerobot * Bot = NULL;


Emerobot::Emerobot ( string ProgramName, int argc, string ** argv )
{
    root      = NULL;
    next      = NULL;

    running_p = 1;
    id        = 0;
    Title     = "";
    Program   = ProgramName;
    Argc      = argc;
    Argv      = argv;
    Process   = CreateThread ( Boot, this, true );
}


Emerobot::~Emerobot()
{
    for ( int i=0; i<Argc; i++ )
	delete Argv[i];

    free (Argv);
}


void Emerobot::Lock_Full()   { root->Lock(); Mutex.lock(); }
void Emerobot::Unlock_Full() { Mutex.unlock(); root->Unlock(); }


void Emerobot::Boot ( void * p )
{
    Emerobot * bot = (Emerobot*) p;

    bot->Run();
    bot->running_p = 0;

    ExitThread (0);
}

void Emerobot::AssignRoot ( Emerobots * new_root )
{
    assert ( root == NULL );
    assert ( new_root != NULL );
    root = new_root;
}

void Emerobot::AssignID ( int new_id )
{
    assert ( id == 0 );
    assert ( new_id > 0 );
    id = new_id;
}

bool Emerobot::IsFinished() { return ! running_p; }

int Emerobot::GetID() { return id; }
string Emerobot::GetProgram() { return Program; }

string Emerobot::GetTitle() { return Title; }

void Emerobot::SetTitle ( string new_title )
{
    Title = new_title;
}

void Emerobot::SetTitle ( const char * new_title )
{
    Title = new_title;
}





void Emerobot::InstallAPI()
{
    InstallAPI_pctl();
    InstallAPI_bitcoin();


    duk_idx_t arr_idx = duk_push_array (ctx);

    for ( int i=0; i<Argc; i++ )
    {
	duk_push_string ( ctx, Argv[i]->c_str() );
	duk_put_prop_index ( ctx, arr_idx, i );
    }

    duk_put_prop_string ( ctx, -2, "ARGV" );
}


void Emerobot::Run()
{
    Bot = this;


    boost::filesystem::path  program_path = GetDataDir() / "bots" / "app" / (Program + ".js");

    ctx = duk_create_heap_default();

    duk_push_global_object (ctx);

    InstallAPI();

    if ( duk_peval_file ( ctx, program_path.string().c_str() ) != 0 )
    {
        printf ( "Bot[%d/%s]: (Loading from \"%s\"): %s\n",
		 id, Program.c_str(), program_path.string().c_str(), duk_safe_to_string(ctx, -1) );

	SetTitle ( duk_safe_to_string(ctx, -1) );

        goto finished;
    }

    duk_pop (ctx);  /* ignore result */


 finished:
    ;

#if 0
    for (;;)
    {
	sleep (12);
	printf ( "Bot[%s]: Working...\n", Program.c_str() );
	duk_eval_string ( ctx, "print('Hello world!');" );
    }
#endif
}


