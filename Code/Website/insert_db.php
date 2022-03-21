<!-- <?php
$temperature = $_GET["temperature"];
 echo "$temperature";
 $outdoor = $_GET["outdoor"];
 echo "$outdoor";
?> -->

<?php 
$temperature = $_GET["temperature"];
$outdoor = $_GET["outdoor"];


$servername = "localhost";
$username = "iot_stefano";
$password = "QQcRwpEg/AvPTu[r";
$dbname = "iot_webapp";


// Create connection
$conn = new mysqli($servername, $username, $password, $dbname);
// Check connection
if ($conn->connect_error) {
  die("Connection failed: " . $conn->connect_error);
}

$sql = "INSERT INTO temperature (tempVal, outdoor)
VALUES ($temperature, $outdoor)";


if ($conn->query($sql) === TRUE) {
  echo "New record ";

} else {
  echo "Error: " . $sql . "<br>" . $conn->error;
}

$conn->close();
?>