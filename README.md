# digital-watch
simple digital watch using esp8266
Trương Quốc Huy

1. Chuẩn bị
- esp8266
- i2clcd
- 2 button
- trở 10k ohm
- dây nối
- arduino ide

2. Kết nối
Hai button 1 và 2 được nối với 2 chân GPIO 12 và 14 trên esp8266

3. Hướng dẫn sử dụng
Có 4 chế độ hoạt động:

Mode 0: Chạy đồng hồ bình thường (hh:mm:ss)
Mode 1: Chỉnh giờ ở mode 0
Mode 2: Chỉnh phút ở mode 0
Mode 3: Chỉnh giây ở mode 0
Mode 4: Chạy đồng hồ bấm giờ

Dùng button 1 để chuyển giữa các mode

Ở mode 1, 2, 3 dùng button 2 để chỉnh. Nếu button 2 được nhấn thì tăng thời gian, nếu được nhấn hơn 1s thì tăng 5 giá trị thời gian mỗi 1s

Ở mode 4 dùng button 2 để start và stop. Chuyển sang mode khác thì đồng hồ bấm giờ reset về 00:00:00. Đồng hồ bình thường vẫn chạy nền khi 
đồng hồ bấm giờ chạy.

