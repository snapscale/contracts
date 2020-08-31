#include <xst.actlog.hpp>

namespace XST_FLAG 
{
    
void actlog::addlog( std::string actname, std::string loginfo )
{

   logitems logitem(get_self(),  get_self().value );

   uint64_t logid;

   logitem.emplace(get_self(), [&](auto &item) {
            item.id = logitem.available_primary_key();
            item.actname = actname;
            item.loginfo = loginfo;
            logid = item.id;
        });
   print("logid=",logid, " actname=",actname ,", loginfo=",loginfo, "\n");
 
}

}
// XST_DISPATCH(XST_FLAG::actlog, (addmem)(changestatus)(addcert)(addcrl)(delmem)(delcrl)(delallmem))