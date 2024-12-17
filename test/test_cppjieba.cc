#include "../include/cppjieba/Jieba.hpp"
#include <string>
#include <iostream>
#include <vector>

using std::string;
using std::vector;
using std::cout;
using std::endl;

int main(){
    const char * dict_path = "dict/jieba.dict.utf8";
    const char * model_path = "dict/hmm_model.utf8";
    const char * user_dict_path = "dict/user.dict.utf8";
    const char * idf_path = "dict/idf.utf8";
    const char * stop_sord_path = "dict/stop_words.utf8";
    
    cppjieba::Jieba jieba(dict_path,model_path,user_dict_path,idf_path,stop_sord_path);

    string sentence = "这是一段测试代码，测试结巴";
    vector<string> words;

    jieba.Cut(sentence,words,true);

    for(auto word:words){
        cout<<"word = "<<word<<"\n";
    }
    
    return 0;
}
