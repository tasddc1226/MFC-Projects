// hanoi.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include <iostream>

using namespace std;

struct Hanoi
{
	char s_name; // Hanoi tower name
	int data[4] = { 999, 999, 999, 999}; // in tower disk data
	int top_idx;
};

struct Hanoi A;
struct Hanoi B;
struct Hanoi C;
int totalCount = 0;

void init() {
	A.s_name = 'A';
	B.s_name = 'B';
	C.s_name = 'C';

	// init 
	// A disk 999, 3, 2, 1
	// B disk 999, 999, 999, 999
	// C disk 999, 999, 999, 999
	int j = 3;
	for (int i = 1; i < 4; i++) {
		A.data[i] = j;
		j--;
	}
	A.top_idx = 3;
	B.top_idx = 0;
	C.top_idx = 0;
}

// 하노이 종료 조건을 위한 함수
bool finish() {
	if (C.data[1] == 3 && C.data[2] == 2 && C.data[3] == 1) {
		return true;
	}
	return false;
}

void show() {
	cout << "-------------------\n";
	for (int i = 3; i > -1 ; i--) {
		cout << "[" << i << "] ";
		cout << A.data[i] << "\t";
		cout << B.data[i] << "\t";
		cout << C.data[i] << "\n";
	}
	cout << "    A\t" << " B\t" << "C\n";
	cout << "-------------------\n";
}

int getTopIndex(char name) {
	if (name == 'A') {
		return A.top_idx;
	} else if (name == 'B') {
		return B.top_idx;
	} else {
		return C.top_idx;
	}
}

int getTopElement(char name) {
	if (name == 'A') {
		return A.data[A.top_idx];
	} else if (name == 'B') {
		return B.data[B.top_idx];
	} else {
		return C.data[C.top_idx];
	}
	return -1;
}

void addTopIndex(char name) {
	if (name == 'A') {
		A.top_idx++;
	}
	else if (name == 'B') {
		B.top_idx++;
	}
	else {
		C.top_idx++;
	}
}

void subTopIndex(char name) {
	if (name == 'A') {
		A.top_idx--;
	}
	else if (name == 'B') {
		B.top_idx--;
	}
	else {
		C.top_idx--;
	}
}

void updateTower(char s, char d) {
	int temp;
	// A -> B
	if (s == 'A' && d == 'B') {
		temp = A.data[A.top_idx];
		A.data[A.top_idx] = B.data[B.top_idx + 1];
		B.data[B.top_idx + 1] = temp;
	}
	// A -> C
	else if (s == 'A' && d == 'C') {
		temp = A.data[A.top_idx];
		A.data[A.top_idx] = C.data[C.top_idx + 1];
		C.data[C.top_idx + 1] = temp;
	}
	// B -> C
	else if (s == 'B' && d == 'C') {
		temp = B.data[B.top_idx];
		B.data[B.top_idx] = C.data[C.top_idx + 1];
		C.data[C.top_idx + 1] = temp;
	}
	// B -> A
	else if (s == 'B' && d == 'A') {
		temp = B.data[B.top_idx];
		B.data[B.top_idx] = A.data[A.top_idx + 1];
		A.data[A.top_idx + 1] = temp;
	}
	// C -> A
	else if (s == 'C' && d == 'A') {
		temp = C.data[C.top_idx];
		C.data[C.top_idx] = A.data[A.top_idx + 1];
		A.data[A.top_idx + 1] = temp;
	}
	// C -> B
	else if (s == 'C' && d == 'B') {
		temp = C.data[C.top_idx];
		C.data[C.top_idx] = B.data[B.top_idx + 1];
		B.data[B.top_idx + 1] = temp;
	}
	
	// top index fix
	subTopIndex(s);
	addTopIndex(d);
}

int main()
{
	int control;
	bool flag = false;
	char src;
	char des;
	cout << "Welcome to Hanoi Tower!\ninput 1: start\ninput 2: exit\n\n>> ";
	cin >> control;

	while (1) {
		if (control == 1 && flag == false) {
			init();
			show();
			flag = true;
			cout << " init OK!\n";
		}
		else if (control == 2) {
			cout << "Exit!\n";
			system("pause");
			break;
		}

		cout << "input source Tower name >> ";
		cin >> src;
		cout << "input destination Tower name >> ";
		cin >> des;

		if (src == des) {
			"출발지와 목적지가 같습니다!\n";
			continue;
		}

		int src_top_elem;
		int des_top_elem;

		// get source top element
		if (src == 'A') {
			src_top_elem = getTopElement('A');
		}
		else if (src == 'B') {
			src_top_elem = getTopElement('B');
		}
		else {
			src_top_elem = getTopElement('C');
		}

		// 옮기려고 하는 기둥에 원소(원판)이 없는 경우
		if (src_top_elem == 999) {
			cout << "기둥에 원판이 없습니다..\n";
			continue;
		}

		// get destination top element
		if (des == 'A') {
			des_top_elem = getTopElement('A');
		} else if (des == 'B') {
			des_top_elem = getTopElement('B');
		} else {
			des_top_elem = getTopElement('C');
		}

		if (src_top_elem < des_top_elem) {
			// update tower
			// swap src <-> des
			updateTower(src, des);
			
			// 총 시도 횟수 증가
			totalCount++;
		}
		else {
			cout << "목적지의 원판의 값이 더 작습니다!\n";
			continue;
		}

		// print hanoi tower
		show();

		// check finish
		if (finish()) {
			cout << "\n---------- FINISH ----------\n";
			cout << "total try : " << totalCount << "\n";
			system("pause");
			break;
		} else {
			continue;
		}
	}
	
}

