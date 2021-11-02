<?php 

$servername = "localhost";
$database = "kontroll_betaphonik_iot";
$username = "kontroll_betaiot";
$password = "v)NUx$^SXwny";


$konekdb = mysqli_connect($servername, $username, $password, $database);


		function uplot($file){
            $namafile   = $file['profil']['name'];
            $ukuran     = $file['profil']['size'];
            $error      = $file['profil']['error'];
            $tmpSementara = $file['profil']['tmp_name'];
            //cek ekstensi file
            $ekstensigambar = ['svg','JPG','PNG','JPEG','jpg','jpeg','png'];
            $tipefile = explode('.', $namafile);
            $tipefile = end($tipefile);
            if (!in_array($tipefile, $ekstensigambar)) {
                echo "
                    <script>
                        alert('Pilih gambar (jpg, jpeg, png)');
                    </script>
                ";
                return false;
            }
            //cek ukuran
            if ($ukuran > 1000000) {
                echo "
                    <script>
                        alert('File gambar harus dibawah 1 MB');
                    </script>
                ";
                return false;
            }
            //lolos dan uplot
            move_uploaded_file($tmpSementara, 'img/akun/'.$namafile);
            return $namafile;

        }

	
 ?>