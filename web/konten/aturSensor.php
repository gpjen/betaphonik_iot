<?php 

$sql = mysqli_query($konekdb, "SELECT * FROM `atursensor` ORDER BY no DESC LIMIT 1");

$data = mysqli_fetch_array($sql);


if (isset($_POST['simpanAturSensor'])) {

    $tdsMin = $_POST['tdsMinimum'];
    $tdsMax = $_POST['tdsMaksimal'];
    $phMin = $_POST['phMinimum'];
    $phMax = $_POST['ph_maksimal'];
    $pompaOn = $_POST['pompaOn'];
    $pompaOff = $_POST['pompaOff'];


    $sql = "INSERT INTO `atursensor` VALUES ('', '$tdsMin', '$tdsMax', '$phMin', '$phMax', '$pompaOn', '$pompaOff', current_timestamp())";
    
    $hasil = mysqli_query($konekdb, $sql);

    if ($hasil) {
        echo "
        <div class='container-fluid'>
        <div class='alert alert-success alert-dismissible' role='alert'>
          <button type='button' class='close' data-dismiss='alert' aria-label='Close'><span aria-hidden='true'>&times;</span></button>
          <strong>Berhasil</strong> menyimpan data.
        </div>
        </div>
        ";
    }else{
        echo "
        <div class='container-fluid'>
        <div class='alert alert-danger alert-dismissible' role='alert'>
          <button type='button' class='close' data-dismiss='alert' aria-label='Close'><span aria-hidden='true'>&times;</span></button>
          <strong>Gagal</strong> menyimpan data.
        </div>
        </div>
        ";
    }

    $sql = mysqli_query($konekdb, "SELECT * FROM `atursensor` ORDER BY no DESC LIMIT 1");

    $data = mysqli_fetch_array($sql);
}
    
 ?>

<br>    
<div class="container" data-aos="fade-right">
    <div class="row">
        <div class="col-lg-12 mb-4">
            <div class="card border-left-success shadow mb-4">
                <div class="card-header py-3">
                    <center><h4 class="m-0 font-weight-bold text-success">ATUR NILAI SENSOR</h4></center>
                </div>
                <div class="card-body">
                    <form method="post">
                        <div class="form-group row">
                            <div class="col-sm-6 mb-3 mb-sm-0">
                                <center><label for="floatingInputValue">TDS Minimum</label></center>
                                <input type="number" class="form-control" name="tdsMinimum" value="<?= $data['tds_minimal']; ?>" required style="text-align: center;" >
                            </div>
                            <div class="col-sm-6">
                                <center><label for="floatingInputValue">TDS Maksimal</label></center>
                                <input type="number" class="form-control" name="tdsMaksimal" value="<?= $data['tds_maksimal']; ?>" required style="text-align: center;">
                            </div>
                            <div class="col-sm-6 mb-3 mb-sm-0"><br>
                                <center><label for="floatingInputValue">PH Minimum</label></center>
                                <input type="text" class="form-control" name="phMinimum" value="<?= $data['ph_minimal']; ?>" required style="text-align: center;">
                            </div>
                            <div class="col-sm-6"><br>
                                <center><label for="floatingInputValue">PH Maksimal</label></center>
                                <input type="text" class="form-control" name="ph_maksimal" value="<?= $data['ph_maksimal']; ?>" required style="text-align: center;">
                            </div>

                            <div class="col-sm-6 mb-3 mb-sm-0"><br>
                                <center><label for="floatingInputValue">Pompa ON</label></center>
                                <input type="time" name="pompaOn" class="form-control" value="<?= $data['pompa_on']; ?>" required style="text-align: center;">
                            </div>
                            <div class="col-sm-6"><br>
                                <center><label for="floatingInputValue">Pompa Off</label></center>
                                <input type="time"  name="pompaOff" class="form-control" value="<?= $data['pompa_off']; ?>" required style="text-align: center;">
                            </div>
                            <div class="col-sm-3"></div>
                            <div class="col-sm-6"><br><br>
                                <button class="btn btn-success btn-block" name="simpanAturSensor" type="submit" onclick="">Simpan</button> 
                            </div>
                            <div class="col-sm-3"></div>
                            <div class="col-sm-12"><br><br>                                
                            </div>
                        </div>
                    </form>
                </div>
            </div>
        </div>
    </div>


</div>