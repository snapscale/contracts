#pragma once
#include "typedef.hpp"

#include XST_HEAD_ASSET
#include XST_HEAD_TOKEN
#include <string>

namespace XST_FLAG {

   using std::string;




   class [[XST_FLAG::contract("xst.charge")]] charge : public contract
   {
      public:
         using contract::contract;

         static constexpr XST_FLAG::name charge_account{"xst.charge"_n};
         static constexpr XST_FLAG::name station_account{"sowner"_n};
         static constexpr XST_FLAG::name token_account{XST_NAME_TOKEN_N};
         static constexpr XST_FLAG::name active_permission{"active"_n};

         static constexpr int64_t  factor_precision  = 10000;

         /**
          * Add station.
          */
         [[XST_FLAG::action]]
         void addst(std::string country, std::string province, std::string city,
            std::string name,
            std::string owner,
            std::string units,
            std::string latitude,
            std::string longitude,
            std::string price
            );

         /**
          * update station.
          */
         [[XST_FLAG::action]]
         void updatest(uint64_t id,std::string country, std::string province, std::string city,
            std::string name,
            std::string owner,
            std::string units,
            std::string latitude,
            std::string longitude,
            std::string price
            );

         /**
          * delete station.
          */
         [[XST_FLAG::action]]
         void delst(uint64_t id);


         /**
          * do an order
          */
         [[XST_FLAG::action]]
         void sendorder( const name& from,uint64_t stid, uint64_t duration);

         /**
          * Add action logs.
          */
         [[XST_FLAG::action]]
         void actlog(std::string loginfo);


      private:
         struct [[XST_FLAG::table]] station
         {
            uint64_t id;

            std::string  country;
            std::string  province;
            std::string  city;

            std::string name;
            std::string owner;
            std::string units;
            std::string latitude;
            std::string longitude;
            std::string price;

            uint64_t primary_key() const { return id; }

            XSTLIB_SERIALIZE( station, (id)(country)(province)(city)(name)(owner)(units)(latitude)(longitude)(price) )
         };

         typedef XST_FLAG::multi_index< "station"_n, station > station_table;

         struct [[XST_FLAG::table]] order
         {
            uint64_t orderid;
            uint64_t stationid;
            uint64_t duration;

            uint64_t primary_key() const { return orderid; }
            XSTLIB_SERIALIZE( order, (orderid)(stationid)(duration) )
         };

         typedef XST_FLAG::multi_index< "order"_n, order > orders;

         struct [[XST_FLAG::table]] logitem
         {
            uint64_t     logid;
            std::string  loginfo;

            uint64_t primary_key() const { return logid; }
            XSTLIB_SERIALIZE( logitem, (logid)(loginfo) )
         };
         typedef XST_FLAG::multi_index< "logitem"_n, logitem > logitems;

   };
} /// namespace XST_FLAG