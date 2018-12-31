// 編譯(Build) = 齒輪 // 六合彩
// 編譯完成的執行檔在 .\bin\Debug [ run = 執行 基碼變數 ] , [ ST0002.TXT = 歷年開獎紀錄 ]
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
#include <set>
#include <vector>
#include "file_tools.h"
#include "pattern.h"

using namespace std;

int main ( int argc, char* argv[] )
{
	int i, j ;
	int key_1, key_2, key_3 ;
	int max_key_distance_1, max_key_distance_2, max_key_distance_3 ;
	int key_distance_1, key_distance_2, key_distance_3 ;
	int L_base, L01, L12, L13;
	// ##### tt 1 #############################

	int init_key_distance_1, init_key_distance_2, init_key_distance_3 ; //tt

	int dataLength ; // 資料長度
	bool flag_1, flag_2, flag_3 ;
	vector<int> collection ;
	vector<int>::reverse_iterator reverse_vector_it;
	vector<int>::iterator vector_it;
	string filename; // 資料檔案名稱
	ifstream lotteryDataFile ;  // 宣告一個資料串流讀入
	vector<int> *rawData ;
	vector<int> collecting_number ;
	int target_index, counting_index, counter;
	int requirement ;

	ofstream standard, future, detail;
	string standard_filename, future_filename, detail_filename;
	stringstream ss;
    //***********************************************
    filename = "3st0002.txt" ; // 定義資料檔檔名 // ######
	//filename = argv[1] ;     // 定義資料檔檔名

	if ( argc != 4 )
	{
		printf("Usage: %s key1 key2 key3\n", argv[0]);
		return -1;
	}

	// 外部輸入版本 run.bat
	key_1 = atoi( argv[1] ) ; // 第一個基準號碼
	key_2 = atoi( argv[2] ) ; // 第二個基準號碼
	key_3 = atoi( argv[3] ) ; // 第三個基準號碼

	// 直接指定數字
    //key_1 = 3 ; // 第一個基準號碼
	//key_2 = 5 ; // 第二個基準號碼
	//key_3 = 7 ; // 第二個基準號碼

	// ##### tt 3 ##############################################

    // key_distance_1 = 1 ; // 第一個號碼起始距離  //tt
	// key_distance_2 = 1 ; // 第二個號碼起始距離  //tt
	// key_distance_3 = 1 ; // 第三個號碼起始距離  //tt

	key_distance_1 = init_key_distance_1 = 1; // 第一個號碼起始距離  // ######
	key_distance_2 = init_key_distance_2 = 1; // 第二個號碼起始距離  // ######
	key_distance_3 = init_key_distance_3 = 1; // 第三個號碼起始距離  // ######

	max_key_distance_1 = 400; // 第一個號碼最大距離  Max = 1100 // ######
	max_key_distance_2 = 400; // 第二個號碼最大距離  Max = 1100 // ######
	max_key_distance_3 = 400; // 第三個號碼最大距離  Max = 1100 // ######

    requirement = 6 ; // 連續值大於等於 N 輸出檔案 // ######

	ss << "3S1ouput_" << key_1 << '_' << key_2 << '_' << key_3 << ".txt" ; // ######
	standard_filename = ss.str().c_str() ; // 輸出檔名
	ss.str( "") ;
	ss.clear() ;
	ss << "future_" << key_1 << '_' << key_2 << '_' << key_3 << ".txt" ;
	future_filename = ss.str().c_str() ; // 輸出未來的預測統計
	ss.str( "") ;
	ss.clear() ;
	ss << "detail_" << key_1 << '_' << key_2 << '_' << key_3 << ".txt" ;
	detail_filename = ss.str().c_str() ; // 輸出細節 方便用於驗算
	standard.open( standard_filename.c_str(), ios::out | ios::trunc ) ;
	future.open ( future_filename.c_str(), ios::out | ios::trunc ) ;
	detail.open ( detail_filename.c_str(), ios::out | ios::trunc ) ;

	dataLength = lines_of_file ( filename ) ;
	if ( dataLength < 0 )
	{
		printf("Filename %s doesn't exsist.\n", filename.c_str() );
		return -1;
	}
	cout << "Data length: " << dataLength << endl;

	// 宣告記憶體並且將檔案的資料讀入記憶體
	rawData = new vector<int> [dataLength] ;
	i = import_data ( dataLength, filename, rawData );
	if ( i < 0 ) cout << "Problem in reading file." << endl;

	while ( key_distance_1 <= max_key_distance_1 && key_distance_2 <= max_key_distance_2 && key_distance_3 <= max_key_distance_3 )
	{
		collection.clear() ;

		// 根據所要求的 key 與 距離 掃過整組資料並且記錄符合的資料
		// 三個 Key 與 未知數(根) 之間的相對距離先定義好，但是三個 Key 的位置有高有低 要把整個 pattern 對低點做修正 L_base 讓
		// 未知數(根) 與第一個之間的距離 L01
		// 第一個與第二個之間 L12
		// 第二個與第三個之間 L23

		L_base = 0;
		L01 = key_distance_1;
		L12 = key_distance_2 - key_distance_1;
		L13 = key_distance_3 - key_distance_1;
		if( L12 < 0 || L13 < 0 )
		{
			if ( L13 < L12 )
				L_base = L13;
			else
				L_base = L12;
		}

		// collection 紀錄的 index 是 L1 的位置
		for ( i = 0 ; i < dataLength + L_base; i++ )
		{
			// 第一個 key 是否符合
			flag_1 = find_key_at_distance ( i, 0, key_1, rawData ) ;
			// 第二個 key 是否符合
			if ( flag_1 ) flag_2 = find_key_at_distance ( i, L12, key_2, rawData ) ;
            // 第三個 key 是否符合
			if ( flag_1 && flag_2 ) flag_3 = find_key_at_distance ( i, L13, key_3, rawData ) ;

			if ( flag_1  &&  flag_2 &&  flag_3 )
			{
				collection.push_back ( i ) ;
			}
		}

		// 符合條件的最後一筆 資料編號 target_index
		target_index = 0;
		if ( collection.size() > 0 )
		{
			for ( reverse_vector_it = collection.rbegin() ; reverse_vector_it != collection.rend(); ++reverse_vector_it )
			{
				// 從最後一筆資料開始，透過 L01 計算根的位置，假如跟比資料 dataLength 還要大，表示跟的位置是未來，沒有辦法知道數字
				// 找最後一筆有用的根作位target_index
				if ( ! ( *reverse_vector_it + L01 > dataLength  ) )
				{
					target_index = *reverse_vector_it;
					break;
				}
			}
		}
		if ( collection.size() > 5 )
			cout << target_index << " " << key_1 << " " << key_2 << " " << key_3 << endl;
        //***********************************************************************************
        // 統計大樂透 6 + 1 的出現次數 j = 1 ~ 7
        // 或是 6 個正常號的統計數數字 j = 1 ~ 6
		for ( j = 1; j < 7 ; j++ )
		{
            // 連續出現則 i 遞增, 若是中斷則跳出
			i = 0 ;
			for ( reverse_vector_it = collection.rbegin() ; reverse_vector_it != collection.rend(); ++reverse_vector_it )
			{
				if ( *reverse_vector_it < target_index )  // 跳過未來的筆數
				{
					counter = count( rawData[ *reverse_vector_it ].begin() + 1,  rawData[ *reverse_vector_it ].end(), rawData[target_index][j] ) ;
					if ( counter == 0 ) break;
					// 遇到特別號 不計算
					if ( rawData[target_index][j] == rawData[ *reverse_vector_it ][7] ) break;
					i++ ;
				}
			}

            // 連續出現超過 requirement 次 則將結果寫入檔案
			if ( i >= requirement )
			{
				standard  << key_distance_3 << '\t' << key_3 << '\t' << key_distance_2  << '\t' << key_2 << '\t' << key_distance_1 << '\t'  << key_1 << '\t'<< rawData[target_index][j] << '\t' << i  << endl;

				// 印出未來預期的號碼
				for ( vector_it = collection.begin() ; vector_it != collection.end(); vector_it++ )
				{
					if ( *vector_it >= target_index )  // 跳過未來的筆數
					{
						future << key_distance_3 << '\t' << key_3 << '\t' << key_distance_2  << '\t' << key_2 << '\t' << key_distance_1 << '\t'  << key_1 << '\t'<< rawData[target_index][j] << '\t' << *vector_it  << endl;
					}
				}

				// 以下四行 輸出細節做驗算用 不需要的話可以註解掉
				detail << "Key ( " << key_1 << ", " << key_2 << ", " << key_3 << "). " << "Dist ( " << key_distance_1 << ", " << key_distance_2 << ", " << key_distance_3 << " )"  << '\t' << rawData[target_index][j] << " (j="<< j <<") shows " << i << " times.\t" ;
			 	for ( counter = 0 ; counter < collection.size() ; counter++ )
			 	detail << collection[counter] << '\t' ;
			 	detail << endl;
			}
		}


		key_distance_3++;
		if ( key_distance_3 > max_key_distance_3 )
		{
		    // ##### tt 1 ############################

			// key_distance_3 = 1;  //tt

			key_distance_3 = init_key_distance_3; // tt

			key_distance_2 ++ ;
			cout << "\r" << key_distance_2 << "(" << key_distance_1 << ")"  ;
		}

		if ( key_distance_2 > max_key_distance_2 )
		{
		    // ##### tt 1 ##############################

			// key_distance_2 = 1; // tt

			key_distance_2 = init_key_distance_2; // tt

			key_distance_1 ++ ;
			cout << "\r                                "  ;
			cout << "\r" << key_distance_1 ;
		}

	}

	standard.close() ;
	detail.close() ;

	return 0;
}
