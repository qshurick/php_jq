--TEST--
Exception mapping
--EXTENSIONS--
php_jq
--FILE--
<?php

use Qshurick\Jq\Jq;

$jq = new Jq();
$json = json_encode(["id" => 42, "flag" => true, "list" => [0, 1, 2, 3], "hello" => "world"]);

$dataProvider = [
    "invalid program" => [":", $json],
    "invalid json" => [".", ".{}"],
    "invalid transformation" => [".list|map(1/.)", $json],
];

foreach ($dataProvider as $title => [$program, $jsonString]) {
    try {
        $result = $jq->transform($program, $jsonString);
        var_dump($result);
    } catch (\Throwable $exception) {
        var_dump(get_class($exception));
    }
}

?>
--EXPECT--
string(35) "Qshurick\Jq\InvalidProgramException"
string(38) "Qshurick\Jq\InvalidJsonStringException"
string(36) "Qshurick\Jq\UnableTransformException"

