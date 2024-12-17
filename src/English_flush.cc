#include"../include/English_flush.h"
#include<fstream>
#include<ostream>
#include<iostream>
//构造函数
English_flush::English_flush(){

}

//读文件到buf
void English_flush::read_file(string file_path)//读文件
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
    
}

//处理单词
void English_flush::handle_words()//处理buf中的每一个单词
{
    for(int i = 0 ;i < buf.size();i++){
        if(isalpha(buf[i])){//如果是字母
            if(isupper(buf[i])){
                //如果是大写字母
                buf[i] = tolower(buf[i]);
            }
        }else{
            //不是字母
            buf[i]=' ';//设置为空格
        }
    } 
}

//写文件到目标位置
void English_flush::write_dic(string pos_buf)//向目标文件写词典数据，用于保存数据 
{
    std::ofstream ofs(pos_buf); 
    string word = buf;
    ofs<<word;
    ofs.close();
}
