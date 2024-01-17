#ifndef _ispd2def_
#define _ispd2def_

class Node
{
public:
    int id;
    double x;
    double y;
    double cap;
    Node(int _id,double _x ,double _y,double _cap):id{_id},x{_x},y{_y},cap{_cap}
    {

    }
};

void ispd2def();

#endif
