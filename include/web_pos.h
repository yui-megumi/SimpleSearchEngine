#include<istream>
#include<vector>
#include<string>
#include<fstream> 

using std::vector;
using std::string;

class web_pos{

public:
    web_pos();
    void read_xml(string file_path);//用于读文件、生成网页偏移库
    void put_pos(string file_path);//用于保存文件

private:
    vector<std::pair<int, int>> pos;//用于存放网页偏移库

};
