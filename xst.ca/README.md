# 命令演示
## 以合约部署账号为 xst.ca 为例, 测试使用的密钥对
xst.ca的密钥对

``` Private key: 5KF5jtD8QGKpypuT3HLDYjDiVTzrLvkYiEb2XXtxwabty87m9ib ```
``` Public key: XST71cZdtoJbJyC89sTpUCa14nMCKMv95QzWSZdUKo9FcbusJxy9A ```

## 合约总共有6种action

### 示例中的公钥与签名可以任意替换

### 往CRL合约中加入某个客户端的公钥hash值

```sh
# 从客户端证书中提取出客户端的公钥文件
openssl x509 -in ca/client-cert.pem -pubkey  -noout > ca/client-pubkey.pem

# hash
sha256sum ca/client-pubkey.pem
  #	79fc3ca87dac873243c8955e67ef5b29116517dd64f4d866010af30decd7b63d

#加CRL
cleos push action xst.ca addcrl '{"pk_hash":"79fc3ca87dac873243c8955e67ef5b29116517dd64f4d866010af30decd7b63d"}' -p xst.ca@active

#删CRL
cleos push action xst.ca delcrl '{"pk_hash":"79fc3ca87dac873243c8955e67ef5b29116517dd64f4d866010af30decd7b63d"}' -p xst.ca@active

#查看
cleos get table xst.ca xst.ca crls
```

