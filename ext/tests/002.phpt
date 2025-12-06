--TEST--
test1() Basic test
--SKIPIF--
<?php
if (!extension_loaded('swo')) {
    echo 'skip';
}
?>
--FILE--
<?php
$ret = test1();

var_dump($ret);
?>
--EXPECT--
The extension swo is loaded and working!
NULL
