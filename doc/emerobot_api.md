

API available to javascript code running as emerobot process.
=============================================================

Legend
------

- [x] Implemented and available.
- [ ] Not (YET!) implemented.


Process control functions
-------------------------

- [x] ARGV[] — array of arguments passed.
- [ ] eonid() — get current eon id.
- [ ] eventloop() — switch paradigm from procedure to event-driven.
- [ ] pid() — get current process id.
- [x] settitle(title) — change process title.
- [x] sleep(sec) — pause program execution.
- [ ] suicide() — terminate process execution.


Function homologous to bitcoin JSON-RPC commands
------------------------------------------------

- [x] stop() — stop emercoin/emerobot server.
- [x] getblockcount() — returns the number of blocks in the longest block chain.
- [x] getblocknumber() — same as getblockcount().
- [x] getconnectioncount() — returns the number of connections to other nodes.
- [ ] getdifficulty
- [x] getgenerate() — returns CPU-mining activity flag.
- [ ] setgenerate
- [ ] gethashespersec
- [x] getinfo() — returns an object containing various state info.
- [x] getmininginfo() — returns an object containing mining-related information.
- [x] getnewaddress(account) — returns a new emercoin address for receiving payments.
- [ ] getaccountaddress
- [ ] setaccount
- [ ] getaccount
- [ ] getaddressesbyaccount
- [ ] sendtoaddress
- [ ] getreceivedbyaddress
- [ ] getreceivedbyaccount
- [ ] listreceivedbyaddress
- [ ] listreceivedbyaccount
- [ ] backupwallet
- [ ] keypoolrefill
- [ ] walletpassphrase
- [ ] walletpassphrasechange
- [ ] walletlock
- [ ] encryptwallet
- [ ] validateaddress
- [ ] getbalance
- [ ] move
- [ ] sendfrom
- [ ] sendmany
- [ ] addmultisigaddress
- [ ] getrawmempool
- [ ] getblock
- [ ] getblockhash
- [ ] gettransaction
- [ ] listtransactions
- [ ] signmessage
- [ ] verifymessage
- [ ] getwork
- [ ] listaccounts
- [x] gettxfee
- [x] settxfee
- [ ] getblocktemplate
- [ ] submitblock
- [ ] listsinceblock
- [ ] dumpprivkey
- [ ] importprivkey
- [ ] getcheckpoint
- [ ] reservebalance
- [ ] checkwallet
- [ ] repairwallet
- [ ] makekeypair
- [ ] sendalert
- [ ] getrawtransaction
- [ ] listunspent
- [ ] createrawtransaction
- [ ] signrawtransaction
- [ ] sendrawtransaction
- [ ] decoderawtransaction
- [ ] name_new
- [ ] name_update
- [ ] name_delete
- [ ] sendtoname
- [ ] name_list
- [ ] name_scan
- [ ] name_filter
- [ ] name_show
- [ ] name_debug
- [ ] gettxlistfor
- [ ] deletetransaction
- [ ] spawnbot
- [ ] listbots


Not yet designed function groups
--------------------------------

- [ ] Event handling functions.
- [ ] User interaction functions
- [ ] Date and time functions.
- [ ] HTTP client functions.
- [ ] File reading and writing functions.
- [ ] Database storage functions.

