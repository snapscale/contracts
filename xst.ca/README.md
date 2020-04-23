# 命令演示
## 以合约部署账号为 xst.ca 为例, 测试使用的密钥对
xst.ca的密钥对

``` Private key: 5KF5jtD8QGKpypuT3HLDYjDiVTzrLvkYiEb2XXtxwabty87m9ib ```
``` Public key: XST71cZdtoJbJyC89sTpUCa14nMCKMv95QzWSZdUKo9FcbusJxy9A ```

## 合约总共有6种action

### 示例中的公钥与签名可以任意替换

### 1. addmem  提出申请
A账号

```cleos push action xst.ca addmem '["alice", "XST83jABXUkPLcpeA5fbgKfokdd5YSP6k6n87wpYrApfW7rY9MqT6", "'city':'shagnhai','org':'chinamobile','location':'100,100'"]' -p xst.ca@active ```

B账号

```cleos push action xst.ca addmem '["xst.ca", "XST6MRyAjQq8ud7hVNYcfnVPJqcVpscN5So8BhtHuGYqET5GDW5CV", "'city':'shagnhai','org':'chinamobile','location':'100,100'"]' -p xst.ca@active ```

### 2. addcert 审核通过

``` cleos push action xst.ca addcert '["XST83jABXUkPLcpeA5fbgKfokdd5YSP6k6n87wpYrApfW7rY9MqT6","SIG_K1_KgEqhABVTZABrPYquh5dch63oo7x2ipbwkfCRKE3w1RgSVAx4M8Q4yyfNZavqc176vk5yU9hsppFev1CtWERXx6i4su8eQ"]' -p xst.ca@active ```

### 3. addcrl  加入黑名单

``` cleos push action xst.ca addcrl '["XST5z8Yc9tUj1naSnYPf49XE644bRib6VP3yFM8w9SQ7SHKsrCSNQ"]' -p xst.ca@active ```

### 4. delmem 删除申请记录 (test)
```  cleos push action xst.ca delmem '["XST83jABXUkPLcpeA5fbgKfokdd5YSP6k6n87wpYrApfW7rY9MqT6"]' -p xst.ca@active ```

### 5. delcrl  移除黑名单
```  cleos push action xst.ca delcrl '["XST83jABXUkPLcpeA5fbgKfokdd5YSP6k6n87wpYrApfW7rY9MqT6"]' -p xst.ca@active ```

### 6.changestatus ---- status will change to 1 when addcert 
- 0: 未审核
- 1: 审核通过
- 2: 审核不通过

审核不通过:<br>
``` cleos push action xst.ca changestatus '["XST6MRyAjQq8ud7hVNYcfnVPJqcVpscN5So8BhtHuGYqET5GDW5CV",2]' -p xst.ca@active ```


## gen cert --- need to build develop branch  命令行手工产生数字证书: 申请人的公钥, CA的私钥
``` cleos wallet sign_digest XST8F1RkBYUvCmDmwBHLczq4PZxW28zdW924SjRKX6YEpuBfYuqqP 5KF5jtD8QGKpypuT3HLDYjDiVTzrLvkYiEb2XXtxwabty87m9ib ```

### BP shanghai cert
Private key:  5KFEBbBDtoX7HYM5EfxwYBKdCw6WyriSN7kaEntAKrS14pc4Wzp

Public key: XST75HoYWnMqzhP32wWK7qbKDkKeMgVKAWxJ3fKmkmrjmtb4cxE99
 
``` DC: SIG_K1_KBwUJu2wQGjNrTzBE2VP396ZRNQZqMBv6SXssifhbGXpE8H9T8AFqZ6kRricSK4uko6eFWUrnbUdcrrgkdf5ahJBL4zxNE ```
### BP london cert
Private key: 5J8mCauA6qTZnwUquueG4KpaEvAJ5PU1XT7MbNn5KAnqqMokcLm

Public key: XST68j2daS754PsCC6miwd94ECT4DZP8tb6W1pSDX9UdG5yxgdFAo

``` DC: SIG_K1_KXVQ34yLTFHwonmsRkKFTF1bCb7Xt2f4363dPgYecAppMQ5MDnAFshq8wpHDf9adArkawAUJCiiupsxecA7kPh5i3Fcr2y ```

### BP newyork cert
Private key: 5KiqJnwqCBUecmDEpeD691z9TribXpak5a5Hr6g55A692ufQ937

Public key: XST8F1RkBYUvCmDmwBHLczq4PZxW28zdW924SjRKX6YEpuBfYuqqP

``` DC: SIG_K1_KVd76ycEAzuuWQA98pPSrnXTVG4NY7Q667smrnT4h4y9naTBzsqTLov6WoyFbBXKAwLN2EqiefRxtTmFjBUTQXb6FmnWL5 ```

### Api one :
Private key: 5J75daXKsAESNuPffb7kxeHsGXZmAKDbzSsWrR2tQyzTcuwu5SY

Public key: XST83jABXUkPLcpeA5fbgKfokdd5YSP6k6n87wpYrApfW7rY9MqT6

``` DC: SIG_K1_K5VCusVxRvRbk25YK5zdvm42B7KnRWba4KBbxnekMabK7DiEvykSYEjAci3sN1zmFso1tTjELpkr4bEQcDcViEnKXt99MN ```


### Api two:
Private key: 5K8jggGd1iEqHVUXCHd3z3uvFHgCXvQbveRrM3wKDp3YvLL5f2T

Public key: XST5z8Yc9tUj1naSnYPf49XE644bRib6VP3yFM8w9SQ7SHKsrCSNQ

``` DC: SIG_K1_KhiiSy1uukNfNKc1K1LpjuFPFjCxEM5yqQ3xYwTXRxiDMHPUNhVfcvfbRgyCZWGNuwXR8qQ25kPmCrWNPghiwofYynNB46 ```
