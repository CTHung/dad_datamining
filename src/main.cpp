#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <set>
#include <vector>
#include "file_tools.h"
#include "pattern.h"

using namespace std;

int main ( )
{
	int i, j ;
	int key_1, key_2;
	int max_key_distance_1, max_key_distance_2 ;
	int key_distance_1, key_distance_2 ;
	int dataLength ; // 資料長度
	bool flag_1, flag_2 ;
	vector<int> collection ;
	vector<int>::reverse_iterator reverse_vector_it;
	string filename; // 資料檔案名稱
	ifstream lotteryDataFile ;  // 宣告一個資料串流讀入
	vector<int> *rawData ;
	vector<int> collecting_number ;
	int target_index, counting_index, counter;

	ofstream standard, detail;
	string standard_filename, detail_filename;
	stringstream ss;


	filename = "hcy.txt" ; // 定義資料檔檔名
	key_1 = 1 ; // 第一個基準號碼
	key_2 = 2 ; // 第二個基準號碼
	max_key_distance_1 = 1000; // 第一個號碼最大距離
	max_key_distance_2 = 1000; // 第二個號碼最大距離

	ss << "ouput_" << key_1 << '_' << key_2 << ".txt" ; 
	standard_filename = ss.str().c_str() ; // 輸出檔名
	ss.str( "") ;
	ss.clear() ;
	ss << "detail_" << key_1 << '_' << key_2 << ".txt" ; 
	detail_filename = ss.str().c_str() ; // 輸出細節 方便用於驗算 
	standard.open( standard_filename.c_str(), ios::out | ios::trunc ) ;
	detail.open ( detail_filename.c_str(), ios::out | ios::trunc ) ;

	dataLength = lines_of_file ( filename ) ;
	cout << "Data length: " << dataLength << endl;

	// 宣告記憶體並且將檔案的資料讀入記憶體
	rawData = new vector<int> [dataLength] ;
	i = import_data ( dataLength, filename, rawData );
	if ( i < 0 ) cout << "Problem in reading file." << endl;

	key_distance_1 = 1 ; // 第一個號碼起始距離 
	key_distance_2 = 1 ; // 第二個號碼起始距離
	while ( key_distance_1 <= max_key_distance_1 && key_distance_2 <= max_key_distance_2  )
	{
		collection.clear() ;

		// 根據所要求的 key 與 距離 掃過整組資料並且記錄符合的資料
		for ( i = 0 ; i < dataLength ; i++ )
		{
			// 第一個 key 是否符合
			flag_1 = find_key_at_distance ( i, key_distance_1, key_1, rawData ) ;
			// 第二個 key 是否符合
			flag_2 = find_key_at_distance ( i, key_distance_2, key_2, rawData ) ;

			if ( flag_1  &&  flag_2 )
			{
				collection.push_back ( i ) ;
				//cout << i << " match the requirement. key = ( " <<  key_1 << ", " << key_2 << "). Dist = ( " << key_distance_1 << ", " << key_distance_2 << "). " << flag_1 << " " << flag_2 << endl; 
			}
		}

		//cout << "Key ( " << key_1 << ", " << key_2 << "). " << "Dist ( " << key_distance_1 << ", " << key_distance_2 << " )" << endl; 

		// 符合條件的最後一筆 資料編號 target_index
		target_index = collection[ collection.size() - 1 ];
		for ( j = 1; j < 8 ; j++ )
		{
			i = 0 ;
			for ( reverse_vector_it = collection.rbegin() ; reverse_vector_it != collection.rend(); ++reverse_vector_it )
			{
				counter = count( rawData[ *reverse_vector_it ].begin() + 1,  rawData[ *reverse_vector_it ].end(), rawData[target_index][j] ) ;
				if ( counter == 0 ) break;
				i++ ;
			}

			if ( i >= 5 ) 
			{
				standard << i << '\t' << rawData[target_index][j] << '\t' << key_1 << '\t' << key_distance_1 << '\t' << key_2 << '\t' << key_distance_2 << endl;

				// 以下幾行 輸出細節做驗算用 不需要的話可以註解掉 
				detail << "Key ( " << key_1 << ", " << key_2 << "). " << "Dist ( " << key_distance_1 << ", " << key_distance_2 << " )"  << '\t' << rawData[target_index][j] << " shows " << i << " times.\t" ;
				for ( counter = 0 ; counter < collection.size() ; counter++ ) 
					detail << collection[counter] << '\t' ;
				detail << endl;
			}
    		//i = count ( rawData[target_index].begin(), rawData[target_index].end(),  rawData[target_index][j] );
    		//cout << '\t' <<  *set_it << " shows " << i << " times." << endl;
		}

		key_distance_2++;
		if ( key_distance_2 > max_key_distance_2 )
		{
			key_distance_2 = 1;
			key_distance_1 ++ ;
		}
	}

	//key_distance_1 = 5 ;
	//for ( i = 0 ; i < dataLength ; i++ )
	//	find_key_at_distance ( i, key_distance_1, key_1, rawData ) ;

	//cout << endl;
	//for ( i = 0 ; i < dataLength ; i++ )
	//{
	//	for ( j = 0 ; j < rawData[i].size() ; j++ )
	//		cout << rawData[i][j] << '\t' ;
	//	cout << endl;
	//}

	//latteryDataFile.open ( filename, ios::in ) ; // 將檔案以唯讀形式 讀入串流
	
	//latteryDataFile.close(); // 關閉檔案串流
	
	return 0;
}