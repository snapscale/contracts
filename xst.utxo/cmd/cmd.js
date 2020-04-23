#!/usr/bin/env node

const program = require('commander')
const Eos     = require('eosjs')
const { PublicKey , sha256 } = require('eosjs-ecc')
const Config  = require('./config')
const read    = require('read')
const request = require('request')
const Promise = require('bluebird')
const bip39   = require('bip39')
const Conf = require('conf');

const express = require('express')

// const hdwallet = require('./wallet')

Config.wallet_URL = Config.wallet_URL.replace('~', process.env.HOME);

const config = new Conf({
    configName: 'walletconfig', // Read configuration file
    cwd: './',
    schema: {
        wallet_name: {
            type: 'string',
            default: 'pxst'
        },
        wallet_hd_index: {
            type: 'integer',
            default: 0
        }
    }
});

// let seed = bip39.mnemonicToSeedSync('send invoice')
// hdwallet.initFromMasterSeed(config, seed)

async function createToken(pubkey, signature, svr_pubkey) { //Related to wallet name
    return new Promise((resolve, reject) => {
        const body = [
            pubkey,
            signature,
            svr_pubkey
        ];
        const options = {
            method: "POST",
            url: Config.wallet_URL + "/v1/wallet/create_token",
            body: JSON.stringify(body)
        }
        request(options, function (err, res, body) {
            if (err) {
                reject(err);
            } else {
                resolve(JSON.parse(body));
            }
        })
    })
}

let headers;
async function getHttpHeaders(){
    sender_pk = Config.eos_conn_info.sender_pk;//'XST83jABXUkPLcpeA5fbgKfokdd5YSP6k6n87wpYrApfW7rY9MqT6'
    sender_dc = Config.eos_conn_info.sender_dc;//'SIG_K1_K5VCusVxRvRbk25YK5zdvm42B7KnRWba4KBbxnekMabK7DiEvykSYEjAci3sN1zmFso1tTjELpkr4bEQcDcViEnKXt99MN'
    receiver_pk = Config.eos_conn_info.receiver_pk;//'XST83jABXUkPLcpeA5fbgKfokdd5YSP6k6n87wpYrApfW7rY9MqT6'

    const jwt = await createToken(sender_pk, sender_dc, receiver_pk)
    // console.log(jwt); // "Authorization:eyJhbGciOiJIUzI1NiJ9..."
    var keyvalue = jwt.split(":");
    // console.log(keyvalue[0]);
    // console.log(keyvalue[1]);
    return { 'Authorization' : keyvalue[1]}

    // return {'Authorization' : 
    //         'eyJhbGciOiJIUzI1NiJ9.eyJleHAiOjE1ODY3Nzk1NzksImlhdCI6MTU4Njc3NTk3OSwiaXNzIjoieHN0IiwicHVibGljIjoiWFNUODNqQUJYVWtQTGNwZUE1ZmJnS2Zva2RkNVlTUDZrNm44N3dwWXJBcGZXN3JZOU1xVDYiLCJzaWduYXR1cmUiOiJTSUdfSzFfSzVWQ3VzVnhSdlJiazI1WUs1emR2bTQyQjdLblJXYmE0S0JieG5la01hYks3RGlFdnlrU1lFakFjaTNzTjF6bUZzbzF0VGpFTHBrcjRiRVFjRGNWaUVuS1h0OTlNTiJ9.7WUY3gREMZu8L6jfsXdL7i6MxP2N1jW2XmtRjRAS9VA'
    //         }
}

function getChainInfo() {
    return new Promise((resolve, reject) => {
        const options = {
            method: "GET",
            url: Config.eos_conn_info.httpEndpoint + "/v1/chain/get_info",
            headers: headers
        }
        request(options, function (err, res, body) {
            if (err) reject(err);
            else resolve(JSON.parse(body));
        })
    })
}

function getAcount(account) {
    let body = {
        account_name: account
    }
    return new Promise((resolve, reject) => {
        const options = {
            method: "GET",
            url: Config.eos_conn_info.httpEndpoint + "/v1/chain/get_account",
            body: JSON.stringify(body),
            headers: headers
        }
        request(options, function (err, res, body) {
            if (err) reject(err);
            else resolve(JSON.parse(body));
        })
    })
}

function getKeyAcount(key) { //Get the accounts corresponding to the public key
    let body = {
        public_key: key
    }
    return new Promise((resolve, reject) => {
        const options = {
            method: "GET",
            url: Config.eos_conn_info.httpEndpoint + "/v1/history/get_key_accounts",
            body: JSON.stringify(body),
            headers: headers
        }
        request(options, function (err, res, body) {
            if (err) reject(err);
            else resolve(JSON.parse(body).account_names);
        })
    })
}

function getCurrencyBalance(code, account_name, symbol) {

    return new Promise((resolve, reject) => {
        const body = {
            account : account_name, 
            code    : code, 
            symbol  : symbol
        }

        const options = {
            method: "POST",
            url: Config.eos_conn_info.httpEndpoint + "/v1/chain/get_currency_balance",
            body: JSON.stringify(body),
            headers: headers
        }

        request(options, function (err, res, body) {
            if (err) reject(err);
            else resolve(JSON.parse(body));
        })
    })
}

async function getActiveKey(account) {
    let data = await getAcount(account)
    if (!data.permissions) {
        return
    }

    for (p of data.permissions) {
        if (p.perm_name == 'active') {
            return p.required_auth.keys[0].key
        }
    }
}

function getWalletKeyList() {
    return new Promise((resolve, reject) => {
        const options = {
            method: "POST",
            url: Config.wallet_URL + "/v1/wallet/get_public_keys",
            headers: headers
        }
        request(options, function (err, res, body) {
            if (err) reject(err);
            else {
                body = JSON.parse(body)
                if (!Array.isArray(body)) {
                    console.log('ERROR: Locked wallet')
                    resolve([])
                    return
                }
                resolve(body);
            }
        })
    })
}

function createKey() { //Related to wallet name
    return new Promise((resolve, reject) => {
        let body = 
            [program.name || config.get('wallet_name'), ""]
    
        const options = {
            method: "POST",
            url: Config.wallet_URL + "/v1/wallet/create_key",
            body: JSON.stringify(body),
            headers: headers
        }

        request(options, function (err, res, body) {
            if (err) reject(err);
            else {
                let key = JSON.parse(body)
                if (typeof(key) != 'string') {
                    reject('failed')
                } else {
                    resolve(key);
                }
            }
        })
    })
}

var eos = null;

async function signProvider(buf, sign) {
    return new Promise((resolve, reject) => {
        const body = [
            buf.transaction,
            [Config.active_public_key],
            Config.eos_conn_info.chainId
        ];
        const options = {
            method: "POST",
            url: Config.wallet_URL + "/v1/wallet/sign_transaction",
            body: JSON.stringify(body),
            headers: headers
        }
        request(options, function (err, res, body) {
            if (err) reject(err);
            else {
                resolve(JSON.parse(body).signatures);
            }
        })
    })
}

async function signDigest(digest, key) {
    // console.log("tip signDigest: digest:", digest)
    // console.log("tip signDigest: key:", key)
    
    return new Promise((resolve, reject) => {
        const body = [
            digest,
            key
        ];
        const options = {
            method: "POST",
            url: Config.wallet_URL + "/v1/wallet/sign_digest",
            body: JSON.stringify(body),
            headers: headers
        }
        request(options, function (err, res, body) {
            if (err) {
                console.log(err)
                reject(err);
            } else {
                resolve(JSON.parse(body));
            }
        })
    })
}

const cleos_wallet = {
    getWalletKeyList,
    createKey,
    signDigest
}
let wallet = cleos_wallet
// let wallet = hdwallet

async function makeTransactionHeader(expireInSeconds, callback) {
    let info = await eos.getInfo({});
    chainDate = new Date(info.head_block_time + 'Z')
    expiration = new Date(chainDate.getTime() + expireInSeconds * 1000)
    expiration = expiration.toISOString().split('.')[0]

    let block = await eos.getBlock(info.last_irreversible_block_num);
    let header = {
        expiration: expiration,
        ref_block_num: info.last_irreversible_block_num & 0xFFFF,
        ref_block_prefix: block.ref_block_prefix,

        net_usage_words: 0,
        max_cpu_usage_ms: 0,
        delay_sec: 0,
        context_free_actions: [],
        actions: [],
        signatures: [],
        transaction_extensions: []
    }

    callback(null, header);
}

function makeVerifyActions(account_name, signatures) {
    let actions = [];

    for (let i = 0; i < signatures.length; i++) {
        let action = {
            account: Config.contract_info.code,
            name: 'verifysig',
            data: {
                owner: account_name,
                sig: `${signatures[i]}`
            }
        };

        actions.push(action);
    }

    return actions;
}

function makeTransferAction(account_name, inputs, outputs, memo) {
    // console.log("tip: account_name:", account_name)
    // console.log("tip: inputs:", inputs)
    // console.log("tip: outputs:", outputs)
    // console.log("tip: memo:", memo)

    let action = {
        account: Config.contract_info.code,
        name: 'transferutxo',
        data: {
            payer: account_name,
            inputs,
            outputs,
            memo
        },
        authorization: [{
            actor: account_name,
            permission: 'active'
        }]
    };
    return action;
}

function makeLoadAction(from, key, amount) {
    // console.log("tip: from:", from)
    // console.log("tip: key:", key)
    // console.log("tip: amount:", amount)
    
    let action = {
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
    };
    return action;
}

function fixBufferEndianForEOS(buf) {
    let ret = ''
    
    for(let i = 15 ; i >= 0 ; --i) {
        ret += buf[i]
    }

    for(let i = 31 ; i >= 16 ; --i) {
        ret += buf[i]
    }

    ret = Buffer.from(ret, 'binary')
    
    return ret
}

function getAmount(asset, symbol) {
    symbol = symbol || Config.contract_info.symbol;
    let a = asset.split(' ');
    if (a[1] !== symbol) 
        return 0.0;
    return parseFloat(a[0])
} 

function formatAmount(asset, symbol) {
    return `${asset.toFixed(4)} ${symbol || Config.contract_info.symbol}` 
}

async function getUTXOsForKey(pk) {
    // let hash = fixBufferEndianForEOS(sha256(PublicKey.fromString(pk, Config.eos_conn_info.keyPrefix).toBuffer(), 'binary')).toString('hex')
    let hash = sha256(PublicKey.fromString(pk, Config.eos_conn_info.keyPrefix).toBuffer(), 'hex')
    return new Promise((resolve, reject) => {
        let body = {
            "json": true,
            "code": Config.contract_info.code,  // Contract name
            "scope": Config.contract_info.code,
            "table": "utxos",                   // Multi_index Table name in the contract
            "table_key": "",
            "lower_bound": hash,                // Query conditions
            "upper_bound": hash,                // Query conditions
            "limit": 1000,                      // Query conditions
            "key_type": "sha256",
            "index_position": "2",              // 2nd index ?      
            "encode_type": "hex",
            "reverse": false,
            "show_payer": false
        }
        const options = {
            method: "GET",
            url: Config.eos_conn_info.httpEndpoint + "/v1/chain/get_table_rows", //View Multi_index table data in a contract
            body: JSON.stringify(body),
            headers: headers
        }
        request(options, function (err, res, body) {
            if (err) { reject(err); return; }

            let rows = JSON.parse(body).rows
            if (rows !== undefined) {
                resolve(rows);
            } else {
                resolve([])
            }
        })
    })
}

async function getOwnedUTXOs() {
    let keys = await wallet.getWalletKeyList();
    // console.log("keys: "+ keys.length)
    let utxos = []

    for(let key of keys) {
        let ks = await getUTXOsForKey(key);
        utxos = utxos.concat(ks)
    }

    return utxos
}

async function getWalletBalance() {
    let utxos = await getOwnedUTXOs()
    let balance = 0.0;

    for (utxo of utxos) {
        balance += getAmount(utxo.amount)
    }

    return balance
}

async function getWalletUTXOForAmount(amount) { //Group a group with so many balances
    let all_utxos = await getOwnedUTXOs()
    all_utxos.sort((a, b) => {return getAmount(a.amount) - getAmount(b.amount)});//Sort by balance from big to small

    let balance = 0.0;
    let utxos = []

    for (utxo of all_utxos) {
        balance += getAmount(utxo.amount)
        utxos.push({id: utxo.id, pk: utxo.pk})
        if (balance >= amount) {
            break
        }
    }

    return [utxos, balance]
}

async function init() {
    const chainInfo = await getChainInfo();
    if (chainInfo.chain_id !== Config.eos_conn_info.chainId) {
        console.error('ERROR: Check chain_id!');
        return;
    }
    
    Config.eos_conn_info.signProvider = signProvider;
    Config.eos_conn_info.transactionHeaders = makeTransactionHeader; 
    Config.eos_conn_info.fetchConfiguration = {headers : headers}; // eosjs used
    eos = Eos(Config.eos_conn_info);
}

async function loadutxo(from, to, amount) {
    let key = await getActiveKey(from)
    if (!key) {
        console.error("ERROR: Can't find key for account:", from)
        return
    }

    await init();

    Config.active_public_key = key

    if (to === 'new') {
        try {
            to = await wallet.createKey()
            console.log(`Generated new key ${to}`)
        } catch (err) {
            console.error('ERROR: Failed to generate new key. (locked wallet?)')
            return
        }
    } 

    if(!PublicKey.isValid(to, Config.eos_conn_info.keyPrefix)) {
        console.error("ERROR: Invalid to address")
        return
    }

    let loadAction = makeLoadAction(from, to, amount)

    await eos.transaction({ actions: [loadAction] })
        .then(async (ret) => {
            console.log('Transfer success (Id: ' + ret.transaction_id + ' )');
        })
        .catch((err) => {
            console.error('ERROR: transfer failed:', err)
        })
}

function int2le(data)
{
    const b = Buffer.allocUnsafe(8);
     b[0] = data & 0xFF;
     b[1] = (data >> 8) & 0xFF;
     b[2] = (data >> 16) & 0xFF;
     b[3] = (data >> 24) & 0xFF;
     b[4] = 0; // TODO: handle 64bits in javascript joy
     b[5] = 0;
     b[6] = 0;
     b[7] = 0;
     return b;
}

async function transferutxo(to, amount, cmd) {
    if (!cmd.auth && !cmd.save) {
        console.error("ERROR: No authenticating EOS account. Use --auth <account> or --save to save for relay.")
        return
    }

    let memo = cmd.memo || ''

    await init();

    if (to === 'new') {
        try {
            to = await wallet.createKey()
            console.log(`Generated new key ${to}`)
        } catch (err) {
            console.error('ERROR: Failed to generate new key. (locked wallet?)')
            return
        }
    }

    let outputs = []

    if(PublicKey.isValid(to, Config.eos_conn_info.keyPrefix)) { //When transferring to a valid address, `account` in output is '' 
        outputs.push({ pk:to, account: '', quantity: amount })
    } else {
        // When transferring to an account, `account` in the output is the account name; 
        // the pk here can be specified at will, and the token will not be transferred to this address.
        outputs.push({ pk:'XST6MRyAjQq8ud7hVNYcfnVPJqcVpscN5So8BhtHuGYqET5GDW5CV', account: to, quantity: amount })
    }

    let amountNum = getAmount(amount)
    if (amountNum <= 0) {
        console.log("ERROR: Nothing to send")
        return
    }

    let ret = await getWalletUTXOForAmount(amountNum) //Make up a set of addresses with so many balances
    let utxos = ret[0]
    let change = ret[1] - amountNum
    console.log("tip: utxos:", utxos)
    console.log("tip: change:", change)

    if (change > 0) { //Need to change
        let changeAddress = await wallet.createKey()
        outputs.push({ pk:changeAddress, account:"", quantity: `${change.toFixed(4)} `+ Config.contract_info.symbol })
    }

    if (change < 0) {
        console.log('ERROR: Insufficient balance')
        return
    }

    let buf = eos.fc.toBuffer('uint8', outputs.length)
    for (o of outputs) {
        buf = Buffer.concat([buf, 
            eos.fc.toBuffer('public_key', o.pk), 
            eos.fc.toBuffer('name', o.account), 
            eos.fc.toBuffer('asset', o.quantity)])
    }

    let outputDigest = fixBufferEndianForEOS(sha256(buf, 'binary'))

    let utxoIds = []
    await Promise.map(utxos, async (u)=>{
        let buf = Buffer.concat([int2le(u.id), outputDigest])
        let digest = sha256(buf)   //Summary

        let sig = await wallet.signDigest(digest, u.pk) //signature
        
        utxoIds.push({
            id: u.id,
            sig 
        })
    })
    
    console.assert(change >= 0, "Negative change! " + change)

    let tranferAction = makeTransferAction(cmd.auth || '', utxoIds, outputs, memo)

    if (cmd.auth) {
        let key = await getActiveKey(cmd.auth)
        if (!key) {
            console.error("ERROR: Can't find key for account:", cmd.auth)
            return
        }
        Config.active_public_key = key
    
        await eos.transaction({ actions: [tranferAction] })
            .then(async (ret) => {
                console.log('Transfer success (Id: ' + ret.transaction_id + ' )');
            })
            .catch((err) => {
                console.log('ERROR: transfer failed:', err)
            })
    } else {
        console.log(JSON.stringify(tranferAction))
    }
}

async function relayAction(auth, action) {
    if (!auth) {
        console.error("ERROR: No authenticating EOS account.")
        return
    }

    if (!action) {
        console.error("ERROR: No action.")
        return
    }

    let actionJson

    try {
        actionJson = JSON.parse(action)
        actionJson.data.payer = auth
        actionJson.authorization[0].actor = auth    
    } catch (err) {
        console.error('ERROR: Action not valid: ', err.message)
        return
    }

    await init();

    let key = await getActiveKey(auth)
    if (!key) {
        console.error("ERROR: Can't find key for account:", auth)
        return
    }
    Config.active_public_key = key

    await eos.transaction({ actions: [actionJson] })
        .then(async (ret) => {
            console.log('Transfer success (Id: ' + ret.transaction_id + ' )');
        })
        .catch((err) => {
            console.log('ERROR: transfer failed:', err)
        })
}

async function serveRelayAction(auth) {
    if (!auth) {
        console.error("ERROR: No authenticating EOS account.")
        return
    }

    await init();

    let key = await getActiveKey(auth)
    if (!key) {
        console.error("ERROR: Can't find key for account:", auth)
        //return
    }
    Config.active_public_key = key

    const app = express()

    app.use(function(req, res, next) {
        res.header("Access-Control-Allow-Headers", "Origin, X-Requested-With, Content-Type, Accept")
        res.header("Access-Control-Allow-Origin", "*")
        next();
    });

    app.post('/relay', async (req, res) => {
        const msg = req.body
        const action = msg.action

        let actionJson

        try {
            actionJson = JSON.parse(action)
            actionJson.data.payer = auth
            actionJson.authorization[0].actor = auth    
        } catch (err) {
            console.error('ERROR: Action not valid: ', err.message)
            return
        }

        await eos.transaction({ actions: [actionJson] })
        .then(async (ret) => {
            console.log('Transfer success (Id: ' + ret.transaction_id + ' )')
        })
        .catch((err) => {
            console.log('ERROR: transfer failed:', err)
        })


    })

    const port = 8080

    app.listen(port, (e) => {
        if (e) console.error(e)
        else console.log(`Server listening on port ${port}...`)
    });
}

async function tranferAction(from, to, amount, cmd) {
    if (from === 'utxo') {
        await transferutxo(to, amount, cmd)
    } else {
        await loadutxo(from, to, amount)
    }
}

async function getReceiveKey(cmd) {
    if(cmd.reuse) {
        let keys = await wallet.getWalletKeyList();

        for(let key of keys) {
            if((await getUTXOsForKey(key)).length === 0) {
                return key
            }
        }
    }

    return await wallet.createKey()
}

async function getAllAccounts(cmd) {
    let code = cmd.code || 'eosio.token'
    let symbol = cmd.symbol || 'EOS'
    let exclude = (cmd.exclude || '').split(',')
    let keys = await getWalletKeyList();
    // console.log("tip: keys:", keys)

    let sum = 0

    for(let key of keys) {
        let accounts = await getKeyAcount(key) //Obtain the accounts corresponding to the public key
        for(let account of accounts) {
            if (exclude.includes(account)){ //Exclude certain accounts
                continue
            }

            //Get the balance of a token of the specified token contract
            let balance = await getCurrencyBalance(code, account, symbol)
            if (balance.length == 0) {
                balance.push(`0.0000 ${symbol}`)
            }
            let amount = parseFloat(balance[0].split(' ')[0])
            sum += amount
            console.log(account, amount, symbol)
        }
    }

    console.log('Total:', sum)
}

async function _main() {
    headers = await getHttpHeaders()

    program
    .version('0.1', '-v --version')
    .description('UTXO wallet for Snapscale. Learn more at https://xeniro.io')
    .option('-n, --name <wallet>', 'EOS wallet name', config.get('wallet_name'))

    program
    .command('balance')
    .option('-u, --utxo', 'Report all UTXOS')
    .action(async function (cmd) {
        if (cmd.utxo) {
            let utxos = await getOwnedUTXOs() //Get a used address under the management of the wallet
            // console.log(utxos.length)
            console.log('+---------+-------------------------------------------------------+----------------------+')
            console.log('| Id      | Address                                               | Amount               |')
            console.log('+---------+-------------------------------------------------------+----------------------+')
            for (utxo of utxos) {
                console.log(`| ${utxo.id.toFixed(0).padEnd(8)}| ${utxo.pk} | ${utxo.amount.padStart(20)} |`)
            }
            console.log('+---------+-------------------------------------------------------+----------------------+')
        } else {
            let balance = await getWalletBalance()
            console.log(`Wallet balance: ${formatAmount(balance)}`)
        }
    })

    program
    .command('receive')
    .option('-r, --reuse', 'Reuse unsued keys in the wallet')
    .action(async (cmd) => {
        let key = await getReceiveKey(cmd)
        console.log(`Receive address: ${key}`)
    })

    program
    .command('transfer <from> <to> <amount>')
    .option('-a, --auth <account>', 'Authenticating EOS account')
    .option('-s, --save', 'Save the transaction for later relay') //relay, Looks like no use
    .option('-m, --memo <memo>', 'Memo for when sending to accounts')
    .action(tranferAction)

    program
    .command('relay <auth> <action>') //<action>: json format, specifies an action in the calling contract, that is, a function
    .action(relayAction)

    program
    .command('serve <auth>') //Provide http service, listen to port 8080
    .action(serveRelayAction)

    program
    .command('set <variable> <value>')
    .action((variable, value, cmd)=>{
        config.set(variable, value)
    })

    program
    .command('get <variable> ')
    .action((variable, value, cmd)=>{
        console.log(config.get(variable))
    })

    program
    .command('all')
    .option('-s, --symbol <symbol>', 'Token symbol')
    .option('-c, --code <code>', 'Token contract')
    .option('-e, --exclude <accounts>', 'Comma separated accounts to exclude')
    .action((cmd)=>{
        getAllAccounts(cmd)
    })
 
    program.parse(process.argv)    

    if (!program.args.length) program.help();
}

_main();

