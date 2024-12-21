#include"../include/new_web.h"
#include<fstream>
#include<iostream>
#include<sstream>

using std::ifstream;
using std::ofstream;
using std::istringstream;

new_web::new_web()
{
    
}

void new_web::load_simhash(string web_path, string pos_path){
    //根据网页库和偏移库生成每一篇文>
    ifstream ifs_pos(pos_path);
    string line;
    int num,key,value;

    while(getline(ifs_pos,line)){
        istringstream iss(line);
        iss>>num>>key>>value;
        pos.push_back(std::make_pair(key,value));//构造偏移数组
    }

    ifs_pos.close();
    
    simhash::Simhasher simhasher("dict/jieba.dict.utf8",
                                 "dict/hmm_model.utf8",
                                 "dict/idf.utf8",
                                 "dict/stop_words.utf8"); 
    ifstream ifs(web_path);

    for(auto elem : pos){
        char * buf = new char[elem.second+1]();
        ifs.seekg(elem.first);


        int length = elem.second;
        ifs.read(buf,length);

        string tmp = buf;
        size_t topN = 5;
        uint64_t u64 = 0;
        simhasher.make(tmp,topN,u64);//生成指纹

        sm.push_back(u64);

        delete []buf;
    }
    
    ifs.close();

}

void new_web::hash_compare(string web_path, string position){
    //对比xml文章哈希之后将数据持久化
    ifstream ifs(web_path);
    ofstream ofs(position,std::ios::app);

    simhash::Simhasher simhasher("dict/jieba.dict.utf8",
                                 "dict/hmm_model.utf8",
                                 "dict/idf.utf8",
                                 "dict/stop_words.utf8"); 
    for(int i=0;i<pos.size();i++){
        char * buf = new char[pos[i].second+1]();
        ifs.seekg(pos[i].first);
        int length = pos[i].second;
        ifs.read(buf,length);

        string tmp = buf;
        size_t topN = 5;
        uint64_t u64 = 0;
        simhasher.make(tmp,topN,u64);//生成指纹
        
        bool add_xml = true;

        for(int j = 0;j<sm.size();j++){
            if(i==j){
                continue;
            }

            bool flag = simhash::Simhasher::isEqual(u64,sm[j]);

            if(flag){
                //相等
                add_xml = false;
                break;
            }
        }

        if(add_xml){
            ofs<<buf;
        }
        delete []buf;
    }

    
    ofs.close();
    ifs.close();
}
