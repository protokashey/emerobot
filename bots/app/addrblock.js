//
// EMEROBOT, APP, ADDRESSBLOCK CREATION AND OPTIONAL TOP UP
//
// ### Programmed by kashey@protonmail.com,
// ### source code published under terms of GPLv3 license.
//


function make_addrblock ( account_name, addr_count )
{
    var addrlist = new Array();

    for ( var i=0; i<addr_count; i++ )
    {
	addrlist [i] = getnewaddress (account_name);
    }

    return addrlist;
}

function topup_addrlist ( list, from, amount )
{
    // Not (YET!) implemented. Coming soon. Stay tuned.
    settitle ( "Top up " + list.length + " address(es), by " + amount + " EMC each, from " + from + " (TODO)." );
}


if ( ARGV.length == 2 ) // <account_name> <addr_count>
{
    make_addrblock ( ARGV[0], ARGV[1] );
}
else if ( ARGV.length == 4 ) // <account_name> <addr_count> <amount_of_each_addr> <fill_from>
{
    var addrlist = make_addrblock ( ARGV[0], ARGV[1] );
    topup_addrlist ( addrlist, ARGV[3], ARGV[2] );
}
else
{
    settitle ("Arguments error, usage: addrblock <account> <count> [<amount> <fill-from>]");
}


