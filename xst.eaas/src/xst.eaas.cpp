#include <xst.eaas.hpp>
namespace XST_FLAG
{

void eaas::addeaas(
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
   uint64_t storageFee)
{
   eaas_table eaases(get_self(), get_self().value);//code.scope

   uint64_t id;

   eaases.emplace(get_self(), [&](auto &item){
       item.id = eaases.available_primary_key();
       item.from = from;
       item.to = to;
       item.name = name;
       item.description = description;
       item.location = location;
       item.validity = validity;
       item.devices = devices;
       item.operator_ = operator_;
       item.plan = plan;
       item.esimFee = esimFee;
       item.storage = storage;
       item.storageFee = storageFee;
       id = item.id;
   });
   print("add id=",id, " from=",from ,", to=",to,", name=",name,
         "descripoperatortion=",description,
         "location=",location,
         "validity=",validity,
         "operator_=",operator_,
         "plan=",plan,
         "esimFee=",esimFee,
         "storage=",storage,
         "storageFee=",storageFee,
         "\n");
}

void eaas::cleareaas(){
    //require_auth(get_self());

     eaas_table eaases(get_self(), get_self().value);//code.scope

     //Delete all records 
     auto msg_itr = eaases.begin();
     while (msg_itr != eaases.end()){
         msg_itr = eaases.erase(msg_itr);
     }
     
     print( "[eaas] ", "Delete all records in table: ", name("eaasstruct"), "\n" ); //log level: debug
}
}//namespace XST_FLAG