#include<iostream>
#include<string>
#include<cstring>
#include<iomanip>
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

// Hàm định dạng số
char* DinhDangSo(double num){
    char NumStr[50]; 
    sprintf(NumStr,"%.2f",num); // chuyển đổi kiểu dữ liệu từ double sang stringstring

    int len = strlen(NumStr); // chiều dài của chuỗi
    int DemThap = len -1;
    while(DemThap >= 0 && NumStr[DemThap] != '.'){  // tìm vị trí dấu chấm đầu tiên từ phải qua 
        DemThap--;
    }
    int DemCham = (DemThap -1)/3; // số dấu chấm cần thêm vào
    int NewSize = len + DemCham +1; // kích thước mới của chuỗi sau khi thêm dấu chấm, +1 là thêm vị trí cho null-terminal(\0) để biết là cần kết thúc chuỗi ở đâuđâu
    char* SoMoi = new char[NewSize]; // cấp phát bộ nhớ cho chuỗi mới là SoMoi
    SoMoi[NewSize-1] = '\0'; 

    int Dem = 0;
    int ViTri = len -1;

    for(int i = NewSize -2; i >= 0; --i ){ // -2 là do bỏ thêm vị trí của null-terminal(\0)
        if(NumStr[ViTri] =='.'){ // nếu gặp dấu chấm 
            SoMoi[i] =NumStr[ViTri--]; // thêm dấu chấm đó vào chuỗi SoMoi
            Dem = 0; // giá trị biến Dem sẽ qua lại 0
        }
        else if(Dem == 3){ // nếu biến Dem = 3 
            SoMoi[i] = '.'; // chuỗi SoMoi sẽ đc thêm dấu chấm vào chuỗi
            Dem = 0; // giá trị biến Dem sẽ qua lại 00
        }
        else{ // TH còn lại
            SoMoi[i] = NumStr[ViTri--]; // thêm các ký tự vào chuỗi SoMoi 
            Dem++; // Giá trị biến Dem tăng lên 1 đơn vịvị
        }
    }
    return SoMoi; // xuất chuỗi SoMoiSoMoi

}

void TongGiaKho(Book ds[], int &size,int Max_size){
    int TongSoLuong;
    double TongSoTien;

    for(int i = 0; i < size; i++ ){
        TongSoLuong += ds[i].tongtonkho;
        TongSoTien += ds[i].tong;
    }

    cout<<"Ton kho sach: \n";
    cout<<"- So luong: "<<TongSoLuong<<endl;
    char* DinhDangTong = DinhDangSo(TongSoTien);
    cout<<"- So tien: "<<DinhDangTong<<" VND"<<endl;
    delete[] DinhDangTong; // giải phóng bộ nhớ 

}
//  Hàm in sách
void InSach(Book ds[], int &size, int Max_size){
    cout<<"Danh sach hang hoa:\n";
    for(int i = 0; i < size; i++){
        char* DinhDangVon = DinhDangSo(ds[i].giavon);
        char* DinhDangban = DinhDangSo(ds[i].giaban);
        char* DinhDangtong = DinhDangSo(ds[i].tong);

        cout<<"\nSo thu tu: "<< ds[i].stt<<"."<<endl;
        cout<<"- Ma sach: "<<ds[i].masach<<"\t"<<"\t"<<"||"<<"\t"<< "Ten sach: "<<ds[i].tensach<<"."<<endl;
        cout<<"- So luong ton kho: "<<ds[i].tongtonkho<<"\t"<<"||"<<"\t"<<"Don gia: "<<DinhDangVon<<"."<<endl;
        cout<<"- Don gia ban: "<<DinhDangban<<"\t"<<"||"<<"\t"<<"Thanh tien: "<<DinhDangtong<<"."<<"\n";
        delete[] DinhDangVon; // giải phóng bộ nhớ
        delete[] DinhDangban;
        delete[] DinhDangtong;
    }
}


int main() {
    const int Max_size = 100; // này là kích thước của danh sách mày muốn để nhiêu thì để!!!!!
    Book ds[Max_size];
    int size = 0;

    // Thêm một số sách để kiểm tra
    ds[size++] = {1, 1001, "C++ Programming", 10, 200.0, 300.0, 2000.0};
    ds[size++] = {2, 1002, "Data Structures", 5, 150.0, 250.0, 750.0};

    // TongGiaKho(ds, size, Max_size);
    InSach(ds, size, Max_size);

    return 0;
}

