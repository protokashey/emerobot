/* -*- Mode: C; c-basic-offset: 4; -*-
 *
 * EMEROBOT, JAVASCRIPT API IMPLEMENTATION, SAME AS BITCOINRPC FUNCTIONS
 *
 * ### Programmed by kashey@protonmail.com,
 * ### source code published under terms of GPLv3 license.
 *
 */


#include <stdlib.h>


#include "init.h"
#include "net.h"
#include "base58.h"
#include "bitcoinrpc.h"


#include "emerobot.h"
#include "emerobotec.h"



static duk_ret_t API__stop ( duk_context * ctx )
{
    StartShutdown();
    return 0;
}

static duk_ret_t API__getblockcount ( duk_context * ctx )
{
    duk_push_int ( ctx, nBestHeight );
    return 1;
}

static duk_ret_t API__getconnectioncount ( duk_context * ctx )
{
    duk_push_int ( ctx, vNodes.size() );
    return 1;
}

static duk_ret_t API__getgenerate ( duk_context * ctx )
{
    duk_push_boolean ( ctx, GetBoolArg ("-gen") );
    return 1;
}


double GetDifficulty(const CBlockIndex* blockindex = NULL);

static duk_ret_t API__getinfo ( duk_context * ctx )
{
    duk_idx_t idx;

    idx = duk_push_object(ctx);

    duk_push_string ( ctx, FormatFullVersion().c_str() );
    duk_put_prop_string ( ctx, idx, "version" );

    duk_push_int ( ctx, PROTOCOL_VERSION );
    duk_put_prop_string ( ctx, idx, "protocolversion" );

    duk_push_int ( ctx, pwalletMain->GetVersion() );
    duk_put_prop_string ( ctx, idx, "walletversion" );

    duk_push_number ( ctx, (double) pwalletMain->GetBalance() / COIN );
    duk_put_prop_string ( ctx, idx, "balance" );

    duk_push_number ( ctx, (double) pwalletMain->GetNewMint() / COIN );
    duk_put_prop_string ( ctx, idx, "newmint" );

    duk_push_number ( ctx, (double) pwalletMain->GetStake() / COIN );
    duk_put_prop_string ( ctx, idx, "stake" );

    duk_push_int ( ctx, nBestHeight );
    duk_put_prop_string ( ctx, idx, "blocks" );

    duk_push_number ( ctx, (double) pindexBest->nMoneySupply / COIN );
    duk_put_prop_string ( ctx, idx, "moneysupply" );

    duk_push_int ( ctx, vNodes.size() );
    duk_put_prop_string ( ctx, idx, "connections" );

    duk_push_string ( ctx, (fUseProxy ? addrProxy.ToStringIPPort().c_str() : "") );
    duk_put_prop_string ( ctx, idx, "proxy" );

    duk_push_string ( ctx, addrSeenByPeer.ToStringIP().c_str() );
    duk_put_prop_string ( ctx, idx, "ip" );

    duk_push_number ( ctx, GetDifficulty(NULL) );
    duk_put_prop_string ( ctx, idx, "difficulty" );

    duk_push_boolean ( ctx, fTestNet );
    duk_put_prop_string ( ctx, idx, "testnet" );

    duk_push_number ( ctx, pwalletMain->GetOldestKeyPoolTime() );
    duk_put_prop_string ( ctx, idx, "keypoololdest" );

    duk_push_int ( ctx, pwalletMain->GetKeyPoolSize() );
    duk_put_prop_string ( ctx, idx, "keypoolsize" );

    duk_push_number ( ctx, nTransactionFee );
    duk_put_prop_string ( ctx, idx, "paytxfee" );

    if (pwalletMain->IsCrypted())
    {
        duk_push_int ( ctx, nWalletUnlockTime / 1000 );
	duk_put_prop_string ( ctx, idx, "unlocked_until" );
    }

    duk_push_string ( ctx, GetWarnings("statusbar").c_str() );
    duk_put_prop_string ( ctx, idx, "errors" );

    return 1;
}


static duk_ret_t API__getmininginfo ( duk_context * ctx )
{
    duk_idx_t idx;

    idx = duk_push_object(ctx);

    duk_push_int ( ctx, nBestHeight );
    duk_put_prop_string ( ctx, idx, "blocks" );

    duk_push_int ( ctx, nLastBlockSize );
    duk_put_prop_string ( ctx, idx, "currentblocksize" );

    duk_push_int ( ctx, nLastBlockTx );
    duk_put_prop_string ( ctx, idx, "currentblocktx" );

    duk_push_number ( ctx, GetDifficulty(NULL) );
    duk_put_prop_string ( ctx, idx, "difficulty" );

    duk_push_string ( ctx, GetWarnings("statusbar").c_str() );
    duk_put_prop_string ( ctx, idx, "errors" );

    duk_push_boolean ( ctx, GetBoolArg ("-gen") );
    duk_put_prop_string ( ctx, idx, "generate" );

    duk_push_int ( ctx, GetArg ( "-genproclimit", -1 ) );
    duk_put_prop_string ( ctx, idx, "genproclimit" );

    duk_push_int ( ctx, 0 ); /* (TODO) */
    duk_put_prop_string ( ctx, idx, "hashespersec" );

    duk_push_number ( ctx, mempool.size() );
    duk_put_prop_string ( ctx, idx, "pooledtx" );

    duk_push_boolean ( ctx, fTestNet );
    duk_put_prop_string ( ctx, idx, "testnet" );

    return 1;
}


static duk_ret_t API__getnewaddress ( duk_context * ctx )
{
    const char * account;

    account = duk_require_string ( ctx, 0 );

    if (!pwalletMain->IsLocked())
        pwalletMain->TopUpKeyPool();

    // Generate a new key that is added to wallet
    CPubKey newKey;

    if (!pwalletMain->GetKeyFromPool(newKey, false))
	duk_error ( ctx, EMEROBOT_ERR_KEYPOOL_RAN_OUT,
		    "Keypool ran out, please call keypoolrefill first" );

    CKeyID keyID = newKey.GetID();

    pwalletMain->SetAddressBookName ( keyID, account );

    duk_push_string ( ctx, CBitcoinAddress(keyID).ToString().c_str() );
    return 1;
}

/*
static duk_ret_t API__getaccountaddress ( duk_context * ctx )
{
    const char * account;

    account = duk_require_string ( ctx, 0 );

    duk_push_string ( ctx, CBitcoinAddress(keyID).ToString().c_str() );
    return 1;
}
*/

static duk_ret_t API__gettxfee ( duk_context * ctx )
{
    duk_push_number ( ctx, nTransactionFee );
    return 1;
}

static duk_ret_t API__settxfee ( duk_context * ctx )
{
    duk_double_t old, fee;

    fee = duk_require_number ( ctx, 0 );
    old = nTransactionFee;

    nTransactionFee = (fee / CENT) * CENT;

    duk_push_number ( ctx, old );
    return 1;
}


void Emerobot::InstallAPI_bitcoin()
{
    duk_push_c_function ( ctx, API__stop, 0 );
    duk_put_prop_string ( ctx, -2, "stop" );

    duk_push_c_function ( ctx, API__getblockcount, 0 );
    duk_put_prop_string ( ctx, -2, "getblockcount" );

    duk_push_c_function ( ctx, API__getblockcount, 0 );
    duk_put_prop_string ( ctx, -2, "getblocknumber" );

    duk_push_c_function ( ctx, API__getconnectioncount, 0 );
    duk_put_prop_string ( ctx, -2, "getconnectioncount" );

    duk_push_c_function ( ctx, API__getgenerate, 0 );
    duk_put_prop_string ( ctx, -2, "getgenerate" );

    duk_push_c_function ( ctx, API__getinfo, 0 );
    duk_put_prop_string ( ctx, -2, "getinfo" );

    duk_push_c_function ( ctx, API__getmininginfo, 0 );
    duk_put_prop_string ( ctx, -2, "getmininginfo" );

    duk_push_c_function ( ctx, API__getnewaddress, 1 );
    duk_put_prop_string ( ctx, -2, "getnewaddress" );

    duk_push_c_function ( ctx, API__gettxfee, 0 );
    duk_put_prop_string ( ctx, -2, "gettxfee" );

    duk_push_c_function ( ctx, API__settxfee, 1 );
    duk_put_prop_string ( ctx, -2, "settxfee" );
}


