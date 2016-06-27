<?php

/**
 * shared interface for interactions 
 */
interface Model {
  /**
   * load model
   * @param int $address_id 
   */
  static function load($address_id);
  
  /**
   * save model 
   */
  function save();
}