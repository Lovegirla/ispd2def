#include "ispd2def.h"
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdio.h>
#include <vector>
using namespace std;
void ispd2def(string input,string output)
{
    cout<<"开始读取点对"<<endl;
    vector<Node> nodes;

    //处理输入点
    fstream fin;
    fin.open(input,ios::in);
    if (!fin.is_open())
    {
        cout<<"文件不存在"<<endl;
        return;
    }
    string line;
    getline(fin,line);
    stringstream sstream;
    sstream<<line;
    //读取layout
    double max_x,max_y;
    double temp;
    sstream>>temp>>temp>>max_x>>max_y;
    max_x*=2;
    max_y*=2;
    //读取点
    getline(fin,line);//skip
    line.clear();
    getline(fin,line);
    sstream.str("");
    sstream.clear();
    sstream<<line;

    int node_num=0;
    std::string temp1;
    sstream>>temp1>>temp1>>node_num;
    cout<<"点的数量："<<node_num<<endl;

    while (node_num--)
    {
        getline(fin,line);
        sstream.str("");
        sstream.clear();
        sstream<<line;
        int id;
        double x,y,cap;
        sstream>>id>>x>>y>>cap;
        nodes.emplace_back(id,x,y,cap);
    }
    
    //将点输出
    fin.close();
    cout<<"开始转化"<<endl;
    fstream fot;
    fot.open(output,ios::out);
    //输入头部分
    fot << "VERSION 5.7 ;\n"
    << "DIVIDERCHAR \"/\" ;\n"
    << "BUSBITCHARS \"[]\" ;\n"
    << "DESIGN test_" + std::to_string(nodes.size()) + "_sinks ;\n"
    << "UNITS DISTANCE MICRONS 2000 ;\n"
    << "DIEAREA ( 0 0 ) ( 10000000 10000000) ;\n\n"
    << "COMPONENTS " + std::to_string(nodes.size()) + " ;"<<endl;

    for (size_t i = 0; i < nodes.size(); i++)
    {
            std::stringstream ss;
            ss <<std::fixed<< "- ff" << i+1 << " DFF_X1 + PLACED ( " << static_cast<int>(nodes[i].x *2)<< " " << static_cast<int>(nodes[i].y *2)<< " ) N ;";
            fot << ss.str() << std::endl;
    }
    fot<<"END COMPONENTS"<<endl;
    fot << "PINS 1 ;\n"
    << "- clk + NET clk + DIRECTION INPUT + USE SIGNAL\n"
    << " + LAYER metal6 ( -140 0 ) ( 140 280 ) + FIXED ( 10000 20000 ) S ;\n"
    << "END PINS\n"<<endl;

    fot<<"NETS 1 ;\n\
    - clk ( PIN clk )";
    for (size_t i = 0; i < nodes.size(); i++)
    {
        fot<<" ( ff"<<i+1<<" ck )";
    }
    fot<<
    "\n ;\n"
    <<"END NETS\n"<<endl<<
    "END DESIGN"<<endl;
    fot.close();
    cout<<"完成"<<endl;
}
//test
int main(int argc,char**argv)
{
    if(argc<3)
    {
        cout<<"用法：./程序名 输入文件 想存储转化的文件名"<<endl;
        return 0;
    }
    ispd2def(argv[1],argv[2]);
    return 0;
}