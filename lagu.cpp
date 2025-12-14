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

void createGraph(Graph &G){
    G.first = nullptr;
}

bool isEmptyLibrary(ListLagu L){
    return L.first == nullptr && L.last == nullptr;
}

bool isEmptyPlaylist(ListPlaylist P){
    return P.first == nullptr;
}

adrLagu createElmLagu(string judul, string penyanyi, string album, int tahun, string genre, string bahasa){
    adrLagu l = new elmLagu;
    l->info.judulLagu = judul;
    l->info.penyanyi = penyanyi;
    l->info.album = album;
    l->info.tahun = tahun;
    l->info.genre = genre;
    l->info.bahasa = bahasa;
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
    r->prev = nullptr;

    return r;
}

adrVertex createElmVertex(adrLagu l){
    adrVertex v = new elmVertex;
    v->lagu = l;
    v->firstEdge = nullptr;
    v->next = nullptr;
    v->visited = 0;

    return v;
}

adrEdge createElmEdge(adrVertex v){
    adrEdge e = new elmEdge;
    e->vertex = v;
    e->next = nullptr;

    return e;
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

adrLagu findLagu(ListLagu L, string judul){
    adrLagu q = L.first;
    while(q != nullptr && q->info.judulLagu != judul){
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

void deleteLagu(ListLagu &L,  ListPlaylist &P, string judul){
    adrLagu q = findLagu(L, judul);
    if (q != nullptr){
        deleteLaguFromAllPlaylist(P, q);
        deleteElmLagu(L, q);
    }
}

void playRekomendasi(ListPlaylist &P, Graph G, adrLagu play){
    Queue Q;
    createQueue(Q);
    adrVertex v = findVertex(G, play);
    BFS(G, v, Q);
    adrQueue q = Q.head;
    bool runPlay = true;
    while (runPlay){
        int pilih;
            cout << "======================================" << endl;
            cout << "      PLAYING FROM RECOMMENDATION     " << endl;
            cout << "======================================" << endl;
            cout << q->info->lagu->info.judulLagu << endl;
            cout << q->info->lagu->info.penyanyi << " - " << q->info->lagu->info.album << " - " << q->info->lagu->info.tahun << endl;
            cout << "--------------------------------------" << endl;
        if (q->prev == nullptr){;
            cout << "               2. Pause        3. Next" << endl;
        } else if (q->next == nullptr){
            cout << "1. Prev        2. Pause               " << endl;
        } else {
            cout << "1. Prev        2. Pause        3. Next" << endl;
        }
            cout << "......................................" << endl;
            cout << "4. Like            5. Add To Playlist " << endl;
            cout << "6. Start Mix       0. Exit" << endl;
            cout << "--------------------------------------" << endl;
            cout << "Choice: "; cin >> pilih;
            cout << "--------------------------------------" << endl;
            cout << endl;
        if (pilih == 1){
            q = q->prev;
        } else if (pilih == 2){
            cout << "======================================" << endl;
            cout << "                PAUSED                " << endl;
            cout << "======================================" << endl;
            cout << q->info->lagu->info.judulLagu  << endl;
            cout << q->info->lagu->info.penyanyi << " - " << q->info->lagu->info.album << " - " << q->info->lagu->info.tahun << endl;
            cout << "--------------------------------------" << endl;
            if (q->prev == nullptr){
                cout << "               2. Play         3. Next" << endl;
            } else if (q->next == nullptr){
                cout << "1. Prev        2. Play                " << endl;
            } else {
                cout << "1. Prev        2. Play         3. Next" << endl;
            }
                cout << "......................................" << endl;
                cout << "4. Like            5. Add To Playlist " << endl;
                cout << "6. Start Mix       0. Exit" << endl;
                cout << "--------------------------------------" << endl;
                cout << "Choice: "; cin >> pilih;
                cout << "--------------------------------------" << endl;
                cout << endl;
                if (pilih == 1){
                    q = q->prev;
                } else if (pilih == 3){
                    q = q->next;
                } else if (pilih == 4){
                    adrPlaylist p = findPlaylist(P, "Favorite");
                    addLaguToPlaylist(p, q->info->lagu);
                    cout << " ------------------------------------ " << endl;
                    cout << "|  Successfully Added To Favorite!   |" << endl;
                    cout << " ------------------------------------ " << endl;
                    cout << endl;
                } else if (pilih == 5){
                    string nama;
                    showPlaylist(P);
                    cout << "Simpan ke playlist: "; cin >> nama;
                    adrPlaylist p = findPlaylist(P, nama);
                    if (p != nullptr){
                        addLaguToPlaylist(p, q->info->lagu);
                        cout << " ------------------------------------ " << endl;
                        cout << "|  Successfully Added To " << nama << "!" << endl;
                        cout << " ------------------------------------ " << endl;
                        cout << endl;
                    } else {
                        cout << "Playlist not found :(" << endl;
                    }
                } else if (pilih == 6){
                    play = q->info->lagu;
                } else if (pilih == 0){
                    runPlay = false;
                }
        } else if (pilih == 3){
            q = q->next;
        } else if (pilih == 4){
            adrPlaylist p = findPlaylist(P, "Favorite");
            addLaguToPlaylist(p, q->info->lagu);
            cout << " ------------------------------------ " << endl;
            cout << "|  Successfully Added To Favorite!   |" << endl;
            cout << " ------------------------------------ " << endl;
            cout << endl;
        } else if (pilih == 5){
            string nama;
            showPlaylist(P);
            cout << "Simpan ke playlist: "; cin >> nama;
            adrPlaylist p = findPlaylist(P, nama);
            if (p != nullptr){
                addLaguToPlaylist(p, q->info->lagu);
                cout << " ------------------------------------ " << endl;
                cout << "|  Successfully Added To " << nama << "!" << endl;
                cout << " ------------------------------------ " << endl;
                cout << endl;
            } else {
                cout << "Playlist not found :(" << endl;
            }
        } else if (pilih == 6){
            play = q->info->lagu;
        } else {
            runPlay = false;
        }
    }
}

void playLagu(ListPlaylist &P, Graph G, adrLagu play){
    bool runPlay = true;
    while (runPlay){
        int pilih;
            cout << "======================================" << endl;
            cout << "          PLAYING FROM LIBRARY        " << endl;
            cout << "======================================" << endl;
            cout << play->info.judulLagu  << endl;
            cout << play->info.penyanyi << " - " << play->info.album << " - " << play->info.tahun << endl;
            cout << "--------------------------------------" << endl;
        if (play->prev == nullptr){
            cout << "               2. Pause        3. Next" << endl;
        } else if (play->next == nullptr){
            cout << "1. Prev        2. Pause               " << endl;
        } else {
            cout << "1. Prev        2. Pause        3. Next" << endl;
        }
            cout << "......................................" << endl;
            cout << "4. Like            5. Add To Playlist " << endl;
            cout << "6. Start Mix       0. Exit" << endl;
            cout << "--------------------------------------" << endl;
            cout << "Choice: "; cin >> pilih;
            cout << "--------------------------------------" << endl;
            cout << endl;
        if (pilih == 1){
            play = play->prev;
        } else if (pilih == 2){
            cout << "======================================" << endl;
            cout << "                PAUSED                " << endl;
            cout << "======================================" << endl;
            cout << play->info.judulLagu  << endl;
            cout << play->info.penyanyi << " - " << play->info.album << " - " << play->info.tahun << endl;
            cout << "--------------------------------------" << endl;
            if (play->prev == nullptr){
                cout << "|              2. Play        3. Next|" << endl;
            } else if (play->next == nullptr){
                cout << "|1. Prev       2. Play               |" << endl;
            } else {
                cout << "1. Prev        2. Play         3. Next" << endl;
            }
                cout << "......................................" << endl;
                cout << "4. Like            5. Add To Playlist " << endl;
                cout << "6. Start Mix       0. Exit" << endl;
                cout << "--------------------------------------" << endl;
                cout << "Choice: "; cin >> pilih;
                cout << "--------------------------------------" << endl;
                cout << endl;
                if (pilih == 1){
                    play = play->prev;
                } else if (pilih == 3){
                    play = play->next;
                } else if (pilih == 4){
                    adrPlaylist p = findPlaylist(P, "Favorite");
                    addLaguToPlaylist(p, play);
                    cout << " ------------------------------------ " << endl;
                    cout << "|  Successfully Added To Favorite!   |" << endl;
                    cout << " ------------------------------------ " << endl;
                    cout << endl;
                } else if (pilih == 5){
                    string nama;
                    showPlaylist(P);
                    cout << "Add to playlist: "; cin >> nama;
                    adrPlaylist p = findPlaylist(P, nama);
                    if (p != nullptr){
                        addLaguToPlaylist(p, play);
                        cout << " ------------------------------------ " << endl;
                        cout << "|  Successfully Added To " << nama << "!" << endl;
                        cout << " ------------------------------------ " << endl;
                        cout << endl;
                    } else {
                        cout << "Playlist not found :(" << endl;
                    }

                } else if (pilih == 0){
                    runPlay = false;
                }
        } else if (pilih == 3){
            play = play->next;
        } else if (pilih == 4){
            adrPlaylist p = findPlaylist(P, "Favorite");
            addLaguToPlaylist(p, play);
            cout << " ------------------------------------ " << endl;
            cout << "|  Successfully Added To Favorite!   |" << endl;
            cout << " ------------------------------------ " << endl;
            cout << endl;
        } else if (pilih == 5){
            string nama;
            showPlaylist(P);
            cout << "Add to playlist: "; cin >> nama;
            adrPlaylist p = findPlaylist(P, nama);
            if (p != nullptr){
                addLaguToPlaylist(p, play);
                cout << " ------------------------------------ " << endl;
                cout << "|  Successfully Added To " << nama << "!" << endl;
                cout << " ------------------------------------ " << endl;
                cout << endl;
            } else {
                cout << "Playlist not found :(" << endl;
            }

        } else if (pilih == 6){
            playRekomendasi(P, G, play);
        } else {
            runPlay = false;
        }
    }
}

void playLaguFromPlaylist(ListPlaylist &P, Graph G, adrPlaylist play){
    bool runPlay = true;
    adrRelasi r = play->firstRelasi;
    while (runPlay){
        int pilih;
            cout << "======================================" << endl;
            cout << "          PLAYING FROM PLAYLIST       " << endl;
            cout << "======================================" << endl;
            cout <<  r->lagu->info.judulLagu  << endl;
            cout << r->lagu->info.penyanyi << " - " << r->lagu->info.album << " - " << r->lagu->info.tahun << endl;
            cout << "--------------------------------------" << endl;
        if (r->prev == nullptr){
            cout << "               2. Pause        3. Next" << endl;
        } else if (r->next == nullptr){
            cout << "1. Prev        2. Pause               " << endl;
        } else {
            cout << "1. Prev        2. Pause        3. Next" << endl;
        }
            cout << "......................................" << endl;
            cout << "4. Like            5. Add To Playlist " << endl;
            cout << "6. Start Mix       0. Exit" << endl;
            cout << "--------------------------------------" << endl;
            cout << "Choice: "; cin >> pilih;
            cout << "--------------------------------------" << endl;
            cout << endl;
        if (pilih == 1){
            r = r->prev;
        } else if (pilih == 2){
            cout << "======================================" << endl;
            cout << "                PAUSED                " << endl;
            cout << "======================================" << endl;
            cout <<  r->lagu->info.judulLagu  << endl;
            cout << r->lagu->info.penyanyi << " - " << r->lagu->info.album << " - " << r->lagu->info.tahun << endl;
            cout << "--------------------------------------" << endl;
            if (r->prev == nullptr){
                cout << "               2. Play        3. Next" << endl;
            } else if (r->next == nullptr){
                cout << "1. Prev        2. Play               " << endl;
            } else {
                cout << "1. Prev        2. Play        3. Next" << endl;
            }
                cout << "......................................" << endl;
                cout << "4. Like            5. Add To Playlist " << endl;
                cout << "6. Start Mix       0. Exit" << endl;
                cout << "--------------------------------------" << endl;
                cout << "Choice: "; cin >> pilih;
                cout << "--------------------------------------" << endl;
                cout << endl;
                if (pilih == 1){
                    r = r->prev;
                } else if (pilih == 3){
                    r = r->next;
                } else if (pilih == 4){
                    adrPlaylist p = findPlaylist(P, "Favorite");
                    addLaguToPlaylist(p, r->lagu);
                    cout << " ------------------------------------ " << endl;
                    cout << "|  Successfully Added To Favorite!   |" << endl;
                    cout << " ------------------------------------ " << endl;
                    cout << endl;
                } else if (pilih == 5){
                    string nama;
                    showPlaylist(P);
                    cout << "Add to playlist: "; cin >> nama;
                    adrPlaylist p = findPlaylist(P, nama);
                    if (p != nullptr){
                        addLaguToPlaylist(p, r->lagu);
                        cout << " ------------------------------------ " << endl;
                        cout << "|  Successfully Added To " << nama << "!" << endl;
                        cout << " ------------------------------------ " << endl;
                        cout << endl;
                    } else {
                        cout << "Playlist not found :(" << endl;
                    }

                }else if (pilih == 6){
                    playRekomendasi(P, G, r->lagu);
                } else if (pilih == 0){
                    runPlay = false;
                }
        } else if (pilih == 3){
            r = r->next;
        } else if (pilih == 4){
            adrPlaylist p = findPlaylist(P, "Favorite");
            addLaguToPlaylist(p, r->lagu);
            cout << " ------------------------------------ " << endl;
            cout << "|  Successfully Added To Favorite!   |" << endl;
            cout << " ------------------------------------ " << endl;
            cout << endl;
        } else if (pilih == 5){
            string nama;
            showPlaylist(P);
            cout << "Add to playlist: "; cin >> nama;
            adrPlaylist p = findPlaylist(P, nama);
            if (p != nullptr){
                addLaguToPlaylist(p, r->lagu);
                cout << " ------------------------------------ " << endl;
                cout << "|  Successfully Added To " << nama << "!" << endl;
                cout << " ------------------------------------ " << endl;
                cout << endl;
            } else {
                cout << "Playlist not found :(" << endl;
            }

        } else if (pilih == 6){
            playRekomendasi(P, G, r->lagu);
        }else {
            runPlay = false;
        }
    }
}

void editLagu(adrLagu &p){
    cout << "======================================" << endl;
    cout << "                EDIT SONG             " << endl;
    cout << "======================================" << endl;
    cout << "Title        : "; cin >> p->info.judulLagu;
    cout << "Artist / Band: "; cin >> p->info.penyanyi;
    cout << "Album        : "; cin >> p->info.album;
    cout << "Release Year : "; cin >> p->info.tahun;
    cout << "Genre        : "; cin >> p->info.genre;
    cout << "Language     : "; cin >> p->info.bahasa;
    cout << "--------------------------------------" << endl;
    cout << endl;
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

void deletePlaylist(ListPlaylist &P, string nama){
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
    adrRelasi r = createElmRelasi(L);

    if (p->firstRelasi == nullptr){
        p->firstRelasi = r;
    } else {
        adrRelasi q = p->firstRelasi;
        while (q->next != nullptr){
            q = q->next;
        }
        q->next = r;
        r->prev = q;
    }
}

void deleteRelasiByLagu(adrPlaylist p, adrLagu l){
    adrRelasi r = p->firstRelasi;
    while (r != nullptr && r->lagu != l){
        r = r->next;
    }

    if (r == p->firstRelasi && r->next == nullptr){
        p->firstRelasi = nullptr;
    } else if (r == p->firstRelasi){
        p->firstRelasi = r->next;
        p->firstRelasi->prev = nullptr;
    } else if (r->next == nullptr){
        r->prev->next = nullptr;
    } else {
        r->prev->next = r->next;
        r->next->prev = r->prev;
    }
}

// Queue
void createQueue(Queue &Q){
    Q.head = nullptr;
    Q.tail = nullptr;
}

bool isEmptyQueue(Queue Q){
    return Q.head == nullptr and Q.tail == nullptr;
}

adrQueue createElmQueue(adrVertex v){
    adrQueue q = new elmQueue;
    q->info = v;
    q->next = nullptr;

    return q;
}

void enqueue(Queue &Q, adrVertex v){
    adrQueue q = createElmQueue(v);
    if (isEmptyQueue(Q)){
        Q.head = q;
        Q.tail = q;
    } else {
        q->prev = Q.tail;
        Q.tail->next = q;
        Q.tail = q;
    }
}

adrVertex dequeue(Queue &Q){
    adrQueue q = Q.head;
    adrVertex v;
    v = q->info;
    if (!isEmptyQueue(Q)){
        if (Q.head != Q.tail){
            Q.head = q->next;
            q->next = nullptr;
            Q.head->prev = nullptr;
        } else {
            Q.head = nullptr;
            Q.tail = nullptr;
        }
    }
    return v;
}

// Graph
void addLaguToGraph(Graph &G, adrLagu l){
    adrVertex v = createElmVertex(l);
    adrVertex w = G.first;
    if (w == nullptr){
        G.first = v;
    } else {
        while (w->next != nullptr){
            w = w->next;
        }
        w->next = v;
    }
}

void connectVertex(adrVertex &v1, adrVertex &v2){
    adrEdge e = new elmEdge;
    e->vertex = v2;
    e->next = v1->firstEdge;
    v1->firstEdge = e;
}

void connectGenreOrLang(Graph &G, ListLagu L, adrLagu l){
    adrLagu q = L.first;
    while (q != nullptr){
        if (q != l){
            if (q->info.genre == l->info.genre || q->info.bahasa == l->info.bahasa){
                adrVertex v1 = findVertex(G, l);
                adrVertex v2 = findVertex(G, q);

                connectVertex(v1, v2);
                connectVertex(v2, v1);
            }
        }
        q = q->next;
    }
}

adrVertex findVertex(Graph G, adrLagu l){
    adrVertex v = G.first;
    while (v != nullptr && v->lagu != l){
        v = v->next;
    }
    return v;
}

void resetVisited(Graph &G){
    adrVertex v = G.first;
    while (v != nullptr){
        v->visited = 0;
        v = v->next;
    }
}

void deleteEdgeByLagu(Graph &G, adrLagu l){
    adrVertex v = G.first;
    while (v != nullptr){
        adrEdge e = v->firstEdge;
        adrEdge prev = nullptr;

        while (e != nullptr){
            if (e->vertex->lagu == l){
                if (prev == nullptr){
                    v->firstEdge = e->next;
                } else {
                    prev->next = e->next;
                }
                adrEdge temp = e;
                e = e->next;
                delete temp;
            } else {
                prev = e;
                e = e->next;
            }
        }
        v = v->next;
    }
}

void deleteVertexByLagu(Graph &G, adrLagu l){
    adrVertex v = G.first;
    adrVertex prev = nullptr;

    while (v != nullptr && v->lagu != l){
        prev = v;
        v = v->next;
    }
    if (v == nullptr) return;
    deleteEdgeByLagu(G, l);
    if (v == G.first){
        G.first = v->next;
    } else {
        prev->next = v->next;
    }
    delete v;
}

// display
void showPlaylistLagu(adrPlaylist p){
    adrRelasi r = p->firstRelasi;
    cout << "======================================" << endl;
    cout << "PLAYLIST: " << p->namaPlaylist << endl;
    cout << "======================================" << endl;
    int i = 0;
    if (r != nullptr){
        while (r != nullptr){
            i++;
            cout << "[" << i << "] " << r->lagu->info.judulLagu << endl;
            if (i < 10){
                cout << "    " << r->lagu->info.penyanyi << " - " << r->lagu->info.album << " - " << r->lagu->info.tahun << endl;
            } else {
                cout  << "     " << r->lagu->info.penyanyi << " - " << r->lagu->info.album << " - " << r->lagu->info.tahun << endl;
            }
            cout << "......................................" << endl;
            r = r->next;
        }
    } else {
        cout << "          (Playlist Is Empty)         " << endl;
    }
    cout << "Total " << i << " Songs" << endl;
}

void showLibrary(ListLagu L){
    cout << "======================================" << endl;
    cout << "             SONG LIBRARY             " << endl;
    cout << "======================================" << endl;
    int i = 0;
    adrLagu p = L.first;
    while (p != nullptr){
        i++;
        cout << "[" << i << "] " << p->info.judulLagu << " - " << p->info.penyanyi << endl;
        if (i<10){
            cout << "    " << p->info.album << " | " << p->info.bahasa << " | " << p->info.genre << " | " << p->info.tahun << endl;
        } else{
            cout << "     " << p->info.album << " | " << p->info.bahasa << " | " << p->info.genre << " | " << p->info.tahun << endl;
        }
        cout << "......................................" << endl;
        p = p->next;
    }
    cout << "Total " << i << " Songs" << endl;
}

void showPlaylist(ListPlaylist P){
    cout << "======================================" << endl;
    cout << "             YOUR PLAYLIST           " << endl;
    cout << "======================================" << endl;
    adrPlaylist p = P.first;
    int i = 0;
    while (p != nullptr){
        i++;
        cout << "o " << p->namaPlaylist << endl;
        cout << "--------------------------------------" << endl;
        p = p->next;
    }
    cout << "Total " << i << " Playlist" << endl;
    cout << "--------------------------------------" << endl;
}

void BFS(Graph G, adrVertex start, Queue &QLagu){
    Queue Q;
    createQueue(Q);

    resetVisited(G);

    enqueue(Q, start);
    start->visited = 1;
    while (!isEmptyQueue(Q)){
        adrVertex v = dequeue(Q);
        enqueue(QLagu, v);
        v->visited = 1;

        adrEdge e = v->firstEdge;
        while (e != nullptr){
            adrVertex w = e->vertex;
            if (w->visited == 0){
                w->visited = 1;
                enqueue(Q, w);
            }
            e = e->next;
        }
    }
}

//menu
void menuAdmin(ListLagu &L, ListPlaylist &P, Graph &G){
    Lagu Lg;
    int pilih;
    string judul;
    bool runAdmin = true;
    while (runAdmin){
        cout << "======================================" << endl;
        cout << "                 ADMIN                " << endl;
        cout << "======================================" << endl;
        cout << "1. Add Song" << endl;
        cout << "2. Display Library" << endl;
        cout << "3. Edit Song" << endl;
        cout << "4. Delete Song" << endl;
        cout << "0. Switch" << endl;
        cout << "--------------------------------------" << endl;
        cout << "Choice: "; cin >> pilih;
        cout << "--------------------------------------" << endl;
        cout << endl;
        if (pilih == 1){
            bool runAdd = true;
            while (runAdd){
                cout << "======================================" << endl;
                cout << "             ADD NEW SONG             " << endl;
                cout << "======================================" << endl;
                cout << "Title        : "; cin >> Lg.judulLagu;
                cout << "Artist / Band: "; cin >> Lg.penyanyi;
                cout << "Album        : "; cin >> Lg.album;
                cout << "Release Year : "; cin >> Lg.tahun;
                cout << "Genre        : "; cin >> Lg.genre;
                cout << "Language     : "; cin >> Lg.bahasa;
                cout << "--------------------------------------" << endl;
                cout << endl;
                adrLagu l = createElmLagu(Lg.judulLagu, Lg.penyanyi, Lg.album, Lg.tahun, Lg.genre, Lg.bahasa);
                insertLastLagu(L, l);
                addLaguToGraph(G, l);
                connectGenreOrLang(G, L, l);
                cout << " ------------------------------------ " << endl;
                cout << "| Song Succesfully Added To Library! |" << endl;
                cout << " ------------------------------------ " << endl;
                cout << endl;
                cout << "--------------------------------------" << endl;
                cout << "             Add More Song?           " << endl;
                cout << "--------------------------------------" << endl;
                cout << "       1. Yes             2. No       " << endl;
                cout << "--------------------------------------" << endl;
                cout << "Choice: "; cin >> pilih;
                cout << "--------------------------------------" << endl;;
                cout << endl;
                if (pilih == 2){
                    runAdd = false;
                }
            }

        } else if (pilih == 2){
            showLibrary(L);
            int back;
            cout << "--------------------------------------" << endl;
            cout << "Press any number to back: "; cin >> back;
            cout << "--------------------------------------" << endl;
            cout << endl;
        } else if (pilih == 3){
            cout << "Enter song title to edit: "; cin >> judul;
            adrLagu l = findLagu(L, judul);
            if (l != nullptr){
                int edit;
                cout << "======================================" << endl;
                cout << "           CONFIRM EDIT SONG          " << endl;
                cout << "======================================" << endl;
                cout << "Title        : "; cout << l->info.judulLagu << endl;
                cout << "Artist / Band: "; cout << l->info.penyanyi << endl;
                cout << "Album        : "; cout << l->info.album << endl;
                cout << "Year         : "; cout << l->info.tahun << endl;
                cout << "--------------------------------------" << endl;
                cout << "       1. Yes             2. No       " << endl;
                cout << "--------------------------------------" << endl;
                cout << "Choice: "; cin >> edit;
                cout << "--------------------------------------" << endl;
                cout << endl;
                if (edit == 1){
                    editLagu(l);
                    cout << " ------------------------------------ " << endl;
                    cout << "|             Song Edited!           |" << endl;
                    cout << " ------------------------------------ " << endl;
                    cout << endl;
                } else {
                    cout << " ------------------------------------ " << endl;
                    cout << "|            Edit Cancelled          |" << endl;
                    cout << " ------------------------------------ " << endl;
                    cout << endl;
                }
                cout << endl;
            } else {
                cout << "Song not found :/" << endl;
            }

        } else if (pilih == 4){
            cout << "Input song title to delete: "; cin >> judul;
            adrLagu l = findLagu(L, judul);
            if (l != nullptr){
                int del;
                cout << "======================================" << endl;
                cout << "          CONFIRM DELETE SONG         " << endl;
                cout << "======================================" << endl;
                cout << "Title        : "; cout << l->info.judulLagu << endl;
                cout << "Artist / Band: "; cout << l->info.penyanyi << endl;
                cout << "Album        : "; cout << l->info.album << endl;
                cout << "Year         : "; cout << l->info.tahun << endl;
                cout << "--------------------------------------" << endl;
                cout << "       1. Yes             2. No       " << endl;
                cout << "--------------------------------------" << endl;
                cout << "Choice: "; cin >> del;
                cout << "--------------------------------------" << endl;
                cout << endl;
                if (del == 1){
                    deleteLagu(L, P, judul);
                    deleteEdgeByLagu(G, l);
                    deleteVertexByLagu(G, l);
                    cout << " -------------------------------------- " << endl;
                    cout << "|             Song Deleted!            |" << endl;
                    cout << " -------------------------------------- " << endl;
                    cout << endl;
                } else {
                    cout << " ------------------------------------ " << endl;
                    cout << "|           Delete Cancelled         |" << endl;
                    cout << " ------------------------------------ " << endl;
                    cout << endl;
                }
            } else {
                cout << "Song not found :/" << endl;
            }
        } else {
            runAdmin = false;
        }
    }
}

void menuUser(ListPlaylist &P, ListLagu L, Graph G){
    int pilih;
    bool runUser = true;
    while (runUser){
        cout << "======================================" << endl;
        cout << "                 USER                 " << endl;
        cout << "======================================" << endl;
        cout << "1. Search Song" << endl;
        cout << "2. Play Song From Library" << endl;
        cout << "3. Display Playlist" << endl;
        cout << "0. Switch" << endl;
        cout << "--------------------------------------" << endl;
        cout << "Choice: "; cin >> pilih;
        cout << "--------------------------------------" << endl;
        cout << endl;
        if (pilih == 1){
            string judul;
            cout << "Search song: "; cin >> judul;
            adrLagu l = findLagu(L, judul);
            if (l != nullptr){
                cout << "======================================" << endl;
                cout << "             SEARCH RESULT            " << endl;
                cout << "======================================" << endl;
                cout << "Title        : "; cout << l->info.judulLagu << endl;
                cout << "Artist / Band: "; cout << l->info.penyanyi << endl;
                cout << "Album        : "; cout << l->info.album << endl;
                cout << "Year         : "; cout << l->info.tahun << endl;
                cout << "Genre        : "; cout << l->info.genre << endl;
                cout << "Language     : "; cout << l->info.bahasa << endl;
                cout << "--------------------------------------" << endl;
                cout << "      1. Play            2. Back      " << endl;
                cout << "--------------------------------------" << endl;
                cout << "Choice: "; cin >> pilih;
                cout << "--------------------------------------" << endl;
                cout << endl;
                if (pilih == 1){
                    cout << "======================================" << endl;
                    cout << "          PLAYING FROM LIBRARY         " << endl;
                    cout << "======================================" << endl;
                    cout << "                   ||" << endl;
                    playLagu(P, G, l);
                }
            } else {
                cout << " ------------------------------------ " << endl;
                cout << "|          Song Not Found :/         |" << endl;
                cout << " ------------------------------------ " << endl;
            }
        } else if (pilih == 2){
            playLagu(P, G, L.first);
        } else if (pilih == 3){
            showPlaylist(P);
            string nama;
            cout << "1. Create Playlist" << endl;
            cout << "2. View Playlist" << endl;
            cout << "3. Delete Playlist" << endl;
            cout << "0. Back" << endl;
            cout << "--------------------------------------" << endl;
            cout << "Choice: "; cin >> pilih;
            cout << "--------------------------------------" << endl;
            cout << endl;
            if (pilih == 1){
                cout << "Enter new playlist name: "; cin >> nama;
                adrPlaylist p = createElmPlaylist(nama);
                insertFirstPlaylist(P, p);
                cout << " ------------------------------------ " << endl;
                cout << "|     Succesfully Added Playlist!    |" << endl;
                cout << " ------------------------------------ " << endl;
                cout << endl;
            } else if (pilih == 2){
                cout << "Enter playlist name to view: "; cin >> nama;
                adrPlaylist p = findPlaylist(P, nama);
                if (p != nullptr ){
                    showPlaylistLagu(p);
                    int playPlaylist;
                    if (p->firstRelasi != nullptr){
                        cout << "--------------------------------------" << endl;
                        cout << "1. Add Song           2. Delete Song" << endl;
                        cout << "3. Start Playlist     0. Back" << endl;
                        cout << "--------------------------------------" << endl;
                        cout << "Choice: "; cin >> playPlaylist;
                        cout << "--------------------------------------" << endl;
                        cout << endl;
                        if (playPlaylist == 1){
                            string title;
                            showLibrary(L);
                            cout << "Enter song title to add: "; cin >> title;
                            adrLagu l = findLagu(L, title);
                            if (l != nullptr){
                                addLaguToPlaylist(p, l);
                                cout << " ------------------------------------ " << endl;
                                cout << "|  Successfully Added To Playlist!   |" << endl;
                                cout << " ------------------------------------ " << endl;
                            } else {
                                cout << " ------------------------------------ " << endl;
                                cout << "|          Song Not Found :/         |" << endl;
                                cout << " ------------------------------------ " << endl;
                            }
                        } else if (playPlaylist == 2){
                            string title;
                            cout << "Enter song title to delete: "; cin >> title;
                            adrLagu l = findLagu(L, title);
                            if (l != nullptr){
                                deleteRelasiByLagu(p, l);
                                cout << " ------------------------------------ " << endl;
                                cout << "|     Song Deleted From Playlist!    |" << endl;
                                cout << " ------------------------------------ " << endl;
                            } else {
                                cout << " ------------------------------------ " << endl;
                                cout << "|          Song Not Found :/         |" << endl;
                                cout << " ------------------------------------ " << endl;
                            }
                        } else if (playPlaylist == 3){
                            playLaguFromPlaylist(P, G, p);
                        }
                    } else {
                        cout << "--------------------------------------" << endl;
                        cout << "1. Add Song           0. Back         " << endl;
                        cout << "--------------------------------------" << endl;
                        cout << "Choice: "; cin >> playPlaylist;
                        cout << "--------------------------------------" << endl;
                        cout << endl;
                        if (playPlaylist == 1){
                            string title;
                            showLibrary(L);
                            cout << "Enter song title to add: "; cin >> title;
                            adrLagu l = findLagu(L, title);
                            if (l != nullptr){
                                addLaguToPlaylist(p, l);
                                cout << " ------------------------------------ " << endl;
                                cout << "|  Successfully Added To Playlist!   |" << endl;
                                cout << " ------------------------------------ " << endl;
                            } else {
                                cout << " ------------------------------------ " << endl;
                                cout << "|          Song Not Found :/         |" << endl;
                                cout << " ------------------------------------ " << endl;
                            }
                        } else if (playPlaylist == 2){
                            string title;
                            cout << "Enter song title to delete: "; cin >> title;
                            adrLagu l = findLagu(L, title);
                            if (l != nullptr){
                                deleteRelasiByLagu(p, l);
                                cout << " ------------------------------------ " << endl;
                                cout << "|     Song Deleted From Playlist!    |" << endl;
                                cout << " ------------------------------------ " << endl;
                            } else {
                                cout << " ------------------------------------ " << endl;
                                cout << "|          Song Not Found :/         |" << endl;
                                cout << " ------------------------------------ " << endl;
                            }
                        }
                    }
                }
            } else if (pilih == 3){
                cout << "Enter Playlist name to delete: "; cin >> nama;
                adrPlaylist p = findPlaylist(P, nama);
                if (p != nullptr){
                    deletePlaylist(P, nama);
                    cout << " ------------------------------------ " << endl;
                    cout << "|          Playlist Deleted!         |" << endl;
                    cout << " ------------------------------------ " << endl;
                    cout << endl;
                } else {
                    cout << " ------------------------------------ " << endl;
                    cout << "|        Playlist Not Found :/       |" << endl;
                    cout << " ------------------------------------ " << endl;
                    cout << endl;
                }
            }
        } else {
            runUser = false;
        }
    }
}

void dataDummyLagu(ListLagu &L, Graph &G){
    adrLagu l;
    Lagu Lg;

    Lg.judulLagu = "Love_Scenario";
    Lg.penyanyi = "iKON";
    Lg.album = "Return";
    Lg.tahun = 2018;
    Lg.genre = "Pop";
    Lg.bahasa = "KR";
    l = createElmLagu( Lg.judulLagu, Lg.penyanyi, Lg.album, Lg.tahun, Lg.genre, Lg.bahasa);
    insertLastLagu(L, l);
    addLaguToGraph(G, l);
    connectGenreOrLang(G, L, l);

    Lg.judulLagu = "Gurenge";
    Lg.penyanyi = "LiSA ";
    Lg.album = "LEO-NiNE";
    Lg.tahun = 2020;
    Lg.genre = "Pop";
    Lg.bahasa = "JP";
    l = createElmLagu(Lg.judulLagu, Lg.penyanyi, Lg.album, Lg.tahun, Lg.genre, Lg.bahasa);
    insertLastLagu(L, l);
    addLaguToGraph(G, l);
    connectGenreOrLang(G, L, l);

    Lg.judulLagu = "Seberapa_Pantas";
    Lg.penyanyi = "Sheila_On_7";
    Lg.album = "07_Des";
    Lg.tahun = 2002;
    Lg.genre = "Pop";
    Lg.bahasa = "ID";
    l = createElmLagu(Lg.judulLagu, Lg.penyanyi, Lg.album, Lg.tahun, Lg.genre, Lg.bahasa);
    insertLastLagu(L, l);
    addLaguToGraph(G, l);
    connectGenreOrLang(G, L, l);

    Lg.judulLagu = "Helena";
    Lg.penyanyi = "My_Chemical_Romance";
    Lg.album = "Three_Cheers_for_Sweet_Revenge";
    Lg.tahun = 2004;
    Lg.genre = "rock";
    Lg.bahasa = "EN";
    l = createElmLagu(Lg.judulLagu, Lg.penyanyi, Lg.album, Lg.tahun, Lg.genre, Lg.bahasa);
    insertLastLagu(L, l);
    addLaguToGraph(G, l);
    connectGenreOrLang(G, L, l);

    Lg.judulLagu = "Kamu yang pertama";
    Lg.penyanyi = "Geisha";
    Lg.album = "Cinta dan benci";
    Lg.tahun = 2009;
    Lg.genre = "Pop";
    Lg.bahasa = "ID";
    l = createElmLagu(Lg.judulLagu, Lg.penyanyi, Lg.album, Lg.tahun, Lg.genre, Lg.bahasa);
    insertLastLagu(L, l);
    addLaguToGraph(G, l);
    connectGenreOrLang(G, L, l);

    Lg.judulLagu = "I_Pray";
    Lg.penyanyi = "LANY";
    Lg.album = "A_beautiful_blur";
    Lg.tahun = 2023;
    Lg.genre = "Pop";
    Lg.bahasa = "EN";
    l = createElmLagu(Lg.judulLagu, Lg.penyanyi, Lg.album, Lg.tahun, Lg.genre, Lg.bahasa);
    insertLastLagu(L, l);
    addLaguToGraph(G, l);
    connectGenreOrLang(G, L, l);


    Lg.judulLagu = "Serba_Salah";
    Lg.penyanyi = "Raisa";
    Lg.album = "Raisa";
    Lg.tahun = 2011;
    Lg.genre = "Pop";
    Lg.bahasa = "IN";
    l = createElmLagu(Lg.judulLagu, Lg.penyanyi, Lg.album, Lg.tahun, Lg.genre, Lg.bahasa);
    insertLastLagu(L, l);
    addLaguToGraph(G, l);
    connectGenreOrLang(G, L, l);


    Lg.judulLagu = "Idol";
    Lg.penyanyi = "YOASOBI";
    Lg.album = "THE_BOOK_3";
    Lg.tahun = 2023;
    Lg.genre = "Pop";
    Lg.bahasa = "JP";
    l = createElmLagu(Lg.judulLagu, Lg.penyanyi, Lg.album, Lg.tahun, Lg.genre, Lg.bahasa);
    insertLastLagu(L, l);
    addLaguToGraph(G, l);
    connectGenreOrLang(G, L, l);


    Lg.judulLagu = "Bertaut";
    Lg.penyanyi = "Nadin_Amizah";
    Lg.album = "Selamat_Ulang_Tahun";
    Lg.tahun = 2020;
    Lg.genre = "Indie";
    Lg.bahasa = "IN";
    l = createElmLagu(Lg.judulLagu, Lg.penyanyi, Lg.album, Lg.tahun, Lg.genre, Lg.bahasa);
    insertLastLagu(L, l);
    addLaguToGraph(G, l);
    connectGenreOrLang(G, L, l);


    Lg.judulLagu = "Drawer";
    Lg.penyanyi = "10cm";
    Lg.album = "Our_Beloved_Summer";
    Lg.tahun = 2021;
    Lg.genre = "Indie";
    Lg.bahasa = "KR";
    l = createElmLagu(Lg.judulLagu, Lg.penyanyi, Lg.album, Lg.tahun, Lg.genre, Lg.bahasa);
    insertLastLagu(L, l);
    addLaguToGraph(G, l);
    connectGenreOrLang(G, L, l);


    Lg.judulLagu = "Seasons";
    Lg.penyanyi = "Wave_To_Earth";
    Lg.album = "Summer_Flows_0,02";
    Lg.tahun = 2020;
    Lg.genre = "Indie";
    Lg.bahasa = "EN";
    l = createElmLagu(Lg.judulLagu, Lg.penyanyi, Lg.album, Lg.tahun, Lg.genre, Lg.bahasa);
    insertLastLagu(L, l);
    addLaguToGraph(G, l);
    connectGenreOrLang(G, L, l);


    Lg.judulLagu = "Shoot_Me";
    Lg.penyanyi = "DAY6";
    Lg.album = "Youth_Part_1";
    Lg.tahun = 2018;
    Lg.genre = "Rock";
    Lg.bahasa = "KR";
    l = createElmLagu(Lg.judulLagu, Lg.penyanyi, Lg.album, Lg.tahun, Lg.genre, Lg.bahasa);
    insertLastLagu(L, l);
    addLaguToGraph(G, l);
    connectGenreOrLang(G, L, l);


    Lg.judulLagu = "On_Bended_Knee";
    Lg.penyanyi = "Boyz_II_Men";
    Lg.album = "II";
    Lg.tahun = 1994;
    Lg.genre = "RnB";
    Lg.bahasa = "EN";
    l = createElmLagu(Lg.judulLagu, Lg.penyanyi, Lg.album, Lg.tahun, Lg.genre, Lg.bahasa);
    insertLastLagu(L, l);
    addLaguToGraph(G, l);
    connectGenreOrLang(G, L, l);


    Lg.judulLagu = "Wonderland";
    Lg.penyanyi = "Iri";
    Lg.album = "Shade";
    Lg.tahun = 2019;
    Lg.genre = "RnB";
    Lg.bahasa = "JP";
    l = createElmLagu(Lg.judulLagu, Lg.penyanyi, Lg.album, Lg.tahun, Lg.genre, Lg.bahasa);
    insertLastLagu(L, l);
    addLaguToGraph(G, l);
    connectGenreOrLang(G, L, l);

    Lg.judulLagu = "NewFlash";
    Lg.penyanyi = "NIKI";
    Lg.album = "Zephyr";
    Lg.tahun = 2018;
    Lg.genre = "RnB";
    Lg.bahasa = "EN";
    l = createElmLagu(Lg.judulLagu, Lg.penyanyi, Lg.album, Lg.tahun, Lg.genre, Lg.bahasa);
    insertLastLagu(L, l);
    addLaguToGraph(G, l);
    connectGenreOrLang(G, L, l);
}

