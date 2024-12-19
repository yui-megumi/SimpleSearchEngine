#include"../include/English_index.h"
#include<fstream>
#include<ostream>
#include<iostream>
#include<string>


English_index::English_index(){

}

void English_index::open_flush(string file_path){//打开清洗后的文件
    std::ifstream ifs(file_path);
    if(!ifs){
        std::cerr<<"ifs open file fail!";
        return;
    }

    //获取整个文件的大小
    ifs.seekg(0,std::ios::end);
    long length = ifs.tellg();//获取总字符数

    char * tmp = new char[length+1]();
    //重新设置游标
    ifs.seekg(0,std::ios::beg);//放在文件开头
    ifs.read(tmp,length);

    buf=tmp;
    
    delete  []tmp;
    ifs.close();
}

void English_index::handle_index(string stop_words,string file_path){//处理成索引
    ed.load_stop_words(stop_words);     
    ed.word_count(file_path);
    for(auto &elem : ed.dic){
        dic.push_back(std::make_pair(elem.first,elem.second));
    }
    //创建索引
    for(int v=0;v<dic.size();v++){
        //获取词典中每一个元素
        std::string tmp = dic[v].first;
        //遍历单词中每一个字母
        for(int i=0;i<tmp.size();i++){
            string wd;
            wd = tmp[i];
            if(index.find(wd)!=index.end()){
                //找到了
                index[wd].insert(v);
            }else{
                //没找到
                set<int>s;
                s.insert(v);
                index.insert(std::make_pair(wd,s));
            }
        }
    }

}

void English_index::to_index(string file_path){//存储文件

    std::ofstream ofs(file_path);
    for(auto &elem :index){
        ofs<<elem.first<<" ";
        for(auto it=elem.second.begin();it!=elem.second.end();it++){
            ofs<<*it<<" ";
        }
        ofs<<"\n";
    }

    ofs.close();
}

