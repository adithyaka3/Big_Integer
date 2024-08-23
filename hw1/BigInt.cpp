// CopyRight: Adithya K Anil
// credits: google, chatGPT
#include "BigInt.hpp"
#include <algorithm>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;

// Create a BigInt from a string
BigInt *createBigIntFromString(string num) {
    BigInt *bigInt = new BigInt();
    bigInt->is_negative = (num[0] == '-');
    unsigned long long i;
    if (bigInt->is_negative) {
        i = 1;
    } else {
        i = 0;
    }
    bigInt->digits = num.substr(i);

    return bigInt;
}

BigInt *addBigInts(const BigInt *a, const BigInt *b) {

    BigInt *result = new BigInt();
    unsigned long long p1 = a->digits.size();
    unsigned long long p2 = b->digits.size();
    unsigned long long result_p = max(p1, p2);
    int dig_result = 0, carry = 0;
    result->digits.resize(result_p);

    result_p--;
    p1--;
    p2--;

    while (p1 >= 0 && p2 >= 0) {
        dig_result = carry + (a->digits)[p1] + (b->digits)[p2] - '0' - '0';
        carry = dig_result / 10;
        dig_result = dig_result % 10;
        result->digits[result_p] = (dig_result) + '0';
        if (p1 == 0 || p2 == 0) {
            result_p--;
            break;
        }
        p1--;
        p2--;
        result_p--;
    }

    if (p1 > 0 && p2 == 0) {
        p1--;
        while (p1 >= 0) {
            dig_result = carry + a->digits[p1] - '0';
            carry = dig_result / 10;
            dig_result = dig_result % 10;

            result->digits[result_p] = (dig_result) + '0';
            if (p1 == 0) {
                result_p--;
                break;
            }
            p1--;
            result_p--;
        }
    } else if (p1 == 0 && p2 > 0) {
        p2--;
        while (p2 >= 0) {
            dig_result = carry + (int)((b->digits)[p2]) - '0';
            carry = dig_result / 10;
            dig_result = dig_result % 10;

            result->digits[result_p] = (dig_result) + '0';
            if (p2 == 0) {
                result_p--;
                break;
            }
            p2--;
            result_p--;
        }
    }
    if (carry != 0) {

        result->digits = to_string(carry) + result->digits;
    }
    return result; // Placeholder
}
int compare(const BigInt *a, const BigInt *b) {
    // if result : 1 -> a>b
    // if result : 0 -> a=b
    // if result : -1 -> a<b
    if (a->digits.size() > b->digits.size())
        return 1;
    else if (a->digits.size() < b->digits.size())
        return -1;
    else {
        if (a->digits == b->digits)
            return 0;
        else if (a->digits > b->digits)
            return 1;
        else {
            return -1;
        }
    }
}

BigInt *subtractBigInts(const BigInt *a, const BigInt *b) {

    BigInt *result = new BigInt();
    unsigned long long p1 = a->digits.size();
    unsigned long long p2 = b->digits.size();
    unsigned long long result_p = (max(p1, p2));
    int dig_result = 0, borrow = 0;
    int dig1, dig2;
    result->digits.resize(result_p);
    result_p--;
    p1--;
    p2--;
    while (p1 >= 0 && p2 >= 0) {
        dig1 = a->digits[p1] - '0';
        dig2 = b->digits[p2] - '0';
        if (dig1 - borrow >= dig2) {
            dig_result = dig1 - dig2 - borrow;
            result->digits[result_p] = dig_result + '0';
            borrow = 0;
        } else {
            dig1 = dig1 + 10 - borrow;
            dig_result = dig1 - dig2;
            result->digits[result_p] = dig_result + '0';
            borrow = 1;
        }
        if (p1 == 0 || p2 == 0) {
            result_p--;
            break;
        }
        p1--;
        p2--;
        result_p--;
    }
    if (p1 > 0 && p2 == 0) {
        p1--;
        while (p1 >= 0) {
            dig1 = a->digits[p1] - '0';
            if (dig1 - borrow >= 0) {
                dig_result = dig1 - borrow;
                result->digits[result_p] = dig_result + '0';
                borrow = 0;
            } else {
                dig1 = dig1 + 10 - borrow;
                dig_result = dig1;
                result->digits[result_p] = dig_result + '0';
                borrow = 1;
            }
            if (p1 == 0) {
                break;
            }
            p1--;
            result_p--;
        }
    }
    unsigned long long i = 0;
    for (; i < result->digits.size(); i++) {
        if (result->digits[i] != '0') {
            break;
        }
    }
    if (i == result->digits.size()) {
        result->digits = "0";
    } else {
        result->digits = result->digits.substr(i);
    }
    return result;
}

unsigned long long getResultOfTwoSum(BigInt *target, vector<BigInt *> &arr) {
    unsigned long long result = 0;
    unordered_map<string, unsigned long long> table;
    int comparisonResult;
    string key;
    for (unsigned long long i = 0; i < arr.size(); i++) {
        BigInt *temp = new BigInt;
        comparisonResult = compare(arr[i], target);
        if (arr[i]->is_negative == false) {
            key = arr[i]->digits;
        } else {
            key = "-" + arr[i]->digits;
        }

        if (table[key] != 0) {
            result += table[key];
        }
        if (arr[i]->is_negative == false && target->is_negative == false) {

            if (comparisonResult == 1) {
                temp = subtractBigInts(arr[i], target);
                table[temp->digits]++;
            } else if (comparisonResult == 0) {
                table["0"]++;
            } else {
                temp = subtractBigInts(target, arr[i]);
                temp->digits = "-" + temp->digits;
                table[temp->digits]++;
            }
        } else if (arr[i]->is_negative == false && target->is_negative == true) {
            temp = addBigInts(arr[i], target);
            table[temp->digits]++;
        } else if (arr[i]->is_negative == true && target->is_negative == false) {
            temp = addBigInts(arr[i], target);
            temp->digits = "-" + temp->digits;
            table[temp->digits]++;
        } else if (arr[i]->is_negative == true && target->is_negative == true) {
            if (comparisonResult == 1) {
                temp = subtractBigInts(arr[i], target);
                temp->digits = "-" + temp->digits;
                table[temp->digits]++;
            } else if (comparisonResult == 0) {
                table["0"]++;
            } else {
                temp = subtractBigInts(target, arr[i]);
                table[temp->digits]++;
            }
        }
        if (temp != nullptr)
            delete (temp);
        delete (arr[i]);
    }
    return result;
}

extern "C" unsigned long long readFiles(const char *filepath) {
    string path(filepath); // Convert the C-style string to string
    ifstream file(path);
    unsigned long n;
    if (!file.is_open()) {
        cerr << "Error: Could not open the file." << endl;
        return 1;
    }
    string line;

    file >> line;
    string target_s = line;
    BigInt *target = createBigIntFromString(target_s);
    // if (target_s[target_s.size() - 1] == '\r')
    //     target_s.pop_back();

    file >> line;
    n = stoull(line);

    vector<BigInt *> arrayOfBigNumbers(n);

    unsigned long long i = 0;
    while (i < n) {
        file >> line;
        arrayOfBigNumbers[i] = createBigIntFromString(line);
        i++;
    }
    file.close();
    return getResultOfTwoSum(target, arrayOfBigNumbers);
}
int main() {
    // the main function is only to check if the code is working fine and to debug if anything goes wrong easily.
    cout << readFiles("test_case.txt") << '\n';
}
