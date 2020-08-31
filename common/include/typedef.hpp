#include <eosio/eosio.hpp>

#define XST_HEAD_PRINT <eosio/print.hpp>
#define XST_HEAD_ASSET <eosio/asset.hpp>
#define XST_HEAD_SYSTEM <eosio/system.hpp>
#define XST_HEAD_CRYPTO <eosio/crypto.hpp>
#define XST_HEAD_PERMISSION <eosio/permission.hpp>
#define XST_HEAD_ACTION <eosio/action.hpp>
#define XST_HEAD_SINGLETON <eosio/singleton.hpp>
#define XST_HEAD_TRANSACTION <eosio/transaction.hpp>
#define XST_HEAD_SYMBOL <eosio/symbol.hpp>
#define XST_HEAD_PRIVILEGED <eosio/privileged.hpp>
#define XST_HEAD_DISPATCHER <eosio/dispatcher.hpp>
#define XST_HEAD_FIXED_BYTES <eosio/fixed_bytes.hpp>
#define XST_HEAD_PRODUCER_SCHEDULE <eosio/producer_schedule.hpp>

#define XST_HEAD_TOKEN <eosio.token/eosio.token.hpp>
#define XST_HEAD_MSIG <eosio.msig/eosio.msig.hpp>
#define XST_HEAD_WRAP <eosio.wrap/eosio.wrap.hpp>
#define XST_HEAD_BOOT <eosio.boot/eosio.boot.hpp>
#define XST_HEAD_SC_SYSTEM <eosio.system/eosio.system.hpp>
#define XST_HEAD_SC_REX <eosio.system/rex.results.hpp>
#define XST_HEAD_SC_BIOS <eosio.bios/eosio.bios.hpp>


//#include <eosiolib/print.hpp>
// #define XST_namespace eosio
// #define XST_action eosio::action


#define XST_NAME_SYSTEM "eosio.system"
#define XST_NAME_MSIG "eosio.msig"
#define XST_NAME_CODE_N "eosio.code"_n
#define XST_NAME_TOKEN "eosio.token"
#define XST_NAME_TOKEN_N "eosio.token"_n
#define XST_NAME_TOKEN_TRANSFER "eosio.token::transfer"

#define XST_NAME_TRAIL "eosio.trail"
#define XST_NAME_TRAIL_N "eosio.trail"_n

#define XST_FLAG eosio
#define XST_FLAG_N "eosio"_n
#define XST_SYSTEM eosiosystem
#define XST_DISPATCH EOSIO_DISPATCH
#define XSTLIB_SERIALIZE EOSLIB_SERIALIZE