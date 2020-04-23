# xst.m2m

This example including

- Define contract actions
- Define a table
- Perform read/write/remove operations on the table

## contract name
- Must be a valid Snapscale account name
- folder name == contract name
- xst.m2m

## build
```bash
~/work/xeniro/snapscale.cdt/build/bin/eosio-cpp src/m2musecasexs.cpp -o xst.m2m.wasm --abigen -I ./include
```

## snapscale env
```bash
# create contract account
## debug
cleos create account eosio communityv1 XST6faDa4sP83YXDYNVsiLFw6GB6griEZQmSKZBbLqHQVTZMZtLqx
cleos push action eosio.token transfer '[ "eosio", "communityv1", "1000000.0000 XST", "memo" ]' -p eosio
## release
cleos system newaccount --transfer communityv1 xst.m2m XST6faDa4sP83YXDYNVsiLFw6GB6griEZQmSKZBbLqHQVTZMZtLqx XST6faDa4sP83YXDYNVsiLFw6GB6griEZQmSKZBbLqHQVTZMZtLqx --stake-net "100.0000 XST" --stake-cpu "100.0000 XST" --buy-ram "100.0000 XST"

# deploy m2m contract
cleos set contract xst.m2m ~/work/xeniro/snapscale.contracts/contracts/xst.m2m/ -p xst.m2m

# create test account
## debug
cleos create account eosio usecasecarx1 XST6faDa4sP83YXDYNVsiLFw6GB6griEZQmSKZBbLqHQVTZMZtLqx
cleos create account eosio usecasepile1 XST6faDa4sP83YXDYNVsiLFw6GB6griEZQmSKZBbLqHQVTZMZtLqx
## release
cleos system newaccount --transfer communityv1 usecasecarx1 XST6faDa4sP83YXDYNVsiLFw6GB6griEZQmSKZBbLqHQVTZMZtLqx XST6faDa4sP83YXDYNVsiLFw6GB6griEZQmSKZBbLqHQVTZMZtLqx --stake-net "100.0000 XST" --stake-cpu "100.0000 XST" --buy-ram "100.0000 XST"
cleos system newaccount --transfer communityv1 usecasepile1 XST6faDa4sP83YXDYNVsiLFw6GB6griEZQmSKZBbLqHQVTZMZtLqx XST6faDa4sP83YXDYNVsiLFw6GB6griEZQmSKZBbLqHQVTZMZtLqx --stake-net "100.0000 XST" --stake-cpu "100.0000 XST" --buy-ram "100.0000 XST"

# transaction token to car account
cleos transfer communityv1  usecasecarx1  "100000.0000 XST" "memo" -p communityv1

# add eosio.code premiss
cleos set account permission usecasecarx1 active xst.m2m --add-code -p usecasecarx1@owner
cleos set account permission xst.m2m active xst.m2m --add-code -p xst.m2m@owner

# car auth to pile
cleos push action xst.m2m carauth '{"car":"usecasecarx1","pile":"usecasepile1","quantity":"10.0000 XST"}' -p usecasecarx1@active

# pile Step by step deduction
cleos push action xst.m2m pilepersub '{"pile":"usecasepile1","car":"usecasecarx1"}' -p usecasepile1@active

# pile final settlement
cleos push action xst.m2m settlement '{"pile":"usecasepile1","car":"usecasecarx1","proxy":"communityv1"}' -p usecasepile1@active
```

### chain info
|item           |content                                                                    |
|-|-|
|API Endpoint   |http://192.168.1.201:30088                                                 |
|Chain ID       |`5972900d81de64024d0c1620ac2cf7e06919a2f14f9df041f024685fad496a17`         |
|token symbol   |XST                                                                        |
|contract name  |xst.m2m                                                               |
|contract action|`ACTION carauth(const name &car, const name &pile, const asset& quantity)` |
|contract action|`ACTION pilepersub(const name &pile, const name &car)`                     |
|contract action|`ACTION settlement(const name &pile, const name &car, const name &proxy)`  |

### account info
|role   |account        |public key                                               |private key                                          |
|-|-|-|-|
|car    |usecasecarx1   |`XST6faDa4sP83YXDYNVsiLFw6GB6griEZQmSKZBbLqHQVTZMZtLqx`  |`5J9hCmEE1mPRQtPuvQweNSeiJrUx8PBSnsxSmhHq9xb1RopaFXs`|
|pile   |usecasepile1   |`XST6faDa4sP83YXDYNVsiLFw6GB6griEZQmSKZBbLqHQVTZMZtLqx`  |`5J9hCmEE1mPRQtPuvQweNSeiJrUx8PBSnsxSmhHq9xb1RopaFXs`|
|proxy  |communityv1    |                                                         |                                                     |
