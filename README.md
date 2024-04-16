
# **SDL2-TETRIS-GAME-INT2215-51**
Tetris hay xếp hình tạo ra ngày 06/06/1984 tại Moskva. Số thứ 100 của tạp chí Electronic Gaming Monthly gọi Tetris là "Trò chơi Vĩ đại nhất trong Mọi thời đại". Nó đã bán được hơn 70 triệu phiên bản.
- [**SDL2-TETRIS-GAME-INT2215-51**](#sdl2-tetris-game-int2215-51)
- [Mô tả chung](#mô-tả-chung)
  - [Tổng quan](#tổng-quan)
  - [Cách chơi](#cách-chơi)
- [Các tính năng](#các-tính-năng)
  - [1. MENU](#1-menu)
  - [2. Single player](#2-single-player)
  - [3. BATTLE](#3-battle)
  - [4. VS COMPUTER](#4-vs-computer)
  - [5. SETTING](#5-setting)
    - [LEVEL](#level)
    - [GHOST TETROMINO](#ghost-tetromino)
    - [THEME](#theme)
    - [EFFECT](#effect)
    - [VOLUME](#volume)
  - [6. LƯU GAME](#6-lưu-game)
- [TỔNG KẾT](#tổng-kết)

# Mô tả chung
## Tổng quan
- Trò chơi có bảy loại khối hình: I (thẳng đứng), J, L, O (vuông), S, T, Z. Ta thấy mỗi khối gạch được cấu tạo từ 4 hình vuông nhỏ xếp lại với nhau.

- Các hình khác được tạo ra khi xoay các khối cơ bản này các góc tương ứng 90 độ, 180 độ, 270 độ.

## Cách chơi
- Mục tiêu của trò chơi là di chuyển các khối gạch đang rơi từ từ xuống trong kích thước hình chữ nhật 20 hàng x 10 cột (trên màn hình). Chỗ nào có gạch rồi thì không di chuyển được tới vị trí đó. Người chơi xếp những khối hình sao cho khối hình lấp đầy 1 hàng ngang để ghi điểm và hàng ngang ấy sẽ biến mất.
- Sử dụng a,s,d hay các phím mũi tên phải, xuống, trái để di chuyển, phím w hay phím mũi tên lên dùng để quay tetromino. Phím space và enter dùng để thả tetromino xuống ngay lập tức.

# Các tính năng
## 1. MENU

![example](readme_image/menu.png)

- Menu mang đến cho người chơi các 4 chức năng khác là single play, vs human, vs computer và setting. Vói hiệu lá và tuyết rơi bay bay mang đến cho người chơi trải nghiệm như xem phim 3D

## 2. Single player

- Các thanh Top score, score lưu điểm người chơi
- Cơ chế tính điểm: độ khó càng cao, ăn được càng nhiều hàng cùng 1 lúc thì tăng càng nhanh.
- Next tetromino cho phép người chơi tính toán sao cho hợp lí.
- Các tetromino được sinh ra ngẫu nhiên
- Người chơi nhấn P để pause (tùy với mỗi theme sẽ có pause khác nhau)

![example](readme_image/autumn_board.png)
![example](readme_image/winter_board.png)
- Tại bảng pause người chơi có thể chọn chơi tiếp, chơi lại hoặc quay về menu.
- Khi thua game sẽ hiện ra 1 bảng để người chơi lựa chọn quay về menu hay chơi lại.

![example](readme_image/gameover.png)

## 3. BATTLE
- Cho phép hai người chơi chơi cùng 1 lúc, mang đến những trận battle nóng bỏng, gay cấn đến từng phút giây.
- Các tính năng khác có tương tự như trong single play.

![example](readme_image/battle.png)

## 4. VS COMPUTER 
 
- Nếu như không có ai chơi cùng, bạn hoàn toàn có thể chọn chế độ đấu với máy để so tài (đừng coi thường máy nhé).
- Sử dụng các giá trị kì vọng và expected value để tìm vị trí và trạng thái tốt nhất khi rơi, bot có thể dễ dàng chiến thắng 1 người chơi không chuyên với số điểm có thể lên đến 26000 điểm.

![example](readme_image/bot.png)

## 5. SETTING
### LEVEL
- Giúp bạn điều chỉnh level tùy với khả năng chơi của mình, level càng cao tetromino rơi càng nhanh
- Khi đạt được 1 số điểm nhất định, game sẽ tự động tăng level.
- Level khó nhất (Ultra Hard) không chỉ nhanh mà cứ sau 3s game sẽ tiến vào trạng thái tàng hình trong 3s buộc người chơi phải ghi nhớ.

![example](readme_image/invisible.png)

### GHOST TETROMINO
- Người chơi có thể bật tắt ghost tetromino tùy sở thích và phong cách chơi của mình.

![example](readme_image/ghost_tetromino.png)

### THEME
- Game mang đến 2 theme cho người chơi: phong cảnh tuyết rơi mùa đông và lá thu bay bay hữu tình.
![example](readme_image/autumn.png)
![example](readme_image/winter.png)

### EFFECT
- Hiệu ứng khi 1 hay nhiều hàng được xóa
- Chọn None để không sử dụng
- Chọn capcut để có hiệu ứng giật giật
- Chọn Fade để có hiệu ứng biến mất dần dần

### VOLUME

- Thay vì chỉnh volume truyền thống một cách nhàm chán, giờ đây người chơi có thể chỉnh volume bằng cách bắn đại bác, bắn càng xa thì volume càng to và ngược lại
![example](readme_image/Volume.png)

## 6. LƯU GAME
- Khi thoát game bằng cách nhấn phím X, game sẽ được lưu lại từ cách setting đến ván game đang chơi dở giúp người chơi có thể nghỉ ngơi trong mỗi ván đấu.

# TỔNG KẾT
Với nền tảng học SDL2 từ lazyfoo, game do em tự viết hoàn toàn 100% và không copy 1 dòng code nào.

Việc hoàn thiện 1 dự án lập trình như thế này giúp em mở mang kiến thức rất nhiều.
- Sử dụng thành thạo class, pointer, chia tách file,...
- Cách dùng github.
- Cách viết file readme đơn giản
- Học rất nhiều syntax, thuật toán mới của c++.
- Có cái nhìn tổng quát về lập trình hướng đối tượng
- Hình thành tư duy xử lý và giải quyết bài toán và fix bug (rất nhiều bug).
- Học cách refactor code (học tập từ lazyfoo).

Bên cạnh đó, em xin cảm ơn bạn Nguyễn Lê Minh đã mang đến ý tưởng về thuật toán chạy con tetris bot. Em xin chân thành cảm ơn thầy đã góp ý về hiệu ứng thêm đối với game. 

Với rất nhiều tính năng của game đặc biệt là 1 con tetris bot khá là khôn, hiệu ứng đồ họa từ xóa các hàng đến lá và tuyết rơi bay bay, âm thanh của game, em hi vọng mình có thể đạt 9.5+ con game này.





 



