<?php

require 'class.address.inc';

echo '<h2>Instantiating Address</h2>';
$address = new Address;

echo '<h2>Empty Address</h2>';
echo '<tt><pre>' . var_export($address, TRUE) . '</pre></tt>';

echo '<h2>Setting properties</h2>';
$address->street_address_1 = '2843 N Ricardo';
$address->city_name = 'Mesa';
$address->state = 'Arizona';
$address->postal_code = '85215';
$address->country_name = 'United States of America';
echo '<tt><pre>' . var_export($address, TRUE) . '</pre></tt>';

echo '<h2>Displaying address</h2>';
echo $address->display();

echo '<h2>Testing magic __get and __set</h2>';
unset($address->postal_code);
echo $address->display();

echo '<h2>Testing Address __construct with an array</h2>';
$address_2 = new Address(array(
  'street_address_1' => '2304 N 77th Place',
  'city_name' => 'Mesa',
  'state' => 'Arizona',
  'postal_code' => '85207',
  'country_name' => 'United States of America',
));
echo $address_2->display();

echo '<h2>Address __toString</h2>';
echo $address_2;
