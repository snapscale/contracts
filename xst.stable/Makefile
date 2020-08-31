CPP_IN=xst.stable
CLEOS=$(CLEOS)
CONTRACT_ACCOUNT=xst.stable
CLEOS=../../../snapscale/cmake-vsbuild-debug/bin/cleos -u http://127.0.0.1:8888

build:
	../../../snapscale.cdt/build/bin/eosio-cpp -abigen $(CPP_IN).cpp -o $(CPP_IN).wasm

all: build

deploy-first:
	$(CLEOS) create account eosio $(CONTRACT_ACCOUNT) XST63gKbqNRZjboQyfXBJPijZHNr1GtXJu5eCan3e6iSqN7yP5nFZ
	$(CLEOS)  transfer  eosio  $(CONTRACT_ACCOUNT)  "10000.0000 XST"  -p  eosio
	$(CLEOS) set contract $(CONTRACT_ACCOUNT) ../../build/contracts/$(CONTRACT_ACCOUNT) -p $(CONTRACT_ACCOUNT)

deploy:
	$(CLEOS) set contract $(CONTRACT_ACCOUNT) ../../build/contracts/$(CONTRACT_ACCOUNT) -p $(CONTRACT_ACCOUNT)

create:
	$(CLEOS) push action $(CONTRACT_ACCOUNT) create '{"issuer":"$(CONTRACT_ACCOUNT)", "maximum_supply":"1000000000.0000 ST"}' -p $(CONTRACT_ACCOUNT)

issue:	
	$(CLEOS) push action $(CONTRACT_ACCOUNT) issue '[ "$(CONTRACT_ACCOUNT)", "150000000.0000 ST", "memo" ]' -p $(CONTRACT_ACCOUNT)
	
transfer:
	$(CLEOS) push action $(CONTRACT_ACCOUNT) transfer '{"from":"'$(CONTRACT_ACCOUNT)'", "to":"eosio",  "quantity":"1.0000 ST", "memo":"test"}' -p $(CONTRACT_ACCOUNT)
	
pause:
	$(CLEOS) push action $(CONTRACT_ACCOUNT) pause '{}' -p $(CONTRACT_ACCOUNT)

unpause:
	$(CLEOS) push action $(CONTRACT_ACCOUNT) unpause '{}' -p $(CONTRACT_ACCOUNT)

clean:
	rm -f $(CPP_IN).wast $(CPP_IN).wasm


#cleos -u http://kylin-testnet.jeda.one:8888 push action woooooooooop create '{"issuer":"woooooooooop", "maximum_supply":"100 XT"}' -p woooooooooop