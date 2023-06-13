#include <iostream>

using namespace std;

struct customer {

    std::string name;
    std::string phone;
    int money;

    bool operator > (const customer& customer2){
        return money > customer2.money;
    }

    
};