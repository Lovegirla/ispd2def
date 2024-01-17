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
    cout<<max_x<<"  "<<max_y<<endl;
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
    cout<<node_num<<endl;

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
}
//test
int main()
{
    cout<<"hello"<<endl;
    ispd2def("input","q");
    return 0;
}