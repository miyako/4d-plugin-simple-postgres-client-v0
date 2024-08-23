![version](https://img.shields.io/badge/version-16%2B-8331AE)
![platform](https://img.shields.io/static/v1?label=platform&message=mac-intel%20|%20win-32%20|%20win-64&color=blue)
![deprecated](https://img.shields.io/badge/-deprecated-inactive)

# 4d-plugin-simple-postgres-client-v0

Simple PostgreSQL client

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
