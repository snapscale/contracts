# m2musecasexs

This example including

- Define contract actions
- Define a table
- Perform read/write/remove operations on the table

## contract name
- Must be a valid EOS account name
- folder name == contract name
- m2musecasexs

## build
```bash
/mnt/d/wcc/work/blockchain/cucubao/eosio.cdt/build/bin/eosio-cpp src/m2musecasexs.cpp -o m2musecasexs.wasm --abigen -I ./include
```

## snapscale env
```bash
# create contract account
cleos system newaccount --transfer communityv1 m2musecasexs EOS6faDa4sP83YXDYNVsiLFw6GB6griEZQmSKZBbLqHQVTZMZtLqx EOS6faDa4sP83YXDYNVsiLFw6GB6griEZQmSKZBbLqHQVTZMZtLqx --stake-net "100.0000 XST" --stake-cpu "100.0000 XST" --buy-ram "100.0000 XST"
# deploy m2m contract
cleos set contract m2musecasexs /mnt/d/wcc/work/xeniro/snapscale.contracts/contracts/m2musecasexs/ -p m2musecasexs

# create test account
cleos system newaccount --transfer communityv1 usecasecarx1 EOS6faDa4sP83YXDYNVsiLFw6GB6griEZQmSKZBbLqHQVTZMZtLqx EOS6faDa4sP83YXDYNVsiLFw6GB6griEZQmSKZBbLqHQVTZMZtLqx --stake-net "100.0000 XST" --stake-cpu "100.0000 XST" --buy-ram "100.0000 XST"

cleos system newaccount --transfer communityv1 usecasepile1 EOS6faDa4sP83YXDYNVsiLFw6GB6griEZQmSKZBbLqHQVTZMZtLqx EOS6faDa4sP83YXDYNVsiLFw6GB6griEZQmSKZBbLqHQVTZMZtLqx --stake-net "100.0000 XST" --stake-cpu "100.0000 XST" --buy-ram "100.0000 XST"

# transaction token to car account
cleos transfer communityv1  usecasecarx1  "100000.0000 XST" "memo" -p communityv1

# add eosio.code premiss
cleos set account permission usecasecarx1 active m2musecasexs --add-code -p usecasecarx1@owner
cleos set account permission m2musecasexs active m2musecasexs --add-code -p m2musecasexs@owner

# car auth to pile
cleos push action m2musecasexs carauth '{"car":"usecasecarx1","pile":"usecasepile1","quantity":"10.0000 XST"}' -p usecasecarx1@active

# pile Step by step deduction
cleos push action m2musecasexs pilepersub '{"pile":"usecasepile1","car":"usecasecarx1"}' -p usecasepile1@active

# pile final settlement
cleos push action m2musecasexs settlement '{"pile":"usecasepile1","car":"usecasecarx1","proxy":"communityv1"}' -p usecasepile1@active
```

### chain info
|item           |content                                                                    |
|-|-|
|API Endpoint   |http://192.168.1.201:30088                                                 |
|Chain ID       |`5972900d81de64024d0c1620ac2cf7e06919a2f14f9df041f024685fad496a17`         |
|token symbol   |XST                                                                        |
|contract name  |m2musecasexs                                                               |
|contract action|`ACTION carauth(const name &car, const name &pile, const asset& quantity)` |
|contract action|`ACTION pilepersub(const name &pile, const name &car)`                     |
|contract action|`ACTION settlement(const name &pile, const name &car, const name &proxy)`  |

### account info
|role   |account        |public key                                               |private key                                          |
|-|-|-|-|
|car    |usecasecarx1   |`EOS6faDa4sP83YXDYNVsiLFw6GB6griEZQmSKZBbLqHQVTZMZtLqx`  |`5J9hCmEE1mPRQtPuvQweNSeiJrUx8PBSnsxSmhHq9xb1RopaFXs`|
|pile   |usecasepile1   |`EOS6faDa4sP83YXDYNVsiLFw6GB6griEZQmSKZBbLqHQVTZMZtLqx`  |`5J9hCmEE1mPRQtPuvQweNSeiJrUx8PBSnsxSmhHq9xb1RopaFXs`|
|proxy  |communityv1    |                                                         |                                                     |
