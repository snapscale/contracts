
const eosEcc = require('eosjs-ecc')

gencert()

function gencert(){
    rootPrivS = '5KF5jtD8QGKpypuT3HLDYjDiVTzrLvkYiEb2XXtxwabty87m9ib';

    // 替换这个地址
    pks = 'XST83jABXUkPLcpeA5fbgKfokdd5YSP6k6n87wpYrApfW7rY9MqT6';

    let rootPriv = eosEcc.PrivateKey(rootPrivS);
    console.log('CA rootPriv: ' + rootPriv);


    let pk = eosEcc.PublicKey(pks, 'XST').toBuffer();
    // console.log('EOS pk: ' + pk);
    // console.log('EOS pk: ' + eosEcc.PublicKey(pks).toString());

    let digest =eosEcc.sha256(pk,'hex');

    console.log(' digest: ' + digest);

    let signature = eosEcc.signHash(digest,rootPriv).toString();
    console.log('pk DC: ' + signature);
}


