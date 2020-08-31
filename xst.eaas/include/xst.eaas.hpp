#pragma once
#include "typedef.hpp"

#include XST_HEAD_ASSET
#include XST_HEAD_TOKEN
#include <string>

namespace XST_FLAG{

   using std:: string;

   class [[XST_FLAG::contract("xst.eaas")]] eaas : public contract
  {
     public:
        using contract::contract;

         /**
         *Add record.
         */
        [[XST_FLAG::action]]
        void addeaas(
            std::string from,
            std::string to,
            std::string name,
            std::string description,
            std::string location,
            std::string validity,
            std::string devices, //转成string保存json
            std::string operator_,
            std::string plan,
            uint64_t esimFee,
            uint64_t storage,
            uint64_t storageFee
             );

             /**
             *Delete all record.
             */
            [[XST_FLAG::action]]
            void cleareaas();

    private:
       struct [[XST_FLAG::table]] eaasstruct
       {
           uint64_t id;

            std::string from;
            std::string to;
            std::string name;
            std::string description;
            std::string location;
            std::string validity;
            std::string devices;//转成string保存json
            std::string operator_;
            std::string plan;
            uint64_t esimFee;
            uint64_t storage;
            uint64_t storageFee;

            uint64_t primary_key() const { return id; }

            XSTLIB_SERIALIZE(eaasstruct, (id)(from)(to)(name)(description)(location)(validity)(devices)(operator_)(plan)(esimFee)(storage)(storageFee))
       };

       using  eaas_table = XST_FLAG::multi_index<"eaasstruct"_n, eaasstruct>;

        
  };//class eaas
}//namespace XST_FLAG