--TEST--
\Solarwinds\Sampler\setting() Basic test
--EXTENSIONS--
swo
--INI--
swo.service_key=PwgwKsUjyYk05D566SzV1sGFrxT_PnS4ra3ewducWRu54auIIcxKcpUDH3cPtKJoRvtQK4A:ext-swo
--FILE--
<?php
$ret = \Solarwinds\Sampler\setting();
var_dump(strlen($ret) == 0);

sleep(1);

$ret = \Solarwinds\Sampler\setting();
var_dump(strlen($ret) > 0);
var_dump($ret);
?>
--EXPECT--
bool(true)
bool(true)