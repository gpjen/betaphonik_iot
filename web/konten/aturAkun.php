<?php 

	
	//hapus akun
	if (isset($_GET['hapusin'])) {
		$hapus = $_GET['hapusin'];
		$sql = mysqli_query($konekdb, "DELETE FROM `akun` WHERE `id`= '$hapus'");
	}


	//tambah akun
	if (isset($_POST['daftar'])) {

		$nama 		= $_POST['nama'];
		$user 		= $_POST['email'];
		$pass 		= mysqli_real_escape_string($konekdb, $_POST['pass']) ;

		//cek & uplot gambar profil
		$gambar		= uplot($_FILES);

		if ( !$gambar ){
			return false;
		}

		//enkripsi password
		$pass = password_hash($pass, PASSWORD_DEFAULT);


		$masukin = mysqli_query($konekdb, "INSERT INTO `akun` VALUES (NULL, '$nama', '$user', '$pass', '$gambar');");	

	}


	$sql = "SELECT * FROM akun;";
	$akun = mysqli_query($konekdb, $sql);

 ?>



<div class="container" data-aos="fade-right"><br>
	<div class="card border-left-success shadow mb-4">
	    <div class="card-header py-3">
	    	<center><h4 class="m-0 font-weight-bold text-success">AKUN TERDAFTAR</h4></center>
	    </div>
	    <div class="card-body">
	        <div class="table-responsive"><br>
	            <table class="table table-hover" id="dataTable" width="100%" cellspacing="0">
	                <thead>
	                    <tr>
	                    	<th>Profil</th>
	                        <th>Nama</th>
	                        <th>Email</th>
	                        <th>Edit</th>
	                        <th>Hapus</th>
	                       
	                    </tr>
	                </thead>
	                <tbody >

	                	<?php foreach ($akun as $row) { ?>

	                    <tr>
	                    	<form>
	                            <td>
	                            	<img style="border-radius: 10%; height: 80px; box-shadow: 4px 2px 1px rgba(0, 0, 0, 0.2);" src="img/akun/<?= $row['profil'] ?>">
	                            </td>
	                            <td>
	                            	<?= $row['nama'] ?>
	                            </td>
	                            <td>
	                            	<?= $row['user'] ?>
	                            </td>
	                            <td>
	                            	<a href="index.php?page=nvakdoabdhgv&id=<?= $row['id'] ?>" class="btn btn-info btn-block">
                                        <span class="icon text-white-50 float-left">
                                            <i class="fas fa-edit"></i>
                                        </span>
                                        <span class="text">Edit akun</span>
                                    </a>
	                            	
	                            </td>
	                            <td> 
                            		<a name="hapus" onclick="return confirm('<?= $row['user'] ?> Akan dihapus..? ');" href="index.php?page=aturAkun&hapusin=<?= $row['id'] ?>"  class="btn btn-danger btn-block">
                                        <span class="icon text-white-50 float-left">
                                            <i class="fas fa-trash"></i>
                                        </span>
                                        <span class="text">Hapus akun</span>
                                    </a>

	                            </td>
	                     	</form>
	                    </tr>

	                <?php } ?>
	                </tbody>
	            </table>
	        </div><br><br><br>


	        <!-- <button type="submit" class="btn btn-success btn-user btn-block" data-toggle="modal" data-target="#tambahakun">
			  Tambah Akun
			</button> -->


			 <button class="btn btn-success btn-user btn-block" data-target="#tambahakun" data-toggle="modal" data-backdrop="static" data-keyboard="false">
			    TAMBAH BARU
			 </button>`

			<div class="modal fade" id="tambahakun" tabindex="-1" aria-labelledby="exampleModalLabel" aria-hidden="true">
			  <div class="modal-dialog">
			    <div class="modal-content">
			      <div class="modal-header">
			        <h4 class="m-0 font-weight-bold text-primary">BUAT AKUN</h4>
			      </div>
			      <div class="modal-body">
			        
                    <form method="POST" class="user" enctype="multipart/form-data">
                        <div class="form-group row">
                            <div class="col-sm-12 mb-3 mb-sm-0">
                                <input type="text" class="form-control form-control-user" id="exampleFirstName"
                                    placeholder="Nama" name="nama" required>
                            </div>
                        </div>
                        <div class="form-group">
                            <input type="email" class="form-control form-control-user" id="exampleInputEmail"
                                placeholder="Email" name="email" required>
                        </div>
                        <div class="form-group">
                            <input type="password" class="form-control form-control-user" id="exampleInputEmail"
                                placeholder="Password" name="pass" required>
                        </div><br>
                        <div class="form-group row">
                        	<div class="col-sm-12 mb-3 mb-sm-0">
                                <label for="uplot">Upload Foto Profil</label>
                            </div>
                            <div class="col-sm-12 mb-3 mb-sm-0">
                                <input value="" type="file" class="form-control-file border" id="uplot" name="profil" required>
                            </div>
                        </div><br>

                        <button type="submit" name="daftar" class="btn btn-primary btn-user btn-block">Buat Akun</button>

                    </form>

			      </div>
			      <div class="modal-footer">
			        <button type="button" class="btn btn-secondary btn-user btn-block" data-dismiss="modal">Batal</button>
			      </div>
			    </div>
			  </div>
			</div>


	        <br><br>
	    </div>
	</div>
</div>

