#include <xst.charge.hpp>
#include <math.h>
namespace XST_FLAG 
{
    
void charge::addst(std::string country, std::string province, std::string city,
   std::string name,
   std::string owner,
   std::string units,
   std::string latitude,
   std::string longitude,
   std::string price)
{

   station_table stations(get_self(),  get_self().value );

   uint64_t id;

   stations.emplace(get_self(), [&](auto &item) {
            item.id = stations.available_primary_key();
            item.country  = country;
            item.province = province;
            item.name = name;
            item.city = city;
            item.owner = owner;
            item.units = units;
            item.latitude = latitude;
            item.longitude = longitude;
            item.price = price;
            id = item.id;
        });
   print("add id=",id, " country=",country ,", province=",province,", city=",city,
         "name=",name,
         "owner=",owner,
         "units=",units,
         "latitude=",latitude,
         "longitude=",longitude,
         "price=",price,
         "\n");
 
}

void charge::updatest(uint64_t id,std::string country, std::string province, std::string city,
   std::string name,
   std::string owner,
   std::string units,
   std::string latitude,
   std::string longitude,
   std::string price)
{

   station_table stations(get_self(),  get_self().value );

   auto iter = stations.find(id);
   if ( iter != stations.end() ) {
      stations.modify( iter, get_self(), [&](auto& item) {
            item.country  = country;
            item.province = province;
            item.city = city;
            item.name = name;
            item.owner = owner;
            item.units = units;
            item.latitude = latitude;
            item.longitude = longitude;
            item.price = price;
      });
      print("modify id=",id, " country=",country ,", province=",province,", city=",city,
         "name=",iter->name,
         "owner=",iter->owner,
         "units=",iter->units,
         "latitude=",iter->latitude,
         "longitude=",iter->longitude,
         "price=",iter->price,
         "\n");
   } else {
      print("index by id=",id, " do not find to modify.", "\n");
   }
 
}

void charge::delst(uint64_t id)
{
   station_table stations(get_self(),  get_self().value );

   auto iter = stations.find(id);
   if ( iter != stations.end() ) {
      print("delete id=",iter->id, " country=",iter->country ,", province=",iter->province,", city=",iter->city,
         "name=",iter->name,
         "owner=",iter->owner,
         "units=",iter->units,
         "latitude=",iter->latitude,
         "longitude=",iter->longitude,
         "price=",iter->price,
         "\n");
      stations.erase( iter );
   } else {
      print("index by id=",id, " do not find to delete.", "\n");
   }
 
}
double mystof(std::string str)
{   
   int digits = 0;
   std::size_t pos = str.find(".");
   if (pos!=str.npos)
   {
      digits = str.length() - pos - 1;
      str.erase(pos, 1); 
   }
   return atoi(str.c_str()) / pow(10, digits);
}

void charge::sendorder(const name& from,uint64_t stid, uint64_t duration)
{

   require_auth( from );

   orders ordertbl(get_self(),  get_self().value );

   uint64_t oid;

   ordertbl.emplace(get_self(), [&](auto &item) {
            item.orderid = ordertbl.available_primary_key();
            item.stationid = stid;
            item.duration  = duration;
            oid = item.orderid;
        });
   print("added  orderid=", oid, ", stationid=", stid, ", duration=", duration, "\n");

   // TODO: send transaction
   station_table stations(get_self(),  get_self().value );
   auto iter = stations.find(stid);
   if ( iter != stations.end() ) {
      print("location id=",iter->id, " country=",iter->country ,", province=",iter->province,", city=",iter->city,
         "name=",iter->name,
         "owner=",iter->owner,
         "units=",iter->units,
         "latitude=",iter->latitude,
         "longitude=",iter->longitude,
         "price=",iter->price,
         "\n");
      double price = mystof(iter->price);
      int64_t to_pay = static_cast<int64_t>( price * duration * uint128_t(factor_precision));
      if( to_pay > 0 ) {
         token::transfer_action tocharge_act{ token_account, { {from, active_permission} } };
         tocharge_act.send(from, station_account, asset(to_pay, symbol(symbol_code("XST"), 4)), "charge fee" );
         print("transfer ", asset(to_pay, symbol(symbol_code("XST"), 4)), " from ", from, " to ",station_account, "\n");
      }
   } else {
      print("index by station id=",stid, " do not find to location.", "\n");
   }

}



void charge::actlog(std::string loginfo )
{

   logitems logitem(get_self(),  get_self().value );

   uint64_t logid;

   logitem.emplace(get_self(), [&](auto &item) {
            item.logid = logitem.available_primary_key();
            item.loginfo = loginfo;
            logid = item.logid;
        });
   print("logid=", logid, ", loginfo=", loginfo, "\n");

}



}