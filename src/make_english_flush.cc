#include"../include/English_flush.h"


int main(){
    English_flush ef;
    ef.read_file("../resource/english.txt");
    ef.handle_words();
    ef.write_dic("../resource/flush_english.txt");
    return 0;
}
