#include"../include/web_pos.h"

int main(){
    web_pos wb;
    wb.read_xml("../resource/oldripepage.dat");

    wb.put_pos("../resource/old_web_pos.dat");

    return 0;
}
