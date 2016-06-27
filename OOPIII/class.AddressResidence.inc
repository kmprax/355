<?php

/**
 * residential address 
 */
class AddressResidence extends Address {
  /**
   * initialization 
   */
  protected function _init() {
    $this->_setAddressTypeId(Address::ADDRESS_TYPE_RESIDENCE);
  }
}