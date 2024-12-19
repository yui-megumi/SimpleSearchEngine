#pragma once
#include<string>
#include<vector>
#include<map>
#include<set>
#include"cppjieba/Jieba.hpp"

using std::map;
using std::set;
using std::string;
using std::vector;
using std::pair;

class Chinese_dic_index
{
public:
    Chinese_dic_index();
    void handle_flush(string file_path);//存储待处理的中文文件
    void handle_dic(string stop_path);//将清洗后的文件存储成字典
    size_t nBytesCode(const char ch);//获取一个字符有多少字节
    void handle_index();//创建中英文混合索引
    void to_dic(string file_path);//将数据持久化
    void to_index(string file_path);

private:
    string buf;//存放清洗之后的文章
    set<string> stop;//存放停用词
    map<string,int> m_dic;
    vector<pair<string,int> >dic;
    map<string,set<int> > index;
};

