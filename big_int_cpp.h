#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <iomanip>

using namespace std;

class BigInt {
    bool sign;
    vector <int> a;
    int base; 
    long long int pow10;

    void readString (const string &str){
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
        if(a.empty()){
            sign = 1;
            a.push_back(0);
        }
    }

    public:
    BigInt (){
        base = 9;
        pow10 = 1000000000;
        sign = 1;
    }
    BigInt (const string s){
        base = 9;
        pow10 = 1000000000;
        sign = 1;
        readString(s);
    }
    BigInt (const long long int num){
        base = 9;
        pow10 = 1000000000;
        sign = num >= 0;
        string s = to_string(num);
        readString(s);
    }

    void printVector () const{
        //temporary function
        for(int i: a){
            cout << i << " ";
        }
        cout << endl;
    }

    void print () const{
        if(!sign){
            cout << "-";
        }
        int i = a.size()-1;
        //Dealing with this part seperately as the first part of number does not require leading zeros
        cout << a[i--]; 
        for( ; i>=0 ; i--){
            cout << setw(base) << setfill('0') << a[i];
        }
    }
    void update(string s){
        readString (s);
    }

    bool operator== (const BigInt &b1) const{
        return this->sign == b1.sign and this->a == b1.a;
    }
    BigInt operator- () const{
        BigInt ans = *this;
        ans.sign = !ans.sign;
        return ans;
    }
    BigInt operator+ () const{
        return *this;
    }
    BigInt operator+ (const BigInt &b1) const{
        if(b1.sign != this->sign){
            return *this - (-b1);
        }
        BigInt ans;
        ans.sign = this->sign;
        long long int carry = 0;
        for(int i=0; i<min(this->a.size(), b1.a.size()); i++){
            long long int temp = b1.a[i] + this->a[i] + carry;
            ans.a.push_back(temp % pow10);
            carry = temp / pow10;
        }
        //this is longer
        for(int i=min(this->a.size(), b1.a.size()); i<this->a.size(); i++){
            long long int temp = this->a[i] + carry;
            ans.a.push_back(temp % pow10);
            carry = temp / pow10;
        }
        //b1 is longer
        for(int i=min(this->a.size(), b1.a.size()); i<b1.a.size(); i++){
            long long int temp = b1.a[i] + carry;
            ans.a.push_back(temp % pow10);
            carry = temp / pow10;
        }
        while(carry != 0){
            ans.a.push_back(carry % pow10);
            carry = carry / pow10;
        }
        return ans;
    }
    BigInt operator- (const BigInt &b1) const{
        //Check sign
        if(b1.sign != this->sign){
            return *this + (-b1);
        }
        if(*this == b1){
            return (BigInt)"0";
        }
        BigInt ans;
        if(this->abs() > b1.abs()){
            ans = *this;
            for(int i=0; i<ans.a.size(); i++){
                if(i==b1.a.size()){
                    break;
                }
                ans.a[i] -= b1.a[i];
                if(ans.a[i] < 0 and i!=ans.a.size()-1){
                    ans.a[i] += pow10;
                    ans.a[i+1] -= 1;
                }
            }
        }
        else{
            ans = -b1;
            for(int i=0; i<ans.a.size(); i++){
                if(i==this->a.size()){
                    break;
                }
                ans.a[i] -= this->a[i];
                if(ans.a[i] < 0 and i!=ans.a.size()-1){
                    ans.a[i] += pow10;
                    ans.a[i+1] -= 1;
                }
            }
        }
        ans.removeZero();
        return ans;
    }
    BigInt abs() const{
        BigInt b1 = *this;
        b1.sign = 1;
        return b1;
    }
    bool operator< (const BigInt &b1) const{
        //Evaluating this < b1
        if(this->sign != b1.sign){
            return this->sign < b1.sign;
        }
        if(this->a.size() != b1.a.size()){
            return this->a.size() < b1.a.size();
        }
        for(int i=(this->a.size())-1; i>=0; i--){
            if(this->a[i]!=b1.a[i]){
                return this->a[i] < b1.a[i];
            }
        }
        //Both of the numbers are equal
        return false;
    } 
    bool operator<= (const BigInt &b1) const{
        //Evaluating this < b1
        if(this->sign != b1.sign){
            return this->sign < b1.sign;
        }
        if(this->a.size() != b1.a.size()){
            return this->a.size() < b1.a.size();
        }
        for(int i=(this->a.size())-1; i>=0; i--){
            if(this->a[i]!=b1.a[i]){
                return this->a[i] < b1.a[i];
            }
        }
        //Both of the numbers are equal
        return true;
    }
    bool operator> (const BigInt &b1) const{
        //Evaluating this < b1
        if(this->sign != b1.sign){
            return this->sign > b1.sign;
        }
        if(this->a.size() != b1.a.size()){
            return this->a.size() > b1.a.size();
        }
        for(int i=(this->a.size())-1; i>=0; i--){
            if(this->a[i]!=b1.a[i]){
                return this->a[i] > b1.a[i];
            }
        }
        //Both of the numbers are equal
        return false;
    }
    bool operator>= (const BigInt &b1) const{
        //Evaluating this < b1
        if(this->sign != b1.sign){
            return this->sign > b1.sign;
        }
        if(this->a.size() != b1.a.size()){
            return this->a.size() > b1.a.size();
        }
        for(int i=(this->a.size())-1; i>=0; i--){
            if(this->a[i]!=b1.a[i]){
                return this->a[i] > b1.a[i];
            }
        }
        //Both of the numbers are equal
        return true;
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