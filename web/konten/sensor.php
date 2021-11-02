<?php 

$sql = mysqli_query($konekdb, "SELECT * FROM sensor_30 ORDER BY id DESC LIMIT 1");
$sensor_30 = mysqli_fetch_array($sql);
$sql = mysqli_query($konekdb, "SELECT * FROM sensor_1j ORDER BY id DESC LIMIT 1");
$sensor_1j = mysqli_fetch_array($sql);

 ?>




<div class="container-fluid">

    <!-- Page Heading -->
    <div class="d-sm-flex align-items-center justify-content-between mb-4">
        <h1 class="h3 mb-0 text-gray-800">Laporan Sensor Hari Ini</h1> 
    </div>

    <!-- Content Row -->
    <div class="row">


        <div class="col-lg-12 mb-4" data-aos="fade-up">
            <div class="card shadow mb-4">
                <!-- Card Header - Accordion -->
                <a href="#Stok" class="d-block card-header py-3" data-toggle="collapse"
                    role="button" aria-expanded="true" aria-controls="collapseCardExample">
                    <h6 class="m-0 font-weight-bold text-primary">Stok Nutrisi & Ph down</h6>
                </a>
                <!-- Card Content - Collapse -->
                <div class="collapse" id="Stok">
                    <div class="card-body">
                    <h4 class="small font-weight-bold">Nutrisi A 
                        <span id="stok_nutrisiA"></span>
                    <h4 class="small font-weight-bold">Nutrisi B 
                        <span id="stok_nutrisiB"></span>
                    <h4 class="small font-weight-bold">Ph down 
                        <span id="PhDown"></span>

                </div>
                </div>
            </div>
        </div>


        <!-- SUHU UDARA -->
        <div class="col-xl-4 col-md-6 mb-4" data-aos="fade-up">
            <div class="card border-left-info shadow h-100 py-2">
                <div class="card-body">
                    <div class="row no-gutters align-items-center">
                        <div class="col mr-2">
                            <div class="text-xs font-weight-bold text-info text-uppercase mb-1">
                                Suhu Udara</div>
                            <div class="h5 mb-0 font-weight-bold text-gray-800">
                                <span id="suhu_udara"></span> &deg;C
                            </div>
                        </div>
                        <div class="col-auto">
                            <a class="" href="#SuhuUdara">
                            <svg xmlns="http://www.w3.org/2000/svg" width="30" height="30" fill="currentColor" class="bi bi-thermometer-half" viewBox="0 0 16 16">
<path d="M9.5 12.5a1.5 1.5 0 1 1-2-1.415V6.5a.5.5 0 0 1 1 0v4.585a1.5 1.5 0 0 1 1 1.415z"/>
<path d="M5.5 2.5a2.5 2.5 0 0 1 5 0v7.55a3.5 3.5 0 1 1-5 0V2.5zM8 1a1.5 1.5 0 0 0-1.5 1.5v7.987l-.167.15a2.5 2.5 0 1 0 3.333 0l-.166-.15V2.5A1.5 1.5 0 0 0 8 1z"/>
</svg></a>
                        </div>
                    </div>
                </div>
            </div>
        </div>

        <!-- KELEMBAPAN UDARA -->
        <div class="col-xl-4 col-md-6 mb-4" data-aos="fade-up">
            <div class="card border-left-dark shadow h-100 py-2">
                <div class="card-body">
                    <div class="row no-gutters align-items-center">
                        <div class="col mr-2">
                            <div class="text-xs font-weight-bold text-dark text-uppercase mb-1">
                                Kelembapan Udara</div>
                            <div class="h5 mb-0 font-weight-bold text-gray-800">
                                <span id="kelembapan_udara"></span> %
                            </div>
                        </div>
                        <div class="col-auto"><a href="#KelembapanUdara">
                            <svg xmlns="http://www.w3.org/2000/svg" width="30" height="30" fill="currentColor" class="bi bi-cloud-haze" viewBox="0 0 16 16">
<path d="M8.5 3a4.002 4.002 0 0 0-3.8 2.745.5.5 0 1 1-.949-.313 5.002 5.002 0 0 1 9.654.595A3 3 0 0 1 13 12H4.5a.5.5 0 0 1 0-1H13a2 2 0 0 0 .001-4h-.026a.5.5 0 0 1-.5-.445A4 4 0 0 0 8.5 3zM0 7.5A.5.5 0 0 1 .5 7h5a.5.5 0 0 1 0 1h-5a.5.5 0 0 1-.5-.5zm2 2a.5.5 0 0 1 .5-.5h9a.5.5 0 0 1 0 1h-9a.5.5 0 0 1-.5-.5zm-2 4a.5.5 0 0 1 .5-.5h9a.5.5 0 0 1 0 1h-9a.5.5 0 0 1-.5-.5z"/>
</svg></a>
                        </div>
                    </div>
                </div>
            </div>
        </div>

        <!-- SENSOR CAHAYA -->
        <div class="col-xl-4 col-md-6 mb-4" data-aos="fade-up">
            <div class="card border-left-danger shadow h-100 py-2">
                <div class="card-body">
                    <div class="row no-gutters align-items-center">
                        <div class="col mr-2">
                            <div class="text-xs font-weight-bold text-danger text-uppercase mb-1">Cahaya
                            </div>
                            <div class="row no-gutters align-items-center">
                                <div class="col-auto">
                                    <div class="h5 mb-0 mr-3 font-weight-bold text-gray-800">
                                        <span id="cahaya"></span> Lux
                                    </div>
                                </div>
                            </div>
                        </div>
                        <div class="col-auto"><a href="#luxCahaya">
                            <svg xmlns="http://www.w3.org/2000/svg" width="30" height="30" fill="currentColor" class="bi bi-brightness-high" viewBox="0 0 16 16">
<path d="M8 11a3 3 0 1 1 0-6 3 3 0 0 1 0 6zm0 1a4 4 0 1 0 0-8 4 4 0 0 0 0 8zM8 0a.5.5 0 0 1 .5.5v2a.5.5 0 0 1-1 0v-2A.5.5 0 0 1 8 0zm0 13a.5.5 0 0 1 .5.5v2a.5.5 0 0 1-1 0v-2A.5.5 0 0 1 8 13zm8-5a.5.5 0 0 1-.5.5h-2a.5.5 0 0 1 0-1h2a.5.5 0 0 1 .5.5zM3 8a.5.5 0 0 1-.5.5h-2a.5.5 0 0 1 0-1h2A.5.5 0 0 1 3 8zm10.657-5.657a.5.5 0 0 1 0 .707l-1.414 1.415a.5.5 0 1 1-.707-.708l1.414-1.414a.5.5 0 0 1 .707 0zm-9.193 9.193a.5.5 0 0 1 0 .707L3.05 13.657a.5.5 0 0 1-.707-.707l1.414-1.414a.5.5 0 0 1 .707 0zm9.193 2.121a.5.5 0 0 1-.707 0l-1.414-1.414a.5.5 0 0 1 .707-.707l1.414 1.414a.5.5 0 0 1 0 .707zM4.464 4.465a.5.5 0 0 1-.707 0L2.343 3.05a.5.5 0 1 1 .707-.707l1.414 1.414a.5.5 0 0 1 0 .708z"/>
</svg></a>
                        </div>
                    </div>
                </div>
            </div>
        </div>

        <!-- SUHU AIR -->
        <div class="col-xl-4 col-md-6 mb-4" data-aos="fade-up">
            <div class="card border-left-warning shadow h-100 py-2">
                <div class="card-body">
                    <div class="row no-gutters align-items-center">
                        <div class="col mr-2">
                            <div class="text-xs font-weight-bold text-warning text-uppercase mb-1">
                                Suhu AIR</div>
                            <div class="h5 mb-0 font-weight-bold text-gray-800">
                                <span id="suhu_air"></span> &deg;C
                            </div>
                        </div>
                        <div class="col-auto"><a href="#SuhuAir">
                            <svg xmlns="http://www.w3.org/2000/svg" width="30" height="30" fill="currentColor" class="bi bi-droplet" viewBox="0 0 16 16">
<path fill-rule="evenodd" d="M7.21.8C7.69.295 8 0 8 0c.109.363.234.708.371 1.038.812 1.946 2.073 3.35 3.197 4.6C12.878 7.096 14 8.345 14 10a6 6 0 0 1-12 0C2 6.668 5.58 2.517 7.21.8zm.413 1.021A31.25 31.25 0 0 0 5.794 3.99c-.726.95-1.436 2.008-1.96 3.07C3.304 8.133 3 9.138 3 10a5 5 0 0 0 10 0c0-1.201-.796-2.157-2.181-3.7l-.03-.032C9.75 5.11 8.5 3.72 7.623 1.82z"/>
<path fill-rule="evenodd" d="M4.553 7.776c.82-1.641 1.717-2.753 2.093-3.13l.708.708c-.29.29-1.128 1.311-1.907 2.87l-.894-.448z"/>
</svg></a>
                        </div>
                    </div>
                </div>
            </div>
        </div>

        <!-- NUTRISI AIR -->
        <div class="col-xl-4 col-md-6 mb-4" data-aos="fade-up">
            <div class="card border-left-success shadow h-100 py-2">
                <div class="card-body">
                    <div class="row no-gutters align-items-center">
                        <div class="col mr-2">
                            <div class="text-xs font-weight-bold text-success text-uppercase mb-1">
                                Nutrisi AIR</div>
                            <div class="h5 mb-0 font-weight-bold text-gray-800">
                                <span id="nutrisi_air"></span> Ppm
                            </div>
                        </div>
                        <div class="col-auto"><a href="#NutrisiAir">
                            <svg xmlns="http://www.w3.org/2000/svg" width="30" height="30" fill="currentColor" class="bi bi-droplet-fill" viewBox="0 0 16 16">
<path fill-rule="evenodd" d="M8 16a6 6 0 0 0 6-6c0-1.655-1.122-2.904-2.432-4.362C10.254 4.176 8.75 2.503 8 0c0 0-6 5.686-6 10a6 6 0 0 0 6 6zM6.646 4.646c-.376.377-1.272 1.489-2.093 3.13l.894.448c.78-1.559 1.616-2.58 1.907-2.87l-.708-.708z"/>
</svg></a>
                        </div>
                    </div>
                </div>
            </div>
        </div>

        <!-- PH AIR -->
        <div class="col-xl-4 col-md-6 mb-4" data-aos="fade-up">
            <div class="card border-left-primary shadow h-100 py-2">
                <div class="card-body">
                    <div class="row no-gutters align-items-center">
                        <div class="col mr-2">
                            <div class="text-xs font-weight-bold text-primary text-uppercase mb-1">
                                PH AIR</div>
                            <div class="h5 mb-0 font-weight-bold text-gray-800">
                                <span id="ph_air"></span> Ph
                            </div>
                        </div>
                        <div class="col-auto"><a href="#PhAir">
                            <svg xmlns="http://www.w3.org/2000/svg" width="30" height="30" fill="currentColor" class="bi bi-water" viewBox="0 0 16 16">
<path d="M.036 3.314a.5.5 0 0 1 .65-.278l1.757.703a1.5 1.5 0 0 0 1.114 0l1.014-.406a2.5 2.5 0 0 1 1.857 0l1.015.406a1.5 1.5 0 0 0 1.114 0l1.014-.406a2.5 2.5 0 0 1 1.857 0l1.015.406a1.5 1.5 0 0 0 1.114 0l1.757-.703a.5.5 0 1 1 .372.928l-1.758.703a2.5 2.5 0 0 1-1.857 0l-1.014-.406a1.5 1.5 0 0 0-1.114 0l-1.015.406a2.5 2.5 0 0 1-1.857 0l-1.014-.406a1.5 1.5 0 0 0-1.114 0l-1.015.406a2.5 2.5 0 0 1-1.857 0L.314 3.964a.5.5 0 0 1-.278-.65zm0 3a.5.5 0 0 1 .65-.278l1.757.703a1.5 1.5 0 0 0 1.114 0l1.014-.406a2.5 2.5 0 0 1 1.857 0l1.015.406a1.5 1.5 0 0 0 1.114 0l1.014-.406a2.5 2.5 0 0 1 1.857 0l1.015.406a1.5 1.5 0 0 0 1.114 0l1.757-.703a.5.5 0 1 1 .372.928l-1.758.703a2.5 2.5 0 0 1-1.857 0l-1.014-.406a1.5 1.5 0 0 0-1.114 0l-1.015.406a2.5 2.5 0 0 1-1.857 0l-1.014-.406a1.5 1.5 0 0 0-1.114 0l-1.015.406a2.5 2.5 0 0 1-1.857 0L.314 6.964a.5.5 0 0 1-.278-.65zm0 3a.5.5 0 0 1 .65-.278l1.757.703a1.5 1.5 0 0 0 1.114 0l1.014-.406a2.5 2.5 0 0 1 1.857 0l1.015.406a1.5 1.5 0 0 0 1.114 0l1.014-.406a2.5 2.5 0 0 1 1.857 0l1.015.406a1.5 1.5 0 0 0 1.114 0l1.757-.703a.5.5 0 1 1 .372.928l-1.758.703a2.5 2.5 0 0 1-1.857 0l-1.014-.406a1.5 1.5 0 0 0-1.114 0l-1.015.406a2.5 2.5 0 0 1-1.857 0l-1.014-.406a1.5 1.5 0 0 0-1.114 0l-1.015.406a2.5 2.5 0 0 1-1.857 0L.314 9.964a.5.5 0 0 1-.278-.65zm0 3a.5.5 0 0 1 .65-.278l1.757.703a1.5 1.5 0 0 0 1.114 0l1.014-.406a2.5 2.5 0 0 1 1.857 0l1.015.406a1.5 1.5 0 0 0 1.114 0l1.014-.406a2.5 2.5 0 0 1 1.857 0l1.015.406a1.5 1.5 0 0 0 1.114 0l1.757-.703a.5.5 0 1 1 .372.928l-1.758.703a2.5 2.5 0 0 1-1.857 0l-1.014-.406a1.5 1.5 0 0 0-1.114 0l-1.015.406a2.5 2.5 0 0 1-1.857 0l-1.014-.406a1.5 1.5 0 0 0-1.114 0l-1.015.406a2.5 2.5 0 0 1-1.857 0l-1.757-.703a.5.5 0 0 1-.278-.65z"/>
</svg></a>
                        </div>
                    </div>
                </div>
            </div>
        </div>
    </div>

    

    <div class="row">

        <div class="col-xl-6 col-lg-6" id="PhAir" data-aos="zoom-in-right">
            <div class="card border-bottom-primary shadow mb-4">
                <div
                    class="card-header py-3 d-flex flex-row align-items-center justify-content-between">
                    <h6 class="m-0 font-weight-bold text-primary">Keasaman AIR (PH)</h6>
                </div>
                <!-- Card Body -->
                <div class="card-body">
                    <div class="chart-area">
                        <canvas id="PH_Chart">Bowser Anda tidak suport Canvas</canvas>
                    </div>
                </div>
            </div>
        </div>

        <!-- Area Chart -->
        <div class="col-xl-6 col-lg-6" id="NutrisiAir" data-aos="zoom-in-left">
            <div class="card border-bottom-success shadow mb-4">
                <div
                    class="card-header py-3 d-flex flex-row align-items-center justify-content-between">
                    <h6 class="m-0 font-weight-bold text-success">Nutrisi AIR AB Mix (PPM)</h6>
                </div>
                <!-- Card Body -->
                <div class="card-body">
                    <div class="chart-area">
                        <canvas id="TDS_Chart">Bowser Anda tidak suport Canvas</canvas>
                    </div>
                </div>
            </div>
        </div>



        <div class="col-xl-6 col-lg-6" id="SuhuAir" data-aos="zoom-in-right">
            <div class="card border-bottom-warning shadow mb-4">
                <div
                    class="card-header py-3 d-flex flex-row align-items-center justify-content-between">
                    <h6 class="m-0 font-weight-bold text-warning">Suhu AIR (&deg;C)</h6>
                </div>
                <!-- Card Body -->
                <div class="card-body">
                    <div class="chart-area">
                        <canvas id="SAIR_Chart">Bowser Anda tidak suport Canvas</canvas>
                    </div>
                </div>
            </div>
        </div>



        <div class="col-xl-6 col-lg-6" id="luxCahaya" data-aos="zoom-in-left">
            <div class="card border-bottom-danger shadow mb-4">
                <div
                    class="card-header py-3 d-flex flex-row align-items-center justify-content-between">
                    <h6 class="m-0 font-weight-bold text-danger">Cahaya (Lux)</h6>
                </div>
                <!-- Card Body -->
                <div class="card-body">
                    <div class="chart-area">
                        <canvas id="LUX_Chart">Bowser Anda tidak suport Canvas</canvas>
                    </div>
                </div>
            </div>
        </div>


        <div class="col-xl-6 col-lg-6" id="SuhuUdara" data-aos="zoom-in-right">
            <div class="card border-bottom-info shadow mb-4">
                <div
                    class="card-header py-3 d-flex flex-row align-items-center justify-content-between">
                    <h6 class="m-0 font-weight-bold text-info">Suhu Udara (&deg;C)</h6>
                </div>
                <!-- Card Body -->
                <div class="card-body">
                    <div class="chart-area">
                        <canvas id="TEMP_Chart">Bowser Anda tidak suport Canvas</canvas>
                    </div>
                </div>
            </div>
        </div>

        <div class="col-xl-6 col-lg-6" id="KelembapanUdara" data-aos="zoom-in-left">
            <div class="card border-bottom-dark shadow mb-4">
                <div
                    class="card-header py-3 d-flex flex-row align-items-center justify-content-between">
                    <h6 class="m-0 font-weight-bold text-dark">Kelembapan Udara (%)</h6>
                </div>
                <!-- Card Body -->
                <div class="card-body">
                    <div class="chart-area">
                        <canvas id="HUMI_Chart">Bowser Anda tidak suport Canvas</canvas>
                    </div>
                </div>
            </div>
        </div>

    </div>

</div>
