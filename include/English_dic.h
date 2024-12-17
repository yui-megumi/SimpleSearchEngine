#include<string>
#include<vector>
#include<func.h>
#include<set>
#include<map>

using std::map;
using std::set;
using std::string;
using std::vector;
using std::pair;

class English_dic
{
public:
    English_dic();
    void load_stop_words(string file_path);//加载停用词
    void word_count(string file_path);//单词统计
    void update_dic(string file_path);//存储成词典

private:
    string buf;//用于存放中间数据
    set<string> stop;//停用词
    map<string,int> dic;//词典
};
