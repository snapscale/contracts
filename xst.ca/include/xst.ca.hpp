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

   class [[XST_FLAG::contract("xst.ca")]] ca : public contract
   {
   public:
      using contract::contract;

      // /**
      //  * Add member action.
      //  */
      // [[XST_FLAG::action]]
      // void addmem(std::string owner, public_key pk, std::string meminfo);

      // /**
      //     * Change member's status action，default->0, pass->1, reject->2
      //     */
      // [[XST_FLAG::action]] void changestatus(public_key pk, uint8_t status);

      // /**
      //     * Add ca action.
      //     */
      // [[XST_FLAG::action]] void addcert(public_key pk, signature cert);

      // /**
      //     * Del member action.
      //     */
      // [[XST_FLAG::action]] void delmem(public_key pk);

      // /**
      //     * Del all mem.
      //     */
      // [[XST_FLAG::action]] void delallmem();

      /**
          * Table global_id return to previous member id when delete one member.
          */
      // [[XST_FLAG::action]]
      // void prevmemid();

      // static inline checksum256 getKeyHash(const public_key &pk)
      // {
      //    return sha256((const char *)&pk, 33);
      // }

      /**
          * Add crl action.
          */
      [[XST_FLAG::action]] void addcrl(checksum256 pk_hash);

      /**
          * Del crl action.
          */
      [[XST_FLAG::action]] void delcrl(checksum256 pk_hash);

   private:
      // struct [[XST_FLAG::table]] member
      // {
      //    uint64_t id;
      //    std::string owner;
      //    public_key pk;
      //    uint8_t status;
      //    std::string meminfo;

      //    uint64_t primary_key() const { return id; }
      //    checksum256 by_pk() const { return getKeyHash(pk); }

      //    XSTLIB_SERIALIZE(member, (id)(owner)(pk)(status)(meminfo))
      // };

      // struct [[XST_FLAG::table]] certinfo
      // {
      //    uint64_t id;
      //    public_key pk;
      //    signature cert;

      //    uint64_t primary_key() const { return id; }
      //    checksum256 by_pk() const { return getKeyHash(pk); }

      //    XSTLIB_SERIALIZE(certinfo, (id)(pk)(cert))
      // };

      // typedef XST_FLAG::multi_index<"members"_n, member,
      //                               indexed_by<"bypk"_n, const_mem_fun<member, checksum256, &member::by_pk>>>
      //     members;
      // typedef XST_FLAG::multi_index<"certs"_n,
      //                               certinfo,
      //                               indexed_by<"bypk"_n, const_mem_fun<certinfo, checksum256, &certinfo::by_pk>>>
      //     certs;

      struct [[XST_FLAG::table]] crl
      {
         uint64_t id;
         checksum256 pk_hash;
         // signature cert;

         uint64_t primary_key() const { return id; }
         checksum256 by_pk() const { return pk_hash; }

         XSTLIB_SERIALIZE(crl, (id)(pk_hash))
      };

      struct [[XST_FLAG::table]] global_id
      {
         uint64_t id;
         uint64_t next_id;

         uint64_t primary_key() const { return id; }
      };

      typedef XST_FLAG::multi_index<"crls"_n,
                                    crl,
                                    indexed_by<"bypk"_n, const_mem_fun<crl, checksum256, &crl::by_pk>>>
          crls;
      typedef XST_FLAG::multi_index<"globalid"_n, global_id> global_ids;

      /**
          * Get table next  id, 0->members, 1->certs, 2->crls .
          */
      uint64_t nextid(uint8_t type);
   };
} // namespace XST_FLAG
