#define _CRT_SECURE_NO_SECURES
#include <iostream>
#include <cstring>

using namespace std;

// 棋盘 16 * 16
int a[16][16] = { 0 };
// 覆盖棋盘的编号
int count = 0;
/**
 * tr 棋盘左上角所在的行
 * c 棋盘右上角所在的列
 * dr 特殊棋子的行
 * dc 特殊棋子的列
 * size 棋盘的大小
 */
template<class T>
void ChessBoard_Coverage(T tr, T tc, T dr, T dc, T size) {
	if (size == 1) {
		//只剩一个棋子的棋盘不用覆盖，因为那个就是特殊棋子
		return;
	}
	// 全局变量，用::指明
	T t = ::count++, s = size / 2;
	// 覆盖左上角的棋盘
	if (dr < tr + s && dc < tc + s) {
		// 特殊棋子在左上角棋盘中，直接递归调用，进行覆盖
		ChessBoard_Coverage(tr, tc, dr, dc, s);
	}
	else {
		// 特殊棋子不在左上角棋盘中，那么左上角棋盘在其最右下面有一枚特殊棋子
		// 特殊棋子覆盖
		a[tr + s - 1][tc + s - 1] = t;
		//此时左上角也变成了有特殊棋子的棋盘了，递归调用，进行覆盖
		ChessBoard_Coverage(tr, tc, tr + s - 1, tc + s - 1, s);
	}
	if (dr < tr + s && dc >= tc + s) {
		// 特殊棋子在右上角棋盘中，直接递归调用，进行覆盖
		ChessBoard_Coverage(tr, tc + s, dr, dc, s);
	}
	else {
		// 特殊棋子不在右上角棋盘中，那么右上角棋盘在其最右下面有一枚特殊棋子
		// 特殊棋子覆盖
		a[tr + s - 1][tc + s] = t;
		ChessBoard_Coverage(tr, tc + s, tr + s - 1, tc + s, s);
	}
	if (dr >= tr + s && dc < tc + s) {
		// 特殊棋子在左下角棋盘中，直接递归调用，进行覆盖
		ChessBoard_Coverage(tr + s, tc, dr, dc, s);
	}
	else {
		// 特殊棋子不在左下角棋盘中，那么左下角棋盘在其最右下面有一枚特殊棋子
		// 特殊棋子覆盖
		a[tr + s][tc + s - 1] = t;
		ChessBoard_Coverage(tr + s, tc, tr + s, tc + s - 1, s);
	}
	if (dr >= tr + s && dc >= tc + s) {
		// 特殊棋子在右下角棋盘中，直接递归调用，进行覆盖
		ChessBoard_Coverage(tr + s, tc + s, dr, dc, s);
	}
	else {
		// 特殊棋子不在右下角棋盘中，那么左下角棋盘在其最右下面有一枚特殊棋子
		// 特殊棋子覆盖
		a[tr + s][tc + s] = t;
		ChessBoard_Coverage(tr + s, tc + s, tr + s, tc + s, s);
	}
}

int main() {
	int dr = 0, dc = 0;

	cout << "请输入特殊棋子的行列坐标 : ";

	cin >> dr >> dc;
	//循环将二维数组置0
	for (int i = 0; i < 16; i++) {
		memset(a[i], 0, 16 * sizeof(int));
	}
	//特殊棋子的值设置为-1，方便区分
	a[dr][dc] = -1;

	//调用函数，覆盖棋盘，这里选的是(16 * 16)的棋盘
	ChessBoard_Coverage(0, 0, dr, dc, 16);

	// 输出结果
	for (int i = 0; i < 16; i++) {
		for (int j = 0; j < 16; j++) {
			cout << a[i][j] << "\t";
		}
		cout << endl;
	}
	cout << ::count - 1 << endl;
	return 0;
}
