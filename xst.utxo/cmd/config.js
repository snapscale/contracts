
module.exports = {

    eos_conn_info : {
        httpEndpoint: 'http://127.0.0.1:8888', // private Testnet
        // httpEndpoint: 'https://api.jungle.alohaeos.com', // Jungle Testnet
        // httpEndpoint: 'https://eos.greymass.com', // mainnet
        chainId: 
        //private Testnet
            'cf057bbfb72640471fd910bcb67639c22df9f92470936cddc1ade0e2f2e7dc4f',
        //Jungle
            // 'e70aaab8997e1dfce58fbfac80cbbb8fecec7b99cf982a9444273cbc64c41473',
        //mainnet
            // 'aca376f206b8fc25a6ed44dbdc66547c36c6c33e3a119ffbeaef943642f0e906',

        keyProvider : [],
        sign        : true,
        broadcast   : true,
        expireInSeconds: 60,
        keyPrefix : 'XST',
        
        sender_pk : 'XST83jABXUkPLcpeA5fbgKfokdd5YSP6k6n87wpYrApfW7rY9MqT6',
        sender_dc : 'SIG_K1_K5VCusVxRvRbk25YK5zdvm42B7KnRWba4KBbxnekMabK7DiEvykSYEjAci3sN1zmFso1tTjELpkr4bEQcDcViEnKXt99MN',
        receiver_pk : 'XST83jABXUkPLcpeA5fbgKfokdd5YSP6k6n87wpYrApfW7rY9MqT6' 
    },

    wallet_URL: 'http://unix:~/eosio-wallet/keosd.sock:',

    active_public_key : '',
    
    contract_info: {
        code: 'xst.utxo', //private testnet
        symbol: 'UTXO'
    },

}
