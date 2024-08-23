![deprecated](https://img.shields.io/badge/-deprecated-inactive)

# 4d-plugin-simple-postgres-client

Simple PostgreSQL client.

### Platform

| carbon | cocoa | win32 | win64 |
|:------:|:-----:|:---------:|:---------:|
||<img src="https://cloud.githubusercontent.com/assets/1725068/22371562/1b091f0a-e4db-11e6-8458-8653954a7cce.png" width="24" height="24" />|<img src="https://cloud.githubusercontent.com/assets/1725068/22371562/1b091f0a-e4db-11e6-8458-8653954a7cce.png" width="24" height="24" />|<img src="https://cloud.githubusercontent.com/assets/1725068/22371562/1b091f0a-e4db-11e6-8458-8653954a7cce.png" width="24" height="24" />|

### Version

<img width="32" height="32" src="https://user-images.githubusercontent.com/1725068/73986501-15964580-4981-11ea-9ac1-73c5cee50aae.png"> <img src="https://user-images.githubusercontent.com/1725068/73987971-db2ea780-4984-11ea-8ada-e25fb9c3cf4e.png" width="32" height="32" />

### Examples

```
  //most easy
$connect:="user=miyako dbname=postgres"
$SQL:="SELECT * FROM users"
ARRAY TEXT($rows;0)

$errorMessage:=PQ EXECUTE ($connect;$SQL;$rows)

  //the result is an array of json
ARRAY OBJECT($results;0)
For ($i;1;Size of array($rows))
APPEND TO ARRAY($results;JSON Parse($rows{$i}))
End for 

  //using parameters 
$SQL:="SELECT * FROM users WHERE email=$1"
ARRAY TEXT($params;1)
$params{1}:="hoge@hoge.com"
$errorMessage:=PQ EXECUTE ($connect;$SQL;$rows;$params)

ARRAY OBJECT($results;0)
For ($i;1;Size of array($rows))
APPEND TO ARRAY($results;JSON Parse($rows{$i}))
End for 

  //example of binary (base64)
$errorMessage:=PQ EXECUTE ($connect;$SQL;$rows;$params;PQ_RESULT_BINARY)

ARRAY OBJECT($results;0)
For ($i;1;Size of array($rows))
APPEND TO ARRAY($results;JSON Parse($rows{$i}))
  //each field is an object, 
  //e.g. {"id":{"data":"AAAAAQ=="},"username":{"data":"aG9nZQ=="},"email":{"data":"aG9nZUBob2dlLmNvbQ=="}}
End for 
```
