<?php
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

    $sql = "SELECT * FROM `temperature`";
    $result = $conn->query($sql);

    $data = array();
    $temperature = array();
    $outdoor = array();
    $time = array();

    if ($result->num_rows > 0) {
    // output data of each row
        while($row = $result->fetch_assoc()) {
            //echo $row["time"] . " " . $row["tempVal"];
            //$data[] = $row;
            $temperature[] = $row["tempVal"];
            $outdoor[] = $row["outdoor"];
            $time[] = $row["time"];
        }
    } else {
        echo "0 results";
    }
    $conn->close();

    $data["time"] = $time;
    $data["temperature"] = $temperature;
    $data["outdoor"] = $outdoor;
   

    print_r(json_encode($data));
?>