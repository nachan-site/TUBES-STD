#ifndef LAGU_H_INCLUDED
#define LAGU_H_INCLUDED
#include <iostream>
using namespace std;

// List Library Lagu (Parent 1 - DLL)
typedef struct elmLagu *adrLagu;

struct Lagu {
    string judulLagu;
    string penyanyi;
    string album;
    int tahun;
    string genre;
    string bahasa;
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
    adrRelasi prev;
    adrRelasi next;
};

// List Playlist (Parent 2 - SLL)
typedef struct elmPlaylist *adrPlaylist;

struct elmPlaylist{
    string namaPlaylist;
    adrPlaylist next;
    adrRelasi firstRelasi;
};

// Graph
typedef struct elmVertex *adrVertex;
typedef struct elmEdge *adrEdge;

struct elmVertex{
    adrLagu lagu;
    int visited;
    adrEdge firstEdge;
    adrVertex next;
};

struct elmEdge{
    adrVertex vertex;
    adrEdge next;
};

struct Graph {
    adrVertex first;
};

// struktur list
struct ListPlaylist{
    adrPlaylist first;
};

struct ListLagu{
    adrLagu first;
    adrLagu last;
};

// Queue
typedef struct elmQueue *adrQueue;

struct elmQueue {
    adrVertex info;
    adrQueue next;
    adrQueue prev;
};

struct Queue {
    adrQueue head;
    adrQueue tail;
};

void createListLagu(ListLagu &L);
// {I.S. List Lagu belum terdefinisi.
//  F.S. Terbentuk List Lagu L, dimana first dan last dari L bernilai NIL.}
void createListPlaylist(ListPlaylist &P);
// {I.S. List Playlist P belum terdefinisi.
//  F.S. Terbentuk List Lagu P, dimana first P bernilai NIL.}
void createGraph(Graph &G);
// {I.S. Graph G belum terdefinisi.
//  F.S. Terbentuk Graph Lagu G, dimana first G bernilai NIL.}
void createQueue(Queue &Q);
// {I.S. Queue Q belum terdefinisi.
//  F.S. Terbentuk queue kosong dengan head dan tail bernilai NIL.}

bool isEmptyLibrary(ListLagu L);
// {I.S. Terdefinisi List Lagu L.
//  F.S. Mengemballikan true jika L kosong, false jika ada isinya.}
bool isEmptyPlaylist(ListPlaylist P);
// {I.S. Terdefinisi List Playlist.
//  F.S. Mengemballikan true jika P kosong, false jika ada isinya.}

adrLagu createElmLagu(string judul, string penyanyi, string album, int tahun, string genre, string bahasa);
// {I.S. Terdefinisi data lagu melalui parameter.
//  F.S. Menghasilkan elemen lagu baru dengan data sesuai parameter dan pointer bernilai NIL.}
adrPlaylist createElmPlaylist(string nama);
// {I.S. nama playlist diberikan melalui parameter.
//  F.S. Mengembalikan alamat playlist baru dengan nama yang diberikan dan list relasi kosong.}
adrRelasi createElmRelasi(adrLagu L);
// {I.S. Terdefinisi alamat Lagu L melalui parameter.
//  F.S. Mengembalikan alamat elemen Relasi baru yang menunjuk ke lagu L.}
adrVertex createElmVertex(adrLagu l);
// {I.S. Terdefinisi alamat lagu l.
//  F.S. Menghasilkan elemen vertex baru yang menunjuk ke lagu l.}
adrEdge createElmEdge(adrVertex v);
// {I.S. Terdefinisi alamat vertex v.
//  F.S. Menghasilkan elemen edge baru yang menunjuk ke vertex v.}
adrQueue createElmQueue(adrVertex v);
// {I.S. Terdefinisi alamat vertex v.
//  F.S. Mengembalikan alamat queue edge baru dengan info dari vertex v dan next yang bernilai NIL.}

// List Lagu (DLL)
void insertLastLagu(ListLagu &L,  adrLagu p);
// {I.S. Isi List Lagu L mungkin kosong.
//  F.S. elemen p ditambahkan ke bagian akhir List Lagu.}
adrLagu findLagu(ListLagu L, string judul);
// {I.S. List lagu L mungkin kosong.
//  F.S. Mengembalikan alamat lagu dengan Judul yang dicari jika ditemukan; mengembalikan NIL jika tidak ada.}
void deleteLaguFromAllPlaylist(ListPlaylist P, adrLagu q);
// {I.S. List Playlist P terdefinisi dan alamat Lagu q terdefinisi.
//  F.S. Menghapus semua lagu yang ada di playlist.}
void deleteElmLagu(ListLagu &L, adrLagu p);
// {I.S. List Lagu L terdefinisi dan alamat Lagu p terdefinisi.
//  F.S. Menghapus lagu dari libbrary}
void deleteLagu(ListLagu &L, ListPlaylist &P, string judul);
// {I.S. List Lagu L dan List Playlist P terdefinisi.
//  F.S. Lagu dengan judul yang telah ditentukan dihapus dari Library dan semua Playlist.}
void editLagu(adrLagu &p);
//{I.S. Terdefinisi elemen p lagu yang tidak NIL.
// F.S. Data lagu diubah.}

// Detail Lagu
void playLagu(ListPlaylist &P, Graph G, adrLagu play);
//{I.S. Tidak ada lagu diputar atau lagu dalam keadaan pause.
// F.S. Lagu memunculkan notifikasi "Playing From Library" dan memutar lagu sesuai urutan lagu yang terakhir kali dimasukkan admin.}
void playLaguFromPlaylist(ListPlaylist &P, Graph G, adrPlaylist play);
// {I.S. Terdefinisi list playlist.
//  F.S. Lagu memunculkan notifikasi "Playing From Playlist" dan memutar lagu sesuai urutan lagu yang terakhir kali dimasukkan user.}
void playRekomendasi(ListPlaylist &P, Graph G, adrLagu play);
// {I.S. Terdefinisi list playlist dan Graph yang berisi lagu.
//  F.S. Lagu memunculkan notifikasi "Playing From Recommendation" dan memutar lagu sesuai urutan rekomendasi.}

// List Playlist (SLL)
void insertFirstPlaylist(ListPlaylist &P, adrPlaylist p);
// {I.S. Isi Playlist P mungkin kosong.
//  F.S. Elemen p ditambahkan ke awal List Playlist.}
adrPlaylist findPlaylist(ListPlaylist P, string nama);
// {I.S. List Playlist P mungkin kosong
//  F.S. Mengembalikan alamat playlist dengan nama yang dicari jika ditemukan; NIL jika tidak ada.}
void deletePlaylist(ListPlaylist &P, string nama);
// {I.S. List Playlist P sudah terisi.
//  F.S. Playlist dengan nama tertentu akan terhapus dari list jika ditemukan.}

// Relasi
void addLaguToPlaylist(adrPlaylist p, adrLagu L);
// {I.S. Playlist P mungkin kosong atau sudah memiliki relasi.
//  F.S. Relasi Lagu L dimasukkan ke dalam playlist.}
void deleteRelasiByLagu(adrPlaylist p, adrLagu L);
// {I.S. Playlist P mungkin kosong.
//  F.S. Relasi yang menunjuk ke Lagu L terhapus jika ditemukan.}

// Queue
bool isEmptyQueue(Queue Q);
// {I.S. Terdefinisi queue Q.
//  F.S. Mengembalikan true jika queue kosong, false jika tidak kosong.}
void enqueue(Queue &Q, adrVertex v);
// {I.S. Terdefinisi queue Q dan vertex v.
//  F.S. Vertex v ditambahkan ke bagian belakang queue.}
adrVertex dequeue(Queue &Q);
// {I.S. Queue Q tidak kosong.
//  F.S. Elemen terdepan queue dihapus dan alamat vertex dikembalikan.}

// Graph
void addLaguToGraph(Graph &G, adrLagu l);
// {I.S. Terdefinisi graph G dan lagu l.
//  F.S. Vertex baru yang merepresentasikan lagu l ditambahkan ke dalam graph G.}
void connectVertex(adrVertex &v1, adrVertex &v2);
// {I.S. Terdefinisi dua buah vertex v1 dan v2.
//  F.S. Terbentuk edge dari vertex v1 menuju vertex v2.}
void connectGenreOrLang(Graph &G, ListLagu L, adrLagu l);
// {I.S. Terdefinisi graph G, list lagu L, dan lagu l.
//  F.S. Vertex lagu l terhubung dengan lagu lain dalam graph yang memiliki genre atau bahasa yang sama.}
adrVertex findVertex(Graph G, adrLagu l);
// {I.S. Terdefinisi graph G dan lagu l.
//  F.S. Mengembalikan alamat vertex yang menunjuk ke lagu l jika ditemukan; NIL jika tidak ditemukan.}
void resetVisited(Graph &G);
// {I.S. Terdefinisi graph G.
//  F.S. Mengubah status visited menjadi 0.}
void deleteEdgeByLagu(Graph &G, adrLagu l);
// {I.S. Graph G terdefinisi dan alamat Lagu l terdefinisi.
//  F.S. Seluruh edge pada Graph G yang terhubung ke Lagu l terhapus.}
void deleteVertexByLagu(Graph &G, adrLagu l);
// {I.S. Graph G terdefinisi dan alamat Lagu l terdefinisi.
//  F.S. Vertex beserta seluruh edge yang terhubung terhapus dari Graph G.}


void showLibrary(ListLagu L);
// {I.S. Terdefinisi List Lagu L yang mungkin kosong.
//  F.S. Menampilkan Seluruh lagu dari Library.}
void showPlaylist(ListPlaylist P);
// {I.S. Terdefinisi List Playlist yang mungkin kosong.
//  F.S. Menampilkan daftar Playlist yang telah dibuat beserta daftar lagu di dalamnya.}
void showPlaylistLagu(adrPlaylist p);
// {I.S. Terdefinisi playlist yang sudah berisi lagu.
//  F.S. Menampilkan daftar lagu yang terdapat dalam playlist p.}
void BFS(Graph G, adrVertex start, Queue &Q);
// {I.S. Terdefinisi Graph G dan alamat vertex start, Queue Q belum terdefinisi
//  F.S. Queue akan terisi urutan lagu melalui algoritma traverssal BFS.}

//menu
void menuAdmin(ListLagu &L, ListPlaylist &P, Graph &G);
// {I.S. Terdefinisi list lagu L, list playlist P, dan graph G.
//  F.S. Menampilkan menu admin untuk melihat dan mengelola data lagu}
void menuUser(ListPlaylist &P, ListLagu L, Graph G);
// {I.S. Terdefinisi list playlist P dan list lagu L.
//  F.S. Menampilkan menu user untuk melihat dan memutar lagu serta membuat playlist.}


void dataDummyLagu(ListLagu &L, Graph &G);
// {I.S. List Lagu L dan Graph G terdefinisi dan masih kosong.
//  F.S. List Lagu L terisi dengan sejumlah data lagu dummy dan Graph G terbentuk sesuai relasi lagu.}
#endif // LAGU_H_INCLUDED
