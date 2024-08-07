#include <iostream>
#include <vector>
#include <climits>

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

double Find_Median( vector<int> nums1, vector<int> nums2 ) {
    int num1_len = nums1.size() ;
    int num2_len = nums2.size() ;
    int length = num1_len + num2_len ;

    // Ensure nums1 < nums2
    if (num1_len > num2_len) return Find_Median(nums2, nums1); // switch

    //int middle = (length + 1) /2 ;

    if( num1_len == 0 ) { // arr1 empty
        if( num1_len%2 == 1 ) {
            return nums1[num1_len/2] ;
        }
        else return (nums1[num1_len/2]+nums1[num1_len/2-1])/2.0 ;
    }

    if( num2_len == 0 ) { // arr2 empty
        if( num2_len%2 == 1 ) {
            return nums2[num2_len/2] ;
        }
        else return (nums2[num2_len/2]+nums2[num2_len/2-1])/2.0 ;
    }

    int left = 0, right = num1_len;
    int cut1, cut2;
    int l1, r1, l2, r2;
    int halfLength = (length + 1) / 2;

    while (left <= right) {
        cut1 = (left + right) / 2;
        cut2 = halfLength - cut1;

        l1 = (cut1 == 0) ? INT_MIN : nums1[cut1 - 1];
        l2 = (cut2 == 0) ? INT_MIN : nums2[cut2 - 1];
        r1 = (cut1 == num1_len) ? INT_MAX : nums1[cut1];
        r2 = (cut2 == num2_len) ? INT_MAX : nums2[cut2];

        if (l1 <= r2 && l2 <= r1) {
            if (length % 2 == 1) {
                return max(l1, l2);
            } else {
                return (max(l1, l2) + min(r1, r2)) / 2.0;
            }
        } else if (l1 > r2) {
            right = cut1 - 1;
        } else {
            left = cut1 + 1;
        }
    }

    return 0 ;

}

int main() {
    string nums1, nums2 ;
    vector<int> arr_nums1, arr_nums2 ;
    cout << "Please input nums (ex. [1,2], nums1-> 0 to quit)" << endl ;
    cout << "nums1 = " ;
    cin >> nums1 ;
    
    while (nums1 != "0") {
        cout << "nums2 = " ;
        cin >> nums2 ;

        if( SplitNums( nums1, arr_nums1 ) && SplitNums( nums2, arr_nums2 ) ) {
            double sol = Find_Median( arr_nums1, arr_nums2 ) ;
            cout << "Median : " << sol << endl ;
        }
        else cout << "wrong format" << endl ;

        //------
        arr_nums1.clear() ;
        arr_nums2.clear() ;
        cout << "Please input nums (ex. [1,2], nums1-> 0 to quit)" << endl ;
        cout << "nums1 = " ;
        cin >> nums1 ;

    }
    
}