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
	int i, j, k;
	int key_1, key_2, key_3 ;
	int max_key_distance_1, max_key_distance_2, max_key_distance_3 ;
	int key_distance_1, key_distance_2, key_distance_3 ;
	int L_base, L12, L13;
	int init_index, end_index;
	int index_2, index_3, width;
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

	ss.str( "") ;
	ss.clear() ;
	ss << "3S1ouput_" << key_1 << '_' << key_2 << '_' << key_3 << ".txt" ; // ######
	standard_filename = ss.str().c_str() ; // 輸出檔名
	//ss.str( "") ;
	//ss.clear() ;
	//ss << "future_" << key_1 << '_' << key_2 << '_' << key_3 << ".txt" ;
	//future_filename = ss.str().c_str() ; // 輸出未來的預測統計
	//ss.str( "") ;
	//ss.clear() ;
	//ss << "detail_" << key_1 << '_' << key_2 << '_' << key_3 << ".txt" ;
	//detail_filename = ss.str().c_str() ; // 輸出細節 方便用於驗算
	standard.open( standard_filename.c_str(), ios::out | ios::trunc ) ;
	//future.open ( future_filename.c_str(), ios::out | ios::trunc ) ;
	//detail.open ( detail_filename.c_str(), ios::out | ios::trunc ) ;

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
	if ( i < 0 ) 
		cout << "Problem in reading file." << endl;

	for ( index_2 = - max_key_distance_2 + 1 ; index_2 < max_key_distance_2 ; index_2++ )
		for ( index_3 = - max_key_distance_3 + 1 ; index_3 < max_key_distance_3 ; index_3++ )
		{
			collection.clear() ;
			// 已知 index_2 index_3 的相對位置，計算 index_1 的範圍
			width = max( 0, max( index_2, index_3 )) - min ( 0, min( index_2, index_3 ) );
			L_base = max(max_key_distance_2, max_key_distance_3) - width;
			if ( L_base <= 0 )
			{
				//cout << "L_base = " << L_base << " index_2 = " << index_2 << " index_3 = " << index_3 << " Ignored. " << endl;
				goto ENDOFLOOP;
			}

			init_index = max( 0, max(index_2, index_3));
			if ( min( index_2, index_3 ) <= 0 )
				end_index = dataLength + min( index_2, index_3 );
			else 
				end_index = dataLength;
			//cout << "L_base = " << L_base << " index_2 = " << index_2 << " index_3 = " << index_3 << " InitIndex = " << init_index << endl;

			for (i = init_index; i < end_index; i++ )
			{
				// 第一個 key 是否符合
				flag_1 = find_key_at_distance ( i, 0, key_1, rawData ) ;
				// 第二個 key 是否符合
				if ( flag_1 ) flag_2 = find_key_at_distance ( i, index_2, key_2, rawData ) ;
				// 第三個 key 是否符合
				if ( flag_1 && flag_2 ) flag_3 = find_key_at_distance ( i, index_3, key_3, rawData ) ;
				
				// 滿足 pattern 的全部放到 collection
				if ( flag_1  &&  flag_2 &&  flag_3 )
				{
					collection.push_back ( i ) ;
					//cout << "push i = " << i << " index_2 = " << index_2 << " index_3 = " << index_3 << endl;
				}
			}

			// 假如 collection 小於 requirement，不可能會找出結果，所以直接放棄
			if ( collection.size() < requirement )
			{
				//cout << "Not engough collection pattern for index_2 = " << index_2 << " and index_3 = " << index_3 << " ; collection size = " << collection.size() << endl;
				goto ENDOFLOOP;
			}

			// Dump the collection data
			//cout << "Dump collection data" << endl;
			//for ( reverse_vector_it = collection.rbegin() ; reverse_vector_it != collection.rend(); ++reverse_vector_it )
			//{
			//	cout << *reverse_vector_it << endl;
			//}
			//cout << "End of dump collection data" << endl;

			// i 走過所有 1 ~ L_base
			for ( i = 1; i <= L_base; i++ )
			{
				// 符合條件的最後一筆 資料編號 target_index
				target_index = 0;
				j = 0;
				for ( reverse_vector_it = collection.rbegin() ; reverse_vector_it != collection.rend(); ++reverse_vector_it )
				{
					// 從最後一筆 collection 資料 + (index_2/index_3 的 shift) + L_base 就是對應的開獎資料，若是開獎資料在 dataLength 之外，就表示那是未來的期數。
					target_index = *reverse_vector_it - ( min(0, min(index_2, index_3) ) ) + i;

					if ( ! (target_index >= dataLength) )
					{
						goto TARGETINDEX;
					}
					j++;
				}

				cout << "Something wrong, goto NEXTLBASE." << endl;
				goto NEXTLBASE;
			
TARGETINDEX:
				// 檢查剩下的 collection 夠不夠滿足 requirement
				if ( collection.size() - j < requirement )
				{
					//cout << "Taget_index in the reverse = " << target_index << " index = " << i << " fail " << endl;
					goto NEXTLBASE;
				} 

				for ( j = 1; j < 7 ; j++ )
				{
					k = 0;
					for ( reverse_vector_it = collection.rbegin() ; reverse_vector_it != collection.rend(); ++reverse_vector_it )
					{
						if ( *reverse_vector_it - ( min(0, min(index_2, index_3) ) ) + L_base < target_index )  // 跳過未來的筆數
						{
							counter = count( rawData[ *reverse_vector_it ].begin() + 1,  rawData[ *reverse_vector_it ].end(), rawData[target_index][j] ) ;
							
							if ( counter == 0 ) 
								goto SERIALCOUNT;
					
							// 遇到特別號 不計算
							if ( rawData[target_index][j] == rawData[ *reverse_vector_it ][7] ) 
								goto SERIALCOUNT;

							k++;
						}
					}

SERIALCOUNT:
					if ( k >= requirement )
					{
						key_distance_1 = - min(0, min(index_2, index_3)) + 1;
						key_distance_2 = key_distance_1 + index_2;
						key_distance_3 = key_distance_1 + index_3;

						standard  << key_distance_3 << '\t' << key_3 << '\t' << key_distance_2  << '\t' << key_2 << '\t' << key_distance_1 << '\t'  << key_1 << '\t'<< rawData[target_index][j] << '\t' << k ;

						for ( vector_it = collection.begin() ; vector_it != collection.end(); vector_it++ )
						{
							if ( *vector_it - ( min(0, min(index_2, index_3) ) ) + L_base >= target_index )  // 跳過未來的筆數
							{
								standard << '\t' << *vector_it - ( min(0, min(index_2, index_3) ) ) + L_base ;
							}
						}
						standard << endl;

						//cout << "KD1 " << key_distance_1 << " KD2 " << key_distance_2 <<  " KD3 " << key_distance_3 << " ---- j = " << j << " " << rawData[target_index][j] << " repeat " << k << " times : target_index " <<  target_index << endl;
					}


				}

NEXTLBASE:
				;
			}


ENDOFLOOP:

			;
		}

	standard.close() ;

	return 0;
}
