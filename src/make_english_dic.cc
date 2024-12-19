#include "../include/English_dic.h"

int main(){
    English_dic ed;
    ed.load_stop_words("../resource/stop_words_eng.txt");

    ed.word_count("../resource/flush_english.txt");

    ed.update_dic("../data/dict.dat");

    return 0;
}
