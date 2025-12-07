#include <iostream>
#include "lagu.h"
using namespace std;

int main()
{
    ListLagu LL;
    ListPlaylist LP;

    createListLagu(LL);
    createListPlaylist(LP);

    adrLagu l;
    adrPlaylist p;
    adrRelasi r;

    Lagu L;

    dataDummyLagu(LL);
    p = createElmPlaylist("Favorite");
    insertFirstPlaylist(LP, p);
    int pilih;

    cout << " --------------------------- " << endl;
    cout << "|  Kamu masuk sebagai apa?  |" << endl;
    cout << "|---------------------------|" << endl;
    cout << "|1. Admin                   |" << endl;
    cout << "|2. User                    |" << endl;
    cout << " --------------------------- " << endl;
    cout << "|Pilih: "; cin >> pilih;
    cout << " --------------------------- " << endl;
    cout << endl;
    if (pilih == 1){
        cout << " --------------------------- " << endl;
        cout << "|         Menu Admin        |" << endl;
        cout << "|---------------------------|" << endl;
        cout << "|1. Tambahkan lagu          |" << endl;
        cout << "|2. Lihat daftar lagu       |" << endl;
        cout << "|3. Ubah data lagu          |" << endl;
        cout << "|4. Hapus lagu              |" << endl;
        cout << " --------------------------- " << endl;
        cout << "|Pilih: "; cin >> pilih;
        cout << " --------------------------- " << endl;
        cout << endl;
        if (pilih == 1){
            cout << " --------------------------- " << endl;
            cout << "| Tambahkan lagu ke Library |" << endl;
            cout << "|---------------------------|" << endl;
            cout << "|Lengkapi data-data berikut!|" << endl;
            //for (int i = 1; i<= 5; i++){
                L.IDLagu = 4;
                cout << "|Judul Lagu: "; cin >> L.judulLagu;
                cout << "|Nama Penyanyi / Band: "; cin >> L.penyanyi;
                cout << "|Nama Album: "; cin >> L.album;
                cout << "|Tahun Rilis Lagu: "; cin >> L.tahun;
                cout << "|Genre Lagu: "; cin >> L.genre;
                cout << "|Bahasa: "; cin >> L.bahasa;
                cout << " --------------------------- " << endl;
                l = createElmLagu(L.IDLagu, L.judulLagu, L.penyanyi, L.album, L.tahun, L.genre, L.bahasa);
                insertLastLagu(LL, l);
            //}
            cout << endl;

            showLibrary(LL);
        } else if (pilih == 2){
            showLibrary(LL);
        } else if (pilih == 3){

        } else if (pilih == 4){
            int id;
            cout << "Masukkan id lagu yang ingin dihapus: "; cin >> id;
            adrLagu l = findLagu(LL, id);
            if (l != nullptr){
                deleteElmLagu(LL, l);
                cout << "Lagu telah dihapus!" << endl;
                showLibrary(LL);
            } else {
                cout << "Lagu tidak ditemukan." << endl;
            }
        }


    } else if (pilih == 2){

        cout << " --------------------------- " << endl;
        cout << "|         Menu User         |" << endl;
        cout << "|---------------------------|" << endl;
        cout << "|1. Cari Lagu               |" << endl;
        cout << "|2. Play lagu               |" << endl;
        cout << "|3. Buat Playlist           |" << endl;
        cout << "|4. Lihat Daftar Playlist   |" << endl;
        cout << "|5. Lihat Isi Playlist      |" << endl;
        cout << " --------------------------- " << endl;
        cout << "|Pilih: "; cin >> pilih;
        cout << " --------------------------- " << endl;
        cout << endl;
        if (pilih == 1){
            int id;
            cout << "Masukkan id lagu yang ingin dicari: "; cin >> id;
            adrLagu l = findLagu(LL, id);
            if (l != nullptr){
                cout << " ----------------------------------- " << endl;
                cout << "|            Lagu ditemukan!        |" << endl;
                cout << " ----------------------------------- " << endl;
                cout << " ID Lagu: " << l->info.IDLagu << endl;
                cout << " Judul Lagu: " << l->info.judulLagu <<endl;
                cout << " Nama Penyanyi / Band: " << l->info.penyanyi << endl;
                cout << " Nama Album: " << l->info.album << endl;
                cout << " Tahun Rilis Lagu: " << l->info.tahun << endl;
                cout << " Genre Lagu: " << l->info.genre << endl;
                cout << " Bahasa: "<< l->info.bahasa << endl;
                cout << " ----------------------------------- " << endl;
                cout << "|Apakah kamu ingin memutar lagu ini?|" << endl;
                cout << "|-----------------------------------|" << endl;
                cout << "|1. Iya                             |" << endl;
                cout << "|2. Tidak                           |" << endl;
                cout << "|-----------------------------------|" << endl;
                cout << "|Pilih: "; cin >> pilih;
                cout << "|-----------------------------------|" << endl;
                cout << endl;
                if (pilih == 1){
                    cout << " ------------------------------------ " << endl;
                    cout << "|      LAGU DIPUTAR DARI LIBRARY     |" << endl;
                    cout << "|------------------------------------|" << endl;
                    playLagu(LP, l);
                }
            } else {
                cout << "Lagu tidak ditemukan." << endl;
            }
        } else if (pilih == 2){
            playLagu(LP, LL.first);
        } else if (pilih == 3){
            string nama;
            cout << "Masukkan nama playlist lagu: "; cin >> nama;
            adrPlaylist p = createElmPlaylist(nama);
            insertFirstPlaylist(LP, p);
            cout << " ----------------------------------- " << endl;
            cout << "|      Playlist telah ditambah!     |" << endl;
            cout << " ----------------------------------- " << endl;
            showPlaylist(LP);
        } else if (pilih == 4){
            showPlaylist(LP);
        } else if (pilih == 5){
            showPlaylist(LP);
        }
    }




    return 0;
}
