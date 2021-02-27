//Họ tên: Đặng Minh Tân
//MSSV: 0306171391


/*Chú thích toàn source:
-Source được viết theo đúng phong cách kỹ thuật lập trình C/C++ theo các giảng viên bộ môn tin học trường Cao Đẳng Kỹ Thuật Cao Thắng giảng
dạy
-Viết đúng phong cách lập trình thủ tục, source nhìn dễ đọc dễ hiểu
-Các quy tắc khai báo trong source:
+Khai báo hằng được viết toàn bộ in hoa
+Khai báo biến và khai báo hàm được viết thường từ đầu tiên, viết hoa chữ cái đầu của mỗi từ tiếp theo
+Khai báo cấu trúc được viết hoa chữ cái đầu của mỗi từ
+Tất cả khai báo đều được mang định danh theo ý nghĩa và tác dụng của nó, tác dụng gợi nhớ!
*/

//Khai báo thư viện hỗ trợ
#include<iostream>
#include<ctime>
#include"kmin_console.h"
using namespace std;

//Định nghĩa hằng
#define DAU_RAN 1
#define DOT_RAN 254
#define MOI 15
#define DIEM 15
#define TANG_TOC 43
#define GIAM_TOC 45
#define LEN 1
#define XUONG 2
#define TRAI 3
#define PHAI 4
#define TUONG_TREN 1
#define TUONG_DUOI 20
#define TUONG_TRAI 3
#define TUONG_PHAI 63


//Khai báo cấu trúc
typedef struct ToaDo{
	int x;
	int y;
};
typedef struct Node{
	ToaDo info;
	Node *pNext;
};
typedef struct List{
	Node *pHead;
	Node *pTail;
};

//Nguyên mẫu hàm
void khoiTaoList(List &list);
Node *getNode(ToaDo toaDo);
void insertHead(List &list, Node *p);
void insertTail(List &list, Node* p);
void deleteHead(List &list);
void deleteTail(List &list);
void khoiTaoRan(List &list);
void hienThiRan(List &list, ToaDo dotCuoiCu);
ToaDo ranDiChuyen(List &list, int huong);
void batSuKien(int &huong);
void veTuong();
ToaDo taoMoi();
void hienThiMoi(ToaDo toaDoMoi);
bool kiemTraThua(List list);
bool kiemTraAnMoi(List &list, ToaDo toaDoMoi, int &diem, int chiSoTangToc, int chiSoGiamToc);
void veTangToc();
void veGiamToc();
bool kiemTraTangToc(List list, int &chiSoTangToc);
bool kiemTraGiamToc(List list, int &chiSoGiamToc);

//Hàm chính
int main(){
	ToaDo dotCuoiCu;
	ToaDo moi;
	List listRan;
	int chiSoTangToc;
	int chiSoGiamToc;
	int speed;
	int huong;
	int diem;
	chiSoTangToc = 1;
	chiSoGiamToc = 0;
	speed = 300;
	huong = PHAI;
	diem = 0;
	khoiTaoList(listRan);
	khoiTaoRan(listRan);
	veTuong();
	gotoXY(TUONG_PHAI + 2, TUONG_TREN + 2);
	cout << "Diem: " << diem << (char)DIEM;
	gotoXY(TUONG_PHAI + 2, TUONG_TREN + 3);
	cout << "Chi so tang: " << chiSoTangToc;
	gotoXY(TUONG_PHAI + 2, TUONG_TREN + 4);
	cout << "Chi so giam: " << chiSoGiamToc;
	moi = taoMoi();

	//game loop
	while (true){
		gotoXY(TUONG_PHAI + 2, TUONG_TREN + 2);
		cout << "Diem: " << diem << (char)DIEM;
		gotoXY(TUONG_PHAI + 2, TUONG_TREN + 3);
		cout << "Chi so tang: " << chiSoTangToc;
		gotoXY(TUONG_PHAI + 2, TUONG_TREN + 4);
		cout << "Chi so giam: " << chiSoGiamToc;
		veTangToc();
		veGiamToc();
		batSuKien(huong);
		dotCuoiCu = ranDiChuyen(listRan, huong);
		if (kiemTraTangToc(listRan, chiSoTangToc)){
			speed -= 50;
		}
		if (kiemTraGiamToc(listRan, chiSoGiamToc)){
			speed += 30;
		}

		if (kiemTraAnMoi(listRan, moi, diem, chiSoTangToc, chiSoGiamToc)){
			moi = taoMoi();
			hienThiMoi(moi);
		}
		else{
			//có thể mồi rand trúng thân rắn, mà rắn đi qua thì mất mồi, mất mất khi rắn vẫn chưa ăn thì phải hiển thị mồi lại vị trí cũ
			hienThiMoi(moi);
		}
		if (kiemTraThua(listRan)){
			gotoXY(TUONG_TRAI + 13, TUONG_DUOI + 2);
			cout << "Thua oy!!huuuuuuuuuuuuuuuuuuuuuuuuuu" << endl;
			break;
		}
		hienThiRan(listRan, dotCuoiCu);
		Sleep(speed);
	}
	system("pause");
	return 0;
}

/*Hàm khoiTaoList giúp ta khởi tạo ra 1 list rỗng theo cấu trúc của List được định nghĩa phía trên, đầu list và cuối list được gán trỏ đến giá
trị NULL*/
void khoiTaoList(List &list){
	list.pHead = NULL;
	list.pTail = NULL;
}

/*Hàm getNode giúp ta tạo ra 1 Node mới theo cấu trúc Node được định nghĩa phía trên, tham số truyền vào là 1 biến có kiểu ToaDo, hàm trả về 1
biến có kiểu Node* */
Node *getNode(ToaDo toaDo){
	Node *p;
	p = new Node;
	if (p == NULL){
		cout << "Khong du bo nho" << endl;
		return p;
	}
	else{
		p->info = toaDo;
		p->pNext = NULL;
		return p;
	}
}

/*Hàm insertHead cho phép chèn 1 Node mới vào đầu List và giữ lại sự thay đổi đó khi thoát khỏi hàm, tham số truyền vào là 1 List có tham chiếu
và 1 Node, hàm trả về List được thay đổi sau khi chèn vào đâu (hiểu theo tư duy, nếu hiểu theo định nghĩa hàm thì hàm không có giá
trị trả về)*/
void insertHead(List &list, Node *p){
	if (list.pHead == NULL){
		list.pHead = p;
		list.pTail = p;
	}
	else{
		p->pNext = list.pHead;
		list.pHead = p;
	}
}

/*Hàm insertTail cho phép chèn 1 Node mới vào cuối List và giữ lại sự thay đổi đó khi thoát khỏi hàm, tham số truyền vào là 1 List có tham chiếu
và 1 Node, hàm trả về List được thay đổi sau khi chèn vào cuối (hiểu theo tư duy, nếu hiểu theo định nghĩa hàm thì hàm không có giá
trị trả về)*/
void insertTail(List &list, Node *p){
	if (list.pHead == NULL){
		list.pHead = p;
		list.pTail = p;
	}
	else{

		list.pTail->pNext = p;
		list.pTail = p;
	}
}

/*Hàm deleteHead cho phép xóa 1 Node đầu của List và giữ lại sự thay đổi đó khi thoát khỏi hàm, tham số truyền vào là 1 List có tham chiếu, hàm
trả về List được thay đổi sau khi xóa Node đầu (hiểu theo tư duy, nếu hiểu theo định nghĩa hàm thì hàm không có giá trị trả về)*/
void deleteHead(List &list){
	Node *p;
	p = list.pHead;
	list.pHead = p->pNext;
	delete p;
	p = NULL;
}

/*Hàm deleteTail cho phép xóa 1 Node cuối của List và giữ lại sự thay đổi đó khi thoát khỏi hàm, tham số truyền vào là 1 List có tham chiếu, hàm
trả về List được thay đổi sau khi xóa Node cuối (hiểu theo tư duy, nếu hiểu theo định nghĩa hàm thì hàm không có giá trị trả về)*/
void deleteTail(List &list){
	Node *p;//Node duyệt
	Node *q; //Node trước p
	p = list.pHead;
	q = list.pTail;
	for (p; p != NULL; p = p->pNext){
		if (p->pNext == q){
			delete q;
			q = NULL;
			list.pTail = p;
			list.pTail->pNext = NULL;
		}
	}
}

/*Hàm khoiTaoRan cho phép khỏi tạo ra List rắn với số đốt rắn tự cho ban đầu (ở đây em cho rắn có 3 đốt), và điều kiện rắn nằm trong ranh giới 4
bức tường. Hàm truyền vào tham chiếu của 1 List, hàm trả về List rắn có 3 đốt (hiểu theo tư duy, nếu hiểu theo định nghĩa hàm thì hàm không có giá
trị trả về)*/
void khoiTaoRan(List &list){
	ToaDo toaDo;
	Node *p;
	toaDo.x = TUONG_TREN + 5;
	toaDo.y = TUONG_TRAI;
	for (int i = 0; i < 3; i++){
		p = getNode(toaDo);
		insertTail(list, p);
		toaDo.x++;
	}
}

/*Hàm hienThiRan cho phép hiện thị ra màn hình console 1 con rắn với số đốt đang có của nó, đốt rắn và đầu rắn được hiện thị theo khai báo hằng
phía trên, đốt cuối cũ được trền vào sẽ không hiện thị trên màn hình console (bằng cách hiển thị chỗ đấy ký tự "khoảng trắng". Hàm truyền vào 1
List có tham chiếu và đốt cuối cũ, hàm không có giá trị trả về)*/
void hienThiRan(List &list, ToaDo dotCuoiCu){
	Node *p;
	p = list.pHead;
	for (p; p->pNext != NULL; p = p->pNext){
		gotoXY(p->info.x, p->info.y);
		cout << (char)DOT_RAN;
		gotoXY(list.pTail->info.x, list.pTail->info.y);
		cout << (char)DAU_RAN;
	}
	gotoXY(dotCuoiCu.x, dotCuoiCu.y);
	cout << " ";
}

/*Hàm ranDiChuyen cho phép rắn di chuyển theo hướng được truyền vào (lên-xuống-trái-phải). Hàm truyền vào 1 List có tham chiều và hướng di cần di
chuyển của rắn, hàm trả về đốt cuối cũ sau khi rắn di chuyên theo hướng truyền vào*/
ToaDo ranDiChuyen(List &list, int huong){
	ToaDo dotCuoiCu;
	ToaDo toaDo;
	Node *p;
	dotCuoiCu.x = list.pHead->info.x;
	dotCuoiCu.y = list.pHead->info.y;
	switch (huong)
	{
	case LEN:{
				 toaDo.x = list.pTail->info.x;
				 toaDo.y = list.pTail->info.y - 1;
				 insertTail(list, getNode(toaDo));
				 deleteHead(list);
				 break;

	}
	case XUONG:{
				   toaDo.x = list.pTail->info.x;
				   toaDo.y = list.pTail->info.y + 1;
				   insertTail(list, getNode(toaDo));
				   deleteHead(list);
				   break;
	}
	case TRAI:{
				  toaDo.x = list.pTail->info.x - 1;
				  toaDo.y = list.pTail->info.y;
				  insertTail(list, getNode(toaDo));
				  deleteHead(list);
				  break;

	}
	case PHAI:{
				  toaDo.x = list.pTail->info.x + 1;
				  toaDo.y = list.pTail->info.y;
				  insertTail(list, getNode(toaDo));
				  deleteHead(list);
				  break;
	}
	}
	return dotCuoiCu;
}

/*Hàm batSuKien lấy ký tự từ bàn phím, ở đây hàm chỉ lấy những ký tự W-S-A-D và w-s-a-d và lên-xuống-trái-phải để truyền cho hướng mà rắn sẽ di
chuyển. Hàm truyền vào tham chiếu của hướng, hàm không có giá trị trả về*/
void batSuKien(int &huong){
	int key;
	key = inputKey();
	if (key == 'W' || key == 'w' || key == KEY_UP){
		huong = LEN;
	}
	else if (key == 'S' || key == 's' || key == KEY_DOWN){
		huong = XUONG;
	}
	else if (key == 'A' || key == 'a' || key == KEY_LEFT){
		huong = TRAI;
	}
	else if (key == 'D' || key == 'd' || key == KEY_RIGHT){
		huong = PHAI;
	}

}

/*Hàm veTuong cho phép ta vẽ ra màn hình console 4 bức tường, để đặt giới hạn chết của rắn. Hàm không có tham số truyền vào cũng như không có giá
trị trả về*/
void veTuong(){
	//Vẽ từng bức tường
	for (int x = TUONG_TRAI; x <= TUONG_PHAI; x++){
		//vẽ tường trên
		gotoXY(x, TUONG_TREN);
		cout << (char)220;

	}

	for (int y = TUONG_TREN + 1; y <= TUONG_DUOI; y++){
		//vẽ tường trái
		gotoXY(TUONG_TRAI, y);
		cout << (char)221;
	}

	for (int x = TUONG_TRAI; x <= TUONG_PHAI; x++){
		//vẽ tường dưới
		gotoXY(x, TUONG_DUOI);
		cout << (char)223;
	}

	for (int y = TUONG_TREN + 1; y < TUONG_DUOI; y++){
		//vẽ tường phải
		gotoXY(TUONG_PHAI, y);
		cout << (char)222;
	}
	cout << endl << endl;
}

ToaDo taoMoi(){
	//rand từ a->b bằng công thức:
	//a+rand()%(b-a+1)
	ToaDo toaDoMoi;
	srand(time(NULL));
	toaDoMoi.x = TUONG_TRAI + 1 + rand() % (TUONG_PHAI - TUONG_TRAI - 1);
	toaDoMoi.y = TUONG_TREN + 1 + rand() % (TUONG_DUOI - TUONG_TREN - 1);
	return toaDoMoi;
}

//Hàm hienThiMoi hiển thị ra màn hình console ký tự mồi, hàm truyền vào tọa độ của mồi và không có giá trị trả về
void hienThiMoi(ToaDo toaDoMoi){
	gotoXY(toaDoMoi.x, toaDoMoi.y);
	cout << (char)MOI;
}

//Hàm kiemTraThua dùng để kiểm tra điều kiện thua của người chơi. Hàm truyền vào 1 List, hàm trả về giá trị true or false
bool kiemTraThua(List list){
	//Kiểm tra trường hợp rắn cắn trúng tường và rắn cắn chính bản thân mình
	if (list.pTail->info.x == TUONG_TRAI || list.pTail->info.x == TUONG_PHAI){
		//rắn cắn trúng tường trái hoặc tường phải
		return true;
	}
	if (list.pTail->info.y == TUONG_TREN || list.pTail->info.y == TUONG_DUOI){
		//rắn cắn trúng tường trên hoặc tường dưới
		return true;
	}

	ToaDo toaDo;
	toaDo = list.pTail->info;
	for (Node *p = list.pHead; p->pNext != NULL; p = p->pNext){
		if (toaDo.x == p->info.x && toaDo.y == p->info.y){
			//rắn cắn trúng bản thân mình
			return true;
		}
	}
	return false;
}

/*Hàm kiemTraAnMoi để kiểm tra rắn đã ăn mồi hay chưa, nếu rắn ăn mồi thì đuôi rắn sẽ dài thêm 1 đốt. Hàm truyền vào tham chiếu của 1 List, tọa
độ của mồi, tham chiếu điểm số của người chơi và chỉ số tăng tốc - chỉ số giảm tốc để tính điểm, hàm trả về giá trị true or false (rắn đã ăn hoặc chưa ăn mồi)*/
bool kiemTraAnMoi(List &list, ToaDo toaDoMoi, int &diem, int chiSoTangToc, int chiSoGiamToc){
	if (list.pTail->info.x == toaDoMoi.x && list.pTail->info.y == toaDoMoi.y){
		for (int i = 0; i < chiSoTangToc; i++){
			diem++;
		}
		if (diem >= (chiSoTangToc - chiSoGiamToc)){
			diem += chiSoGiamToc;
		}
		
		ToaDo toaDo;
		toaDo.x = list.pHead->info.x;
		toaDo.y = list.pHead->info.y;
		insertHead(list, getNode(toaDo));
		return true;
	}
	return false;
}

//Hàm veTangToc vẽ ra màn hình console ký tự dấu "+" là ký hiệu tăng tốc độ cho rắn. Hàm không có tham số truyền vào và không có giá trị trả về
void veTangToc(){
	gotoXY(TUONG_TRAI + 5, TUONG_TREN + 5);
	cout << (char)TANG_TOC;
	gotoXY(TUONG_TRAI + 35, TUONG_TREN + 15);
	cout << (char)TANG_TOC;
	gotoXY(TUONG_TRAI + 50, TUONG_TREN + 7);
	cout << (char)TANG_TOC;
}

//Hàm veGiamToc vẽ ra màn hình console ký tự dấu "-" là ký hiệu giảm tốc độ cho rắn. Hàm không có tham số truyền vào và không có giá trị trả về
void veGiamToc(){
	gotoXY(TUONG_TRAI + 10, TUONG_TREN + 15);
	cout << (char)GIAM_TOC;
	gotoXY(TUONG_TRAI + 30, TUONG_TREN + 9);
	cout << (char)GIAM_TOC;
}

//Hàm kiemTraTangToc kiểm tra xem có cắn ký tự tăng tốc trên màn hình console hay không. Hàm truyên vào List và tham chiếu của chỉ số tăng tốc, hàm trả về giá trị true or false
bool kiemTraTangToc(List list, int &chiSoTangToc){
	if ((list.pTail->info.x == TUONG_TRAI + 5 && list.pTail->info.y == TUONG_TREN + 5) || (list.pTail->info.x == TUONG_TRAI + 35 && list.pTail->info.y == TUONG_TREN + 15) ||
		(list.pTail->info.x == TUONG_TRAI + 50 && list.pTail->info.y == TUONG_TREN + 7)){
		chiSoTangToc++;
		return true;
	}
	return false;
}

//Hàm kiemTraGiamToc kiểm tra xem có cắn ký tự giảm tốc trên màn hình console hay không. Hàm truyên vào List và tham chiếu của chỉ số giảm tốc, hàm trả về giá trị true or false
bool kiemTraGiamToc(List list, int &chiSoGiamToc){
	if ((list.pTail->info.x == TUONG_TRAI + 10 && list.pTail->info.y == TUONG_TREN + 15) || (list.pTail->info.x == TUONG_TRAI + 30 && list.pTail->info.y == TUONG_TREN + 9)){
		chiSoGiamToc--;
		return true;
	}
	return false;
}
