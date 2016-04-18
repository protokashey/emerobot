/* -*- Mode: C; c-basic-offset: 4; -*-
 *
 * EMEROBOT, RPC COMMANDS
 *
 * ### Programmed by kashey@protonmail.com,
 * ### source code published under terms of GPLv3 license.
 *
 */


#ifndef EMEROBOTRPC_H_INCLUDED
#define EMEROBOTRPC_H_INCLUDED


#include "json/json_spirit_reader_template.h"
#include "json/json_spirit_writer_template.h"
#include "json/json_spirit_utils.h"


extern json_spirit::Value spawnbot ( const json_spirit::Array& params, bool fHelp );
extern json_spirit::Value listbots ( const json_spirit::Array& params, bool fHelp );


#endif

