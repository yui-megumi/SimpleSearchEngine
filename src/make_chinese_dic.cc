#include"../include/Chinese_dic_index.h"

int main(){
    Chinese_dic_index cdi;
    cdi.handle_flush("../resource/C3-Art0019.txt");
    cdi.handle_dic("../resource/stop_words_zh.txt");
    cdi.to_dic("../resource/Chinese_dic.txt");

    cdi.handle_index();
    cdi.to_index("../resource/Chinese_index.txt");
    return 0;
}
