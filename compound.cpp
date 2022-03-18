#include<iostream>
#include<bits/stdc++.h>
using namespace std;

struct info {
    float atomic_weight;
    string symbol;
    string elementName;
};

info data[118];

void split(const string &s, char delim, vector<string> &elems);
void splitInfo(string line, info& Build);
void getElementAndWeight(string &compoundCopy, string &element, float &weight);
void getElementWeight(string element, float &weight, string &name, info data[118]);

int main() {
    string filename = "./resources/atomic_weights.txt";
    ifstream infile(filename);
    string line;
    int i = 0;
    while(getline(infile,line)) {
        splitInfo(line, data[i]);
        ++i;
    }
    string compound;  
    cout<<"Chemical Composition? ";
    while(cin>>compound) {
        float compoundWeight = 0;
        string compoundCopy = compound;
        vector<string> elementsInCompound;
        map<string,int> mapIt;
        while(compoundCopy.length() != 0) {
            string element = "";
            string currentName;
            float weight = 1;
            getElementAndWeight(compoundCopy, element, weight);
            getElementWeight(element, weight, currentName, data);
            if(!mapIt.count(currentName)) {
                mapIt.insert(pair<string,int>(currentName,0));
                elementsInCompound.push_back(currentName);
            }
            compoundWeight += weight;
        }
        sort(elementsInCompound.begin(), elementsInCompound.end());
        cout<<"The atomic weight of "<<compound<<" is "<<compoundWeight<<endl;
        if(elementsInCompound.size() == 1) {
            cout<<"The element is ";
        }
        else {
            cout<<"The elements are ";
        }
        for(int x = 0; x < elementsInCompound.size(); ++x) {
            if(x == elementsInCompound.size()-1 && elementsInCompound.size() != 1) {
                cout<<"and "<<elementsInCompound[x]<<endl;
            }
            else if(elementsInCompound.size() == 1) {
                cout<<elementsInCompound[0]<<endl;
                break;
            }
            else if(elementsInCompound.size() == 2) {
                cout<<elementsInCompound[0]<<" and "<<elementsInCompound[1]<<endl;
                break;
            }
            else {
                cout<<elementsInCompound[x]<<", ";
            }
        }
        cout<<"Chemical Composition? ";
    }

    return 0;
}

void split(const string &s, char delim, vector<string> &elems) {
    stringstream ss;
    ss.str(s);
    string item;
    while(getline(ss,item,delim)) {
        elems.push_back(item);
    }
}

void splitInfo(string line, info& Build) {
    vector<string> values;
    split(line, '\t', values);
    Build.atomic_weight = stof(values[0]);
    Build.symbol = values[1];
    Build.elementName = values[2];
}

void getElementAndWeight(string &compoundCopy, string &element, float &weight) {
    string number = "";
    int i = 0;
    element += compoundCopy[i];
    ++i;
    if(islower(compoundCopy[i])) {
        element += compoundCopy[i];
        ++i;
    }
    while(compoundCopy[i] >= '0' && compoundCopy[i] <= '9') {
        number += compoundCopy[i];
        ++i;
    }
    if(number.length() != 0) {
        weight = stof(number);
    }
    string molecule = element + number;
    compoundCopy.erase(0, molecule.length());
}

void getElementWeight(string element, float &weight, string &name, info data[118]) {
    map<string,int> mapIt;
    for(int i = 0; i < 118; ++i) {
        if(data[i].symbol == element) {
            weight = weight * data[i].atomic_weight;
            name = data[i].elementName;
            break;
        }
    }
}