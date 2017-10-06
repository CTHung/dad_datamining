#include <iostream>
#include <fstream>
#include <string>
#include "file_tools.h"

using namespace std;

int main ( )
{
	int dataLength ; // 資料長度
	string filename; // 資料檔案名稱
	ifstream latteryDataFile ;  // 宣告一個資料串流讀入
	

	filename = "hcy.txt" ; // 定義資料檔檔名

	dataLength = lines_of_file ( filename ) ;
	cout << "Data length " << dataLength << endl;


	//latteryDataFile.open ( filename, ios::in ) ; // 將檔案以唯讀形式 讀入串流
	
	//latteryDataFile.close(); // 關閉檔案串流
	
	return 0;
}