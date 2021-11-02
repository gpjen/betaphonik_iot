
<?php 
    
    
    if (isset($_POST['carilapor'])) {

        $date   = $_POST['tanggallapor'];
        $sql    = "SELECT * FROM `statuskendali` WHERE tanggal = '$date' ORDER BY id ASC;";
        $hasil  = mysqli_query($konekdb, $sql);

        $datet   = date("d F Y", strtotime($date));

    } else {
        $sql    = "SELECT * FROM `statuskendali` WHERE tanggal = CURDATE() ORDER BY id ASC;";
        $hasil  = mysqli_query($konekdb, $sql);    
        $date   = date("Y-m-d");
    }

 ?>


<br>
<div class="container" data-aos="fade-right">
<div class="card border-left-success shadow mb-4">
    <div class="card-header py-3">

        <div class="container"><br>
            <center>
            <h3 class="text-success">AKTIFITAS PPM & PH
                <?php 
                    if ($date === date("Y-m-d")) {
                        echo "HARI INI";
                    }else {
                        echo "( ".$datet." )";
                    }
                 ?>
            </h3><br>

            <form method="POST" class="d-sm-inline-block form-inline ml-md-3 my-2 my-md-0 mw-100">
                <div class="input-group">
                    <input type="date" name="tanggallapor" class="form-control bg-light border-5 small" 
                        aria-label="Search" aria-describedby="basic-addon2" value="<?= $date ?>">
                    <div class="input-group-append">
                        <button class="btn btn-success" type="submit" name="carilapor">
                            <i class="fas fa-search fa-sm"></i>
                        </button>
                    </div>
                </div>
            </form>


            </center>
        </div>


        
    </div>
    <div class="card-body">
        <div class="table-responsive">
            <table class="table table-hover" id="dataTable" width="100%" cellspacing="0">
                <thead>
                    <tr style="text-align: center;">
                        <th >Waktu</th>
                        <th>Status PPM</th>
                        <th>Status PH</th>
                    </tr>
                </thead>
                <tbody>

                <?php 

                foreach ($hasil as $X) {
                    
                 ?>
                    <tr"> 
                        <td style="text-align: center;"><?= $X['waktu']; ?></td>
                        <?php

                            switch ($X['Status_PPM']) {
                                case 'SISTEM AKTIF':
                                    echo "
                                        <td class='border-left-info' style=' text-align: center;'> 
                                          SISTEM AKTIF
                                        </td>
                                    ";
                                    break;
                                case 'SISTEM TIDAK AKTIF':
                                    echo "
                                        <td class='border-left-info' style='text-align: center;'> 
                                          SISTEM NON-AKTIF
                                        </td>  
                                        
                                    ";
                                    break;
                                case 'Ganti Air Nutrisi':
                                    echo "
                                        <td class='border-left-danger' style='text-align: center;'> 
                                          PERINGATAN, GANTI AIR NUTRISI
                                        </td> 

                                    ";
                                    break;
                                case 'Suhu Air Lebih Dari 38 C':
                                    echo "
                                        <td class='border-left-warning' style='text-align: center;'> 
                                          Suhu Air > 38&deg;C
                                        </td>
                                        
                                    ";
                                    break;
                                case 'Penambahan Nutrisi':
                                    echo "
                                        <td class='border-left-success' style='text-align: center;'> 
                                          Penambahan Nutrisi <br> ke Air Nutrisi
                                        </td>
                                    ";
                                    break;
                                case 'PPM AMAN':
                                    echo "
                                        <td class='border-left-success' style='text-align: center;'> 
                                          PPM AMAN <br> ke Air Nutrisi
                                        </td>
                                    ";
                                    break;
                                
                                default:
                                    echo "<td></tr>";
                                    break;
                            }


                        ?> 
                        <?php

                        switch ($X['Status_PH']) {
                                case 'SISTEM AKTIF':
                                    echo "
                                        <td class='border-left-info' style='text-align: center;'> 
                                          SISTEM AKTIF
                                        </td> 
                                    ";
                                    break;
                                case 'SISTEM TIDAK AKTIF':
                                    echo "
                                        <td class='border-left-info' style='text-align: center;'> 
                                          SISTEM NON-AKTIF
                                        </td>  
                                        
                                    ";
                                    break;
                                case 'Ganti Air Nutrisi':
                                    echo "
                                        <td class='border-left-danger' style='text-align: center;'> 
                                          PERINGATAN, GANTI AIR NUTRISI
                                        </td>  
                                    ";
                                    break;
                                case 'PH Aman':
                                    echo "
                                        <td class='border-left-success' style='text-align: center;'> 
                                          PH AMAN
                                        </td>
                                        
                                    ";
                                    break;
                                case 'Penambahan PH Down':
                                    echo "
                                        <td class='border-left-success' style='text-align: center;'> 
                                          PH Down Ditambahkan <br> ke Air Nutrisi
                                        </td>
                                        
                                    ";
                                    break;
                                
                                default:
                                    echo "<td></tr>";
                                    break;

                        }

                        ?>
                    </tr>

                <?php  } ?>
                </tbody>
            </table><br><br>
        </div>
    </div>
</div>
</div>
