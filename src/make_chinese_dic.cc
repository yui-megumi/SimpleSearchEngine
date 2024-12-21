#include"../include/Chinese_dic_index.h"
#include<func.h>

int main(){
    DIR* pdir = opendir("../resource/art");
    if (pdir == NULL) {
    error(1, errno, "opendir" );
    }

    errno = 0;

    struct dirent* pdirent;
    
    Chinese_dic_index chi;
    while ((pdirent = readdir(pdir)) != NULL) {
        string s("../resource/art/");
        string add(pdirent->d_name);
        s += add;
        std::cout<<s<<"\n";
        if(add.compare(".")==0){
            continue;
        }
        if(add.compare("..")==0){
            continue;
        }
        chi.handle_flush(s);
        chi.handle_dic("../resource/stop_words_zh.txt");
        chi.handle_index();
        chi.to_dic("../data/Chinese_dic.dat");
        chi.to_index("../data/Chinese_index.dat");
    }

    closedir(pdir);

    if (errno) {
        // 发生了错误
        error(1, errno, "readdir");
    }

    return 0;
}
