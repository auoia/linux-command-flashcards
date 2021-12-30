#pragma once

#include <iostream>
#include "node.h"


template<class Utype1, class Utype2>
class List {
private:
    Node<Utype1, Utype2> *head;
    //Node<Utype1, Utype2> *tail;

public:
    // constructor
    List () {
        head = nullptr;
    }
    
    // void recursive_destruct(Node<Utype1, Utype2> *i_head) {
    //     if(head->get_next()) {
    //         std::cout << "recursive delete\n";
    //         recursive_destruct(i_head->get_next());
    //         delete i_head;
    //     }
    // }

    /* referenced this https://stackoverflow.com/a/15672823
     */
    void list_destruct() {
        while (head != nullptr) { 
            Node<Utype1, Utype2> *tmp = head->get_next();
            delete head;
            head = tmp;
        }
    }

    // destructor
    ~List() {
        list_destruct();
        // head = nullptr;
        //
    }

    // Getters
    Node<Utype1, Utype2> *get_head(void) {
        return head;
    }

    // Setters
    void set_head(Node <Utype1, Utype2> *new_head) {
        head = new_head;
    }

    // List Operations
    Node<Utype1, Utype2> *create_node(Utype1 data1, Utype2 data2) {
        Node<Utype1, Utype2> *new_node = new Node<Utype1, Utype2>;

        new_node->set_data1(data1);
        new_node->set_data2(data2);
        new_node->set_next(nullptr);

        return new_node;
    }
    
    /* insert(Utype1 data1, Utype2 data2) takes two arguments of types
     *      defined by the user and returns either a true or false. 
     *      It checks if there already exists data1 in the list. If so, 
     *      it returns false, otherwise it creates a new node, and if successful,
     *      it returns true.
     */
    bool insert(Utype1 data1, Utype2 data2) {
        //std::cout << "INSERT FRONT";
        Node<Utype1, Utype2> *new_node = search(data1);
        bool success = false;

        // Checks if a node with value provided for data1 already exists
        if (new_node) {
            success = false;
        } else {
            new_node = create_node(data1, data2);
            // Check if memory was allocated to new_node
            if (new_node) {
                if(head == nullptr) {
                    // if list is empty, then head is the new node
                    head = new_node;
                    head->set_next(nullptr);
                    success = true;
                } else {
                    // list is not empty, insert node front
                    Node<Utype1, Utype2> *tmp;
                    tmp = head;
                    head = new_node;
                    head->set_next(tmp);
                    success = true;
                }
            }
        }

        return success;
    }

    Utype1 data1_by_index(int index=0) {
        Node<Utype1, Utype2> *traversal = head;

        int i = 0;
        while(traversal->get_next() && i < index) {
            traversal = traversal->get_next();
            i++;
        }

        return traversal->get_data1();
    }

    Utype2 data2_by_index(int index=0) {
        Node<Utype1, Utype2> *traversal = head;

        int i = 0;
        while(traversal->get_next() && i < index) {
            traversal = traversal->get_next();
            i++;
        }

        return traversal->get_data2();
    }

    /* Node<> search traverses the list to find an element by type Utype1.
     * It returns the Node if it is found, and nullptr otherwise
     */
    Node<Utype1, Utype2> *search(Utype1 data1) {
        Node<Utype1, Utype2> *traversal = head;
        bool found_node = 0;

        while(traversal && !found_node) {
            if(traversal->get_data1() == data1)
                found_node = 1;
            else
                traversal = traversal->get_next();
        }

        if (found_node) {
            return traversal;
        } else {
            return nullptr;
        }
    }

    /* Helper function for remove() that removes the last node in the list
     */
    void remove_tail(Utype1 data1) {
        Node<Utype1, Utype2> *traversal = head;
        Node<Utype1, Utype2> *tmp = traversal;

        while(traversal->get_next() != nullptr) {
            tmp = traversal;
            traversal = traversal->get_next();
        }

        tmp->set_next(nullptr);
        delete traversal;
    }

    /* bool remove_node(Utype1 data1) searches the list for the first Node matching
     * data1 and then deletes it from the list and returns 1, otherwise it returns 0
     */
    bool remove(Utype1 data1) {
        Node<Utype1, Utype2> *node = nullptr;
        bool success = 0;

        node = search(data1);
        if (node) {
            // If the node is the head node, then delete it and change head ptr
            if(node == head) {
                Node<Utype1, Utype2> *tmp = head;
                head = head->get_next();
                delete tmp;
                success = 1;
            } else {
                // Checks if next node is not the tail (points to nullptr)
                if(node->get_next() != nullptr) {
                    Node<Utype1, Utype2> *tmp = nullptr;
                    tmp = node->get_next();

                    node->set_data1(node->get_next()->get_data1());
                    node->set_data2(node->get_next()->get_data2());

                    node->set_next(tmp->get_next());

                    delete tmp;
                    success = 1;
                } else { // node is the last one in the list
                    remove_tail(data1);
                    success = 1;
                }
            }
        }

        return success;
    }
    
    // returns the size of the linked list
    int size(void) {
        Node<Utype1, Utype2> *traversal = head;

        int size = 0;
        while(traversal) {
            size++;
            traversal = traversal->get_next();
        }

        return size;
    }

    /* print all elements in the list separated by '-'
     */
    void print() {
        Node<Utype1, Utype2> *traversal = head;

        while(traversal) {
            std::cout << traversal->get_data1()
                << " - "
                << traversal->get_data2()
                << std::endl;
            
            traversal = traversal->get_next();
        }
    }
};
