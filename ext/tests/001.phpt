--TEST--
Check if swo is loaded
--SKIPIF--
<?php
if (!extension_loaded('swo')) {
    echo 'skip';
}
?>
--FILE--
<?php
echo 'The extension "swo" is available';
?>
--EXPECT--
The extension "swo" is available
