#pragma once
#include "typedef.hpp"

#include <eosio/ignore.hpp>
#include XST_HEAD_TRANSACTION

namespace XST_FLAG {
   /**
    * @defgroup eosiowrap XST_FLAG.wrap
    * @ingroup eosiocontracts
    * XST_FLAG.wrap contract simplifies Block Producer superuser actions by making them more readable and easier to audit.

    * It does not grant block producers any additional powers that do not already exist within the
    * system. Currently, 15/21 block producers can already change an account's keys or modify an
    * account's contract at the request of ECAF or an account's owner. However, the current method
    * is opaque and leaves undesirable side effects on specific system accounts.
    * XST_FLAG.wrap allows for a cleaner method of implementing these important governance actions.
    * @{
    */
   class [[XST_FLAG::contract("eosio.wrap")]] wrap : public contract {
      public:
         using contract::contract;

         /**
          * Execute action.
          *
          * Execute a transaction while bypassing regular authorization checks.
          *
          * @param executer - account executing the transaction,
          * @param trx - the transaction to be executed.
          *
          * @pre Requires authorization of XST_FLAG.wrap which needs to be a privileged account.
          *
          * @post Deferred transaction RAM usage is billed to 'executer'
          */
         [[XST_FLAG::action]]
         void exec( ignore<name> executer, ignore<transaction> trx );

         using exec_action = XST_FLAG::action_wrapper<"exec"_n, &wrap::exec>;
   };
   /** @}*/ // end of @defgroup eosiowrap XST_FLAG.wrap
} /// namespace XST_FLAG
