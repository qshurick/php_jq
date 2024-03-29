--TEST--
Simple JQ integration
--EXTENSIONS--
php_jq
--FILE--
<?php
use Qshurick\Jq\Jq;

$jq = new Jq();

$json = json_encode([
    "id" => 42,
    "flag" => true,
    "list" => [1, 2, 3, 4],
    "hello" => "world",
]);

var_dump($jq->transform(".", $json));
var_dump($jq->transform(".id", $json));
var_dump($jq->transform(".list|map(.*2)", $json));
?>
--EXPECT--
string(54) "{"id":42,"flag":true,"list":[1,2,3,4],"hello":"world"}"
string(2) "42"
string(9) "[2,4,6,8]"
