--- Ubuntu Shortcuts ---
Ctrl + Alt + T         : Mở terminal
Ctrl + Shift + T       : Mở tab terminal mới
Ctrl + C               : Dừng lệnh đang chạy
Ctrl + D               : Đăng xuất terminal / thoát shell
Ctrl + L               : Xóa màn hình terminal
Ctrl + Shift + C       : Copy trong terminal
Ctrl + Shift + V       : Paste trong terminal
Alt + Tab              : Chuyển giữa các ứng dụng
Alt + F4               : Đóng cửa sổ hiện tại
Ctrl + Alt + L         : Khóa màn hình
Super (Windows key)    : Mở dash / tìm kiếm ứng dụng
Ctrl + Alt + arrow key : Chuyển workspace
Ctrl + Shift + N       : Tạo folder mới trong file manager
Ctrl + H               : Hiện/ẩn file ẩn trong file manager

--- Compile C++ trên Linux ---
g++ filename.cpp -o outputfile      : Compile C++ ra executable
chmod +x outputfile                  : Cho phép chạy file executable
./outputfile                         : Chạy file executable
g++ -O2 filename.cpp -o outputfile   : Compile với tối ưu hóa
g++ -Wall filename.cpp -o outputfile : Hiển thị tất cả warning
g++ -std=c++17 filename.cpp -o outputfile : Compile theo chuẩn C++17

--- Compile C trên Linux ---
gcc filename.c -o outputfile          : Compile C ra executable
chmod +x outputfile                   : Cho phép chạy file executable
./outputfile                          : Chạy file executable

--- Notes ---
- Trên Linux, "exe" thường là file nhị phân chạy trực tiếp, không cần đuôi .exe
- Lệnh chmod +x là bắt buộc nếu muốn chạy file sau khi compile
