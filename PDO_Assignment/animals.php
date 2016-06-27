<?php
try {
//Instantiate a database object
$dbh = new PDO("mysql:host=localhost; dbname=kpraxel_animals", "kpraxel_user", "*********");
echo "Connected to Database!";
}
catch (PDOException $e) {
echo $e->getMessage();
}
?>
<!DOCTYPE html>
<html lang="en">
  <head>
    <!--
IT355 - AGILEDEVELOPMENT
animals.php PDO Assignment
Author: Kimberly M. Praxel
Date: 6/26/16
-->
    <meta charset="utf-8">
    <meta http-equiv="x-ua-compatible" content="ie=edge">
    <link rel="stylesheet" href="animals.css">
    <meta charset="utf-8">
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <link rel="stylesheet" href="http://maxcdn.bootstrapcdn.com/bootstrap/3.3.6/css/bootstrap.min.css">
    <script src="https://ajax.googleapis.com/ajax/libs/jquery/1.12.2/jquery.min.js"></script>
    <script src="http://maxcdn.bootstrapcdn.com/bootstrap/3.3.6/js/bootstrap.min.js"></script>
    <script>
    function clearform(){
    document.getElementById("animalName").value="";
    document.getElementById("animalType").value="";
    }
    </script>
    <title>PDO Assignment</title>
  </head>
  <body>
         <?php
           $name = '';
           $type = '';
           //Form has been submitted 
           if (isset($_POST['submit'])) {
           //Set variables and create empty variables
           $isValid = true;
           $name = '';
           $type = '';
           //Validate first name
           if (!empty($_POST['animal_name'])) {
           $name = $_POST['animal_name'];
           } else {
           echo '<p>Please enter valid name.</p>';
           $isValid = false;
           $name="";
           }
           //Validate last name  
           if (!empty($_POST['animal_type'])) {
           $type = $_POST['animal_type'];
           } else {
           echo '<p>Please enter valid type.</p>';
           $isValid = false;
           $type ="";
           }
           //Form data is good send to database
           if ($isValid) {
           //Define the query
           $sql = "INSERT INTO `animals`( `animal_name`, `animal_type`) VALUES (:name, :type)";
           //Prepare the statement
           $statement = $dbh->prepare($sql);
           //Bind the parameters
           $statement->bindParam(':type', $type, PDO::PARAM_STR);
           $statement->bindParam(':name', $name, PDO::PARAM_STR);
           //Execute
           $statement->execute();
           }
           }
           ?>
           <!-- Information BOX -->
    <div class="container">
      <div class="panel panel-default">
        <div class="panel-body">
            <h3 class="headerbox">PDO Assignment Due 6/26/16.</h3>
            <h1 class="headerbox">ANIMALS</h1>
        </div>
      </div>
      <!-- ADD ANIMAL FORM  -->
        <div class="panel panel-default">
          <div class="panel-body">
            <div class="row">
                <h1 class="formBox">Add a new Animal.</h1>
                <form method="post">
                  <div class="col-lg-5 col-md-5 col-sm-5">     
                    <label for="animal_name">Enter Name:</label>
                    <input type="text" id="animalName" name="animal_name" placeholder="Animal Name" value="<?php echo $name; ?>">
                  </div>
                  <div class="col-lg-5 col-md-5 col-sm-5">
                    <label for="animal_type">Enter Type:</label>
                    <input type="text" id="animalType"  name="animal_type" placeholder="Animal Type" value="<?php echo $type; ?>">
                  </div>
                  <div class="col-lg-2 col-md-2 col-sm-2">
                  <button type="submit" value="Validate" name="submit" class="btn btn-default">Submit</button>
                  </div>
                </form>
            </div>
          </div>
        </div>
      <!-- LIST ANIMALS IN DATABASE -->
      <div class="panel panel-default">
        <div class="panel-body">
          <div class="row">
            <div class="col-lg-10 col-md-10 col-sm-10">
              <?php 
               $sql = "SELECT animal_name, animal_type FROM animals ORDER BY animal_id";
               //prepare statement
               $statement = $dbh->prepare($sql);
               //execute
               $statement->execute();
               //process the results
               $result = $statement->fetchAll(PDO::FETCH_ASSOC);
               foreach ($result as $row) {
               echo '<ul>';
               echo '<li>' . $row["animal_name"] . " - " . $row["animal_type"] . '</li>';
               echo '</ul>';
               }
               ?>
            </div>
          </div>
        </div>
      </div>
    </div>
    <!-- jQuery first, then Bootstrap JS. -->
    <script src="https://ajax.googleapis.com/ajax/libs/jquery/2.1.4/jquery.min.js"></script>
    <script src="https://maxcdn.bootstrapcdn.com/bootstrap/4.0.0-alpha.2/js/bootstrap.min.js" integrity="sha384-vZ2WRJMwsjRMW/8U7i6PWi6AlO1L79snBrmgiDpgIWJ82z8eA5lenwvxbMV1PAh7" crossorigin="anonymous"></script>
  </body>
</html>
