#include "typedef.hpp"
#include XST_HEAD_BOOT
#include XST_HEAD_PRIVILEGED

namespace eosioboot {

void boot::onerror( ignore<uint128_t>, ignore<std::vector<char>> ) {
   check( false, "the onerror action cannot be called directly" );
}

void boot::activate( const XST_FLAG::checksum256& feature_digest ) {
   require_auth( get_self() );
   XST_FLAG::preactivate_feature( feature_digest );
}

void boot::reqactivated( const XST_FLAG::checksum256& feature_digest ) {
   check( XST_FLAG::is_feature_activated( feature_digest ), "protocol feature is not activated" );
}

}
