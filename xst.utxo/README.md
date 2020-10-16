# UTXO Implementation

## ./contract/

The source code of the contract that handles the UTXO token. 

## ./deploy/

Deploy node and contract

## ./cmd/

`ln -s cmd.js clutxo`

The command line utility `clutxo` provides an interface to the UTXO 
enabled UTXO smart contract. 

**The utility uses the original EOSIO wallet to store your keys, so that
must be installed and setup. It is advised to create a new wallet for this purpose and set that in the configuration file.  **

# Usage

## Deploy nodeos, keosd and contract
see ./deploy/README.md

## trading UTXO
```bash
cd cmd
# if first run
npm install

# see help
chmod 777 clutxo 
./clutxo
```

### 1.Generate a new address that receives utxo
```bash
./clutxo receive
# Get a previously generated, unused utxo address; if not found, a new one is automatically generated
./clutxo receive -r
```

### 2.trading
![](https://miro.medium.com/max/4012/1*9Mh0fzsxsJtNxaC1gF3p4Q.png)
> fees is not necessary

```bash
# *****************
accout -> address
# *****************
## transfer [from_account]] [to] [amount]
## Convert your balance to utxo, the balance on the account will be reduced, and the balance on the address will increase.
### 1)Go to the new utxo address
./clutxo transfer voter1 new "2.0000 UTXO" 
### 2)Go to the specified utxo address
./clutxo transfer voter1 XST52FzMMyKmKDkotMLpRKQFDuHNuYnbNZ35BMZYF4434XorypqkB "1.0000 UTXO" 

# *****************
address -> address
# *****************
## transfer utxo [to] [amount]
### 1)Transfer a new address to yourself
./clutxo transfer utxo new "1.0000 UTXO" -a voter1 
./clutxo transfer utxo new "1.0000 UTXO" -a voter1 -s -m "memo"
### 2)Go to the specified address
./clutxo transfer utxo XST52FzMMyKmKDkotMLpRKQFDuHNuYnbNZ35BMZYF4434XorypqkB "0.5000 UTXO" -a voter1

# *****************
address -> account
# *****************
## transfer utxo [to_account] [amount]
./clutxo transfer utxo eosio "0.2000 UTXO" -a voter1
./clutxo transfer utxo voter1 "1.0000 UTXO" -a voter1
```

### 3.View balance
Only count used addresses under current wallet management
```bash
# View the balance under the utxo system
./clutxo balance
# View balance details under the utxo system
./clutxo balance -u

# Get the balance of all accounts managed by the wallet (ie the key is kept in this wallet)
## Default EOS of the eosio.token contract
./clutxo all
/clutxo all -s SYS
## Designated token -e <accounts>    //Comma separated accounts to exclude
./clutxo all -s UTXO -c xst.utxo 
./clutxo all -s UTXO -c xst.utxo | grep -E "voter1|xst.utxo"
```

## 3. Additional features of js

```bash
# Json format, specifies an action in the calling contract, that is, a function
./clutxo relay voter1 '{action}'
# Provide http service, listen to port 8080, post body action information, json format
./clutxo serve voter1

# The value of the set config variable (will be saved to walletconfig.json)
./clutxo set <variable> <value>
# The value of the get config variable (read from walletconfig.json)
./clutxo get x 

```

The json format of the action is as follows:
```json
{
        account: Config.contract_info.code,
        name: 'loadutxo',
        data: {
            from: from,
            pk: key,
            quantity: amount
        },
        authorization: [{
            actor: from,
            permission: 'active'
        }]
}
```

