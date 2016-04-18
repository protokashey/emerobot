/* -*- Mode: C; c-basic-offset: 4; -*-
 *
 * EMEROBOT, BOT PROCESS INSTANCE
 *
 * ### Programmed by kashey@protonmail.com,
 * ### source code published under terms of GPLv3 license.
 *
 */

#ifndef EMEROBOT_H_INCLUDED
#define EMEROBOT_H_INCLUDED


#include <string>
using namespace std;


#include "util.h"

#include "duktape.h"

class Emerobots;

class Emerobot
{
 public:
    Emerobot ( string ProgramName, int argc, string ** argv );
    ~Emerobot();

    boost::mutex   Mutex;
    void           Lock()   { Mutex.lock();   }
    void           Unlock() { Mutex.unlock(); }
    void           Lock_Full();
    void           Unlock_Full();

    Emerobots   * root;
    Emerobot    * next;

    void AssignRoot ( Emerobots * new_root );
    void AssignID ( int new_id );

    bool IsFinished();
    int GetID();
    string GetProgram();
    string GetTitle();
    void SetTitle ( string new_title );
    void SetTitle ( const char * new_title );

 private:
    int           running_p;
    int           id;
    string        Program;
    int           Argc;
    string     ** Argv;
    string        Title;
    pthread_t     Process;
    duk_context * ctx;

    static void Boot ( void * p );

    void InstallAPI();
    void InstallAPI_pctl();
    void InstallAPI_bitcoin();

    void Run();
};


extern __thread Emerobot * Bot;


#endif

