<?php


$data = file_get_contents("nl80211attr.txt");

$values = explode(",",$data);

echo "/*
 Generated by php
 Do not modify
*/
";


echo "char nlt_attrname[] = {\n";
$c="";
foreach($values as $val){
	echo $c.'"'.trim($val).'"';
	$c=",\n";

}
echo "\n};";