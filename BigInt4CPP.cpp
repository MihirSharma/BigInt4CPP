#include<iostream>
#include<vector>
#include<string>

using namespace std;

class BigInt {
	
private:
	vector<int> number;
	bool negative = false;

public:
	static BigInt returnNum;
	friend istream& operator >>(istream& in, BigInt& x);
	friend ostream& operator <<(ostream& out, BigInt& x);
	friend BigInt& operator + (BigInt& num, BigInt& num1);	
	friend BigInt& operator - (BigInt& num, BigInt& num1);
	friend BigInt& operator * (BigInt& num, BigInt& num1);
	//pending

	void operator = (BigInt num1) {

		number = num1.number;
		negative = num1.negative;
		
	}

	void operator = (string s) {
		
		if (s[0] == '-') {
			for (int i = 1; i < s.size(); i++) {
				number.push_back(static_cast<int>(s[i] - '0'));
				negative = true;
			}
		}
		else {
			for (int i = 0; i < s.size(); i++) {
				number.push_back(static_cast<int>(s[i] - '0'));
			}
		}

		
	}

};

BigInt BigInt::returnNum;

istream& operator >> (istream& in, BigInt& x) {
	string s;
	in >> s;
	for (int i = 0; i < s.size(); i++) {
		if (i == 0 && s[i] == '-') {
			x.negative = true;
			i++;
		}
		x.number.push_back(static_cast<int>(s[i] - '0'));
	}
	return in;
}

ostream& operator << (ostream& out, BigInt& x) {
	if (x.negative == true) {
		out << '-';
	}
	for (auto it : x.number) {
		out << it;
	}
	return out;
}

BigInt& operator + (BigInt& num, BigInt& num1) {

	BigInt::returnNum.number.clear();
	vector<int> big, small, reversing;
	int size;

	if(num.negative) {
		BigInt::returnNum = num1 - num;
		//BigInt::returnNum.negative = true;
		return BigInt::returnNum;
	}

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

BigInt& operator - (BigInt& num, BigInt& num1) {

	BigInt::returnNum.number.clear();
	vector<int> big, small, reversing;
	bool negResult = false;
	int size;
	if (num.negative) {
		BigInt::returnNum = num + num1;
		BigInt::returnNum.negative = true;
		return BigInt::returnNum;
	}

	//*********************************************************************************************************************************
	//Check which number is bigger and assign to big and small and set the sign
	//*********************************************************************************************************************************
	if (num.number.size() > num1.number.size()) {
		big = num.number;
		small = num1.number;
	}
	else if(num.number.size() < num1.number.size()) {
		big = num1.number;
		small = num.number;
		BigInt::returnNum.negative = true;
	}
	else if (num.number.size() == num1.number.size()) {
		//*********************************************************************************************************************************
		//if sizes are euqual then scan the numbers to find the first one with a bigger digit. Assign to big and small and assign sign
		//*********************************************************************************************************************************
		for (int i = 0; i < num.number.size(); i++) {
			if (num.number[i] > num1.number[i]) {
				big = num.number;
				small = num1.number;
				break;
			}
			else if (num.number[i] < num1.number[i]) {
				big = num1.number;
				small = num.number;
				negResult = true;
				break;
			}
			else {
				BigInt::returnNum.number.push_back(0);
				BigInt::returnNum.negative = false;
				return BigInt::returnNum;
			}
		}
	}

	size = small.size();
	int sizediff = big.size() - small.size();
	int carry = 0;
	for (int i = size - 1; i >= 0; i--) {
		if (big[i + sizediff] < small[i]) {
			BigInt::returnNum.number.push_back(10+(big[i + sizediff] - small[i] - carry));
			carry = 1;
		}
		else if (big[i + sizediff] > small[i]) {
			BigInt::returnNum.number.push_back((big[i + sizediff] - small[i] - carry));
			carry = 0;
		}
		else if (big[i + sizediff] == small[i]) {
			if (carry == 0) {
				BigInt::returnNum.number.push_back(0);
				carry = 0;
			}
			else if (carry == 1) {
				BigInt::returnNum.number.push_back(10 + (big[i + sizediff] - small[i] - carry));
				carry = 1;
			}
		}
		//BigInt::returnNum.number.push_back((big[i + sizediff] - small[i] - carry));
		//carry = (big[i + sizediff] + small[i] + carry) / 10;
		//cout << carry << endl;
	}
	for (int i = sizediff - 1; i >= 0; i--) {
		if ((big[i] - carry) != 0 && i == 0) {
			BigInt::returnNum.number.push_back((big[i] - carry));
			carry = 0;
		}
		else if (i != 0) {
			BigInt::returnNum.number.push_back(10+(big[i] - carry));
			carry = 1;
		}
	}
	//if (carry > 0) BigInt::returnNum.number.push_back(carry);
	reversing = BigInt::returnNum.number;
	size = reversing.size();
	for (int i = 0; i < size; i++) {
		BigInt::returnNum.number[size - 1 - i] = reversing[i];
	} 
	return BigInt::returnNum;

}

BigInt& operator * (BigInt& num, BigInt& num1) {
	BigInt::returnNum.number.clear();
	vector<int>  reversing;
	BigInt multiplicand, multiplier, interSum, netSum;;
	bool negResult;

	if (num.negative ^ num1.negative) {
		BigInt::returnNum.negative = true;
	}
	else if (!(num.negative ^ num1.negative)) {
		BigInt::returnNum.negative = false;
	}

	if (num.number.size() > num1.number.size()) {
		multiplicand.number = num.number;
		multiplier.number = num1.number;
	}
	else {
		multiplicand.number = num1.number;
		multiplier.number = num.number;
	}
	netSum.number.push_back(0);
	int carry = 0;
	int ctr = 0;
	for (int i = multiplier.number.size()-1; i >=0 ; i--) {
		interSum.number.clear();
		carry = 0;
		for (int j = multiplicand.number.size() - 1; j >= 0; j--) {
			interSum.number.push_back((multiplier.number[i] * multiplicand.number[j] + carry) % 10);
			carry = (multiplier.number[i] * multiplicand.number[j] + carry) / 10;
		}
		interSum.number.push_back(carry);
		reversing.clear();
		for (int x = interSum.number.size() - 1; x >=0 ; x--) {
			reversing.push_back(interSum.number[x]);
		}
		for (int k = 0; k < ctr; k++) {
			reversing.push_back(0);
		}
		ctr++;
		interSum.number = reversing;
		netSum = interSum + netSum;
	}
	netSum.number = BigInt::returnNum.number;
	return BigInt::returnNum;
}

//pending



int main() {

	BigInt x,y,sum,a,b;
	x = "-256";
	y = "-64";
	x = x*y;
	cout << x;
	
	
	


}
