#include"../include/English_dic.h"
#include<iostream>
#include<fstream>
#include<sstream>

English_dic::English_dic(){

}

void English_dic::load_stop_words(string file_path)//加载停用词
{
    std::ifstream ifs(file_path);
    if(!ifs){
    std::cerr<<"ifs open file fail!";
    return;
    }

    string Tmp;
    //获取整个文件的大小
    ifs.seekg(0,std::ios::end);
    long length = ifs.tellg();//获取总字符数

    char * tmp = new char[length+1]();
    //重新设置游标
    ifs.seekg(0,std::ios::beg);//放在文件开头
    ifs.read(tmp,length);

    Tmp=tmp;//拷贝文件内容到临时变量中

    delete  []tmp;
    ifs.close();

    for(int i = 0 ;i < Tmp.size();i++){
        if(isalpha(Tmp[i])){//如果是字母
            if(isupper(Tmp[i])){
                //如果是大写字母
                Tmp[i] = tolower(Tmp[i]);
            }
        }else{
            //不是字母
            Tmp[i]=' ';//设置为空格
        }
    } 
    
    string ans;
    std::istringstream iss (Tmp);
    while(iss>>ans){
        //将停用词插入到set中
        stop.insert(ans);
        ans.clear();
    }
}

void English_dic::word_count(string file_path)//单词统计
{
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

    //分词
    std::istringstream iss(buf);
    string tmp2;
    while(iss>>tmp2){
        auto it = stop.find(tmp2);
        if(it == stop.end()){
            //插入
            auto it_m = dic.find(tmp2);
            int value = it_m->second;
            dic.insert(std::make_pair("tmp2",value+1));
        }else{
            //不插入
        }

        tmp2.clear();
    }
}

void English_dic::update_dic(string file_path)//存储成词典
{
    std::ofstream ofs(file_path,std::ios::app);
    for(auto &elem :dic){
        ofs<<elem.first<<" "<<elem.second<<"\n";
    }
    
    ofs.close();
}
