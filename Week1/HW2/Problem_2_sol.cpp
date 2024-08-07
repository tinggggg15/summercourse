#include <iostream>
#include <vector>
#include <math.h>

using namespace std;

string Find_LongestPalindromic( string s ) {
    int length = s.length() ;
    if( length == 0 ) return "" ;

    string return_str = "" ;
    int maxlen = 0 ;
    for ( int i = 0 ; i < length ; i++ ) {
        
        // odd i middle
        int j = 0 ;

        while ( i-j>=0 && i+j < length && s[i-j] == s[i+j] ){
            j++ ;
        }
        j-- ;
        int s_sublen = s.substr( i-j, i+j ).length() ;
        if( maxlen < s_sublen ) return_str = s.substr( i-j, i+j ), maxlen = s_sublen ;

        // even
        j = 0 ;
        while( i-j >= 0 && i+j+1 < length && s[i-j] == s[i+j+1] ) {
            j++ ;
        }
        j-- ;
        s_sublen = s.substr( i-j, i+j+1 ).length() ;
        if( maxlen < s_sublen ) return_str = s.substr( i-j, i+j+1 ), maxlen = s_sublen ;

    }
    return return_str ;

}

int main() {
    string s ;
    cout << "Please input string s (0 to quit)= " ;
    cin >> s ;
    while( s != "0" ) {
        string p = Find_LongestPalindromic(s) ;
        if( p.length() == 0 ) cout << "No Palindromic" << endl ;
        else cout << "Longest Palindromic : " << p << endl ;
        cout << "---------------------------------------------" << endl ;      
        cout << "Please input string s (0 to quit)= " ;
        cin >> s ;
    }
}