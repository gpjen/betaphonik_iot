<?php 
//suhu_udara kelembapan_udara cahaya suhu_air nutrisi_air ph_air PhDown

include 'koneksi.php';

$sql = mysqli_query($konekdb, "SELECT * FROM sensor_30 ORDER BY id DESC LIMIT 1");
$sensor_30 = mysqli_fetch_array($sql);
$sql = mysqli_query($konekdb, "SELECT * FROM sensor_1j ORDER BY id DESC LIMIT 1");
$sensor_1j = mysqli_fetch_array($sql);

$stokA = $sensor_1j['stok_nutrisiA'];
$stokB = $sensor_1j['stok_nutrisiB'];

$update = $_GET['update'];

switch ($update) {
    case 'suhu_udara':
        echo $sensor_30['suhu_udara'];
        break;
    case 'kelembapan_udara':
        echo $sensor_30['kelembapan_udara'];
        break;
    case 'cahaya':
        echo $sensor_30['cahaya'];
        break;
    case 'suhu_air':
        echo $sensor_30['suhu_air'];
        break;   
    case 'nutrisi_air':
        echo $sensor_1j['sensor_tds'];
        break; 
    case 'ph_air':
        echo $sensor_1j['sensor_ph'];
        break; 
    case 'PhDown':
        echo "
        <span class='float-right'>
        ".$sensor_1j['PhDown']." %
            </span></h4>
        <div class='progress mb-4'>
            <div class='progress-bar' role='progressbar' style='width: ".$sensor_1j['PhDown']."%'
                aria-valuenow='60' aria-valuemin='0' aria-valuemax='100'></div>
        </div>

        ";
        break;
    case 'stok_nutrisiA':
        echo "
	        <span class='float-right'>
		     ".$sensor_1j['stok_nutrisiA']." %
		        </span></h4>
		    <div class='progress mb-4'>
		        <div class='progress-bar bg-info' role='progressbar' style='width: 
		     ".$sensor_1j['stok_nutrisiA']."%'
		            aria-valuenow='80' aria-valuemin='0' aria-valuemax='100'></div>
		    </div>
        	 ";
        break;
    case 'stok_nutrisiB':
        echo "
	        <span class='float-right'>
		     ".$sensor_1j['stok_nutrisiB']." %
		        </span></h4>
		    <div class='progress mb-4'>
		        <div class='progress-bar bg-success' role='progressbar' style='width: 
		     ".$sensor_1j['stok_nutrisiB']."%'
		            aria-valuenow='80' aria-valuemin='0' aria-valuemax='100'></div>
		    </div>
        	 ";
        break;     
    default:
        echo "gagal update nilai";
        break;
}




 ?>