#pragma once

#include <eosio/asset.hpp>
#include <eosio/eosio.hpp>
#include <eosio/crypto.hpp>
#include <eosio/transaction.hpp>
#include <string>

namespace eosiosystem {
   class system_contract;
}

namespace eosio {

   using std::string;

   class [[eosio::contract("xst.ca")]] ca : public contract 
   {
      public:
         using contract::contract;

         /**
          * Add member action.
          */
         [[eosio::action]]
         void addmem(std::string owner, public_key pk, std::string meminfo);

          /**
          * Change member's status action，default->0, pass->1, reject->2
          */
         [[eosio::action]]
         void changestatus( public_key pk, uint8_t status);

         /**
          * Add ca action.
          */
         [[eosio::action]]
         void addcert(public_key pk, signature cert);

         /**
          * Add crl action.
          */
         [[eosio::action]]
         void addcrl(public_key pk);

         /**
          * Del member action.
          */
         [[eosio::action]]
         void delmem(public_key pk);

         /**
          * Del crl action.
          */
         [[eosio::action]]
         void delcrl(public_key pk);

         /**
          * Del all mem.
          */
         [[eosio::action]]
         void delallmem();

          /**
          * Table global_id return to previous member id when delete one member.
          */
         // [[eosio::action]]
         // void prevmemid();


         static inline checksum256 getKeyHash(const public_key &pk)
         {
            return sha256((const char *)&pk, 33);
         }

      private:
         struct [[eosio::table]] member 
         {
            uint64_t id;
            std::string owner;
            public_key pk;
            uint8_t status;
            std::string  meminfo;

            uint64_t primary_key() const { return id; }
            checksum256 by_pk() const { return getKeyHash(pk); }

            EOSLIB_SERIALIZE( member, (id)(owner)(pk)(status)(meminfo) )

         };

         struct [[eosio::table]] certinfo {
            uint64_t id;
            public_key pk;
            signature cert;

            uint64_t primary_key() const { return id; }
            checksum256 by_pk() const { return getKeyHash(pk); }

            EOSLIB_SERIALIZE( certinfo, (id)(pk)(cert) )

         };

         struct [[eosio::table]] crl {
            uint64_t id;
            public_key pk;
            // signature cert;

            uint64_t primary_key() const { return id; }
            checksum256 by_pk() const { return getKeyHash(pk); }

            EOSLIB_SERIALIZE( crl, (id)(pk) )

         };

      struct [[eosio::table]] global_id
      {
         uint64_t    id;
         uint64_t    next_id;

         uint64_t primary_key() const { return id; }
      };

    
         typedef eosio::multi_index<"members"_n, member,
                                    indexed_by<"bypk"_n, const_mem_fun<member, checksum256, &member::by_pk>> 
                                    > members;
         typedef eosio::multi_index<"certs"_n, 
                                    certinfo,
                                    indexed_by<"bypk"_n, const_mem_fun<certinfo, checksum256, &certinfo::by_pk>> 
                                    > certs;
         typedef eosio::multi_index<"crls"_n, 
                                    crl,
                                    indexed_by<"bypk"_n, const_mem_fun<crl, checksum256, &crl::by_pk>> 
                                    > crls;
           typedef eosio::multi_index<"globalid"_n, global_id> global_ids;

         /**
          * Get table next  id, 0->members, 1->certs, 2->crls .
          */
           uint64_t nextid(uint8_t type);

   };
} /// namespace eosio
