# Update 1:
- Sửa toàn bộ digitalWrite thành analogWrite.
- set analogWrite() với tham số thứ 2 là vận tốc trung bình (sử dụng vận tốc default)
- Tự code Propotional trong PID từ scratch. Ý tưởng: Nếu khoangcach > 2 && khoangcach < gioihan: vantoctrungbinh = khoangcach*Kp
