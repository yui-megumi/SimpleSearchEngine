#include"../include/English_index.h"

int main(){
    English_index ei;
    ei.handle_index("../resource/stop_words_eng.txt","../resource/flush_english.txt");
    ei.to_index("../data/english_index.dat");

    return 0;

}
