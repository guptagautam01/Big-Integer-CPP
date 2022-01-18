#include <iostream>
#include <vector>
#include <string>
#include <cmath>

using namespace std;

class BigInt {
    bool sign;
    vector <int> a;
    int base; 
    long long int pow10;

    void readString (string &str){
        //remove any previous value
        a.clear();
        if(str.empty()) return;

        sign = 1;
        int start=0;
        if(str[start]=='+' or str[start]=='-'){
            if(str[start]=='-') sign = !sign;
            start++;
        }

        int counter = 0;
        int curr = 0;
        for(int i=str.length()-1; i >= start; i--){
            curr += pow(10, counter) * (str[i]-'0');
            counter++;
            if(counter==base or i==start){
                a.push_back(curr);
                curr = 0;
                counter = 0;
            }
        }
        removeZero();
    }

    void removeZero (){
        while(!a.empty() and a.back()==0){
            a.pop_back();
        }
        if(a.empty())   sign = 1;
    }

    public:
    BigInt (){
        base = 9;
        pow10 = 1000000000;
        sign = 1;
    }
    BigInt (string s){
        base = 9;
        pow10 = 1000000000;
        sign = 1;
        readString(s);
    }
    BigInt (long long int num){
        base = 9;
        pow10 = 1000000000;
        sign = num >= 0;
        string s = to_string(num);
        readString(s);
    }

    void printVector (){
        //temporary function
        for(int i: a){
            cout << i << " ";
        }
        cout << endl;
    }

    void print (){
        if(!sign){
            cout << "-";
        }
        
        for(int i = a.size()-1; i>=0 ; i--){
            cout << a[i];
        }
    }
    void update(string s){
        readString (s);
    }
};

istream& operator >> (istream &is, BigInt &num){
    string s;
    cin >> s;
    num.update(s);
    return is;
}

ostream& operator << (ostream &os, BigInt &num){
    num.print();
    return os;
}