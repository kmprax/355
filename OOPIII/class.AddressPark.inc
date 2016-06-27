<?php

/**
 * park address
 */
class AddressPark extends Address {
  public function display() {
    $output = '<div style="background-color:PaleGreen;">';
    $output .= parent::display();
    $output .= '</div>';
    return $output;
  }
  
  
  /**
   * initialization 
   */
  protected function _init() {
    $this->_setAddressTypeId(Address::ADDRESS_TYPE_PARK);
  }
}