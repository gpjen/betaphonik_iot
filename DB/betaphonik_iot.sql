-- phpMyAdmin SQL Dump
-- version 5.1.1
-- https://www.phpmyadmin.net/
--
-- Host: 127.0.0.1
-- Waktu pembuatan: 16 Agu 2021 pada 05.21
-- Versi server: 10.4.19-MariaDB
-- Versi PHP: 7.4.20

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Database: `betaphonik_iot`
--

-- --------------------------------------------------------

--
-- Struktur dari tabel `akun`
--

CREATE TABLE `akun` (
  `id` int(11) NOT NULL,
  `nama` varchar(100) NOT NULL,
  `user` varchar(50) NOT NULL,
  `pass` varchar(255) NOT NULL,
  `profil` varchar(100) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

--
-- Dumping data untuk tabel `akun`
--

INSERT INTO `akun` (`id`, `nama`, `user`, `pass`, `profil`) VALUES
(113, 'agan95', 'nyonggpj9995@gmail.com', '$2y$10$scRZ4MWj4nj8FNNTnVhFdem6y6k1j9T5GMuft8Ai9ulFpUbwg2krS', 'hidroponik_43.jpeg'),
(114, 'admin', 'admin123@gmail.com', '$2y$10$1dxbAqkKKcT0E5FYqYAxDOzeXLubTLVKIjuNZ.V.LrUhJhRiVHjIG', 'undraw_environment_iaus.svg'),
(124, 'gandi purna jen', 'gandipurna@yahoo.co.id', '$2y$10$I174tYRg7gEHjdO4/HG3u.oOt/TbeaPJGH7HwooDN/0K8Lm7KA4Gm', 'relay.jpg');

-- --------------------------------------------------------

--
-- Struktur dari tabel `atursensor`
--

CREATE TABLE `atursensor` (
  `no` int(11) NOT NULL,
  `tds_minimal` int(10) NOT NULL,
  `tds_maksimal` int(10) NOT NULL,
  `ph_minimal` decimal(10,2) NOT NULL,
  `ph_maksimal` decimal(10,2) NOT NULL,
  `pompa_on` varchar(10) NOT NULL,
  `pompa_off` varchar(10) NOT NULL,
  `waktu_update` datetime NOT NULL DEFAULT current_timestamp()
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

--
-- Dumping data untuk tabel `atursensor`
--

INSERT INTO `atursensor` (`no`, `tds_minimal`, `tds_maksimal`, `ph_minimal`, `ph_maksimal`, `pompa_on`, `pompa_off`, `waktu_update`) VALUES
(11, 1, 2, '3.30', '4.40', '01:00', '02:00', '2021-07-20 22:39:16'),
(12, 3, 4, '5.88', '8.90', '02:00', '18:00', '2021-07-20 22:52:35'),
(13, 800, 1230, '4.80', '7.10', '06:00', '20:30', '2021-07-21 06:07:46'),
(14, 700, 1200, '4.77', '6.90', '06:00', '20:30', '2021-07-21 06:12:53'),
(15, 600, 1180, '4.77', '6.90', '06:00', '20:30', '2021-07-21 06:13:54'),
(16, 599, 1179, '4.99', '7.88', '06:00', '20:30', '2021-07-21 06:17:10'),
(17, 599, 1179, '4.99', '7.88', '06:00', '21:00', '2021-07-21 06:18:06'),
(18, 890, 1200, '4.88', '7.10', '06:00', '18:00', '2021-07-21 15:14:02'),
(19, 890, 1200, '4.88', '7.10', '06:00', '18:00', '2021-08-10 13:38:35');

-- --------------------------------------------------------

--
-- Struktur dari tabel `sensor_1j`
--

CREATE TABLE `sensor_1j` (
  `id` int(11) NOT NULL,
  `waktu` varchar(6) NOT NULL,
  `tanggal` date NOT NULL,
  `sensor_tds` int(10) NOT NULL,
  `sensor_ph` decimal(10,2) NOT NULL,
  `PhDown` int(10) NOT NULL,
  `stok_nutrisiA` int(10) NOT NULL,
  `stok_nutrisiB` int(10) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

--
-- Dumping data untuk tabel `sensor_1j`
--

INSERT INTO `sensor_1j` (`id`, `waktu`, `tanggal`, `sensor_tds`, `sensor_ph`, `PhDown`, `stok_nutrisiA`, `stok_nutrisiB`) VALUES
(76, '6:37:9', '2021-08-16', 168, '4.06', 100, 0, 100),
(77, '6:37:1', '2021-08-16', 1339, '3.37', 100, 0, 100),
(80, '10:0:2', '2021-08-16', 1457, '7.12', 100, 100, 100),
(81, '10:0:2', '2021-08-16', 1002, '7.13', 100, 100, 100),
(83, '06:00', '2021-08-16', 890, '6.20', 4, 50, 60);

-- --------------------------------------------------------

--
-- Struktur dari tabel `sensor_30`
--

CREATE TABLE `sensor_30` (
  `id` int(11) NOT NULL,
  `waktu` varchar(10) NOT NULL,
  `tanggal` date NOT NULL,
  `suhu_udara` int(10) NOT NULL,
  `kelembapan_udara` int(10) NOT NULL,
  `cahaya` int(10) NOT NULL,
  `suhu_air` int(10) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

--
-- Dumping data untuk tabel `sensor_30`
--

INSERT INTO `sensor_30` (`id`, `waktu`, `tanggal`, `suhu_udara`, `kelembapan_udara`, `cahaya`, `suhu_air`) VALUES
(118, '6:36:39', '2021-08-16', 28, 89, 5, 12),
(119, '6:37:9', '2021-08-16', 28, 88, 8, 26),
(120, '6:42:17', '2021-08-11', 28, 88, 9, 33),
(121, '6:43:18', '2021-08-16', 28, 88, 88, 26),
(122, '6:44:20', '2021-08-16', 28, 88, 8, 26),
(125, '10:0:23', '2021-08-16', 28, 91, 14, 26),
(126, '10:1:12', '2021-08-16', 28, 91, 14, 26),
(127, '10:2:13', '2021-08-16', 28, 91, 12, 26),
(128, '10:3:14', '2021-08-16', 28, 91, 10, 26),
(129, '10:4:15', '2021-08-16', 28, 92, 10, 26),
(130, '10:5:17', '2021-08-16', 28, 92, 10, 26),
(131, '10:6:19', '2021-08-16', 28, 92, 10, 26),
(132, '10:7:21', '2021-08-16', 28, 91, 10, 26),
(133, '10:8:23', '2021-08-16', 28, 91, 10, 26),
(134, '10:9:24', '2021-08-16', 28, 91, 8, 26),
(135, '10:10:25', '2021-08-16', 28, 91, 9, 26),
(136, '10:11:26', '2021-08-16', 28, 91, 10, 26),
(137, '10:12:27', '2021-08-16', 28, 92, 10, 26),
(138, '10:13:29', '2021-08-16', 28, 92, 10, 26),
(139, '10:14:30', '2021-08-16', 27, 92, 11, 26),
(140, '10:15:31', '2021-08-16', 27, 92, 12, 26),
(141, '10:16:32', '2021-08-16', 27, 92, 12, 26),
(142, '10:17:33', '2021-08-16', 27, 92, 12, 26),
(143, '10:18:35', '2021-08-16', 27, 92, 12, 26),
(144, '10:19:36', '2021-08-16', 27, 92, 13, 26),
(145, '10:20:37', '2021-08-06', 27, 92, 13, 26),
(146, '10:21:38', '2021-08-06', 27, 92, 13, 26),
(147, '10:22:40', '2021-08-06', 27, 92, 13, 26),
(148, '10:23:41', '2021-08-06', 27, 93, 14, 26),
(149, '10:24:42', '2021-08-06', 27, 93, 14, 26),
(150, '10:25:43', '2021-08-06', 27, 93, 14, 26),
(151, '10:26:44', '2021-08-06', 27, 93, 13, 26),
(152, '10:27:46', '2021-08-06', 27, 92, 14, 26),
(153, '10:28:47', '2021-08-06', 27, 92, 14, 26),
(154, '10:29:48', '2021-08-06', 27, 92, 14, 26),
(155, '10:30:49', '2021-08-06', 27, 92, 13, 26),
(156, '10:31:50', '2021-08-06', 27, 93, 14, 26),
(157, '10:32:52', '2021-08-06', 27, 93, 14, 26),
(158, '10:33:53', '2021-08-06', 27, 93, 14, 26),
(159, '10:34:54', '2021-08-06', 27, 93, 14, 26),
(160, '10:35:55', '2021-08-06', 27, 93, 14, 26),
(161, '10:36:57', '2021-08-06', 27, 93, 14, 26),
(162, '10:37:58', '2021-08-16', 27, 93, 14, 26);

-- --------------------------------------------------------

--
-- Struktur dari tabel `statuskendali`
--

CREATE TABLE `statuskendali` (
  `id` int(11) NOT NULL,
  `waktu` varchar(7) NOT NULL,
  `tanggal` date NOT NULL,
  `Status_PPM` varchar(60) NOT NULL,
  `Status_PH` varchar(50) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

--
-- Dumping data untuk tabel `statuskendali`
--

INSERT INTO `statuskendali` (`id`, `waktu`, `tanggal`, `Status_PPM`, `Status_PH`) VALUES
(93, '10:0:23', '2021-08-16', 'SISTEM AKTIF', 'SISTEM AKTIF'),
(96, '11:01', '2021-08-16', 'SISTEM TIDAK AKTIF', 'SISTEM TIDAK AKTIF'),
(97, '12:01', '2021-08-16', 'Ganti Air Nutrisi', 'Ganti Air Nutrisi'),
(98, '12:02', '2021-08-16', 'Suhu Air Lebih Dari 38 C', 'PH Aman');

--
-- Indexes for dumped tables
--

--
-- Indeks untuk tabel `akun`
--
ALTER TABLE `akun`
  ADD PRIMARY KEY (`id`),
  ADD UNIQUE KEY `user` (`user`);

--
-- Indeks untuk tabel `atursensor`
--
ALTER TABLE `atursensor`
  ADD PRIMARY KEY (`no`);

--
-- Indeks untuk tabel `sensor_1j`
--
ALTER TABLE `sensor_1j`
  ADD PRIMARY KEY (`id`);

--
-- Indeks untuk tabel `sensor_30`
--
ALTER TABLE `sensor_30`
  ADD PRIMARY KEY (`id`);

--
-- Indeks untuk tabel `statuskendali`
--
ALTER TABLE `statuskendali`
  ADD PRIMARY KEY (`id`);

--
-- AUTO_INCREMENT untuk tabel yang dibuang
--

--
-- AUTO_INCREMENT untuk tabel `akun`
--
ALTER TABLE `akun`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=125;

--
-- AUTO_INCREMENT untuk tabel `atursensor`
--
ALTER TABLE `atursensor`
  MODIFY `no` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=20;

--
-- AUTO_INCREMENT untuk tabel `sensor_1j`
--
ALTER TABLE `sensor_1j`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=84;

--
-- AUTO_INCREMENT untuk tabel `sensor_30`
--
ALTER TABLE `sensor_30`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=163;

--
-- AUTO_INCREMENT untuk tabel `statuskendali`
--
ALTER TABLE `statuskendali`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=99;
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
