<?php 

	$id = $_GET['id'];
	$akun = mysqli_query($konekdb, "SELECT * FROM akun WHERE id='$id'");
	$row = mysqli_fetch_array($akun);


    if (isset($_POST['editsimpan'])) {

        $id         = $row['id'];
        $nama       = $_POST['editnama'];
        $user       = $_POST['editemail'];
        $pass       = mysqli_real_escape_string($konekdb, $_POST['editpass']);


        if ($row['profil'] !== ""){
            $gambar     = uplot($_FILES);
        } else {
            $gambar     = $row['profil'];
        }

        
        if ( !$gambar ){
            return false;
        }

        //enkripsi password
        $pass = password_hash($pass, PASSWORD_DEFAULT);

        $masukin = mysqli_query($konekdb, "UPDATE `akun` SET `id`='$id',`nama`='$nama',`user`='$user',`pass`='$pass',`profil`='$gambar' WHERE id='$id'");

        $akun = mysqli_query($konekdb, "SELECT * FROM akun WHERE id='$id'");
        $row = mysqli_fetch_array($akun);

    }

 ?>

<!-- Outer Row -->
        <div class="row justify-content-center" data-aos="zoom-in">
            <img src="">
            <div class="col-xl-10 col-lg-12 col-md-9">
                <div class="card border-0 shadow-lg my-5">
                    <div class="card-body">
                        <div class="row">
                            <div class="col-lg-6 ">
                                <div class="container" ><br><br><br><center>
                                    
                                    <div class="center">
                                        <div class="form-input">
                                            <h5 class=" font-weight-bold text-secondary">Profil sekarang</h5>
                                            <div class="preview" >
                                              <img src="img/akun/<?= $row['profil']; ?>" class="shadow-lg my-4" style="width: 50%; border-radius: 15px;">
                                            </div>
                                        <label for="profil" class="btn btn-success btn-icon-split">
                                            <span class="icon text-white-50"><i class="fas fa-cloud-upload-alt"></i></span>
                                            <span class="text">Ganti profil dengan</span>
                                        </label>
                                        </div>
                                        <div class="preview" >
                                          <img id="editprofil-preview" class="shadow-lg my-4" style="width: 50%; border-radius: 15px;">
                                        </div>                                      
                                    </div>

                                </center></div><br>

                            </div>
                            <div class="col-lg-6">
                                <div class="p-5"><br>
                                    <div class="text-center">
                                        <h4 class="m-0 font-weight-bold text-success">Edit <?= $row['nama']; ?></h4><br>
                                    </div><br>
                                    <form method="POST" class="user" enctype="multipart/form-data">
                                        <div class="col-sm-12 mb-3 mb-sm-0">
                                            <input hidden="" type="file" id="profil" name="profil" accept="image/*" onchange="showPreview(event);">
                                        </div>
                                        <div class="form-group row">
                                            <div class="col-sm-12 mb-3 mb-sm-0">
                                                <input type="text" class="form-control form-control-user" id="exampleFirstName"
                                                    value="<?= $row['nama']; ?>" name="editnama">
                                            </div>
                                        </div>
                                        <div class="form-group">
                                            <input type="email" class="form-control form-control-user" id="exampleInputEmail"
                                                value="<?= $row['user']; ?>" name="editemail">
                                        </div>
                                        <div class="form-group">
                                            <input type="password" class="form-control form-control-user" id="exampleInputEmail"
                                                placeholder="Password Baru" name="editpass" required>
                                        </div><br><br>
                                        <button type="submit" name="editsimpan" class="btn btn-success btn-user btn-block">Simpan Perubahan </button>

                                        <a type="button" onclick="return confirm('Batalkan Perubahan..? ');" href="index.php?page=aturAkun"  class="btn btn-secondary btn-user btn-block">KELUAR / BATAL</a>
                                    </form>
                                </div>
                            </div>
                        </div>  
                    </div>
                </div>
            </div>
        </div>



    