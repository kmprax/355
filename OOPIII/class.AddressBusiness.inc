<?php

/**
 * business address. 
 */
class AddressBusiness extends Address {
  /**
   * initialization
   */
  protected function _init() {
    $this->_setAddressTypeId(Address::ADDRESS_TYPE_BUSINESS);
  }
}