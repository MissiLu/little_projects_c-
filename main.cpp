#include <iostream>
#include <exception>
#include <sstream>
#include <algorithm>
#include <iomanip>
using namespace std;

class Rational {
public:
    Rational() {
        num=0;
        den=1;
    }
    Rational(int numerator, int denominator) {
        if (denominator==0){
            throw invalid_argument("Invalid argument");
        } else {
            num = numerator;
            den = denominator;
        }
    }
    int Numerator() const {
        if (num==0){
            return 0;
        } else {
            int n = abs(num);
            int d = abs(den);
            while (n > 0 && d > 0) {
                if (n > d) {
                    n = n % d;
                } else {
                    d = d % n;
                }
            }
            if((den<0 && num>0)||(den<0 && num<0) ) {
                return -num / (n + d);
            } else {
                return num / (n + d);
            }
        }
    }
    int Denominator() const {
        if (num==0){
            return 1;
        } else {
            int n = abs(num);
            int d = abs(den);
            while (n > 0 && d > 0) {
                if (n > d) {
                    n = n % d;
                } else {
                    d = d % n;
                }
            }
            return abs(den / (n + d));
        }
    }
private:
    int num;
    int den;
};
Rational operator+(const Rational& r1, const Rational& r2){
    return Rational {r1.Numerator() * r2.Denominator() + r1.Denominator() * r2.Numerator(),
                     r1.Denominator() * r2.Denominator()};
}
Rational operator-(const Rational& r1, const Rational& r2){
    return Rational {r1.Numerator() * r2.Denominator() - r1.Denominator() * r2.Numerator(),
                     r1.Denominator() * r2.Denominator()};
}
Rational operator*(const Rational& r1, const Rational& r2){
    return Rational {r1.Numerator() *  r2.Numerator(),
                     r1.Denominator() * r2.Denominator()};
}
Rational operator/(const Rational& r1, const Rational& r2){
    if(r2.Numerator()==0){
        throw domain_error("Division by zero");
    }
    return Rational {r1.Numerator() *  r2.Denominator(),
                     r1.Denominator() * r2.Numerator()};
}
/*


bool operator==(const Rational& r1, const Rational& r2){
    if(r1.Numerator() == r2.Numerator() && r1.Denominator() == r2.Denominator()) {
        return true;
    } else {
        return false;
    }
}
*/
Rational ReadRational(istream& stream){ // функция принимает на вход поток - строка и выводит дробь
    int Numerator,Denominator;

    stream>>Numerator;
    if(stream.peek() != '/'){
        throw invalid_argument("Invalid argument");
    }
    stream.ignore(1);
    stream>>Denominator;
    return Rational{Numerator,Denominator};
}

int main() {
    try {
        string ss_left, ss_right, ss_operator;

        cin >> ss_left >> ss_operator >> ss_right;
        stringstream left_s(ss_left); //записываем в поток полученную строку
        Rational left = ReadRational(left_s); //записываем левый операнд

        stringstream right_s(ss_right);
        Rational right = ReadRational(right_s);//записываем правый операнд

        if (ss_operator == "+") {
            Rational answer = left + right;
            cout << answer.Numerator() << "/" << answer.Denominator() << endl;
        } else if (ss_operator == "-") {
            Rational answer = left - right;
            cout << answer.Numerator() << "/" << answer.Denominator() << endl;
        } else if (ss_operator == "*") {
            Rational answer = left * right;
            cout << answer.Numerator() << "/" << answer.Denominator() << endl;
        } else if (ss_operator == "/") {
            Rational answer = left / right;
            cout << answer.Numerator() << "/" << answer.Denominator() << endl;
        }
    }catch (invalid_argument& ar){
        cout<<ar.what();
    }catch (domain_error& rr) {
        cout<< rr.what();
    }
    return 0;
}