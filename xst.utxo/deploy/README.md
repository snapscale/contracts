# 0. private Testnet
启用单节点
```bash
# 后台运行本地私链结点
nohup ./nodeos -e -p eosio \
	--plugin eosio::chain_api_plugin --plugin eosio::history_api_plugin \
	--contracts-console --config-dir=./config_eosio  \
	--blocks-dir blocks  \
	--data-dir data \
	&

# hard-replay	
nohup ./nodeos -e -p eosio \
	--plugin eosio::chain_api_plugin --plugin eosio::history_api_plugin \
	--contracts-console --config-dir=./config_eosio  \
	--blocks-dir blocks  \
	--data-dir data \
	--hard-replay \
	&

# 观察运行情况
tail -f nohup.out 
or
./cleos get info

# 加载默认钱包
nohup ./keosd --unlock-timeout 31536000 & 
./cleos wallet open
./cleos wallet unlock --password < ./default


```

部署utxo合约
```bash
### 自己用eosio.cdt编译
eosio.cdt/build/bin/eosio-cpp src/xst.utxo.cpp -o xst.utxo.wasm --abigen -I ./include

## 在bin目录下跑脚本部署 *********
#创建合约账户  (带后缀的账户,用eosio可以创建出来)
./cleos system newaccount --transfer eosio xst.utxo EOS63gKbqNRZjboQyfXBJPijZHNr1GtXJu5eCan3e6iSqN7yP5nFZ EOS63gKbqNRZjboQyfXBJPijZHNr1GtXJu5eCan3e6iSqN7yP5nFZ --stake-net "1.0000 SYS" --stake-cpu "1 SYS" --buy-ram "1000 SYS"
#部署
./cleos set contract xst.utxo ~/work/xeniro/snapscale/unittests/contracts/xst.utxo/ -p xst.utxo
#调用verify
./cleos push action xst.utxo verifyring '{}' -p xst.utxo@active

./2.deploy_SC.sh
# ************************************

```

## 1. 运行 my local wallet : keosd
```bash
nohup ./keosd --unlock-timeout 999999999999 & 

# 首次运行,创建名为`utxo`的钱包,将钱包密码保存在名为`utxo`的文件中
./cleos wallet create --file utxo  -n utxo

# 二次运行
./cleos wallet open -n utxo
./cleos wallet unlock -n utxo --password < ./utxo

# 查看钱包是否解锁
./cleos wallet list
# 查看受钱包保管的公钥
./cleos wallet keys
```

> 关闭 keosd
> `./cleos wallet stop`
