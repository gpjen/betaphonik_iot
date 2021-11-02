<?php 

session_start();

$_SESSION = [];
session_encode();
session_destroy();

header("location: login.php");

 ?>