#include <iostream>
#include "lagu.h"
using namespace std;

int main()
{
    ListLagu LL;
    ListPlaylist LP;
    Graph G;

    createListLagu(LL);
    createListPlaylist(LP);
    createGraph(G);

    adrLagu l;
    adrPlaylist p;
    adrRelasi r;

    dataDummyLagu(LL, G); // insert data dummy (awal)
    p = createElmPlaylist("Favorite"); //playlist deafult
    insertFirstPlaylist(LP, p);

    bool run = true;
    int pilih;
    while (run){
        cout << "======================================" << endl;
        cout << "        NFN - MUSIC PLAYER APP        " << endl;
        cout << "======================================" << endl;
        cout << "Select your role:" << endl;
        cout << "--------------------------------------" << endl;
        cout << "1. Admin" << endl;
        cout << "2. User" << endl;
        cout << "0. Exit" << endl;
        cout << "--------------------------------------" << endl;
        cout << "Choice: "; cin >> pilih;
        cout << "--------------------------------------" << endl;
        cout << endl;
        if (pilih == 1){
            menuAdmin(LL, LP, G);
        } else if (pilih == 2){
            menuUser(LP, LL, G);
        } else {
            run = false;
        }
    }



    return 0;
}
