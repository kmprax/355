<?php
class Address{
    
    const ADDRESS_TYPE_RESIDENCE = 1;
    const ADDRESS_TYPE_BUSINESS = 2;
    const ADDRESS_TYPE_PARK = 3;
    
    //address types
    static public $valid_address_types = array(
      Address::ADDRESS_TYPE_RESIDENCE => 'Residence',
      Address::ADDRESS_TYPE_BUSINESS => 'Business',
      Address::ADDRESS_TYPE_PARK => 'Park',
    );
    
    
    //street address
    public $street_address_1;
    public $street_address_2;
    
    //name of city
    public $city_name;
    
    //name of state
    public $state;
    
    //postal code
    protected $_postal_code;
    
    //name of country
    public $country_name;
    
    //primary key for address
    protected $_address_id;
    
    //address type id
    protected $_address_type_id;
    
    //when record was created and updated last
    protected $_time_created;
    protected $_time_updated;
    
    
  /**
   * constructor
   * @param array $data optional array of property names and values
   */
  function __construct($data = array()) {
    $this->_time_created = time();
    
    //ensure that the Address can be populated
    if (!is_array($data)) {
      trigger_error('Unable to construct address with a ' . get_class($name));
    }
    
    //if there is at least one value, populate the Address with it
    if (count($data) > 0) {
      foreach ($data as $name => $value) {
        // Special case for protected properties.
        if (in_array($name, array(
          'time_created',
          'time_updated',
        ))) {
          $name = '_' . $name;
        }
        $this->$name = $value;
      }
    }
  }
    
    
  /**
   * Magic __get
   * @param string $name 
   * @return mixed
   */
  
  function __get($name) {
    //postal code lookup if unset
    if (!$this->_postal_code) {
      $this->_postal_code = $this->_postal_code_guess();
    }
    
    //attempt to return a protected property by name
    $protected_property_name = '_' . $name;
    if (property_exists($this, $protected_property_name)) {
      return $this->$protected_property_name;
    }
    
    //unable to access property; trigger error.
    trigger_error('Undefined property via __get: ' . $name);
    return NULL;
  }
  
  
  /**
   * Magic __set
   * @param string $name
   * @param mixed $value 
   */
  function __set($name, $value) {
    // only set valid address type id
    if ('address_type_id' == $name) {
      $this->_setAddressTypeId($value);
      return;
    }
    
    //allow anything to set the postal code
    if ('postal_code' == $name) {
      $this->$name = $value;
      return;
    }
    
    //unable to access property; trigger error
    trigger_error('Undefined or unallowed property via __set(): ' . $name);
  }
  
  
  /**
   * Magic __toString
   * @return string 
   */
  function __toString() {
    return $this->display();
  }
  
  
  /**
   * will guess postal code given state and city name
   * @todo replace with a database look up
   * @return string
   */
  protected function _postal_code_guess() {
    $db = Database::getInstance();
    $mysqli = $db->getConnection();
    
    $sql_query  = 'SELECT postal_code ';
    $sql_query .= 'FROM location ';
    
    $city_name = $mysqli->real_escape_string($this->city_name);
    $sql_query .= 'WHERE city_name = "' . $city_name . '" ';
    
    $state = $mysqli->real_escape_string($this->state);
    $sql_query .= 'AND state = "' . $state . '" ';
    
    $result = $mysqli->query($sql_query);
    
    if ($row = $result->fetch_assoc()) {
      return $row['postal_code'];
    }
  }
  
    
    /**
     * Display an address in HTML
     * @return string
     */
    
    function display(){
        $output = "";
        
            //street address
            $output .= $this->street_address_1;
            if ($this->street_address_2) {
              $output .= '<br/>' . $this->street_address_2;
            }
            
            //city, state, postal.
            $output .= '<br/>';
            $output .= $this->city_name . ', ' . $this->state;
            $output .= ' ' . $this->postal_code;
            
            //country.
            $output .= '<br/>';
            $output .= $this->country_name;
            
            return $output;
        
    }
    
    /**
     * determine if an address type is valid or not
     * @param int $address_type_id
     * @return boolean
     */
    static public function isValidAddressTypeId($address_type_id) {
      return array_key_exists($address_type_id, self::$valid_address_types);
    }
    
    /**
     * if valid set the address type id
     * @param int $address_type_id 
     */
    protected function _setAddressTypeId($address_type_id) {
      if (self::isValidAddressTypeId($address_type_id)) {
        $this->_address_type_id = $address_type_id;
      }
    }
    
}

?>