#pragma once
#include "typedef.hpp"
#include XST_HEAD_ASSET

#include XST_HEAD_CRYPTO
#include XST_HEAD_TRANSACTION
#include <string>

namespace XST_SYSTEM
{
class system_contract;
}

namespace XST_FLAG
{

using std::string;

const XST_FLAG::symbol TOKEN_SYMBOL = symbol(symbol_code("UTXO"), 4);

class[[XST_FLAG::contract("xst.utxo")]] token : public contract
{
 public:
   using contract::contract;

   [[XST_FLAG::action]] void create(name issuer,
                                 asset maximum_supply);

   [[XST_FLAG::action]] void update(name issuer,
                   asset maximum_supply);

   [[XST_FLAG::action]] void issue(name to, asset quantity, string memo);

   [[XST_FLAG::action]] void retire(asset quantity, string memo);

   [[XST_FLAG::action]] void transfer(name from,
                                   name to,
                                   asset quantity,
                                   string memo);

   [[XST_FLAG::action]] void claim(name owner, symbol_code sym);
   [[XST_FLAG::action]] void recover(name owner, symbol_code sym);
   [[XST_FLAG::action]] void open(name owner, const symbol &symbol, name ram_payer);
   [[XST_FLAG::action]] void close(name owner, const symbol &symbol);

   struct input {
      uint64_t id;
      signature sig;

      XSTLIB_SERIALIZE( input, (id)(sig) )
   };

   struct output {
      public_key pk;
      name account;
      asset quantity;

      XSTLIB_SERIALIZE( output, (pk)(account)(quantity) )
   };

   [[XST_FLAG::action]] void transferutxo(const name &payer /*中间人*/, const std::vector<input> &inputs, const std::vector<output> &outputs, const string &memo);
   [[XST_FLAG::action]] void loadutxo(const name &from, const public_key &pk, const asset &quantity);

   static asset get_supply(name token_contract_account, symbol_code sym_code)
   {
      stats statstable(token_contract_account, sym_code.raw());
      const auto &st = statstable.get(sym_code.raw());
      return st.supply;
   }

   static asset get_balance(name token_contract_account, name owner, symbol_code sym_code)
   {
      accounts accountstable(token_contract_account, owner.value);
      const auto &ac = accountstable.get(sym_code.raw());
      return ac.balance;
   }

 private:
   struct [[XST_FLAG::table]] account
   {
      asset balance;
      bool claimed = false;
      uint64_t primary_key() const { return balance.symbol.code().raw(); }

      XSTLIB_SERIALIZE( account, (balance)(claimed) )
   };

   struct [[XST_FLAG::table]] currency_stats
   {
      asset supply;
      asset max_supply;
      name issuer;

      uint64_t primary_key() const { return supply.symbol.code().raw(); }

      XSTLIB_SERIALIZE( currency_stats, (supply)(max_supply)(issuer) )
   };

   struct [[XST_FLAG::table]] utxo
   {
      uint64_t    id;
      public_key  pk;
      asset    amount;

      uint64_t primary_key() const { return id; }
      checksum256 by_pk() const { return getKeyHash(pk); }

      XSTLIB_SERIALIZE( utxo, (id)(pk)(amount) )
   };

   struct [[XST_FLAG::table]] utxo_global
   {
      uint64_t    id;
      uint64_t    next_pk;

      uint64_t primary_key() const { return id; }

      XSTLIB_SERIALIZE( utxo_global, (id)(next_pk) )
   };

   typedef XST_FLAG::multi_index<"accounts"_n, account> accounts;
   typedef XST_FLAG::multi_index<"stat"_n, currency_stats> stats;
   typedef XST_FLAG::multi_index<"utxos"_n, 
                              utxo,
                              indexed_by<"ipk"_n, const_mem_fun<utxo, checksum256, &utxo::by_pk>>
                              > utxos;
   typedef XST_FLAG::multi_index<"utxoglobals"_n, utxo_global> utxo_globals;

   static inline checksum256 getKeyHash(const public_key &pk)
   {
      return sha256((const char *)&pk, 33);
   }

   void sub_balance(name owner, asset value);
   void add_balance(name owner, asset value, name ram_payer, bool claimed);

   void do_claim(name owner, symbol_code sym, name payer);

   uint64_t getNextUTXOId();
};

} // namespace XST_FLAG