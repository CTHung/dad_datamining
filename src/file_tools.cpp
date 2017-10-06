// 檔案工具
#include <vector>
#include <iostream>
#include <sstream>
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

int import_data ( int size, string filename, vector<int> * data )
{
	int i;
	int index, n1, n2, n3, n4, n5, n6, n7;
	ifstream dataFile ;  // 宣告一個資料串流讀入
	stringstream ss;
 	string line;
	
	dataFile.open ( filename, ios::in ) ; // 將檔案以唯讀形式 讀入串流

	if ( dataFile.is_open() ) 
	{
		i = 0 ;
		while ( getline( dataFile, line ) )
		{
			ss.str( line ) ; // 將一行資料讀入串流
 			ss >> index >> n1 >> n2 >> n3 >> n4 >> n5 >> n6 >> n7 ; // 串流分析並且讀入資料

 			//資料存入記憶資料庫
 			data[i].push_back ( index ) ;
 			data[i].push_back ( n1 ) ;
 			data[i].push_back ( n2 ) ;
 			data[i].push_back ( n3 ) ;
 			data[i].push_back ( n4 ) ;
 			data[i].push_back ( n5 ) ;
 			data[i].push_back ( n6 ) ;
 			data[i].push_back ( n7 ) ;

 			i++ ;
		}
	} else
	{
		cout << "Error while reading file." << endl;
		return  -1 ;
	}
	dataFile.close(); // 關閉檔案串流

	return 0;
} 