#pragma once
#include "typedef.hpp"
#include XST_HEAD_ASSET

#include <eosio/name.hpp>

using XST_FLAG::action_wrapper;
using XST_FLAG::asset;
using XST_FLAG::name;

/**
 * The actions `buyresult`, `sellresult`, `rentresult`, and `orderresult` of `rex.results` are all no-ops. 
 * They are added as inline convenience actions to `rentnet`, `rentcpu`, `buyrex`, `unstaketorex`, and `sellrex`. 
 * An inline convenience action does not have any effect, however, 
 * its data includes the result of the parent action and appears in its trace.
 */
class [[XST_FLAG::contract("rex.results")]] rex_results : XST_FLAG::contract {
   public:

      using XST_FLAG::contract::contract;

      /**
       * Buyresult action.
       *
       * @param rex_received - amount of tokens used in buy order
       */
      [[XST_FLAG::action]]
      void buyresult( const asset& rex_received );

      /**
       * Sellresult action.
       *
       * @param proceeds - amount of tokens used in sell order
       */
      [[XST_FLAG::action]]
      void sellresult( const asset& proceeds );

      /**
       * Orderresult action.
       *
       * @param owner - the owner of the order
       * @param proceeds - amount of tokens used in order
       */
      [[XST_FLAG::action]]
      void orderresult( const name& owner, const asset& proceeds );

      /**
       * Rentresult action.
       *
       * @param rented_tokens - amount of rented tokens
       */
      [[XST_FLAG::action]]
      void rentresult( const asset& rented_tokens );

      using buyresult_action   = action_wrapper<"buyresult"_n,   &rex_results::buyresult>;
      using sellresult_action  = action_wrapper<"sellresult"_n,  &rex_results::sellresult>;
      using orderresult_action = action_wrapper<"orderresult"_n, &rex_results::orderresult>;
      using rentresult_action  = action_wrapper<"rentresult"_n,  &rex_results::rentresult>;
};
