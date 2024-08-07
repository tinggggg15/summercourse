#include <iostream>
#include <vector>
#include <math.h>

using namespace std;

bool SplitNums( string str, vector<int> &num ) {
    string num_temp ;
    int length = str.length() ;
    if( str[0] != '[' || str[length-1] != ']' ) return false ;
    for( int i = 1 ; i < length-1 ; i++ ) {
        if( isdigit( str[i] ) ) num_temp+= str[i] ;
        else if( str[i] == ',' ) {
            if (!num_temp.empty()) {
                num.push_back(stoi(num_temp));
                num_temp.clear();
            } else {
                return false;
            }
        }
        else if( str[i] == ' ' ) ;
        else return false ;
    }

    if (!num_temp.empty()) num.push_back(stoi(num_temp));

    return true ;
}

void FindPosition( int target, vector<int> &nums ) {
    int arr_length = nums.size() ;
    int first , last ;
    bool find_first = false ;
    bool find_last = false ;
    for( int i = 0 ; i < ceil(arr_length/2.0) ; i++) {
        if( nums[i] == target ) { // first half
            if( find_first == false ) {
                find_first = true ;
                first = i;
            }
            else { 
                if(  i < first ) first = i ;
                if( find_last ) {
                    if( i> last ) last = i ;
                }
                else {
                    find_last = true ;
                    last = i ;
                }

            }
        }
        if( nums[arr_length -1- i] == target) { // second haif
            //cout << arr_length -1- i << endl ;
            if( find_last == false ) {
                find_last = true ;
                last = arr_length -1- i;
            }
            else {
                if(  arr_length -1- i > last ) last = arr_length -1- i ;
                if( find_first ) {
                    if( arr_length -1- i < first ) first = arr_length -1- i ;
                }
                else {
                    find_first = true ;
                    first = arr_length -1- i ;
                }

            }
        }
    }

    if( find_first && find_last) cout << "Output: [" << first << "," << last << "]" << endl ;
    else if( find_first ) cout << "Output: [" << first << "," << first << "]" << endl ;
    else if( find_last ) cout << "Output: [" << last << "," << last << "]" << endl ;
    else cout << "Output: [-1,-1]" << endl ;

}

int main() {
    string str_nums ;
    vector<int> nums = {} ;
    int target ;
    cout << "Please input nums (ex. [2,3,4,5], 0 to quit)= " ;
    cin >> str_nums ;
    while( str_nums != "0" ) {
        if( SplitNums( str_nums, nums ) ) {
            cout << "target= " ;
            cin >> target ;
            FindPosition( target, nums ) ;
            //cout << nums.size() ;
        }
        else {
            cout << "wrong format" << endl ;
        }  
        cout << "---------------------------------------------" << endl ;      
        cout << "Please input nums (ex. [2,3,4,5], 0 to quit)= " ;
        cin >> str_nums ;
        nums.clear() ;
    }
    //cout << str_nums << "  " << target << endl ;

}