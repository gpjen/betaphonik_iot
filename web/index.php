<?php 

session_start();
include 'sesuatu/koneksi.php';


if (!isset($_SESSION['loginstatus'])) {
    header("location: login.php");
    echo "keluar";
    exit;
} else {
    $emaillogin = $_SESSION['emaillogin'];
    $akunlogin = mysqli_query($konekdb, "SELECT * FROM akun WHERE user = '$emaillogin'");
    $akunlogin = mysqli_fetch_array($akunlogin);

}

 ?>



<!DOCTYPE html>
<html lang="en">

<head>

    <meta charset="utf-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1, shrink-to-fit=no">
    <meta name="description" content="">
    <meta name="author" content="">
    
    <link rel="icon" href="img/logo.png" type="image/gif" sizes="16x16">
    <title>BETAPHONIK IoT Hidroponic System</title>

    <!-- Custom fonts for this template-->
    <link href="vendor/fontawesome-free/css/all.min.css" rel="stylesheet" type="text/css">
    <link href="https://fonts.googleapis.com/css?family=Nunito:200,200i,300,300i,400,400i,600,600i,700,700i,800,800i,900,900i"
        rel="stylesheet">

    <!-- Custom styles for this template-->
    <link rel="stylesheet" href="https://unpkg.com/aos@next/dist/aos.css" />

    <script src="https://cdn.jsdelivr.net/npm/chart.js"></script>

    <link href="css/sb-admin-2.min.css" rel="stylesheet">
    <link href="vendor/datatables/dataTables.bootstrap4.min.css" rel="stylesheet">

    <script src="js/jquery/jquery.min.js"></script>

    <script type="text/javascript">

        //suhu_udara kelembapan_udara cahaya suhu_air nutrisi_air ph_air StokAir stok_nutrisiA stok_nutrisiB relotchart

        $(document).ready( function(){
            setInterval( function(){
                $("#suhu_udara").load('sesuatu/updatesensor.php?update=suhu_udara');
                $("#kelembapan_udara").load('sesuatu/updatesensor.php?update=kelembapan_udara');
                $("#cahaya").load('sesuatu/updatesensor.php?update=cahaya');
                $("#suhu_air").load('sesuatu/updatesensor.php?update=suhu_air');
                $("#nutrisi_air").load('sesuatu/updatesensor.php?update=nutrisi_air');
                $("#ph_air").load('sesuatu/updatesensor.php?update=ph_air');
                $("#PhDown").load('sesuatu/updatesensor.php?update=PhDown');
                $("#stok_nutrisiA").load('sesuatu/updatesensor.php?update=stok_nutrisiA');
                $("#stok_nutrisiB").load('sesuatu/updatesensor.php?update=stok_nutrisiB');
                $("#stok_nutrisiB").load('sesuatu/updatesensor.php?update=stok_nutrisiB');
                
                
            },1000);  //update setiap 1 detik
        });

        function showPreview(event){
          if(event.target.files.length > 0){
            var src = URL.createObjectURL(event.target.files[0]);
            var preview = document.getElementById("editprofil-preview");
            preview.src = src;
            preview.style.display = "block";
          }
        }

    </script>

</head>

<body id="page-top">

    <!-- Page Wrapper -->
    <div id="wrapper">


        <!-- Sidebar -->
        <ul class="navbar-nav bg-gradient-success sidebar sidebar-dark accordion" id="accordionSidebar">

            <!-- Sidebar - Brand -->
            <a class="sidebar-brand d-flex align-items-center justify-content-center" href="index.php?page=sensor">
                <div class="sidebar-brand-icon rotate-n-15">
                    <img src="img/logo.png" style="height:45px;">
                </div>
                <div class="sidebar-brand-text mx-3">BETAPHONIK </div>
            </a>

            <!-- Divider -->
            <hr class="sidebar-divider my-0">

            <!-- Nav Item - Dashboard -->
            <li class="nav-item active">
                <a class="nav-link" href="index.php?page=sensor">
                    <i class="fas fa-fw fa-tachometer-alt"></i>
                    <span>Sensor</span></a>
            </li>

            <li class="nav-item">
                <a class="nav-link" href="index.php?page=menejemenTanam">
                    <i class="fas fa-fw fa-calendar-alt"></i>
                    <span>Menejemen Tanaman</span></a>
            </li>

            <li class="nav-item">
                <a class="nav-link" href="index.php?page=aktifitasphppm">
                    <i class="fas fa-fw fa-calendar-check"></i>
                    <span>Aktifitas Nutrisi & PH Air</span></a>
            </li>
            <li class="nav-item">
                <a class="nav-link" href="index.php?page=laporanSensor">
                    <i class="fas fa-fw fa-table"></i>
                    <span>Laporan Sensor Harian</span></a>
            </li>

            <!-- Divider -->
            <hr class="sidebar-divider">

            <!-- Nav Item - Pages Collapse Menu -->
            <li class="nav-item">
                <a class="nav-link collapsed" href="#" data-toggle="collapse" data-target="#collapseTwo"
                    aria-expanded="true" aria-controls="collapseTwo">
                    <i class="fas fa-fw fa-cog"></i>
                    <span>Pengaturan</span>
                </a>
                <div id="collapseTwo" class="collapse" aria-labelledby="headingTwo" data-parent="#accordionSidebar">
                    <div class="bg-white py-2 collapse-inner rounded">
                        <h6 class="collapse-header">Atur :</h6>
                        <a class="collapse-item" href="index.php?page=aturSensor">Atur Nilai Sensor</a>
                        <a class="collapse-item" href="index.php?page=aturAkun">Atur Akun</a>
                    </div>
                </div>
            </li>


            <!-- Divider -->
            <hr class="sidebar-divider d-none d-md-block"><br><br>

            <!-- Sidebar Toggler (Sidebar) -->
            <div class="text-center d-none d-md-inline">
                <button class="rounded-circle border-0" id="sidebarToggle"></button>
            </div>

        </ul>
        <!-- End of Sidebar -->

        <!-- Content Wrapper -->
        <div id="content-wrapper" class="d-flex flex-column">

            <!-- Main Content -->
            <div id="content">

                <!-- Topbar -->
                <nav class="navbar navbar-expand navbar-light bg-white topbar mb-4 static-top shadow">

                    <!-- Sidebar Toggle (Topbar) -->
                    <button id="sidebarToggleTop" class="btn btn-link d-md-none rounded-circle mr-3">
                        <i class="fa fa-bars"></i>
                    </button>


                    <!-- Topbar Navbar -->
                    <ul class="navbar-nav ml-auto">

                        <div class="topbar-divider d-none d-sm-block"></div>

                        <!-- Nav Item - User Information -->
                        <li class="nav-item dropdown no-arrow">
                            <a class="nav-link dropdown-toggle" href="#" id="userDropdown" role="button"
                                data-toggle="dropdown" aria-haspopup="true" aria-expanded="false">
                                <span class="mr-2 d-none d-lg-inline text-gray-600 small"><?= $akunlogin['nama'] ?></span>
                                <img class="img-profile rounded-circle"
                                    src="img/akun/<?= $akunlogin['profil'] ?>">
                            </a>
                            <!-- Dropdown - User Information -->
                            <div class="dropdown-menu dropdown-menu-right shadow animated--grow-in"
                                aria-labelledby="userDropdown">
                                <a class="dropdown-item" href="index.php?page=aturProfil">
                                    <i class="fas fa-cogs fa-sm fa-fw mr-2 text-gray-400"></i>
                                    Atur Profil
                                </a>
                                <div class="dropdown-divider"></div>
                                <a class="dropdown-item" href="#" data-toggle="modal" data-target="#logoutModal">
                                    <i class="fas fa-sign-out-alt fa-sm fa-fw mr-2 text-gray-400"></i>
                                    Keluar
                                </a>
                            </div>
                        </li>

                    </ul>

                </nav>
                <!-- End of Topbar -->


<?php 
    if(isset($_GET['page'])){
        $page = $_GET['page'];
 
        switch ($page) {
            case 'sensor':
                include "konten/sensor.php";
                break;
            case 'aturProfil':
                include "konten/aturProfil.php";
                break;
            case 'aktifitasphppm':
                include "konten/aktifitasphppm.php";
                break;
            case 'aturSensor':
                include "konten/aturSensor.php";
                break;
            case 'aturAkun':
                include "konten/aturAkun.php";
                break;   
            case 'menejemenTanam':
                include "konten/menejemenTanam.php";
                break;
            case 'laporanSensor':
                include "konten/laporanSensor.php";
                break; 
            case 'nvakdoabdhgv':
                include "konten/editbyadmin.php";
                break;    
            default:
                echo "<center><h3>Maaf. Halaman tidak di temukan !</h3></center>";
                break;
        }
    }else{
        include "konten/sensor.php";
    }


?>


            </div>
            <!-- End of Main Content -->

            <!-- Footer -->
            <footer class="sticky-footer bg-white">
                <div class="container my-auto">
                    <div class="copyright text-center my-auto">
                        <span>GPJEN95 &copy; Itb - Stikom Ambon 2021</span>
                    </div>
                </div>
            </footer>
            <!-- End of Footer -->

        </div>
        <!-- End of Content Wrapper -->

    </div>
    <!-- End of Page Wrapper -->

    <!-- Scroll to Top Button-->
    <a class="scroll-to-top rounded" href="#page-top">
        <i class="fas fa-angle-up"></i>
    </a>

    <!-- Logout Modal-->
    <div class="modal fade" id="logoutModal" tabindex="-1" role="dialog" aria-labelledby="exampleModalLabel"
        aria-hidden="true">
        <div class="modal-dialog" role="document">
            <div class="modal-content">
                <div class="modal-header">
                    <h5 class="modal-title" id="exampleModalLabel">Apakah Anda ingin Keluar ?</h5>
                    <button class="close" type="button" data-dismiss="modal" aria-label="Close">
                        <span aria-hidden="true">×</span>
                    </button>
                </div>
                <div class="modal-body">Pilih "Keluar" sekali lagi untuk mengakhiri kunjungan</div>
                <div class="modal-footer">
                    <button class="btn btn-secondary" type="button" data-dismiss="modal">Batal</button>
                    <a class="btn btn-primary" href="logout.php">Keluar</a>
                </div>
            </div>
        </div>
    </div>

    <!-- Bootstrap core JavaScript-->
    <script src="vendor/bootstrap/js/bootstrap.bundle.min.js"></script>

    <!-- Core plugin JavaScript-->
    <script src="vendor/jquery-easing/jquery.easing.min.js"></script>

    <!-- Custom scripts for all pages-->
    <script src="js/sb-admin-2.min.js"></script>

    <!-- Page level plugins -->
    <script src="vendor/datatables/jquery.dataTables.min.js"></script>
    <script src="vendor/datatables/dataTables.bootstrap4.min.js"></script>

    <!-- Page level custom scripts -->
    <script src="js/demo/datatables-demo.js"></script>

    <!-- smootscrool -->
    <script src="https://unpkg.com/aos@next/dist/aos.js"></script>
      <script>
        AOS.init({
            once: true,
        });
      </script>

      <script type="text/javascript">
          var ctx = document.getElementById("PH_Chart");
            var myLineChart = new Chart(ctx, {
              type: 'line',
              data: {
                <?php $sql1j = mysqli_query($konekdb, "SELECT * FROM sensor_1j WHERE tanggal=CURDATE() ORDER BY id ASC"); ?>

                labels: [<?php while($a = mysqli_fetch_array($sql1j)){echo '"'.$a['waktu'].'",';} ?>],
                datasets: [{
                  label: "Ph ",
                  lineTension: 0.3,
                  backgroundColor: "rgba(78, 115, 223, 0.05)",
                  borderColor: "rgba(78, 115, 223, 1)",
                  pointRadius: 3,
                  pointBackgroundColor: "rgba(78, 115, 223, 1)",
                  pointBorderColor: "rgba(78, 115, 223, 1)",
                  pointHoverRadius: 3,
                  pointHoverBackgroundColor: "rgba(78, 115, 223, 1)",
                  pointHoverBorderColor: "rgba(78, 115, 223, 1)",
                  pointHitRadius: 10,
                  pointBorderWidth: 2,

                  <?php $sql1j = mysqli_query($konekdb, "SELECT * FROM sensor_1j WHERE tanggal=CURDATE() ORDER BY id ASC"); ?>

                  data: [<?php while($a = mysqli_fetch_array($sql1j)){echo ''.$a['sensor_ph'].',';} ?>],
                }],
              },
              options: {
                maintainAspectRatio: false,
                layout: {
                  padding: {
                    left: 10,
                    right: 25,
                    top: 25,
                    bottom: 0
                  }
                },
                scales: {
                  xAxes: [{
                    time: {
                      unit: 'date'
                    },
                    gridLines: {
                      display: false,
                      drawBorder: false
                    },
                    ticks: {
                      maxTicksLimit: 7
                    }
                  }],
                  yAxes: [{
                    ticks: {
                      maxTicksLimit: 5,
                      padding: 10,
                      // Include a dollar sign in the ticks
                      callback: function(value, index, values) {
                        return 'Ph ' + number_format(value);
                      }
                    },
                    gridLines: {
                      color: "rgb(234, 236, 244)",
                      zeroLineColor: "rgb(234, 236, 244)",
                      drawBorder: false,
                      borderDash: [2],
                      zeroLineBorderDash: [2]
                    }
                  }],
                },
                legend: {
                  display: false
                },
                tooltips: {
                  backgroundColor: "rgb(255,255,255)",
                  bodyFontColor: "#858796",
                  titleMarginBottom: 10,
                  titleFontColor: '#6e707e',
                  titleFontSize: 14,
                  borderColor: '#dddfeb',
                  borderWidth: 1,
                  xPadding: 15,
                  yPadding: 15,
                  displayColors: false,
                  intersect: false,
                  mode: 'index',
                  caretPadding: 10,
                  callbacks: {
                    label: function(tooltipItem, chart) {
                      var datasetLabel = chart.datasets[tooltipItem.datasetIndex].label || '';
                      return datasetLabel + ' : ' + number_format(tooltipItem.yLabel);
                    }
                  }
                }
              }
            });



            //TDS AIR===============================================================================================================
            var ctx = document.getElementById("TDS_Chart");
            var myLineChart = new Chart(ctx, {
              type: 'line',
              data: {
              <?php $sql1j = mysqli_query($konekdb, "SELECT * FROM sensor_1j WHERE tanggal=CURDATE() ORDER BY id ASC"); ?>

                labels: [<?php while($a = mysqli_fetch_array($sql1j)){echo '"'.$a['waktu'].'",';} ?>],
                datasets: [{
                  label: "PPM ",
                  lineTension: 0.3,
                  backgroundColor: "rgba(28, 200, 138, 0.05)",
                  borderColor: "rgba(28, 200, 138, 1)",
                  pointRadius: 3,
                  pointBackgroundColor: "rgba(28, 200, 138, 1)",
                  pointBorderColor: "rgba(28, 200, 138, 1)",
                  pointHoverRadius: 3,
                  pointHoverBackgroundColor: "rgba(28, 200, 138, 1)",
                  pointHoverBorderColor: "rgba(28, 200, 138, 1)",
                  pointHitRadius: 10,
                  pointBorderWidth: 2,
                  <?php $sql1j = mysqli_query($konekdb, "SELECT * FROM sensor_1j WHERE tanggal=CURDATE() ORDER BY id ASC"); ?>

                  data: [<?php while($a = mysqli_fetch_array($sql1j)){echo ''.$a['sensor_tds'].',';} ?>],
                }],
              },
              options: {
                maintainAspectRatio: false,
                layout: {
                  padding: {
                    left: 10,
                    right: 25,
                    top: 25,
                    bottom: 0
                  }
                },
                scales: {
                  xAxes: [{
                    time: {
                      unit: 'date'
                    },
                    gridLines: {
                      display: false,
                      drawBorder: false
                    },
                    ticks: {
                      maxTicksLimit: 7
                    }
                  }],
                  yAxes: [{
                    ticks: {
                      maxTicksLimit: 5,
                      padding: 10,
                      // Include a dollar sign in the ticks
                      callback: function(value, index, values) {
                        return 'Ppm ' + number_format(value);
                      }
                    },
                    gridLines: {
                      color: "rgb(234, 236, 244)",
                      zeroLineColor: "rgb(234, 236, 244)",
                      drawBorder: false,
                      borderDash: [2],
                      zeroLineBorderDash: [2]
                    }
                  }],
                },
                legend: {
                  display: false
                },
                tooltips: {
                  backgroundColor: "rgb(255,255,255)",
                  bodyFontColor: "#858796",
                  titleMarginBottom: 10,
                  titleFontColor: '#6e707e',
                  titleFontSize: 14,
                  borderColor: '#dddfeb',
                  borderWidth: 1,
                  xPadding: 15,
                  yPadding: 15,
                  displayColors: false,
                  intersect: false,
                  mode: 'index',
                  caretPadding: 10,
                  callbacks: {
                    label: function(tooltipItem, chart) {
                      var datasetLabel = chart.datasets[tooltipItem.datasetIndex].label || '';
                      return datasetLabel + ': ' + number_format(tooltipItem.yLabel);
                    }
                  }
                }
              }
            });


            // SUHU air================================================================================================================
            var cti = document.getElementById("SAIR_Chart");
            var myLineChart = new Chart(cti, {
              type: 'line',
              data: {
              <?php $sql30 = mysqli_query($konekdb, "SELECT * FROM sensor_30 WHERE tanggal=CURDATE() ORDER BY id ASC"); ?>

                labels: [<?php while($a = mysqli_fetch_array($sql30)){echo '"'.$a['waktu'].'",';} ?>],
                datasets: [{
                  label: "Suhu Air ",
                  lineTension: 0.3,
                  backgroundColor: "rgba(246,194,62, 0.05)",
                  borderColor: "rgba(246,194,62, 1)",
                  pointRadius: 3,
                  pointBackgroundColor: "rgba(246,194,62, 1)",
                  pointBorderColor: "rgba(246,194,62, 1)",
                  pointHoverRadius: 3,
                  pointHoverBackgroundColor: "rgba(246,194,62, 1)",
                  pointHoverBorderColor: "rgba(246,194,62, 1)",
                  pointHitRadius: 10,
                  pointBorderWidth: 2,
                  <?php $sql30 = mysqli_query($konekdb, "SELECT * FROM sensor_30 WHERE tanggal=CURDATE() ORDER BY id ASC"); ?>

                  data: [<?php while($a = mysqli_fetch_array($sql30)){echo ''.$a['suhu_air'].',';} ?>],
                }],
              },
              options: {
                maintainAspectRatio: false,
                layout: {
                  padding: {
                    left: 10,
                    right: 25,
                    top: 25,
                    bottom: 0
                  }
                },
                scales: {
                  xAxes: [{
                    time: {
                      unit: 'date'
                    },
                    gridLines: {
                      display: false,
                      drawBorder: false
                    },
                    ticks: {
                      maxTicksLimit: 7
                    }
                  }],
                  yAxes: [{
                    ticks: {
                      maxTicksLimit: 5,
                      padding: 10,
                      // Include a dollar sign in the ticks
                      callback: function(value, index, values) {
                        return number_format(value) + ' °C';
                      }
                    },
                    gridLines: {
                      color: "rgb(234, 236, 244)",
                      zeroLineColor: "rgb(234, 236, 244)",
                      drawBorder: false,
                      borderDash: [2],
                      zeroLineBorderDash: [2]
                    }
                  }],
                },
                legend: {
                  display: false
                },
                tooltips: {
                  backgroundColor: "rgb(255,255,255)",
                  bodyFontColor: "#858796",
                  titleMarginBottom: 10,
                  titleFontColor: '#6e707e',
                  titleFontSize: 14,
                  borderColor: '#dddfeb',
                  borderWidth: 1,
                  xPadding: 15,
                  yPadding: 15,
                  displayColors: false,
                  intersect: false,
                  mode: 'index',
                  caretPadding: 10,
                  callbacks: {
                    label: function(tooltipItem, chart) {
                      var datasetLabel = chart.datasets[tooltipItem.datasetIndex].label || '';
                      return datasetLabel + ': ' + number_format(tooltipItem.yLabel) + ' °C';
                    }
                  }
                }
              }
            });




            // CAHAYA LUX=========================================================================================================
            var cti = document.getElementById("LUX_Chart");
            var myLineChart = new Chart(cti, {
              type: 'line',
              data: {
                <?php $sql30 = mysqli_query($konekdb, "SELECT * FROM sensor_30 WHERE tanggal=CURDATE() ORDER BY id ASC"); ?>

                labels: [<?php while($a = mysqli_fetch_array($sql30)){echo '"'.$a['waktu'].'",';} ?>],
                datasets: [{
                  label: "Cahaya ",
                  lineTension: 0.3,
                  backgroundColor: "rgba(231,74,59, 0.05)",
                  borderColor: "rgba(231,74,59, 1)",
                  pointRadius: 3,
                  pointBackgroundColor: "rgba(231,74,59, 1)",
                  pointBorderColor: "rgba(231,74,59, 1)",
                  pointHoverRadius: 3,
                  pointHoverBackgroundColor: "rgba(231,74,59, 1)",
                  pointHoverBorderColor: "rgba(231,74,59, 1)",
                  pointHitRadius: 10,
                  pointBorderWidth: 2,
                  <?php $sql30 = mysqli_query($konekdb, "SELECT * FROM sensor_30 WHERE tanggal=CURDATE() ORDER BY id ASC"); ?>

                  data: [<?php while($a = mysqli_fetch_array($sql30)){echo '"'.$a['cahaya'].'",';} ?>],
                }],
              },
              options: {
                maintainAspectRatio: false,
                layout: {
                  padding: {
                    left: 10,
                    right: 25,
                    top: 25,
                    bottom: 0
                  }
                },
                scales: {
                  xAxes: [{
                    time: {
                      unit: 'date'
                    },
                    gridLines: {
                      display: false,
                      drawBorder: false
                    },
                    ticks: {
                      maxTicksLimit: 7
                    }
                  }],
                  yAxes: [{
                    ticks: {
                      maxTicksLimit: 5,
                      padding: 10,
                      // Include a dollar sign in the ticks
                      callback: function(value, index, values) {
                        return number_format(value);
                      }
                    },
                    gridLines: {
                      color: "rgb(234, 236, 244)",
                      zeroLineColor: "rgb(234, 236, 244)",
                      drawBorder: false,
                      borderDash: [2],
                      zeroLineBorderDash: [2]
                    }
                  }],
                },
                legend: {
                  display: false
                },
                tooltips: {
                  backgroundColor: "rgb(255,255,255)",
                  bodyFontColor: "#858796",
                  titleMarginBottom: 10,
                  titleFontColor: '#6e707e',
                  titleFontSize: 14,
                  borderColor: '#dddfeb',
                  borderWidth: 1,
                  xPadding: 15,
                  yPadding: 15,
                  displayColors: false,
                  intersect: false,
                  mode: 'index',
                  caretPadding: 10,
                  callbacks: {
                    label: function(tooltipItem, chart) {
                      var datasetLabel = chart.datasets[tooltipItem.datasetIndex].label || '';
                      return datasetLabel + ': ' + number_format(tooltipItem.yLabel) + ' Lux';
                    }
                  }
                }
              }
            });



            //SUHU UDARA===============================================================================================================

            var cti = document.getElementById("TEMP_Chart");
            var myLineChart = new Chart(cti, {
              type: 'line',
              data: {
              <?php $sql30 = mysqli_query($konekdb, "SELECT * FROM sensor_30 WHERE tanggal=CURDATE() ORDER BY id ASC"); ?>

                labels: [<?php while($a = mysqli_fetch_array($sql30)){echo '"'.$a['waktu'].'",';} ?>],
                datasets: [{
                  label: "Suhu ",
                  lineTension: 0.3,
                  backgroundColor: "rgba(54,185,204, 0.05)",
                  borderColor: "rgba(54,185,204, 1)",
                  pointRadius: 3,
                  pointBackgroundColor: "rgba(54,185,204, 1)",
                  pointBorderColor: "rgba(54,185,204, 1)",
                  pointHoverRadius: 3,
                  pointHoverBackgroundColor: "rgba(54,185,204, 1)",
                  pointHoverBorderColor: "rgba(54,185,204, 1)",
                  pointHitRadius: 10,
                  pointBorderWidth: 2,
                  <?php $sql30 = mysqli_query($konekdb, "SELECT * FROM sensor_30 WHERE tanggal=CURDATE() ORDER BY id ASC"); ?>

                  data: [<?php while($a = mysqli_fetch_array($sql30)){echo ''.$a['suhu_udara'].',';} ?>],
                }],
              },
              options: {
                maintainAspectRatio: false,
                layout: {
                  padding: {
                    left: 10,
                    right: 25,
                    top: 25,
                    bottom: 0
                  }
                },
                scales: {
                  xAxes: [{
                    time: {
                      unit: 'date'
                    },
                    gridLines: {
                      display: false,
                      drawBorder: false
                    },
                    ticks: {
                      maxTicksLimit: 7
                    }
                  }],
                  yAxes: [{
                    ticks: {
                      maxTicksLimit: 5,
                      padding: 10,
                      // Include a dollar sign in the ticks
                      callback: function(value, index, values) {
                        return number_format(value) + ' °C';
                      }
                    },
                    gridLines: {
                      color: "rgb(234, 236, 244)",
                      zeroLineColor: "rgb(234, 236, 244)",
                      drawBorder: false,
                      borderDash: [2],
                      zeroLineBorderDash: [2]
                    }
                  }],
                },
                legend: {
                  display: false
                },
                tooltips: {
                  backgroundColor: "rgb(255,255,255)",
                  bodyFontColor: "#858796",
                  titleMarginBottom: 10,
                  titleFontColor: '#6e707e',
                  titleFontSize: 14,
                  borderColor: '#dddfeb',
                  borderWidth: 1,
                  xPadding: 15,
                  yPadding: 15,
                  displayColors: false,
                  intersect: false,
                  mode: 'index',
                  caretPadding: 10,
                  callbacks: {
                    label: function(tooltipItem, chart) {
                      var datasetLabel = chart.datasets[tooltipItem.datasetIndex].label || '';
                      return datasetLabel + ': ' + number_format(tooltipItem.yLabel) + ' °C';
                    }
                  }
                }
              }
            });



            //KELEMBAPAN UDARA=========================================================================================================

            var cti = document.getElementById("HUMI_Chart");
            var myLineChart = new Chart(cti, {
              type: 'line',
              data: {
              <?php $sql30 = mysqli_query($konekdb, "SELECT * FROM sensor_30 WHERE tanggal=CURDATE() ORDER BY id ASC"); ?>

                labels: [<?php while($a = mysqli_fetch_array($sql30)){echo '"'.$a['waktu'].'",';} ?>],
                datasets: [{
                  label: "Humi ",
                  lineTension: 0.3,
                  backgroundColor: "rgba(90,92,105, 0.05)",
                  borderColor: "rgba(90,92,105, 1)",
                  pointRadius: 3,
                  pointBackgroundColor: "rgba(90,92,105, 1)",
                  pointBorderColor: "rgba(90,92,105, 1)",
                  pointHoverRadius: 3,
                  pointHoverBackgroundColor: "rgba(90,92,105, 1)",
                  pointHoverBorderColor: "rgba(90,92,105, 1)",
                  pointHitRadius: 10,
                  pointBorderWidth: 2,
                  <?php $sql30 = mysqli_query($konekdb, "SELECT * FROM sensor_30 WHERE tanggal=CURDATE() ORDER BY id ASC"); ?>

                  data: [<?php while($a = mysqli_fetch_array($sql30)){echo '"'.$a['kelembapan_udara'].'",';} ?>],
                }],
              },
              options: {
                maintainAspectRatio: false,
                layout: {
                  padding: {
                    left: 10,
                    right: 25,
                    top: 25,
                    bottom: 0
                  }
                },
                scales: {
                  xAxes: [{
                    time: {
                      unit: 'date'
                    },
                    gridLines: {
                      display: false,
                      drawBorder: false
                    },
                    ticks: {
                      maxTicksLimit: 7
                    }
                  }],
                  yAxes: [{
                    ticks: {
                      maxTicksLimit: 5,
                      padding: 10,
                      // Include a dollar sign in the ticks
                      callback: function(value, index, values) {
                        return number_format(value) + ' %';
                      }
                    },
                    gridLines: {
                      color: "rgb(234, 236, 244)",
                      zeroLineColor: "rgb(234, 236, 244)",
                      drawBorder: false,
                      borderDash: [2],
                      zeroLineBorderDash: [2]
                    }
                  }],
                },
                legend: {
                  display: false
                },
                tooltips: {
                  backgroundColor: "rgb(255,255,255)",
                  bodyFontColor: "#858796",
                  titleMarginBottom: 10,
                  titleFontColor: '#6e707e',
                  titleFontSize: 14,
                  borderColor: '#dddfeb',
                  borderWidth: 1,
                  xPadding: 15,
                  yPadding: 15,
                  displayColors: false,
                  intersect: false,
                  mode: 'index',
                  caretPadding: 10,
                  callbacks: {
                    label: function(tooltipItem, chart) {
                      var datasetLabel = chart.datasets[tooltipItem.datasetIndex].label || '';
                      return datasetLabel + ': ' + number_format(tooltipItem.yLabel) + ' %';
                    }
                  }
                }
              }
            });


      </script>



</body>

</html>