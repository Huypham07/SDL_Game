# TRAP ADVENTURE 2
## CÁC MỤC CHÍNH <br />
* [DEMO](#demo)
* [MÔ TẢ GAME](#info)
* [HƯỚNG DẪN CÀI ĐẶT](#setup)
* [HƯỚNG DẪN CHƠI](#detail)
* [KỸ THUẬT LẬP TRÌNH](#tech)
* [HƯỚNG ĐI TRONG TƯƠNG LAI](#future)
* [KẾT LUẬN](#summary)

### <a name="demo"/> _DEMO_
Video Demo [https://youtu.be/9wpVOchaK8I](https://youtu.be/x94E362bCvQ)
### <a name="info"/> _MÔ TẢ GAME_
Trap Adventure 2 được lấy cảm hứng từ tựa game cùng tên và Mario. Lối chơi vẫn được giữ nguyên, tuy nhiên game đã được cải tiến về mặt đồ họa cũng như map của game được tạo mới gần như hoàn toàn.
### <a name="setup"/> _HƯỚNG DẪN CÀI ĐẶT_
* B1: Download project từ Github về
* B2: Copy các file đuôi "dll" vào đường dẫn "bin/Debug"
* B3: Copy 3 tệp "image", "font", "sound" vào đường dẫn "bin/Debug"
* B4: Mở file "SDL_Game.exe" trong "bin/Debug" để trải nghiệm game
### <a name="detail"/> _HƯỚNG DẪN CHƠI_
* Người chơi click vào ô "start" để bắt đầu <br />
![image](https://user-images.githubusercontent.com/86708207/230606365-cb7d1002-2084-4a01-bdef-4913ddf472e2.png)

* Người chơi điều khiển nhân vật như sau: <br />
&nbsp; - Phím mũi tên sang phải, trái để nhân vật di chuyển sang hai bên. <br />
![image](https://user-images.githubusercontent.com/86708207/230607428-89ac00fa-73f8-45db-859f-5c28faa2ee5e.png)

&nbsp; - Phím cách (space) để nhảy lên. <br />
&nbsp; - Người chơi có thể sử dụng đồng thời các phím di chuyển và phím cách (space) để vừa nhảy vừa có thể di chuyển. <br />
![image](https://user-images.githubusercontent.com/86708207/230607842-bba2c897-caa5-46c7-830f-b9b470379ab8.png)

&nbsp; - Lưu ý: Sẽ có rất nhiều bẫy trong suốt quá trình chơi game: bẫy ẩn, quả bóng, nếu như chạm phải bẫy thì người chơi sẽ thua và phải chơi lại từ đầu <br />
![image](https://user-images.githubusercontent.com/86708207/230608140-81146b2e-5f94-4285-80e6-024841a0f659.png)

* Chức năng setting của game (Bao gồm Music, Sound, Back, Close): <br />
![image](https://user-images.githubusercontent.com/86708207/230606142-a033dd7b-e305-4207-bed6-854ccd40adc0.png)


&nbsp; - Music: Điều khiển âm lượng của nhạc game, người chơi có thể click chuột hoặc cuộn chuột để điều chỉnh âm lượng. <br />
&nbsp; - Sound: Điều khiển âm lượng của các hiệu ứng trong game như tiếng click, hành động nhảy của nhân vật, người chơi có thể click chuột hoặc cuộn chuột để điều chỉnh âm lượng. <br />
&nbsp; - Back: Click vào icon hoặc chữ "Back" để thoát khỏi setting. <br />
&nbsp; - Close: Click vào icon hoặc chữ "Close" để thoát khỏi game. <br />
* Người chơi chạm vào lá cờ để chiến thắng game. <br />
![image](https://user-images.githubusercontent.com/86708207/230608311-b1b742a1-c94f-4b78-9845-24634d6abf2a.png)

### <a name="tech"/> _KỸ THUẬT LẬP TRÌNH_
* Xây dụng trên nền tảng C++ và SDL2 bao gồm: SDL2, SDL_image, SDL_mixer, SDL_ttf
* Sử dụng các kỹ thuật lập trình cơ bản như: <br />
&nbsp; - Biến (static, extern), vòng lặp, cấu trúc rẽ nhánh, mảng, chuỗi. <br />
&nbsp; - Con trỏ, struct. <br />
&nbsp; - Đọc file. <br />
&nbsp; - Tách file. <br />
### <a name="future"/> _HƯỚNG ĐI TRONG TƯƠNG LAI_
* Kết nối hóa: <br />
&nbsp; - Sử dụng kết nối mạng máy tính để kết nối người chơi với nhau, và có thể lưu thông tin người chơi. <br />
&nbsp; - Tạo ra một môi trường mà từ 2-3 người có thể cùng chơi với nhau, có thể chơi xem ai là người về đích sớm nhất, hoặc ai là người sống sót cuối cùng. <br />
&nbsp; - Người chơi có thể giao tiếp với nhau qua game với mic, chat, ... <br />
* Phát triển game: <br />
&nbsp; - Cải thiện độ mượt của game <br />
&nbsp; - Tạo ra nhiều map game với độ khó cao hơn. <br />
&nbsp; - Thêm nhiều nhân vật vào game, thêm tính năng nạp tiền để mua nhân vật. <br />
&nbsp; - Thêm nhiều bot vào game để tăng độ khó <br />
&nbsp; - Thêm chức năng cho nhân vât, VD: bắn quái, dịch chuyển, ... <br />
### <a name="summary"/> _KẾT LUẬN_
* Game được viết do bản thân 100%, có sự học hỏi từ lazyfoo.
* Việc tự hoàn thiện một game cơ bản giúp mở mang kiến thức rất nhiều về quá trình xây dựng một project.
* Tuy nhiên game vẫn còn một số khuyết điểm như: <br />
&nbsp; - Code chưa được tối ưu hoàn toàn nên vẫn còn xảy ra tình trạng treo game khi để mở game quá lâu. <br />
&nbsp; - Code vẫn còn ngây ngô, một số chỗ gây khó hiểu cho người đọc. <br />
* Mọi câu hỏi hoặc đóng góp vui lòng gửi về địa chỉ _huyhochoi541@gmail.com_
#### _CHÚC THẦY CÔ VÀ CÁC BẠN CHƠI GAME VUI VẺ !!!_
