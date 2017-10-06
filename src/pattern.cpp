#include <vector>
#include <iostream>
#include "pattern.h" 


using namespace std ;

/*
	以 localtion 為基準，定位 distance 距離的資料，若是該資料匹配 key ，則回傳 true 
*/
bool find_key_at_distance ( int location, int distance, int key, vector<int> * data ) 
{
	int key_location ;
	vector<int>::iterator it;

	key_location = location - distance ;

	// 假如定位的資料超出範圍 直接放棄
	if ( key_location <= 0 ) return false ; 

	it = find ( data[key_location].begin() + 1 , data[key_location].end(), key );
	if ( it != data[key_location].end() )
	{
		//for ( int i = 0 ; i <  data[key_location].size() ; i++ )
		//	cout << data[key_location][i] << "\t" ;
		//cout << endl;
		//cout << "\tGot the key at " << location << " " << key_location << " " << *it << '\n';
		return true ;
	} else
  	{
  		return false ;
    	//std::cout << "Element not found in myvector\n";
  	}

}