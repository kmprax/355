<?php

require 'class.address2.inc';
require 'class.Database.inc';

echo '<h2>Instantiating Address</h2>';
$address = new Address;

echo '<h2>Setting properties</h2>';
$address->street_address_1 = '2843 N Ricardo';
$address->city_name = 'Mesa';
$address->state = 'Arizona';
$address->country_name = 'United States of America';
$address->address_type_id = 1;
echo $address;

echo '<h2>Testing Address __construct with an array</h2>';
$address_2 = new Address(array(
  'street_address_1' => '21853 SE 267th ST',
  'city_name' => 'Maple Valley',
  'state' => 'Washington',
  'country_name' => 'United States of America',
));
echo $address_2;