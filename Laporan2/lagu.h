#ifndef LAGU_H_INCLUDED
#define LAGU_H_INCLUDED
#include <iostream>
using namespace std;

// List Library Lagu (Parent 1 - DLL)
typedef struct elmLagu *adrLagu;

struct Lagu {
    int IDLagu;
    string judulLagu;
    string penyanyi;
    string album;
    int tahun;
    string genre;
    string bahasa;
    bool disukai;
};

struct elmLagu{
    Lagu info;
    adrLagu prev;
    adrLagu next;
};


// Child = Relasi playlist-lagu
typedef struct elmRelasi *adrRelasi;

struct elmRelasi {
    adrLagu lagu;
    adrRelasi next;
};

// List Playlist (Parent 2 - SLL)
typedef struct elmPlaylist *adrPlaylist;

struct elmPlaylist{
    string namaPlaylist;
    adrPlaylist next;
    adrRelasi firstRelasi;
};

// struktur list
struct ListPlaylist{
    adrPlaylist first;
};

struct ListLagu{
    adrLagu first;
    adrLagu last;
};

// fungsi primitif
void createListLagu(ListLagu &L);
// {I.S. -.
//  F.S. Terbentuk List Lagu L, dimana first dan last dari L bernilai NIL}
void createListPlaylist(ListPlaylist &P);
// {I.S. -.
//  F.S. Terbentuk List Lagu P, dimana first P bernilai NIL}

bool isEmptyLibrary(ListLagu L);
// {I.S. Terdefinisi List Lagu L.
//  F.S. Mengemballikan true jika L kosong, false jika ada isinya.}
bool isEmptyPlaylist(ListPlaylist P);
// {I.S. Terdefinisi List Playlist.
//  F.S. Mengemballikan true jika P kosong, false jika ada isinya.}

adrLagu createElmLagu(int id, string judul, string penyanyi, string album, int tahun, string genre, string bahasa);
// {I.S. Terdefinisi data lagu melalui parameter.
//  F.S. Menghasilkan elemen lagu baru dengan data sesuai parameter; dan pointer bernilai NULL.}
adrPlaylist createElmPlaylist(string nama);
// {I.S. nama playlist diberikan melalui parameter.
//  F.S. Menghasilkan elemen playlist baru dengan nama yang diberikan dan list relasi kosong.}
adrRelasi createElmRelasi(adrLagu L);
// {I.S. Terdefinisi alamat Lagu L melalui parameter.
//  F.S. Mengembalikan alamat elemen Relasi baru yang menunjuk ke lagu L.}

// List Lagu (DLL)
void insertLastLagu(ListLagu &L, adrLagu p);
// {I.S. Isi List Lagu L mungkin kosong.
//  F.S. elemen p ditambahkan ke bagian akhir List Lagu.}
adrLagu findLagu(ListLagu L, int id);
// {I.S. List lagu L mungkin kosong.
//  F.S. Mengembalikan alamat lagu dengan ID yang dicari jika ditemukan; mengembalikan NULL jika tidak ada.}
void deleteLaguFromAllPlaylist(ListPlaylist P, adrLagu q);
// {I.S.
//  F.S. Menghapus semua lagu yang ada di playlist.}
void deleteElmLagu(ListLagu &L, adrLagu p);
// {I.S.
//  F.S. Menghapus lagu dari libbrary}
void deleteLagu(ListLagu &L, ListPlaylist &P, int id);
// {I.S.
//  F.S. Lagu dengan id yang telah ditentukan dihapus dari Library dan semua Playlist.}
void editLagu(adrLagu p);
//{I.S. Terdefinisi elemen p lagu yang tidak NIL.
// F.S. Data lagu diubah.}

// Detail Lagu
void playLagu(ListPlaylist &P, adrLagu &play);
//{I.S. Tidak ada lagu diputar atau lagu dalam keadaan pause.
// F.S. Lagu memunculkan notifikasi "Playing"}

void pauseLagu(ListPlaylist &P, adrLagu &pause);
//{I.S. Tlagu dalam keadaan play.
// F.S. Lagu memunculkan notifikasi "Paused"}


// List Playlist (SLL)
void insertFirstPlaylist(ListPlaylist &P, adrPlaylist p);
// {I.S. Isi Playlist P mungkin kosong.
//  F.S. Elemen p ditambahkan ke awal List Playlist.}
adrPlaylist findPlaylist(ListPlaylist P, string nama);
// {I.S. List Playlist P mungkin kosong
//  F.S. Mengembalikan alamat playlist dengan nama yang dicari jika ditemukan; NULL jika tidak ada.}
void deletePlaylist(ListPlaylist P, string nama);
// {I.S. List Playlist P sudah terisi.
//  F.S. Playlist dengan nama tertentu akan terhapus dari list jika ditemukan.}

// Relasi
void addLaguToPlaylist(adrPlaylist p, adrLagu L);
// {I.S. Playlist P mungkin kosong atau sudah memiliki relasi.
//  F.S. Relasi Lagu L dimasukkan ke dalam playlist.}
void deleteRelasiByLagu(adrPlaylist p, adrLagu L);
// {I.S. Playlist P mungkin kosong.
//  F.S. Relasi yang menunjuk ke Lagu L terhapus jika ditemukan.}


void showLibrary(ListLagu L);
// {I.S. Terdefinisi List Lagu L yang mungkin kosong.
//  F.S. Menampilkan Seluruh lagu dari Library.}
void showPlaylist(ListPlaylist P);
// {I.S. Terdefinisi List Playlist yang mungkin kosong.
//  F.S. Menampilkan daftar Playlist yang telah dibuat beserta daftar lagu di dalamnya.}
void showPlaylistLagu(ListPlaylist P);


void dataDummyLagu(ListLagu &L);

#endif // LAGU_H_INCLUDED
