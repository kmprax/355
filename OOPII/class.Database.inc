<?php

/**
 * MySQLi database; only one connection is allowed 
 */
class Database {
  private $_connection;
  // Store the single instance.
  private static $_instance;
  
  
  /**
   * get an instance of the database
   * @return database 
   */
  public static function getInstance() {
    if (!self::$_instance) {
      self::$_instance = new self();
    }
    return self::$_instance;
  }
  
  /**
   * constructor 
   */
  public function __construct() {
    $this->_connection = new mysqli('localhost', 'kpraxel_user', 'password', 'kpraxel_lynda');
    // Error handling.
    if (mysqli_connect_error()) {
      trigger_error('Failed to connect to MySQL: ' . mysqli_connect_error(), E_USER_ERROR);
    }
  }
  
  /**
   * empty clone magic method to prevent duplication 
   */
  private function __clone() {}
  
  /**
   * get the mysqli connection 
   */
  public function getConnection() {
    return $this->_connection;
  }
}