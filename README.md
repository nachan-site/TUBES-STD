# MUSIC PLAYER APP
## Deskripsi Aplikasi
Proyek yang dikembangkan pada tugas besar ini adalah membuat replika aplikasi pemutar musik modern yang menyerupai aplikasi YT Music. Aplikasi ini memiliki dua peran utama, yaitu Admin dan User, dimana masing-masing memiliki peran dan akses yang berbeda. Admin berperan untuk mengelola data lagu yang ada di library, sedangkan User sebagai pengguna aplikasi yang dapat memanfaatkan fitur pemutaran musik dan pengelolaan playlist.

Pada peran Admin, aplikasi menyediakan fitur untuk menambah, mengubah, melihat, dan menghapus data lagu yang terdapat pada library. Sementara itu, User dapat memutar lagu, baik dari library yang sudah disediakan oleh Admin, maupun dari playlist yang dibuat oleh User sendiri. Selain itu, User juga dapat membuat dan mengatur playlist, memutar lagu berikutnya atau sebelumnya, dan memberikan tanda Like pada lagu yang disukai. Lagu yang diberi tanda Like ini akan secara otomatis dimasukkan ke dalam playlist default bernama “Favorite”, sehingga User dapat mengakses lagunya dengan mudah.

Secara umum, aplikasi ini menggunakan struktur data Multi Linked List (MLL) dengan relasi N-to-N. Terdapat dua parent list utama, yaitu List Lagu sebagai library yang menyimpan seluruh data lagu, dan List Playlist yang menyimpan kumpulan playlist milik User. Hubungan antara playlist dan lagu dibentuk melalui relasi, sehingga satu lagu dapat berada di beberapa playlist tanpa terjadi duplikasi data. Selain itu, konsep graf juga digunakan pada fitur rekomendasi lagu. Karena pengelolaan data lagu sepenuhnya berada di tangan Admin, setiap perubahan data lagu akan langsung tersinkronisasi dan ditampilkan kepada User.

## Fitur Aplikasi
### Admin
- Menambah lagu ke dalam library
- Melihat seluruh lagu di library
- Mengubah data lagu
- Menghapus lagu dari library dan playlist user
- Membuat rekomendasi lagu
### User
- Mencari lagu berdasarkan judul lagu
- Memutar, pause, next dan previous lagu
- Mmebuat dan mengelola playlist
- Menyukai lagu
- Memutar lagu dari playlist atau library
- Mmemutar lagu rekomendasi menggunakan Graph dan BFS
  
## Struktur Data yang Digunakan
- **Doubly Linked List** -> Library lagu
- **Singly Linked List** -> Playlist
- **Multi Linked List** -> Relasi playlist dan lagu
- **Graph** -> Rekomendasi lagu berdasarkan genre atau bahasa
- **Queue** -> Urutan lagu rekomendasi, hasil dari algoritma BFS untuk rekomendasi lagu
  
## Cara Menjalankan Program
1. Pastikan Compiler C++ (seperti CLion atau Code::Blocks) sudah siap, jika belum bisa diinstal terlebih dahulu melalui link berikut : https://www.codeblocks.org/downloads/
2. Download file source (main.cpp dan lagu.cpp) dan file header (lagu.h)
3. Jalankan pada compiler


## Anggota Kelompok 11
- Nurul Inayah - 103052400085
- Maghfira Noura Errahma - 103052400008
- Firly Aurellia Putri - 103052400014
