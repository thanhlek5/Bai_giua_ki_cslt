#include <iostream>
#include<cstring>
using namespace std;
struct Book{
    int stt;
    int masach;
    char tensach[100];
    int tongtonkho;
    double giavon;
    double giaban;
    double tong;
};

bool KtMa(Book ds[],int &size, int masach){
    for(int i =0; i < size; i++){
        if(ds[i].masach == masach){
            return false;
        }
    }
    return true;
}

void Nhapsach(Book ds[], int &size, int Max_size){
    if(size >= Max_size){
        cout<<"danh sach da day!\n";
        return;
    }

    Book Books;
    Books.stt = size +1;

    cout<<"'Nhap ma sach: ";
    cin>> Books.masach;

    while(!KtMa(ds,size, Books.masach)){
        cout<<"Ma sach da ton tai, hay nhap lai ma sach.";
        cin>>Books.masach;
    }

    cout<<"Nhap ten sach: ";
    cin.ignore();
    cin.getline(Books.tensach,100);

    cout<<"Nhap hang ton kho: ";
    cin>>Books.tongtonkho;

    cout<<"Nhap gia von: ";
    cin>>Books.giavon;

    cout<<"Nhap Gia ban: ";
    cin>>Books.giaban;

    Books.tong = Books.giavon * Books.tongtonkho;

    ds[size] = Books;
    size++;
    cout<<"them sach thanh cong! ";    
}

int main(){
    const int Max_size = 100000;  
    Book ds[Max_size];
    int size = 0;
        Nhapsach(ds,size,Max_size);
        
        return 0;
}