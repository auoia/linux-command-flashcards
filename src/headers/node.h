#pragma once

// UtypeX specifies a user provided type
template<class Utype1, class Utype2>
class Node {
private:
    Node *next;
    Utype1 data1;
    Utype2 data2;
public:
    Node() = default;

    // Getters
    Utype1 get_data1(void) {
        return data1;
    }

    Utype2 get_data2(void) {
        return data2;
    }
    
    Node * get_next(void) {
        return next;
    }


    // Setters
    void set_data1(Utype1 in_data1) {
        data1 = in_data1;
    }

    void set_data2(Utype2 in_data2) {
        data2 = in_data2;
    }

    void set_next(Node * in_next) {
        next = in_next;
    }

};
