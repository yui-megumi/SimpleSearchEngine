#include<string>
#include<vector>
#include<func.h>

using std::string;
using std::vector;
using std::pair;

class English_flush
{
public:
    English_flush();
    void read_file(string file_path);//读文件
    void handle_words();//处理buf中的每一个单词
    void write_dic(string pos_buf);//向目标文件写词典数据，用于保存数据

private:
    string buf;
};

