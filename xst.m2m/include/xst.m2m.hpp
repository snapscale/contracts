#include "typedef.hpp"

#include XST_HEAD_ASSET

using namespace std;
using namespace XST_FLAG;

const symbol FIX_SYMBOL = symbol(symbol_code("XST"), 4);
const name FIX_TOKEN_CONTRACT_ACCOUNT = name(XST_NAME_TOKEN);
const asset FIX_PERSUB = asset(10000, FIX_SYMBOL);      //sub token per time  1.0000
const asset FIX_MECFEE = asset(5000, FIX_SYMBOL);       //mec fee, FIX_PERSUB > FIX_MECFEE  0.5000

class [[XST_FLAG::contract("xst.m2m")]] m2musecasexs : public contract {
  using contract::contract;
    
  private:
    void carclear();

    TABLE carauthmsg {
      name    car;
      name    pile;
      asset   quantity;   //total amout
      asset   comsume;    //used amout
      auto primary_key() const { return car.value; }
    };
    typedef multi_index<name("carauthmsg"), carauthmsg> carauthmsg_table;

  //car auth to pile
  public:
    ACTION carauth(const name &car, const name &pile, const asset& quantity);

  //pile Step by step deduction
  public:
    ACTION pilepersub(const name &pile, const name &car);
    ACTION settlement(const name &pile, const name &car, const name &proxy);

  //manager
  public:
    ACTION mgrclear();
};
