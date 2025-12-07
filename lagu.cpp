#include <iostream>
#include "lagu.h"
using namespace std;

void createListLagu(ListLagu &L){
    L.first = nullptr;
    L.last = nullptr;
}

void createListPlaylist(ListPlaylist &P){
    P.first = nullptr;
}

bool isEmptyLibrary(ListLagu L){
    return L.first == nullptr && L.last == nullptr;
}

bool isEmptyPlaylist(ListPlaylist P){
    return P.first == nullptr;
}

adrLagu createElmLagu(int id, string judul, string penyanyi, string album, int tahun, string genre, string bahasa){
    adrLagu l = new elmLagu;
    l->info.IDLagu = id;
    l->info.judulLagu = judul;
    l->info.penyanyi = penyanyi;
    l->info.album = album;
    l->info.tahun = tahun;
    l->info.genre = genre;
    l->info.bahasa = bahasa;
    l->info.disukai = false;
    l->next = nullptr;
    l->prev = nullptr;

    return l;
}

adrPlaylist createElmPlaylist(string nama){
    adrPlaylist p = new elmPlaylist;
    p->namaPlaylist = nama;
    p->next = nullptr;
    p->firstRelasi = nullptr;

    return p;
}

adrRelasi createElmRelasi(adrLagu L){
    adrRelasi r = new elmRelasi;
    r->lagu = L;
    r->next = nullptr;

    return r;
}

// lagu
void insertLastLagu(ListLagu &L, adrLagu p){
    if (isEmptyLibrary(L)){
        L.first = p;
        L.last = p;
    } else {
        p->prev = L.last;
        L.last->next = p;
        L.last = p;
    }
}

adrLagu findLagu(ListLagu L, int id){
    adrLagu q = L.first;
    while(q != nullptr && q->info.IDLagu != id){
        q = q->next;
    }

    return q;
}

void deleteLaguFromAllPlaylist(ListPlaylist P, adrLagu q){
    adrPlaylist p = P.first;
    while (p != nullptr){
        adrRelasi r = p->firstRelasi;
        adrRelasi prec = nullptr;

        while (r != nullptr){
            if (r->lagu == q){
                if (prec == nullptr){
                    p->firstRelasi = r->next;
                } else {
                    prec->next = r->next;
                }
            }
            prec = r;
            r = r->next;
        }
        p = p->next;
    }

}

void deleteElmLagu(ListLagu &L, adrLagu p){
    if (p == L.first && p == L.last){
        L.first = nullptr;
        L.last = nullptr;
    } else if (p == L.first){
        L.first = p->next;
        L.first->prev = nullptr;
    } else if (p == L.last){
        L.last = p->prev;
        L.last->next = nullptr;
    } else {
        p->prev->next = p->next;
        p->next->prev = p->prev;
    }
}

void deleteLagu(ListLagu &L,  ListPlaylist &P, int id){
    adrLagu q = findLagu(L, id);
    if (q != nullptr){
        deleteLaguFromAllPlaylist(P, q);
        deleteElmLagu(L, q);
    } else {
        cout << "Lagu tidak ditemukan." << endl;
    }
}

void playLagu(ListPlaylist &P, adrLagu &play){
    int pilih;
        cout << " ------------------------------------ " << endl;
        cout << "|           Now Playing...           |" << endl;
        cout << "|------------------------------------|" << endl;
        cout << "|" <<  play->info.judulLagu  << endl;
        cout << "|" << play->info.penyanyi << " - " << play->info.album << " - " << play->info.tahun << endl;
        cout << " ------------------------------------ " << endl;
    if (play->prev == nullptr){
        cout << "|             2. Pause       3. Next |" << endl;
    } else if (play->next == nullptr){
        cout << "|1. Prev       2. Pause              |" << endl;
    } else {
        cout << "|1. Prev       2. Pause       3. Next|" << endl;
    }
        cout << "|      4. Like      5. + playlist    |" << endl;
        cout << "|------------------------------------|" << endl;
        cout << "|Pilih: "; cin >> pilih;
        cout << "|------------------------------------|" << endl;
        cout << endl;
    if (pilih == 1){
        playLagu(P, play->prev);
    } else if (pilih == 2){
        pauseLagu(P, play);
    } else if (pilih == 3){
        playLagu(P, play->next);
    } else if (pilih == 4){
        adrPlaylist p = findPlaylist(P, "Favorite");
        addLaguToPlaylist(p, play);
    } else if (pilih == 5){
        string nama;
        showPlaylist(P);
        cout << "Simpan ke playlist: "; cin >> nama;
        adrPlaylist p = findPlaylist(P, nama);
        addLaguToPlaylist(p, play);
    }
}

void pauseLagu(ListPlaylist &P, adrLagu &pause){
    int pilih;
        cout << " ------------------------------------ " << endl;
        cout << "|               Paused               |" << endl;
        cout << "|------------------------------------|" << endl;
        cout << "|" <<  pause->info.judulLagu  << endl;
        cout << "|" << pause->info.penyanyi << " - " << pause->info.album << " - " << pause->info.tahun << endl;
        cout << " ------------------------------------ " << endl;
    if (pause->prev == nullptr){
        cout << "|              2. Play       3. Next |" << endl;
    } else if (pause->next == nullptr){
        cout << "|1. Prev       2. Play               |" << endl;
    } else {
        cout << "|1. Prev       2. Play       3. Next |" << endl;
    }
        cout << "|              4. Like               |" << endl;
        cout << "|----------------------------------- |" << endl;
        cout << "|Pilih: "; cin >> pilih;
        cout << "|----------------------------------- |" << endl;
        cout << endl;
    if (pilih == 1){
        playLagu(P, pause->prev);
    } else if (pilih == 2){
        playLagu(P, pause);
    } else if (pilih == 3){
        playLagu(P, pause->next);
    } else if (pilih == 4){
        adrPlaylist p = findPlaylist(P, "Favorite");
        addLaguToPlaylist(p, pause);
    } else if (pilih == 5){
        string nama;
        showPlaylist(P);
        cout << "Simpan ke playlist: "; cin >> nama;
        adrPlaylist p = findPlaylist(P, nama);
        addLaguToPlaylist(p, pause);
    }
}

// playlist
void insertFirstPlaylist(ListPlaylist &P, adrPlaylist p){
    if (isEmptyPlaylist(P)){
        P.first = p;
    } else {
        p->next = P.first;
        P.first = p;
    }
}

adrPlaylist findPlaylist(ListPlaylist P, string nama){
    adrPlaylist q = P.first;
    while(q != nullptr && q->namaPlaylist != nama){
        q = q->next;
    }

    return q;
}

void deletePlaylist(ListPlaylist P, string nama){
    adrPlaylist q = P.first;
    adrPlaylist prec = nullptr;

    while(q != nullptr && q->namaPlaylist != nama){
        prec = q;
        q = q->next;
    }

    if (q != nullptr){
        if (q == P.first){
            P.first = q->next;
        } else {
            prec->next = q->next;
        }
    }
}

void addLaguToPlaylist(adrPlaylist p, adrLagu L){
    adrRelasi r, q;
    r = new elmRelasi;
    r->lagu = L;
    r->next = nullptr;

    if (p->firstRelasi == nullptr){
        p->firstRelasi = r;
    } else {
        q = p->firstRelasi;
        while (q->next != nullptr){
            q = q->next;
        }
        q->next = r;
    }
}

void deleteRelasiByLagu(adrPlaylist p, adrLagu L){

}

void showLibrary(ListLagu L){
    cout << " ------------------------------------ " << endl;
    cout << "|       DAFTAR LAGU DI LIBRARY       |" << endl;
    adrLagu p = L.first;
    while (p != nullptr){
        cout << "|------------------------------------|" << endl;
        cout << "|" << p->info.IDLagu << ". " <<  p->info.judulLagu  << endl;
        cout << "|" << p->info.penyanyi << " - " << p->info.album << " - " << p->info.tahun << endl;
        p = p->next;
    }
    cout << "|------------------------------------|" << endl;
    cout << endl;
}

void showPlaylist(ListPlaylist P){
    cout << " ------------------------------------ " << endl;
    cout << "|        DAFTAR PLAYLIST KAMU        |" << endl;
    adrPlaylist p = P.first;
    while (p != nullptr){
        cout << "|------------------------------------|" << endl;
        cout << "|" << p->namaPlaylist << endl;
        p = p->next;
    }
    cout << "|------------------------------------|" << endl;
    cout << endl;
}

void dataDummyLagu(ListLagu &L){
    adrLagu l;
    Lagu Lg;
    Lg.IDLagu = 1;
    Lg.judulLagu = "Love_Scenario";
    Lg.penyanyi = "iKON";
    Lg.album = "Return";
    Lg.tahun = 2018;
    Lg.genre = "pop";
    Lg.bahasa = "KR";
    l = createElmLagu(Lg.IDLagu, Lg.judulLagu, Lg.penyanyi, Lg.album, Lg.tahun, Lg.genre, Lg.bahasa);
    insertLastLagu(L, l);

    Lg.IDLagu = 2;
    Lg.judulLagu = "Gurenge";
    Lg.penyanyi = "LiSA ";
    Lg.album = "LEO-NiNE";
    Lg.tahun = 2020;
    Lg.genre = "pop";
    Lg.bahasa = "JP";
    l = createElmLagu(Lg.IDLagu, Lg.judulLagu, Lg.penyanyi, Lg.album, Lg.tahun, Lg.genre, Lg.bahasa);
    insertLastLagu(L, l);

    Lg.IDLagu = 3;
    Lg.judulLagu = "Helena";
    Lg.penyanyi = "My_Chemical_Romance";
    Lg.album = "Three_Cheers_for_Sweet_Revenge";
    Lg.tahun = 2004;
    Lg.genre = "rock";
    Lg.bahasa = "EN";
    l = createElmLagu(Lg.IDLagu, Lg.judulLagu, Lg.penyanyi, Lg.album, Lg.tahun, Lg.genre, Lg.bahasa);
    insertLastLagu(L, l);
}

