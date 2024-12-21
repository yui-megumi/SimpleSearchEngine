#include "../include/Chinese_dic_index.h"
#include<fstream>
#include<ostream>


Chinese_dic_index::Chinese_dic_index(){

}

void Chinese_dic_index::handle_flush(string file_path)//存储待处理的中文文件
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

    buf=tmp;//清洗之后的文件

    delete  []tmp;
    ifs.close();

    //开始清洗
    for(int i = 0 ;i < buf.size();i++){
        if(buf[i]=='\n'||buf[i]=='\r'){//如果是换行或者制表符
            buf[i]=' ';
        } 
    }
}

void Chinese_dic_index::handle_dic(string stop_path)//将清洗后的文件存储成字典
{
    std::ifstream ifs(stop_path);
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

    string ans;
    std::istringstream iss (Tmp);
    while(iss>>ans){
        //将停用词插入到set中
        stop.insert(ans);
        ans.clear();
    }

    //使用cppjieba
    const char *dict_path = "dict/jieba.dict.utf8";
    const char *model_path = "dict/hmm_model.utf8";
    const char *user_dict_path = "dict/user.dict.utf8";
    const char *idf_path = "dict/idf.utf8";
    const char *stop_word_path = "dict/stop_words.utf8";
    cppjieba::Jieba jb(dict_path,model_path,user_dict_path,idf_path,stop_word_path);

    vector<string>words;

    jb.Cut(buf,words,true);

    //将词插入map中
    for(auto word:words){
        auto it = m_dic.find(word);
        if(it==m_dic.end()){
            //没有找到，则直接插入
            if(stop.find(word)==stop.end()){
                //不是停用词，则直接插入
                m_dic.insert(std::make_pair(word,1));
            }
        }else{
            //找到，则计数加1
            m_dic[word]++;
        }
    }


    //最后将map中的内容存入vector
    for(auto elem : m_dic){
        dic.push_back(std::make_pair(elem.first,elem.second));
    }


}

size_t Chinese_dic_index::nBytesCode(const char ch)//获取一个字符有多少字节
{
    if(ch&(1<<7)){
        int nBytes = 1;
        for(int idx  = 0;idx !=6; ++idx){
            if(ch&(1<<(6-idx))){
                ++nBytes;
            }else{
                break;
            }
        }
        return nBytes;
    }
    return 1;
}

void Chinese_dic_index::handle_index()//创建中英文混合索引
{
    for(int v=0;v<dic.size();v++){
        //获取词典中每一个元素
        std::string tmp = dic[v].first;
        //遍历单词中每一个字母
        for(int i=0;i<tmp.size();){
            char wd = tmp[i];
            int wd_length = nBytesCode(wd);
            string mid;
            if((tmp[i] & 0x80) == 0){
                mid = tmp.substr(i,1);
                i++;
            }else {
                mid = tmp.substr(i,3);
                i+=3;
            }
             
            if(index.find(mid)!=index.end()){
                //找到了
                index[mid].insert(v);
            }else{
                //没找到
                set<int>s;
                s.insert(v);
                index.insert(std::make_pair(mid,s));
            }
        }
    }

}

void Chinese_dic_index::to_dic(string file_path)//将数据持久化
{
    std::ofstream ofs(file_path,std::ios::app);
    for(auto &elem :dic){
        ofs<<elem.first<<" "<<elem.second<<"\n";
    }
    ofs.close();
}

void Chinese_dic_index::to_index(string file_path){
    std::ofstream ofs(file_path,std::ios::app);
    for(auto &elem :index){
        ofs<<elem.first<<" ";
        for(auto it=elem.second.begin();it!=elem.second.end();it++){
            ofs<<*it<<" ";
        }
        ofs<<"\n";
    }

    ofs.close();

}
