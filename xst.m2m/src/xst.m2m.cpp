#include <xst.m2m.hpp>
// #include <eosio.token/eosio.token.hpp>
#include "../../eosio.token/include/eosio.token/eosio.token.hpp"

//car 
ACTION m2musecasexs::carauth(const name &car, const name &pile, const asset& quantity){
  require_auth(car);

  check( car != pile, "cannot auth to self" );
  check( is_account( pile ), "pile account does not exist");
  check( quantity.is_valid(), "invalid quantity" );
  check( quantity.amount > 0, "car must transfer positive quantity" );
  check( quantity.symbol == FIX_SYMBOL, "symbol precision mismatch" );

  require_recipient( car );// add to notice list
  require_recipient( pile );
  
  //token: car -> owner
  token::transfer_action transfer_act{ FIX_TOKEN_CONTRACT_ACCOUNT, { {car, name("active")} } };
  transfer_act.send( car, get_self(), quantity, "carauth" );
  // print( "[m2musecasexs] ", name{car}, " auth ", quantity, " to ", name{pile}, "\n" );


  // Init the table
  carauthmsg_table _table(get_self(), get_self().value); // code, scope

  // Find the record car table
  auto msg_itr = _table.find(car.value);
  if (msg_itr == _table.end()) {
    // Create a record if it does not exist
    _table.emplace(car, [&](auto& msg) {
      msg.car = car;
      msg.pile = pile;
      msg.quantity = quantity;
      msg.comsume = asset(0, FIX_SYMBOL);
      
      print( "[m2musecasexs] ", name{car}, " auth ", quantity, " to ", name{pile}, " | create a auth record, quantity:", msg.quantity, " comsume: ", msg.comsume, "\n" );
    });
      
  } else {
    // Modify a record if it exists
    _table.modify(msg_itr, same_payer, [&](auto& msg) {
      if(msg.quantity.amount <= 0)
        msg.quantity.amount = 0;

      msg.pile = pile;
      msg.quantity += quantity;
      
      print( "[m2musecasexs] ", name{car}, " auth ", quantity, " to ", name{pile}, " | modify a auth record, quantity:", msg.quantity, " comsume: ", msg.comsume, "\n" );
    });

  }
  
}

void m2musecasexs::carclear() {
  // require_auth(get_self());

  carauthmsg_table _table(get_self(), get_self().value); // code, scope

  // Delete all records in table
  auto msg_itr = _table.begin();
  while (msg_itr != _table.end()) {
    msg_itr = _table.erase(msg_itr);
  }

  print( "[m2musecasexs] ", "Delete all records in table: ", name("carauthmsg"), "\n" ); //log level: debug
}

//------------------------------------------------------------------------
//pile
ACTION m2musecasexs::pilepersub(const name &pile, const name &car){
  require_auth(pile);

  check( car != pile, "cannot sub token of self" );
  check( is_account( car ), "car account does not exist");


  carauthmsg_table _table(get_self(), get_self().value); // code, scope

  // Find the record car table
  auto msg_itr = _table.find(car.value);
  check( msg_itr != _table.end(), "[pilepersub] car does not auth" );
  check( msg_itr->quantity - msg_itr->comsume >= FIX_PERSUB, "[pilepersub] Insufficient balance, less than FIX_PERSUB" );

  require_recipient( car );// add to notice list
  require_recipient( pile );

  // Modify a record if it exists
  _table.modify(msg_itr, same_payer, [&](auto& msg) {
    msg.comsume += FIX_PERSUB;

    print( "[m2musecasexs] ", "modify a auth record, quantity:", msg.quantity, " comsume: ", msg.comsume, "\n" );
  });
  
}

ACTION m2musecasexs::settlement(const name &pile, const name &car, const name &proxy){
  require_auth(pile);

  check( car != pile, "cannot sub token of self" );
  check( is_account( car ), "car account does not exist");
  check( is_account( proxy ), "proxy account does not exist");


  carauthmsg_table _table(get_self(), get_self().value); // code, scope

  // Find the record car table
  auto msg_itr = _table.find(car.value);
  check( msg_itr != _table.end(), "[pilesettlement] car does not auth" );
  check( msg_itr->quantity.amount > 0, "[pilesettlement] Insufficient quantity" );

  auto quantity = msg_itr->quantity;
  auto comsume = msg_itr->comsume;
  asset returnToCar = quantity - comsume;
  if(returnToCar < asset(0, FIX_SYMBOL)){
    returnToCar = asset(0, FIX_SYMBOL);
    comsume = quantity;

    print( "[m2musecasexs] ", "[pilesettlement] -warn-: returnToCar < 0 , quantity:", quantity, " comsume: ", comsume, "\n" );
  }

  asset payToPile = comsume - FIX_MECFEE;
  asset payToProxy = FIX_MECFEE;

  check( payToPile.amount > 0, "payToPile must transfer positive quantity" );
  check( payToProxy.amount > 0, "payToProxy must transfer positive quantity" );

  require_recipient( car );// add to notice list
  require_recipient( pile );
  require_recipient( proxy );//notice MEC

  //token:
  token::transfer_action transfer_act{ FIX_TOKEN_CONTRACT_ACCOUNT, { {get_self(), name("active")} } };
  if(returnToCar > asset(0, FIX_SYMBOL)){
    transfer_act.send( get_self(), car, returnToCar, "returnToCar" );
  }
  if(payToPile > asset(0, FIX_SYMBOL)){
    transfer_act.send( get_self(), pile, payToPile, "payToPile" );
  }
  if(payToProxy > asset(0, FIX_SYMBOL)){
    transfer_act.send( get_self(), proxy, payToProxy, "payToProxy" );
  }
  print( "[m2musecasexs] ", "[pilesettlement] quantity: ", msg_itr->quantity, "comsume: ", msg_itr->comsume, "returnToCar: ", returnToCar, " payToPile: ", payToPile," payToProxy: ", payToProxy, "\n" );

  // Modify a record
  // _table.modify(msg_itr, same_payer, [&](auto& msg) {
  //   msg.pile = name(0) ;
  //   msg.quantity = asset(0, FIX_SYMBOL);
  //   msg.comsume = asset(0, FIX_SYMBOL);

  //   print( "[m2musecasexs] ", "[pilesettlement] modify a auth record, quantity:", msg.quantity, " comsume: ", msg.comsume, "\n" );
  // });

  // erase a record
  _table.erase(msg_itr);
  print( "[m2musecasexs] ", "[pilesettlement] erase a record, car:", name{car}, " pile: ", name{pile}, "\n" );
  
}

//------------------------------------------------------------------------
//manager
ACTION m2musecasexs::mgrclear() {
  require_auth(get_self());

  carclear();
}

// EOSIO_DISPATCH(m2musecasexs, (carauth)(pilepersub)(settlement)(mgrclear))
