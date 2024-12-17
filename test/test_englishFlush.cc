#include"../include/English_flush.h"
#include<string>
#include<iostream>
#include<fstream>
#include<cstring>
using namespace std;

int main(){
    English_flush eF;
    string filepath("english.txt");
    cout<<filepath<<endl;

    eF.read_file(filepath);
    eF.handle_words();

    ofstream ofs("final.txt");

    cout<<eF.buf.size()<<endl;
    string word = eF.buf;
    ofs<<word;


    ofs.close();
    return 0;
}
