/* -*- Mode: C; c-basic-offset: 4; -*-
 *
 * EMEROBOT, RPC COMMANDS
 *
 * ### Programmed by kashey@protonmail.com,
 * ### source code published under terms of GPLv3 license.
 *
 */

#include "emerobot.h"
#include "emerobots.h"
#include "emerobotrpc.h"


using namespace std;
using namespace json_spirit;



Value spawnbot ( const Array& params, bool fHelp )
{
    if (fHelp || params.size() < 1)
        throw runtime_error(
            "spawnbot <program> [<arg1> <arg2> ...]\n"
            "Start new bot process.");

    string    Program     = params[0].get_str();
    int       ARGC        = params.size() - 1;
    string ** ARGV        = (string**) malloc ( sizeof (string*) * ARGC );
    //    string ** ARGV        = new ( string [ARGC] );
    Array     Argv;

    for ( int i=0; i<ARGC; i++ )
    {
	ARGV[i] = new string (params[i+1].get_str());
	Argv.push_back (*(ARGV[i]));
    }

    Emerobot * bot = new Emerobot ( Program, ARGC, ARGV );
    Bots.Push (bot);

    Object ret;

    ret.push_back ( Pair ( "id",      bot->GetID()      )  );
    ret.push_back ( Pair ( "program", bot->GetProgram() )  );
    ret.push_back ( Pair ( "argv",    Argv              )  );
    //    ret.push_back ( Pair ( "title",   bot->GetTitle()   )  );

    return ret;
}


Value listbots ( const Array& params, bool fHelp )
{
    if (fHelp || params.size() != 0)
        throw runtime_error(
            "listbots\n"
            "List bot processes.");

    Array ret;

    Emerobot * bot;

    Bots.Lock();

    for ( bot=Bots.bots; bot; bot=bot->next )
    {
	Object entry;

	bot->Lock();
	entry.push_back ( Pair ( "id",      bot->GetID()      ) );
	entry.push_back ( Pair ( "finished",bot->IsFinished() ) );
	entry.push_back ( Pair ( "program", bot->GetProgram() ) );
	entry.push_back ( Pair ( "title",   bot->GetTitle()   ) );
	bot->Unlock();

	ret.push_back (entry);
    }

    Bots.Unlock();

    return ret;
}

