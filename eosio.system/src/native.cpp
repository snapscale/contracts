#include <eosio.system/native.hpp>

#include <eosio/check.hpp>

namespace XST_SYSTEM {

   void native::onerror( ignore<uint128_t>, ignore<std::vector<char>> ) {
      XST_FLAG::check( false, "the onerror action cannot be called directly" );
   }

}
