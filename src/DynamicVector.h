//
// Created by Luca De Mori on 29/12/2017.
//

#ifndef NSD10_DYNAMICVECTOR_H
#define NSD10_DYNAMICVECTOR_H

#include <iostream>

using namespace std;

template <class T>
class DynamicVector {
public:

    DynamicVector(unsigned int _size) : size(_size) {
        container = new T[_size]();
    }

    T &operator[](unsigned int i) {
        if (i<0){
            return container[0];
        }

        if (i>=size) {      // array already exist, so realloc
            T *temp = new T[i + 1]();
            std::copy(container, container + size, temp);
            delete[] container;
            container = temp;
            size = i + 1;
            std::cout << "[DEBUG] - DynamicVector::operator[]: container size=" << size << std::endl;
        }

        return container[i];

    }

    unsigned int getSize() const {
        return size;
    }

    void f_print(std::ostream &out) const {
        for (int j=0; j<size; j++){
            out << j << " " << container[j] << endl;
        }
    }

    void f_print_nz(std::ostream &out) const {
        for (int j=0; j<size; j++){
            if (container[j]||j==0||j==size-1) out << j << " " << container[j] << endl;
        }
    }

    void f_print_fill(std::ostream &out) const {
        T last;
        for (int j=0; j<size; j++){
            out << j << " ";
            if (container[j]!=0||j==0||j==size-1){
                out << container[j];
                last = container[j];
            } else {
                out << last;
            }
            out << endl;
        }
    }


private:

    unsigned int size;
    T *container;

};


#endif //NSD10_DYNAMICVECTOR_H
