<?php
class Address{
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
    return 'LOOKUP';
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
}

?>