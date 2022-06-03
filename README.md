# BricksBalls
## Introduction
  Xem demo Game tại : https://www.youtube.com/watch?v=BQM8ThgjV6k 
  
  (Lưu ý : app quay màn hình hiện thị trỏ chuột không chính xác và không ẩn khi chơi game)
## Technologies Used 
* **IDE :** CodeBlock 20.03
* **Thư viện :** SDL-2.0.12, SDL-Image-2.0, SDL-Mixer-2.0, SDL-TTF-2.0
## Use 
**1. Cách chơi**

Quả bóng ban đầu sẽ bay theo hướng trỏ chuột va đập vào tường, cách viên gạch, thanh chắn theo phản xạ vật lý, ta cần phải dùng thanh chắn để các quả bóng không rơi xuống dưới và phá hủy toàn bộ gạch để qua màn.

**2. Cách chơi**

Khi các quả bóng phá hủy gạch sẽ có tỉ lệ ra vật phẩm, khi thanh chắn nhận được vật phẩm xanh thì sẽ có thêm 3 quả bóng bay ra từ thanh chắn, khi nhận được vật phẩm vàng thì mỗi quả bóng sẽ biến thành 3 quả bóng khác
  
 **3. Chế độ custom**
 
 - Khi vào **custom** chọn màu gạch hoặc tường, rồi kéo thả chuột trong lưới để tạo các hình chữ nhật theo ý muốn
 - Sau khi tạo xong map bấm vào biểu tượng **save** rồi chuyển chế độ từ **classic** sang **custom** ở phần **Setting**
 - Vào phần **Play** để bắt đầu chơi màn vừa tạo

## Algorithm
**1. Brick** 

Sử dụng một mảng 2 chiều để lưu trạng thái các ô (như : gạch, là tường, không có gì, ...) và đọc dữ liệu từ 1 file text

**2. Ball** 

Coi game là 1 hệ trục tọa độ với trục Ox là chiều ngang, Oy là chiều dọc và có đơn vị là 1 pixel

Sử dụng một struct(x, y, dirX, dirY) để lưu mỗi quả bóng trong hệ: 
- x, y là tọa độ của bóng hiện tại trong hệ trục tọa độ
- dirX, dirY là vector chỉ hướng của bóng trong hệ trục tọa độ, ta luôn duy trì độ dài vector là 1 đơn vị 

Mỗi một frame ta sẽ thay đổi tọa đổ (x, y) của bóng thành (x + dirX * speed, y + dirY * speed) với speed là tốc độ bóng mong muốn

Gặp vật cản : nếu vật cản theo hướng ngang ta sẽ đổi dấu dirY, nếu gặp vật cản theo hướng dọc ta sẽ đổi dấu dirX

Vật cản đặc biệt : 
- Nếu như ta chỉ bật nảy theo phản xạ thông thường thì hệ số góc của vector sẽ chỉ có 4 dạng dirX/dirY, -dirX/dirY, dirY/dirX, -dirY/dirY, như vậy bóng có thể sẽ không đi vào được một số vùng mà mãi lặp lại theo 1 chu kì di chuyển
- Giải pháp : ta sẽ sử dụng thanh chắn như một hình vòng cung để đổi hệ số góc của vector khi ca chạm với bóng, như vậy vừa có thể làm đa dạng hệ số góc của vector vừa có thể giữ được tính phản xạ 

**3. Items**

Khi bóng phá hủy ô gạch ta sẽ sử dụng hàm random để lấy tỉ lệ sinh ra vật phẩm xanh và vàng

Tỉ lệ sẽ được chọn tỉ lệ thuận với số bóng đang có để giúp cho lượng quà rơi ra một cách ổn định

**4. Custom**

Ta vẫn sử dụng một mảng 2 chiều để lưu trạng thái các ô

Khi nhấn chuột ta sẽ lưu vị trị của ô được nhấn, sau khi kéo lưu thêm vị trí ô thả chuột, rồi đổi toàn bộ trạng thái trong hình chữ nhật có 2 góc là 2 ô trên

Sử dụng flie custom.txt để lưu dữ liệu khi lưu map và nhập dữ liệu khi chơi


