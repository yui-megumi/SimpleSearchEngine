#pragma once
#include<vector>
#include<map>
#include<string>
#include<set>
#include"English_dic.h"

using std::vector;
using std::map;
using std::pair;
using std::string;
using std::set;

class English_index
{
public:
    English_index();
    void open_flush(string file_path);
    void handle_index(string stop_words,string file_path);
    void to_index(string file_path);

private:
    string buf;
    vector<pair<string,int> >dic;//词典
    map<string,set<int> > index;//位置索引
    English_dic ed;
};

