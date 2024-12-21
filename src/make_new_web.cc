#include"../include/new_web.h"
#include"../include/web_pos.h"

int main(){
    new_web nw;
    nw.load_simhash("../resource/oldripepage.dat","../resource/old_web_pos.dat");

    nw.hash_compare("../resource/oldripepage.dat","../data/newripepage.dat");

    web_pos wp;
    wp.read_xml("../data/newripepage.dat");
    wp.put_pos("../data/new_pos.dat");
    return 0;

}
