<?php

$file1 = dirname(__FILE__)."/datasets/1000Points/3557.txt";
$file2 = dirname(__FILE__)."/datasets/10000Points/5075.txt";

$trajectory1Lat = [];
$trajectory1Lng = [];
$trajectory2Lat = [];
$trajectory2Lng = [];

if ( ($handle = fopen($file1, "r")) !== FALSE) {
  while (($data = fgetcsv($handle, 1000, ",")) !== FALSE) {
    $num = count($data);
    $trajectory1Lat[] = $data[$num-2];
    $trajectory1Lng[] = $data[$num-1];
  }
}

if ( ($handle = fopen($file2, "r")) !== FALSE) {
  while (($data = fgetcsv($handle, 10000, ",")) !== FALSE) {
    $trajectory2Lat[] = $data[$num-2];
    $trajectory2Lng[] = $data[$num-1];
  }
}

/* You can include delta parameter here if you want to control how far in time algorithm could go in order to match a given point from one trajectory to a point in another trajectory.*/
$lcss = new LCSS(0.05); 
echo $lcss->findSimilarity($trajectory1Lat, $trajectory1Lng, $trajectory2Lat, $trajectory2Lng);

