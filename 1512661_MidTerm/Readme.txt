1.Thông tin cá nhân:
   - MSSV: 1512661
   - Họ tên: Nguyễn Trương Lê Văn
   - Lớp: Lập trình Win 1
2. Các chức năng đã làm được:
     - Thêm vào danh sách các chỉ mục Loại chi tiêu, nội dung chi và số tiền
     - Tự động nạp các chỉ mục trong file txt lên và lưu vào file txt khi thoát, có hỗ trợ cả tiếng Việt có dấu
     - Vẽ biểu đồ hình tròn thể hiện tỉ lệ giữa các loại chi tiêu
     - Hỗ trợ chức năng xóa loại chi tiêu từ list
     - Hiển thị phần trăm các loại chi tiêu
     - Thêm loadscreen hỗ trợ chương trình, khi thực hiện chức năng nạp tập tin
3. Các luồng sự kiện chính:
   -  Chọn loại chi tiêu -> chọn nội dung -> chọn số tiền -> nhấn button -> thêm vào list view -> hiển thị phần trăm tỉ lệ, hiển thị biểu đồ hình tròn
   -  Chọn chỉ mục cần xóa -> nhấn button -> item bị xóa -> cập nhật phần trăm và biểu đồ
   -  Close Window -> hiện thị hộp thoại Save -> Thoát lưu file hoặc không hoặc hủy bỏ việc thoát
    Các luồng sự kiện phụ:
   - Khi người dùng nhập số vào giá tiền có thông báo lỗi
   - Khi ban đầu không có file input, chương trình không nạp từ file
   - Xử lí khi tổng chi tiêu = 0, chương trình không bị tràn số
   - Khi người dùng thoát, hỗ trợ người dùng chức năng tùy chọn save file hay không
   - Khi người dùng thêm vào những các chỉ mục nhưng bị khuyết các thành phần, thông báo lỗi cho người dùng nhập lại
   - Ngăn người dùng resize window, để cho ứng dụng luôn đẹp mắt
   - Khi file quá lớn, chương trình có màn hình loadscreen, báo hiệu cho người dùng chương trình đang nạp
4. Link git: https://github.com/k3v1n1k88/Lab01
    Link youtube: https://youtu.be/s0UDehNLlPs