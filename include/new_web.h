#pragma once
#include<string>
#include<vector>
#include"simhash/Simhasher.hpp"

using std::string;
using std::vector;
using std::pair;

class new_web
{
public:
    new_web();
    void load_simhash(string web_path,string pos_path);//根据网页库和偏移库生成每一篇文章的指纹
    void hash_compare(string web_path,string position);//对比xml文章哈希之后将数据持久化


private:
    vector<pair<int,int> > pos;//存放偏移库
    vector<uint64_t>sm;//用于存储每一篇文章的指纹

};

