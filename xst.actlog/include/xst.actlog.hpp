#pragma once
#include "typedef.hpp"

#include <string>

namespace XST_SYSTEM {
   class system_contract;
}

namespace XST_FLAG {

   using std::string;

   class [[XST_FLAG::contract("xst.actlog")]] actlog : public contract 
   {
      public:
         using contract::contract;

         /**
          * Add action logs.
          */
         [[XST_FLAG::action]]
         void addlog(std::string actname, std::string loginfo);

      private:
         struct [[XST_FLAG::table]] logitem
         {
            uint64_t id;
            std::string  actname;
            std::string  loginfo;

            uint64_t primary_key() const { return id; }

            XSTLIB_SERIALIZE( logitem, (id)(actname)(loginfo) )
         };
         typedef XST_FLAG::multi_index< "logitem"_n, logitem > logitems;   

   };
} /// namespace XST_FLAG
