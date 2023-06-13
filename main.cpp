#include <iostream>
#include<vector>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include "customer.hh"

using namespace std;

int left(int i){

    return i * 2 + 1;
}

int right(int i){

    return i * 2 + 2;
}

int parent(int i){
    return (i - 1)/2;
}

void heapify(vector<customer>& customers, int i){
    int l = left(i);
    int r = right(i);

    int largest = i;
    int heapSize = customers.size();
    if(l < heapSize && customers[l] > customers[largest]){
        largest = l;
    }
    if (r < heapSize && customers[r] > customers[largest]){
        largest = r;
    }

    if(largest != i){
        customer previousParent = customers[i];
        customers[i] = customers[largest];
        customers[largest] = previousParent;


        
        heapify(customers, largest);
    }
}


void buildHeap(vector<customer>& customers){
    int heapSize = customers.size();
    for(int i = heapSize/2; i >= 0; i--){
        heapify(customers, i);
    }
}


bool isHeap(vector<customer> val, int i, int n){

    if (i >= (n - 1) / 2)
        return true;
  
    if (val[i].money >= val[2 * i + 1].money && val[i].money >= val[2 * i + 2].money && isHeap(val, 2 * i + 1, n) && isHeap(val, 2 * i + 2, n))

        return true;

    return false;
}

customer extractMax(vector<customer>& customers){
    if(customers.size() < 1){
        throw invalid_argument("Heap underflow");
    }

    customer max = customers[0];
    customers[0] = customers[customers.size() - 1];
    customers.pop_back();
    heapify(customers, 0);
    return max;
}



void insert(vector<customer>& customers, customer person){
    customers.push_back(person);

    int i = customers.size() - 1;
    while(i >= 1 && customers[parent(i)].money < person.money){
        customers[i] = customers[parent(i)];
        i = parent(i);
    }
    customers[i] = person;
}

customer generateRandomCustomer(){

    string names[10] = {"Jack", "John", "Joe", "Matt", "Brian", "Olivia", "Oliver", "Theo", "Henry", "James"};
    string phoneNum[20] = { "46209451",
                            "461147242",
                            "461371049",
                            "461394424",
                            "461614222",
                            "462144214",
                            "462189439",
                            "462361439",
                            "463333521",
                            "463356423",
                            "463524829",
                            "463574393",
                            "463671295",
                            "464012314",
                            "464259538",
                            "466012022",
                            "468012312",
                            "468092022",
                            "468139942",
                            "468217666"
                        };
        customer person;
        person.name = names[rand() % 10];
        person.phone = phoneNum[rand() % 20];
        person.money = rand() % 500;
        return person;
}

void printCustomerQueue(vector<customer> customers){
    for(int i = 0; i < customers.size(); i++){
        cout << " Name: " <<  customers[i].name << ",  Phone: " <<  customers[i].phone << ",  Value: " << customers[i].money << " \n";
    }
}

int main(){
    srand(time(NULL));
    vector<customer> customers;

    for(int i = 0; i < 500000; i++){
        customers.push_back(generateRandomCustomer());
    }
    cout << "\n";


    buildHeap(customers);
    
    if(isHeap(customers, 0, customers.size()) == 1){
        cout << "True" << endl;
    } else {
        cout << "False" << endl;
    }

    printCustomerQueue(customers);

    customer customerHelped = extractMax(customers);
    cout << "\n\nCustomer Helped: \n";
    cout << " Name: " << customerHelped.name << ",  Phone: " <<  customerHelped.phone << ",  Value: " << customerHelped.money << endl;

    cout << "\n\nNew Queue: \n";
    
    printCustomerQueue(customers);

    customer insertCustomer = generateRandomCustomer();
    insert(customers, insertCustomer);
    cout << "\n\n Insert Customer: \n";
    cout << " Name: " << insertCustomer.name << ",  Phone: " <<  insertCustomer.phone << ",  Value: " << insertCustomer.money << endl;
    cout << "\n\nNew Queue: \n";
    printCustomerQueue(customers);

    if(isHeap(customers, 0, customers.size()) == 1){
        cout << "True" << endl;
    } else {
        cout << "False" << endl;
    }
    return 0;
}