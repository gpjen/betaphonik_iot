<?php 
session_start();

    include 'sesuatu/koneksi.php';

    if (isset($_POST['login'])) {
        $email = $_POST['loginemail'];
        $pass  = $_POST['loginpass'];

        //cek email
        $masuk = mysqli_query($konekdb, "SELECT * FROM `akun` WHERE `user` = '$email'");

        if (mysqli_num_rows($masuk) === 1) {

            //cek password
            $row = mysqli_fetch_assoc($masuk);

            if (password_verify($pass, $row['pass'])) {

              $_SESSION['loginstatus'] = true;
              $_SESSION['emaillogin'] = $email;
              header("location: index.php");
            }else{
              $userpas = false;
            }

            $userpas = false;
        }

        $userpas = false;

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
    <title>BETAPHONIK Login</title>

    <!-- Custom fonts for this template-->
    <link href="vendor/fontawesome-free/css/all.min.css" rel="stylesheet" type="text/css">
    <link
        href="https://fonts.googleapis.com/css?family=Nunito:200,200i,300,300i,400,400i,600,600i,700,700i,800,800i,900,900i"
        rel="stylesheet">

    <!-- Custom styles for this template-->
    <link rel="stylesheet" href="https://unpkg.com/aos@next/dist/aos.css" />

    <link href="css/sb-admin-2.min.css" rel="stylesheet">

</head>

<body class="bg-gradient-success" >

    <div class="container">

        <!-- Outer Row -->
        <div class="row justify-content-center" data-aos="fade-down"
     data-aos-anchor-placement="top-center">
            <img src="">
            <div class="col-xl-10 col-lg-12 col-md-9">

                <div class="card o-hidden border-0 shadow-lg my-5">
                    <div class="card-body p-0">
    

                        <div class="row" style="height:600px;">
                            <div class="col-lg-6 d-none d-lg-block ">
                                

                                <div id="carouselExampleCaptions" class="carousel slide" data-ride="carousel">
                                  <ol class="carousel-indicators">
                                    <li data-target="#carouselExampleCaptions" data-slide-to="0" class="active"></li>
                                    <li data-target="#carouselExampleCaptions" data-slide-to="1"></li>
                                    <li data-target="#carouselExampleCaptions" data-slide-to="2"></li>
                                    <li data-target="#carouselExampleCaptions" data-slide-to="3"></li>
                                    <li data-target="#carouselExampleCaptions" data-slide-to="4"></li>
                                  </ol>
                                  <div class="carousel-inner">
                                    <div class="carousel-item active">
                                      <img src="img/hidro1.jpg" class="d-block w-100" alt="...">
                                      <div class="carousel-caption d-none d-md-block">
                                        <h3>Teknologi dan pertanian</h3><br><br><br>
                                      </div>
                                    </div>
                                    <div class="carousel-item">
                                      <img src="img/hidro2.jpg" class="d-block w-100" alt="...">
                                      <div class="carousel-caption d-none d-md-block">
                                        <h3>Mudah dan efisien</h3><br><br><br>
                                      </div>
                                    </div>
                                    <div class="carousel-item">
                                      <img src="img/hidro3.jpg" class="d-block w-100" alt="...">
                                      <div class="carousel-caption d-none d-md-block">
                                        <h3>Sehat dan higienis</h3><br><br><br>
                                      </div>
                                    </div>
                                    <div class="carousel-item">
                                      <img src="img/hidro4.jpg" class="d-block w-100" alt="...">
                                      <div class="carousel-caption d-none d-md-block">
                                        <h3>Bernilai ekonomis tinggi</h3><br><br><br>
                                      </div>
                                    </div>
                                    <div class="carousel-item">
                                      <img src="img/hidro5.jpg" class="d-block w-100" alt="...">
                                      <div class="carousel-caption d-none d-md-block">
                                        <h3>mantap lah</h3><br><br><br>
                                      </div>
                                    </div>
                                  </div>
                                  <a class="carousel-control-prev" href="#carouselExampleCaptions" role="button" data-slide="prev">
                                    <span class="carousel-control-prev-icon" aria-hidden="true"></span>
                                    <span class="sr-only">Previous</span>
                                  </a>
                                  <a class="carousel-control-next" href="#carouselExampleCaptions" role="button" data-slide="next">
                                    <span class="carousel-control-next-icon" aria-hidden="true"></span>
                                    <span class="sr-only">Next</span>
                                  </a>
                                </div>





                            </div>
                            <div class="col-lg-6">
                                <div class="p-5"><br><br>
                                    <div class="text-center" data-aos="fade-down" data-aos-delay="800">
                                        <h1 class="h4 text-gray-900 mb-4">Hai, Masuk Sebagai Admin</h1><br>
                                    </div>
                                    <form class="user" method="POST" action="">
                                        <div class="form-group"data-aos="fade-down" data-aos-delay="700">
                                            <input type="email" name="loginemail" class="form-control form-control-user"
                                                id="loginemail" aria-describedby="emailHelp"
                                                placeholder="Username Admin" required>
                                        </div>
                                        <div class="form-group" data-aos="fade-down" data-aos-delay="500">
                                            <input type="password"  name="loginpass" class="form-control form-control-user"
                                                id="loginpass" placeholder="Password" required>
                                        </div><br>
                                        <button class="btn btn-success btn-user btn-block" name="login" data-aos="fade-down" data-aos-delay="300"> MASUK</button>
                                    </form><br><br>

                                    <?php 
                                        
                                        if (isset($userpas) && $userpas === false) {
                                            echo "

                                            <div class='alert alert-danger alert-dismissible fade show' role='alert'>
                                              <strong>Email dan Password salah..!</strong>
                                              <button type='button' class='close' data-dismiss='alert' aria-label='Close'>
                                                <span aria-hidden='true'>&times;</span>
                                              </button>
                                            </div>

                                            ";
                                        }

                                     ?>
                                </div>
                            </div>
                        </div>  
                    </div>
                </div>

            </div>

        </div>

    </div>

    <!-- Bootstrap core JavaScript-->
    <script src="vendor/jquery/jquery.min.js"></script>
    <script src="vendor/bootstrap/js/bootstrap.bundle.min.js"></script>

    <!-- Core plugin JavaScript-->
    <script src="vendor/jquery-easing/jquery.easing.min.js"></script>

    <!-- Custom scripts for all pages-->
    <script src="https://unpkg.com/aos@next/dist/aos.js"></script>
    <script>
      AOS.init();
    </script>

    <script src="js/sb-admin-2.min.js"></script>

</body>

</html>