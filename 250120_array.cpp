#include <iostream>
using namespace std;

void insert(int arr[], int& size, int capacity, int index, int value)
{
	// 배열이 꽉 찼다면 추가 불가하다는 메시지 띄우고 return
	
	// TODO : index 위치에 원소 추가, 뒤로 밀기
}

void erase(int arr[], int& size, int index)
{
	// 삭제 위치가 유효하지 않으면 메시지 return
	
	// TODO : index 위치에 있는 원소 제거, 앞으로 당기기
}

void push_back(int arr[], int& size, int capacity, int value)
{
	// 배열 꽉 찼다면 return

	// TODO : 맨 뒤에 원소 추가
}

void pop_back(int arr[], int& size)
{
	// 비어 있다면 return

	// TODO : 맨 뒤에 있는 원소 제거
}

int main() {
	int arr[10] = { 1, 2, 3, 4, 5 };
	int size = 5;		// 현재 배열 채운 갯수
	int capacity = 10;	// 배열의 최대 크기

	cout << "Original Array : ";
	for (int i = 0; i < size; ++i) 
		cout << arr[i] << " ";
	cout << endl;
	

	return 0;
}