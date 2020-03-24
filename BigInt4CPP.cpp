#include<iostream>
#include<vector>
#include<string>

using namespace std;

class BigInt {
	
private:
	vector<int> number;

public:
	static BigInt returnNum;
	friend BigInt& operator + (BigInt& num, BigInt& num1);
	friend istream& operator >>(istream& in, BigInt& x);
	friend ostream& operator <<(ostream& out, BigInt& x);
	void PrintInt() {
		//cout << "Entered number : ";
		for (auto it : number) {
			cout << it;
		}
		cout << endl;
		
	}
	

	void operator = (BigInt num1) {

		number = num1.number;
		
	}

	void operator = (string s) {
		
		
		for (int i = 0; i < s.size(); i++) {
			number.push_back(static_cast<int>(s[i]-'0'));
		}
		
	}

};

BigInt BigInt::returnNum;

BigInt& operator + (BigInt& num, BigInt& num1) {

	BigInt::returnNum.number.clear();
	vector<int> big, small, reversing;
	int size;
	if (num.number.size() > num1.number.size()) {

		big = num.number;
		small = num1.number;
	}
	else {

		big = num1.number;
		small = num.number;
	}

	size = small.size();
	int sizediff = big.size() - small.size();
	int carry = 0;
	for (int i = size - 1; i >= 0; i--) {
		BigInt::returnNum.number.push_back((big[i + sizediff] + small[i] + carry) % 10);
		carry = (big[i + sizediff] + small[i] + carry) / 10;
		//cout << carry << endl;
	}
	for (int i = sizediff - 1; i >= 0; i--) {
		BigInt::returnNum.number.push_back((big[i] + carry) % 10);
		carry = (big[i] + carry) / 10;
	}
	if (carry > 0) BigInt::returnNum.number.push_back(carry);
	reversing = BigInt::returnNum.number;
	size = reversing.size();
	for (int i = 0; i < size; i++) {
		BigInt::returnNum.number[size - 1 - i] = reversing[i];
	}
	return BigInt::returnNum;

}

istream& operator >> (istream& in, BigInt& x) {
	string s;
	in >> s;
	for (int i = 0; i < s.size(); i++) {
		x.number.push_back(static_cast<int>(s[i] - '0'));
	}
	return in;
}

ostream& operator << (ostream& out, BigInt& x) {
	for (auto it : x.number) {
		out << it;
	}
	return out;
}


int main() {

	BigInt x,y,sum;
	x = "10000000000000000000000000";
	y = x;
	cout << y << "	" << x << endl;
	cin >> sum;
	cout << sum + x << endl;
	y = sum + y;
	cout << y <<"   " <<x<< endl;
	cout << y + x;
	


}
