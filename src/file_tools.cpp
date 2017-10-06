// 檔案工具

#include <iostream>
#include "fstream"

using namespace std;

int lines_of_file ( string filename ) 
{
	int number_of_lines ;
	ifstream dataFile ;  // 宣告一個資料串流讀入
 	string line;
	
	dataFile.open ( filename, ios::in ) ; // 將檔案以唯讀形式 讀入串流

	number_of_lines = 0 ;
	if ( dataFile.is_open() ) 
	{
		while ( getline( dataFile, line ) )
 			number_of_lines++ ;
	} else
	{
		cout << "Error while reading file." << endl;
		number_of_lines = -1 ;
	}
	dataFile.close(); // 關閉檔案串流

	return number_of_lines ;
}

