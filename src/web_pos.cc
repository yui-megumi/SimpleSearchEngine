#include"../include/web_pos.h"

using std::ifstream;

web_pos::web_pos(){

}

void web_pos::read_xml(string file_path){
    ifstream ifs(file_path);
    int now = 0;//存储现在文件游标的位置
    int next = 0;//存储文件游标的下一个位置
    string line;
    string std1("<doc>");
    string std2("</doc>");
    while(getline(ifs,line)){
        if(!line.compare(std1))
        {
            //字符串相等
            now=ifs.tellg();        
        }else if(!line.compare(std2)){
            //如果与第二个位置相等
            next=ifs.tellg();
            pos.push_back(std::make_pair(now-6,next-now+6));
        }
    }

    ifs.close();
}

void web_pos::put_pos(string file_path){
    std::ofstream ofs(file_path);
    int i = 1;
    for(auto elem : pos){
        ofs<<i<<" "<<elem.first<<" "<<elem.second<<"\n";
        i++;
    }

    ofs.close();
}





