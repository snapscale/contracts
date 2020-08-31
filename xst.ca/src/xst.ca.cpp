#include <xst.ca.hpp>

namespace XST_FLAG
{

   // void ca::addmem( std::string owner, public_key pk, std::string meminfo)
   // {
   //    //  check( is_account( owner ), "account does not exist");
   //     members statstable(  get_self(), get_self().value ); // code, scope

   //     // check existing
   //     auto hpk = getKeyHash(pk);
   //     auto member_table = statstable.get_index<"bypk"_n>();
   //     auto member = member_table.find(hpk);
   //     check(member == member_table.end(), "application has been submitted for this public key ");

   //     statstable.emplace( get_self(), [&]( auto& m ) {
   //        m.id = nextid(0);
   //        m.owner = owner;
   //        m.pk    = pk;
   //        m.status = 0;
   //        m.meminfo = meminfo;
   //     });
   // }

   // void ca::changestatus(public_key pk, uint8_t status)
   // {

   //    require_auth(get_self());
   //    check(status <= 2 && status >= 0, "Parameter status must be one of 0,1,2");
   //    auto hpk = getKeyHash(pk);
   //    members statstable(get_self(), get_self().value); // code, scope

   //    auto member_table = statstable.get_index<"bypk"_n>();
   //    auto member = member_table.find(hpk);
   //    check(member != member_table.end(), "Member does not exist in table");
   //    check(member->status != status, "Member is already in this status");
   //    member_table.modify(member, get_self(), [&](auto &m) {
   //       m.status = status;
   //    });
   // }

   // void ca::addcert(public_key pk, signature cert)
   // {
   //    require_auth(get_self());
   //    certs statstable(get_self(), get_self().value); // code, scope

   //    auto hpk = getKeyHash(pk);
   //    auto cert_table = statstable.get_index<"bypk"_n>();
   //    auto tmp = cert_table.find(hpk);
   //    check(tmp == cert_table.end(), "it is exist !");

   //    statstable.emplace(get_self(), [&](auto &c) {
   //       c.id = nextid(1);
   //       c.pk = pk;
   //       c.cert = cert;
   //    });
   //    changestatus(pk, 1);
   // }

   // void ca::delmem(public_key pk)
   // {
   //    require_auth(get_self());
   //    auto hpk = getKeyHash(pk);
   //    members statstable(get_self(), get_self().value); // code, scope

   //    auto member_table = statstable.get_index<"bypk"_n>();
   //    auto member = member_table.find(hpk);
   //    check(member != member_table.end(), "member does not exist");
   //    member_table.erase(member);
   // }

   // void ca::delallmem()
   // {
   //    require_auth(get_self());
   //    members statstable(get_self(), get_self().value); // code, scope
   //    auto mem = statstable.get_index<"bypk"_n>();
   //    for (auto it = mem.cbegin(); it != mem.cend(); ++it)
   //    {
   //       mem.erase(it);
   //    }
   // }

   void ca::addcrl(checksum256 pk_hash)
   {
      require_auth(get_self());

      // if eosio's X509 cert be added crl,  eosio can get another cert
      //  check(is_genesis_key(pk_hash)==false, "Not allowed add the genesis key to CRL");

      crls statstable(get_self(), get_self().value); // code, scope

      auto crl_table = statstable.get_index<"bypk"_n>();
      auto crl = crl_table.find(pk_hash);
      check(crl == crl_table.end(), "it is exist !");

      statstable.emplace(get_self(), [&](auto &c) {
         c.id = nextid(2);
         c.pk_hash = pk_hash;
      });
   }

   void ca::delcrl(checksum256 pk_hash)
   {
      require_auth(get_self());

      crls statstable(get_self(), get_self().value); // code, scope
      auto crl_table = statstable.get_index<"bypk"_n>();
      auto crl = crl_table.find(pk_hash);
      check(crl != crl_table.end(), "it is not exist !");
      crl_table.erase(crl);
   }

   
   uint64_t ca::nextid(uint8_t type)
   {
      global_ids globals(get_self(), get_self().value);

      uint64_t ret = 0;

      auto const &it = globals.find(type);
      if (it == globals.end())
      {
         globals.emplace(_self, [&](auto &g) {
            g.id = type;
            g.next_id = 1;
         });
      }
      else
      {
         globals.modify(it, same_payer, [&](auto &g) {
            ret = g.next_id;
            // g.id = type;
            g.next_id += 1;
         });
      }
      return ret;
   }

} // namespace XST_FLAG