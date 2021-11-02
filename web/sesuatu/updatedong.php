<?php 
		include 'koneksi.php';


	if (!isset($_GET['status'])) {
		header("location: ../404.html");
	}



	if (isset($_GET['status'])) {

		if ($_GET['status'] == 'aktif'){

			//  /sesuatu/updatedong.php?status=aktif&waktu=12:09&ppm=1009&ph=1219&sair=31&cahaya=180&kel=89&sudara=34&stoka=70&stokb=74&stokphdown=98

			if (!isset($_GET['waktu'])  || !isset($_GET['ppm']) || !isset($_GET['ph']) || !isset($_GET['sair']) || !isset($_GET['cahaya']) || !isset($_GET['kel']) || !isset($_GET['sudara']) || !isset($_GET['stoka']) || !isset($_GET['stokb']) || !isset($_GET['stokphdown'])){

				echo "<br><br><center><h1>ngapain lu, data lu seng lengkap.</h1></center>";

			} else {

				$status 	= "Sistem Aktif";
				$waktu 		= $_GET['waktu'];
				$ppm 		= $_GET['ppm'];
				$ph 		= $_GET['ph'];
				$Sair 		= $_GET['sair'];
				$cahaya 	= $_GET['cahaya'];
				$kelembapan	= $_GET['kel'];
				$Sudara 	= $_GET['sudara'];
				$stokA 		= $_GET['stoka'];
				$stokB 		= $_GET['stokb'];
				$stokPHdown	= $_GET['stokphdown'];

				$ppmStatus 	= "SISTEM AKTIF" ;
				$phStatus 	= "SISTEM AKTIF";

				$sql = "INSERT INTO `sensor_30` VALUES (NULL, '$waktu', CURDATE(), '$Sudara', '$kelembapan', '$cahaya', '$Sair');";
	    		$hasil = mysqli_query($konekdb, $sql);

	    		$sql = "INSERT INTO `sensor_1j` VALUES (NULL, '$waktu', CURDATE(), '$ppm', '$ph', '$stokPHdown', '$stokA', '$stokB');";
	    		$hasil = mysqli_query($konekdb, $sql);

	    		$sql = "INSERT INTO `statuskendali` VALUES (NULL, '$waktu', CURDATE(), '$ppmStatus', '$phStatus');";
	    		$hasil = mysqli_query($konekdb, $sql);
			}



		} elseif ($_GET['status'] == 'up1m') {

			//  /sesuatu/updatedong.php?status=up1m&waktu=12:09&sair=29&cahaya=99&kel=89&sudara=39

			if (!isset($_GET['waktu'])  || !isset($_GET['sair']) || !isset($_GET['cahaya']) || !isset($_GET['kel']) || !isset($_GET['sudara'])){

				echo "<br><br><center><h1>ngapain lu, data lu seng lengkap..</h1></center>";

			} else {

				$status 	= "Update Sensor 1 Menit";
				$waktu 		= $_GET['waktu'];
				$Sair 		= $_GET['sair'];
				$cahaya 	= $_GET['cahaya'];
				$kelembapan	= $_GET['kel'];
				$Sudara 	= $_GET['sudara'];

				$sql = "INSERT INTO `sensor_30` VALUES (NULL, '$waktu', CURDATE(), '$Sudara', '$kelembapan', '$cahaya', '$Sair');";
	    		$hasil = mysqli_query($konekdb, $sql);

			}
			
			
		} elseif ($_GET['status'] == 'up1jam') {

			// /sesuatu/updatedong.php?status=up1jam&waktu=12:09&ppm=1009&ppmStatus= ppm masih bisa di atur bang&ph=5.9&phStatus= lha emang ngapa kagak boleh&stoka=10&stokb=11&stokphdown=12

			if (!isset($_GET['waktu'])  || !isset($_GET['ppm']) || !isset($_GET['ppmStatus']) || !isset($_GET['ph']) || !isset($_GET['phStatus']) || !isset($_GET['stoka']) || !isset($_GET['stokb']) || !isset($_GET['stokphdown'])){

				echo "<br><br><center><h1>ngapain lu, data lu seng lengkap...</h1></center>";

			} else {

				$status 	= "Update Sensor 1 Jam";
				$waktu 		= $_GET['waktu'];
				$ppm 		= $_GET['ppm'];
				$ppmStatus 	= $_GET['ppmStatus'];
				$ph 		= $_GET['ph'];
				$phStatus 	= $_GET['phStatus'];
				$stokA 		= $_GET['stoka'];
				$stokB 		= $_GET['stokb'];
				$stokPHdown	= $_GET['stokphdown'];



				$sql = "INSERT INTO `sensor_1j` VALUES (NULL, '$waktu', CURDATE(), '$ppm', '$ph', '$stokPHdown', '$stokA', '$stokB');";
	    		$hasil = mysqli_query($konekdb, $sql);

				$sql = "INSERT INTO `statuskendali` VALUES (NULL, '$waktu', CURDATE(), '$ppmStatus', '$phStatus');";
	    		$hasil = mysqli_query($konekdb, $sql);

			}

		} elseif ($_GET['status'] == 'deet') {

			//  ?status=deet&waktu=1:50:44


			if (!isset($_GET['waktu'])){

				echo "<br><br><center><h1>ngapain lu, data lu seng lengkap...</h1></center>";

			} else {

				$status 	= "WAKTU OFF";
				$waktu 		= $_GET['waktu'];
				$ppmStatus 	= "SISTEM TIDAK AKTIF";
				$phStatus 	= "SISTEM TIDAK AKTIF";


				$sql = "INSERT INTO `statuskendali` VALUES (NULL, '$waktu', CURDATE(), '$ppmStatus', '$phStatus');";
	    		$hasil = mysqli_query($konekdb, $sql);

			}
			
			
		}

	}

 ?>
