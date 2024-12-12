#include <iostream>
#include <string>
#include <sstream>
using namespace std;

struct Book {
    int id;             // Số thứ tự
    string code;        // Mã sách
    string name;        // Tên sách
    int stock;          // Số lượng tồn kho
    double price;       // Đơn giá tồn kho
    double total_value; // Thành tiền
    double sell_price;  // Đơn giá bán
};

// Kiểm tra tính duy nhất của mã sách
bool isUniqueCode(Book books[], int size, string code) {
    for (int i = 0; i < size; i++) {  // vòng lặp duyệt qua từng mã sáchsách
        if (books[i].code == code) {  // nếu mã sách nhập trùng với mã sách đã có thì sẽ return False
            return false;
        }
    }
    return true; // ngược lại thì là True
}

// Nhập danh sách sách
void inputBooks(Book books[], int &size, int max_size) {
    if (size >= max_size) {   // nếu số lượng sách vượt quá max_size nghĩa là danh sách đã đầy không thể thêm vô nữanữa
        cout << "Danh sach da day!\n";
        return;
    }
    Book newBook;
    newBook.id = size + 1;   // tự động thêm số thứ tự của sách
    
    cout << "Nhap ma sach: ";
    cin >> newBook.code;
    while (!isUniqueCode(books, size, newBook.code)) {     // nếu hàm isUniqueCode là False thì vòng lặp này sẽ chạy mãi tới khi nào True
        cout << "ma sach da ton tai, vui long nhap lai: ";
        cin >> newBook.code;
    }

    cout << "Nhap ten sach: ";
    cin.ignore();
    getline(cin, newBook.name);

    cout << "Nhap so luong ton kho: ";
    cin >> newBook.stock;

    cout << "Nhap don gia ton kho: ";
    cin >> newBook.price;

    cout << "Nhap don gia ban: ";
    cin >> newBook.sell_price;

    newBook.total_value = newBook.stock * newBook.price;  

    books[size] = newBook;    // thêm sách vào danh sách 
    size++;
    cout << "Them sach thanh cong!\n";
}
//  Hàm thêm sách 
void addBook(Book books[], int &size, int max_size) {
    if (size >= max_size) {
        cout << "Danh sach da day!\n";
        return;
    }

    int position; // biến vị trí sách 
    cout << "So luong ma sach dang co: " << size <<"\n";
    cout << "Nhap vi tri muon them (1 den " << size + 1 << "): ";
    cin >> position;

    if (position < 1 || position > size + 1) {   // nếu vị trí bé hơn 1 hoặc là lớn hơn size thì xuất ra không hợp lệ
        cout << "Vi tri khong hop le!\n";
        return;
    }

    Book newBook;
    newBook.id = position ; // số thứ tự là vị trí 

    cout << "Nhap ma sach: ";
    cin >> newBook.code;

    for (int i = 0; i < size; i++) {
        if (books[i].code == newBook.code) {
            cout << "Sach da ton tai, cong don so luong.\n";
            int additionalStock;
            double additionalPrice;
            cout << "Nhap so luong them: ";
            cin >> additionalStock;
            cout << "Nhap don gia nhap: ";
            cin >> additionalPrice;

            books[i].stock += additionalStock;
            books[i].price = (books[i].stock * books[i].price + additionalStock * additionalPrice) / (books[i].stock + additionalStock);
            books[i].total_value = books[i].stock * books[i].price;
            return;
        }
    }


    cout << "Nhap ten sach: ";
    cin.ignore();
    getline(cin, newBook.name);

    cout << "nhap so luong ton kho: ";
    cin >> newBook.stock;

    cout << "nhap don gia ton kho: ";
    cin >> newBook.price;

    cout << "Nhap don gia ban: ";
    cin >> newBook.sell_price;

    newBook.total_value = newBook.stock * newBook.price;

    for (int i = size; i >= position; i--) {
        books[i] = books[i - 1];
    }

    books[position - 1] = newBook;
    size++;
    cout << "Them sach thanh cong!\n";
}

void deleteBook(Book books[], int &size) {
    if (size == 0) {
        cout << "Danh sach trong!\n";
        return;
    }

    string code;
    cout << "Nhap ma sach can xoa: ";
    cin >> code;

    for (int i = 0; i < size; i++) {
        if (books[i].code == code) {
            for (int j = i; j < size - 1; j++) {
                books[j] = books[j + 1];
            }
            size--;
            cout << "xoa sach thanh cong!\n";
            return;
        }
    }
    cout << "Khong tim thay ma trong danh sach!\n";
}
// Hàm sắp xếp 
void sortBooksBySellPrice(Book books[], int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = i + 1; j < size; j++) {
            if (books[i].sell_price < books[j].sell_price) {
                Book temp = books[i];
                books[i] = books[j];
                books[j] = temp;
            }
        }
    }
    cout << "Sap xep thanh cong!\n";
}

// Hàm định dạng số
string formatNumber(long long num) {
    stringstream ss;
    ss << num;
    string numStr = ss.str(); // chuyển định dạng thành dạng chuỗi
    string formatted = ""; // biến kết quả

    int count = 0;  // biến đếm để biết khi nào cần thêm dấu chấm (.)
    for (int i = numStr.length() - 1; i >= 0; i--) {   // cho chuỗi chạy ngược vì phải đếm số 0 từ phải sang trái
        formatted = numStr[i] + formatted;    // thêm các số vào biến kết quả
        count++; 
        if (count % 3 == 0 && i != 0) {   // nếu biến đếm chia hết cho 3 và i khác không thì thêm vào biến kết quả dấu (.)
            formatted = "." + formatted; // thêm dấu chấmchấm
        }
    }

    return formatted;
}

//  Hàm tính tổng giá trị tồn kho 
void printTotalStockValue(Book books[], int size) {
    int totalStock = 0;
    double totalValue = 0.0;

    for (int i = 0; i < size; i++) {
        totalStock += books[i].stock;
        totalValue += books[i].total_value;
    }

    cout << "ton kho sach:\n";
    cout << "- So luong: " << totalStock << "\n";
    cout << "- So tien: " << formatNumber(totalValue) <<" VND "<< "\n";
}

//  Hàm in danh sách 
void printBooks(Book books[], int size) {
    cout << "Danh sach hang hoa:\n";
    for (int i = 0; i < size; i++) {
        cout << books[i].id << ". Ma sach: " << books[i].code
            << ", Ten sach: " << books[i].name
            << ", So luong ton kho: " << books[i].stock
            << ", Don gia ton kho: " << formatNumber(books[i].price) << " VND"
            << ", Thanh tien: " << formatNumber(books[i].total_value) << " VND"
            << ", Don gia ban: " << formatNumber(books[i].sell_price) <<" VND"<< "\n";
    }
}


int main() {
    const int MAX_SIZE = 100; // giới hạn số lượng sách của danh sách là 100 mã sáchsách
    Book books[MAX_SIZE];
    int size = 0;

    int choice; // biến để chọn chức năngnăng
    do {   // vòng lặp chức năng 
        cout <<"\nMenu:\n"
            << "1. Nhap danh sach sach\n"
            << "2. Them sach\n"
            << "3. Xoa sach\n"
            << "4. Sap xep theo gia ban\n"
            << "5. Tong gia tri ton kho\n"
            << "6. In danh sach\n"
            << "0. Thoat\n"
            << "Chon: ";
        cin >> choice;

        switch (choice) {
            case 1:
                inputBooks(books, size, MAX_SIZE);
                break;
            case 2:
                addBook(books, size, MAX_SIZE);
                break;
            case 3:
                deleteBook(books, size);
                break;
            case 4:
                sortBooksBySellPrice(books, size);
                break;
            case 5:
                printTotalStockValue(books, size);
                break;
            case 6:
                printBooks(books, size);
                break;
            case 0:
                cout << "Thoat chuong trinh.\n";
                break;
            default:
                cout << "Lua chon khong hop le!\n";
        }
    } while (choice != 0);

    return 0;
}

