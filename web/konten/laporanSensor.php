
<?php 

	if (isset($_POST['carilaporsensor'])) {
		$waktu = $_POST['tanggallaporSensor'];
	}else{
		$waktu = date("Y-m-d");
	}

	//ppm
	$s1j 	= mysqli_query($konekdb, "
		SELECT 
		MAX(sensor_tds) AS tdsMax, MIN(sensor_tds) AS tdsMin, AVG(sensor_tds) AS tdsAVG, 
		MAX(sensor_ph) AS phMax, MIN(sensor_ph) AS phMin, AVG(sensor_ph) AS phAVG 
		FROM sensor_1j WHERE tanggal='$waktu'");

	$s1j 	= mysqli_fetch_array($s1j);
	$ppmMax = $s1j['tdsMax'];
	$ppmMin = $s1j['tdsMin'];
	$ppmAVG = round($s1j['tdsAVG'],1);

	$phMax	= $s1j['phMax'];
	$phMin	= $s1j['phMin'];
	$phAVG	= round($s1j['phAVG'],2);

	//suhu air, suhu udara, kelembapan, cahaya
	$s30 		= mysqli_query($konekdb, "
		SELECT 
		MAX(suhu_air) AS sairMax, MIN(suhu_air) AS sairMin, AVG(suhu_air) AS sairAVG, 
		MAX(suhu_udara) AS saudMax, MIN(suhu_udara) AS saudMin, AVG(suhu_udara) AS saudAVG, 
		MAX(kelembapan_udara) AS kelMax, MIN(kelembapan_udara) AS kelMin, AVG(kelembapan_udara) AS kelAVG, 
		MAX(cahaya) AS cahayaMax, MIN(cahaya) AS cahayaMin, AVG(cahaya) AS cahayaAVG   
		FROM sensor_30 WHERE tanggal='$waktu'");

	$s30 		= mysqli_fetch_array($s30);
	$sairMax 	= $s30['sairMax'];
	$sairMin 	= $s30['sairMin'];
	$sairAVG 	= round($s30['sairAVG'],1);

	$saudMax 	= $s30['saudMax'];
	$saudMin 	= $s30['saudMin'];
	$saudAVG 	= round($s30['saudAVG'],1);

	$kelMax 	= $s30['kelMax'];
	$kelMin 	= $s30['kelMin'];
	$kelAVG 	= round($s30['kelAVG'],1);

	$cahayaMax 	= $s30['cahayaMax'];
	$cahayaMin 	= $s30['cahayaMin'];
	$cahayaAVG 	= round($s30['cahayaAVG'],1);

    

 ?>



<br>
<div class="container" data-aos="fade-right">
<div class="card border-left-success shadow mb-4">
    <div class="card-header py-3">

        <div class="container" ><br>
            <center>
            <h3 class="text-success">LAPORAN SENSOR HARIAN
            </h3><br>

            <form method="POST" class="d-sm-inline-block form-inline ml-md-3 my-2 my-md-0 mw-100">
                <div class="input-group">
                    <input type="date" name="tanggallaporSensor" class="form-control bg-light border-5 small" 
                        aria-label="Search" aria-describedby="basic-addon2" value="<?= $waktu ?>">
                    <div class="input-group-append">
                        <button class="btn btn-success" type="submit" name="carilaporsensor">
                            <i class="fas fa-search fa-sm"></i>
                        </button>
                    </div>
                </div>
            </form>

            </center>
        </div>
    </div><br><br>
    <div class="card-body">

        <div class="table-responsive">

            <table class="table table-hover table-bordered" id="" width="100%" cellspacing="0" style="text-align: center;">
                <thead class="thead-dark">
                    <tr style="font-size: 20px;">
                    	<th>Sensor</th>
                        <th>Minimal</th>
                        <th>Maksimal</th>
                        <th>Rata - Rata</th>
                        <th>Selisih</th>
                    </tr>
                </thead>
                <tbody>

                    <tr">
                    	<th style="padding: 0;" class="bg-success">
                            <a  style="height: 100%;" class="btn btn-success btn-block btn-lg" data-toggle="modal" data-target="#ppmmodalchart">
                                <span class="icon text-white-50 float-left"  >
                                    <i class="far fa-eye"></i>
                                </span>
                                <span class="text">PPM</span>
                            </a>
                        </th>
                    	<td><?= $ppmMin ?></td>
                    	<td><?= $ppmMax ?></td>
                    	<td><?= $ppmAVG ?></td>
                    	<td><?= $ppmMax - $ppmMin ?></td>
                    </tr">

                </tbody>
                <tbody>
                    <tr">
                    	<th style="padding: 0;" class="bg-success">
                            <a style="height: 100%;" class="btn btn-success btn-block btn-lg" data-toggle="modal" data-target="#phmodalchart">
                                <span class="icon text-white-50 float-left"  >
                                    <i class="far fa-eye"></i>
                                </span>
                                <span class="text">PH</span>
                            </a>
                        </th>
                    	<td><?= $phMin ?></td>
                    	<td><?= $phMax ?></td>
                    	<td><?= $phAVG ?></td>
                    	<td><?= round($phMax - $phMin, 2); ?></td>
                    </tr">
                </tbody>
                <tbody>
                    <tr">
                    	<th style="padding: 0;" class="bg-success">
                            <a style="height: 100%;" class="btn btn-success btn-block btn-lg" data-toggle="modal" data-target="#sairmodalchart">
                                <span class="icon text-white-50 float-left"  >
                                    <i class="far fa-eye"></i>
                                </span>
                                <span class="text">SUHU AIR</span>
                            </a>
                        </th>
                    	<td><?= $sairMin ?></td>
                    	<td><?= $sairMax ?></td>
                    	<td><?= $sairAVG ?></td>
                    	<td><?= $sairMax - $sairMin ?></td>
                    </tr">
                </tbody>
                <tbody>    
                    <tr">
                    	<th style="padding: 0;" class="bg-success">
                            <a style="height: 100%;" class="btn btn-success btn-block btn-lg" data-toggle="modal" data-target="#sudaramodalchart">
                                <span class="icon text-white-50 float-left"  >
                                    <i class="far fa-eye"></i>
                                </span>
                                <span class="text">SUHU UDARA</span>
                            </a>
                        </th>
                    	<td><?= $saudMin ?></td>
                    	<td><?= $saudMax ?></td>
                    	<td><?= $saudAVG ?></td>
                    	<td><?= $saudMax - $saudMin ?></td>
                    </tr">
                </tbody>
                <tbody>    
                    <tr">
                    	<th style="padding: 0;" class="bg-success">
                            <a style="height: 100%;" class="btn btn-success btn-block btn-lg" data-toggle="modal" data-target="#lembabmodalchart">
                                <span class="icon text-white-50 float-left"  >
                                    <i class="far fa-eye"></i>
                                </span>
                                <span class="text">KELEMBAPAN</span>
                            </a>
                        </th>
                    	<td><?= $kelMin ?></td>
                    	<td><?= $kelMax ?></td>
                    	<td><?= $kelAVG ?></td>
                    	<td><?= $kelMax - $kelMin ?></td>
                    </tr">
                </tbody>
                <tbody>    
                    <tr">
                    	<th style="padding: 0;" class="bg-success">
                            <a style="height: 100%;" class="btn btn-success btn-block btn-lg" data-toggle="modal" data-target="#cahayamodalchart">
                                <span class="icon text-white-50 float-left"  >
                                    <i class="far fa-eye"></i>
                                </span>
                                <span class="text">CAHAYA</span>
                            </a>
                        </th>
                    	<td><?= $cahayaMin ?></td>
                    	<td><?= $cahayaMax ?></td>
                    	<td><?= $cahayaAVG ?></td>
                    	<td><?= round($cahayaMax - $cahayaMin,2) ?></td>
                    </tr">
                </tbody>
            </table><br><br>
        </div>
    </div>
</div>
</div>








<!--ppm Modal -->
<div class="modal fade" id="ppmmodalchart" tabindex="-1" aria-labelledby="ppmmodalchartLabel" aria-hidden="true">
  <div class="modal-dialog modal-lg modal-dialog-centered">
    <div class="modal-content">
      <div class="modal-header">
        <h5 class="modal-title" id="ppmmodalchartLabel">Riwayat PPM tanggal <?= date('d F Y', strtotime($waktu)) ?></h5>
        <button type="button" class="close" data-dismiss="modal" aria-label="Close">
          <span aria-hidden="true">&times;</span>
        </button>
      </div>
      <div class="modal-body">
        <div class="chart-area">
            <canvas id="ppmmodale"></canvas>
        </div><br><br><br>
      </div>
      <div class="modal-footer">
        <button type="button" class="btn btn-block btn-success" data-dismiss="modal">Close</button>
      </div>
    </div>
  </div>
</div>

<!--ph Modal -->
<div class="modal fade" id="phmodalchart" tabindex="-1" aria-labelledby="phmodalchartLabel" aria-hidden="true">
  <div class="modal-dialog modal-lg modal-dialog-centered">
    <div class="modal-content">
      <div class="modal-header">
        <h5 class="modal-title" id="phmodalchartLabel">Riwayat PH tanggal <?= date('d F Y', strtotime($waktu)) ?></h5>
        <button type="button" class="close" data-dismiss="modal" aria-label="Close">
          <span aria-hidden="true">&times;</span>
        </button>
      </div>
      <div class="modal-body">
        <div class="chart-area">
            <canvas id="phmodale"></canvas>
        </div><br><br><br>
      </div>
      <div class="modal-footer">
        <button type="button" class="btn btn-block btn-success" data-dismiss="modal">Close</button>
      </div>
    </div>
  </div>
</div>


<!--suhu air Modal -->
<div class="modal fade" id="sairmodalchart" tabindex="-1" aria-labelledby="sairmodalchartLabel" aria-hidden="true">
  <div class="modal-dialog modal-lg modal-dialog-centered">
    <div class="modal-content">
      <div class="modal-header">
        <h5 class="modal-title" id="sairmodalchartLabel">Riwayat Suhu AIR tanggal <?= date('d F Y', strtotime($waktu)) ?></h5>
        <button type="button" class="close" data-dismiss="modal" aria-label="Close">
          <span aria-hidden="true">&times;</span>
        </button>
      </div>
      <div class="modal-body">
        <div class="chart-area">
            <canvas id="sairmodale"></canvas>
        </div><br><br><br>
      </div>
      <div class="modal-footer">
        <button type="button" class="btn btn-block btn-success" data-dismiss="modal">Close</button>
      </div>
    </div>
  </div>
</div>



<!--suhu udara Modal -->
<div class="modal fade" id="sudaramodalchart" tabindex="-1" aria-labelledby="sudaramodalchartLabel" aria-hidden="true">
  <div class="modal-dialog modal-lg modal-dialog-centered">
    <div class="modal-content">
      <div class="modal-header">
        <h5 class="modal-title" id="sudaramodalchartLabel">Riwayat Suhu Udara tanggal <?= date('d F Y', strtotime($waktu)) ?></h5>
        <button type="button" class="close" data-dismiss="modal" aria-label="Close">
          <span aria-hidden="true">&times;</span>
        </button>
      </div>
      <div class="modal-body">
        <div class="chart-area">
            <canvas id="sudaramodale"></canvas>
        </div><br><br><br>
      </div>
      <div class="modal-footer">
        <button type="button" class="btn btn-block btn-success" data-dismiss="modal">Close</button>
      </div>
    </div>
  </div>
</div>


<!--suhu kelembapan Modal -->
<div class="modal fade" id="lembabmodalchart" tabindex="-1" aria-labelledby="lembabmodalchartLabel" aria-hidden="true">
  <div class="modal-dialog modal-lg modal-dialog-centered">
    <div class="modal-content">
      <div class="modal-header">
        <h5 class="modal-title" id="lembabmodalchartLabel">Riwayat Kelembapan tanggal <?= date('d F Y', strtotime($waktu)) ?></h5>
        <button type="button" class="close" data-dismiss="modal" aria-label="Close">
          <span aria-hidden="true">&times;</span>
        </button>
      </div>
      <div class="modal-body">
        <div class="chart-area">
            <canvas id="lembabmodale"></canvas>
        </div><br><br><br>
      </div>
      <div class="modal-footer">
        <button type="button" class="btn btn-block btn-success" data-dismiss="modal">Close</button>
      </div>
    </div>
  </div>
</div>


<!--suhu cahaya Modal -->
<div class="modal fade" id="cahayamodalchart" tabindex="-1" aria-labelledby="cahayamodalchartLabel" aria-hidden="true">
  <div class="modal-dialog modal-lg modal-dialog-centered">
    <div class="modal-content">
      <div class="modal-header">
        <h5 class="modal-title" id="cahayamodalchartLabel">Riwayat Cahaya tanggal <?= date('d F Y', strtotime($waktu)) ?></h5>
        <button type="button" class="close" data-dismiss="modal" aria-label="Close">
          <span aria-hidden="true">&times;</span>
        </button>
      </div>
      <div class="modal-body">
        <div class="chart-area">
            <canvas id="cahayamodale"></canvas>
        </div><br><br><br>
      </div>
      <div class="modal-footer">
        <button type="button" class="btn btn-block btn-secondary" data-dismiss="modal">Close</button>
      </div>
    </div>
  </div>
</div>




<script>

// ppm char
var ctx = document.getElementById('ppmmodale').getContext('2d');
var myChart = new Chart(ctx, {
    type: 'line',
    data: {
        <?php $sql1j = mysqli_query($konekdb, "SELECT * FROM sensor_1j WHERE tanggal='$waktu' ORDER BY id ASC"); ?>
        labels: [<?php while($a = mysqli_fetch_array($sql1j)){echo '"'.$a['waktu'].'",';} ?>],
        datasets: [{
            label: 'ppm',
            <?php $sql1j = mysqli_query($konekdb, "SELECT * FROM sensor_1j WHERE tanggal='$waktu' ORDER BY id ASC"); ?>
            data: [<?php while($a = mysqli_fetch_array($sql1j)){echo ''.$a['sensor_tds'].',';} ?>],
            backgroundColor: [
                'rgba(255, 99, 132, 0.2)',
                'rgba(54, 162, 235, 0.2)',
                'rgba(255, 206, 86, 0.2)',
                'rgba(75, 192, 192, 0.2)',
                'rgba(153, 102, 255, 0.2)',
                'rgba(255, 159, 64, 0.2)'
            ],
            borderColor: [
                'rgba(255, 99, 132, 1)',
                'rgba(54, 162, 235, 1)',
                'rgba(255, 206, 86, 1)',
                'rgba(75, 192, 192, 1)',
                'rgba(153, 102, 255, 1)',
                'rgba(255, 159, 64, 1)'
            ],
            borderWidth: 2
        }]
    },
    options: {
        scales: {
            y: {
                beginAtZero: true
            }
        }
    }
});


//ph modale
var ctx = document.getElementById('phmodale').getContext('2d');
var myChart = new Chart(ctx, {
    type: 'line',
    data: {
        <?php $sql1j = mysqli_query($konekdb, "SELECT * FROM sensor_1j WHERE tanggal='$waktu' ORDER BY id ASC"); ?>
        labels: [<?php while($a = mysqli_fetch_array($sql1j)){echo '"'.$a['waktu'].'",';} ?>],
        datasets: [{
            label: 'ph',
            <?php $sql1j = mysqli_query($konekdb, "SELECT * FROM sensor_1j WHERE tanggal='$waktu' ORDER BY id ASC"); ?>
            data: [<?php while($a = mysqli_fetch_array($sql1j)){echo ''.$a['sensor_ph'].',';} ?>],
            backgroundColor: [
                'rgba(255, 99, 132, 0.2)',
                'rgba(54, 162, 235, 0.2)',
                'rgba(255, 206, 86, 0.2)',
                'rgba(75, 192, 192, 0.2)',
                'rgba(153, 102, 255, 0.2)',
                'rgba(255, 159, 64, 0.2)'
            ],
            borderColor: [
                'rgba(255, 99, 132, 1)',
                'rgba(54, 162, 235, 1)',
                'rgba(255, 206, 86, 1)',
                'rgba(75, 192, 192, 1)',
                'rgba(153, 102, 255, 1)',
                'rgba(255, 159, 64, 1)'
            ],
            borderWidth: 2
        }]
    },
    options: {
        scales: {
            y: {
                beginAtZero: true
            }
        }
    }
});


// suhu air

var ctx = document.getElementById('sairmodale').getContext('2d');
var myChart = new Chart(ctx, {
    type: 'line',
    data: {
        <?php $sql30 = mysqli_query($konekdb, "SELECT * FROM sensor_30 WHERE tanggal='$waktu' ORDER BY id ASC"); ?>
        labels: [<?php while($a = mysqli_fetch_array($sql30)){echo '"'.$a['waktu'].'",';} ?>],
        datasets: [{
            label: 'suhu air',
            <?php $sql30 = mysqli_query($konekdb, "SELECT * FROM sensor_30 WHERE tanggal='$waktu' ORDER BY id ASC"); ?>
            data: [<?php while($a = mysqli_fetch_array($sql30)){echo ''.$a['suhu_air'].',';} ?>],
            backgroundColor: [
                'rgba(255, 99, 132, 0.2)',
                'rgba(54, 162, 235, 0.2)',
                'rgba(255, 206, 86, 0.2)',
                'rgba(75, 192, 192, 0.2)',
                'rgba(153, 102, 255, 0.2)',
                'rgba(255, 159, 64, 0.2)'
            ],
            borderColor: [
                'rgba(255, 99, 132, 1)',
                'rgba(54, 162, 235, 1)',
                'rgba(255, 206, 86, 1)',
                'rgba(75, 192, 192, 1)',
                'rgba(153, 102, 255, 1)',
                'rgba(255, 159, 64, 1)'
            ],
            borderWidth: 2
        }]
    },
    options: {
        scales: {
            y: {
                beginAtZero: true
            }
        }
    }
});


// suhu udara

var ctx = document.getElementById('sudaramodale').getContext('2d');
var myChart = new Chart(ctx, {
    type: 'line',
    data: {
        <?php $sql30 = mysqli_query($konekdb, "SELECT * FROM sensor_30 WHERE tanggal='$waktu' ORDER BY id ASC"); ?>
        labels: [<?php while($a = mysqli_fetch_array($sql30)){echo '"'.$a['waktu'].'",';} ?>],
        datasets: [{
            label: 'suhu udara',
            <?php $sql30 = mysqli_query($konekdb, "SELECT * FROM sensor_30 WHERE tanggal='$waktu' ORDER BY id ASC"); ?>
            data: [<?php while($a = mysqli_fetch_array($sql30)){echo ''.$a['suhu_udara'].',';} ?>],
            backgroundColor: [
                'rgba(255, 99, 132, 0.2)',
                'rgba(54, 162, 235, 0.2)',
                'rgba(255, 206, 86, 0.2)',
                'rgba(75, 192, 192, 0.2)',
                'rgba(153, 102, 255, 0.2)',
                'rgba(255, 159, 64, 0.2)'
            ],
            borderColor: [
                'rgba(255, 99, 132, 1)',
                'rgba(54, 162, 235, 1)',
                'rgba(255, 206, 86, 1)',
                'rgba(75, 192, 192, 1)',
                'rgba(153, 102, 255, 1)',
                'rgba(255, 159, 64, 1)'
            ],
            borderWidth: 2
        }]
    },
    options: {
        scales: {
            y: {
                beginAtZero: true
            }
        }
    }
});

// kelembapan

var ctx = document.getElementById('lembabmodale').getContext('2d');
var myChart = new Chart(ctx, {
    type: 'line',
    data: {
        <?php $sql30 = mysqli_query($konekdb, "SELECT * FROM sensor_30 WHERE tanggal='$waktu' ORDER BY id ASC"); ?>
        labels: [<?php while($a = mysqli_fetch_array($sql30)){echo '"'.$a['waktu'].'",';} ?>],
        datasets: [{
            label: 'kelembapan',
            <?php $sql30 = mysqli_query($konekdb, "SELECT * FROM sensor_30 WHERE tanggal='$waktu' ORDER BY id ASC"); ?>
            data: [<?php while($a = mysqli_fetch_array($sql30)){echo ''.$a['kelembapan_udara'].',';} ?>],
            backgroundColor: [
                'rgba(255, 99, 132, 0.2)',
                'rgba(54, 162, 235, 0.2)',
                'rgba(255, 206, 86, 0.2)',
                'rgba(75, 192, 192, 0.2)',
                'rgba(153, 102, 255, 0.2)',
                'rgba(255, 159, 64, 0.2)'
            ],
            borderColor: [
                'rgba(255, 99, 132, 1)',
                'rgba(54, 162, 235, 1)',
                'rgba(255, 206, 86, 1)',
                'rgba(75, 192, 192, 1)',
                'rgba(153, 102, 255, 1)',
                'rgba(255, 159, 64, 1)'
            ],
            borderWidth: 2
        }]
    },
    options: {
        scales: {
            y: {
                beginAtZero: true
            }
        }
    }
});

// cahaya

var ctx = document.getElementById('cahayamodale').getContext('2d');
var myChart = new Chart(ctx, {
    type: 'line',
    data: {
        <?php $sql30 = mysqli_query($konekdb, "SELECT * FROM sensor_30 WHERE tanggal='$waktu' ORDER BY id ASC"); ?>
        labels: [<?php while($a = mysqli_fetch_array($sql30)){echo '"'.$a['waktu'].'",';} ?>],
        datasets: [{
            label: 'cahaya',
            <?php $sql30 = mysqli_query($konekdb, "SELECT * FROM sensor_30 WHERE tanggal='$waktu' ORDER BY id ASC"); ?>
            data: [<?php while($a = mysqli_fetch_array($sql30)){echo ''.$a['cahaya'].',';} ?>],
            backgroundColor: [
                'rgba(255, 99, 132, 0.2)',
                'rgba(54, 162, 235, 0.2)',
                'rgba(255, 206, 86, 0.2)',
                'rgba(75, 192, 192, 0.2)',
                'rgba(153, 102, 255, 0.2)',
                'rgba(255, 159, 64, 0.2)'
            ],
            borderColor: [
                'rgba(255, 99, 132, 1)',
                'rgba(54, 162, 235, 1)',
                'rgba(255, 206, 86, 1)',
                'rgba(75, 192, 192, 1)',
                'rgba(153, 102, 255, 1)',
                'rgba(255, 159, 64, 1)'
            ],
            borderWidth: 2
        }]
    },
    options: {
        scales: {
            y: {
                beginAtZero: true
            }
        }
    }
});

</script>
