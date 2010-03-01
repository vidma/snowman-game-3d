#ifndef COLLECTION_H_INCLUDED
#define COLLECTION_H_INCLUDED

#include <vector>
#include <iostream>

namespace prog3d {
    template <class T> class VCollection :
    public std::vector<T *> {
        public:
        void clean(); // only VCollection can delete its elements
        VCollection();
        void copyFrom(const VCollection &p);
        T operator()(int i);
        void allocate(int n);
        void addEnd(T* t);
        ~VCollection();
        typedef typename VCollection<T>::iterator ItVCollection;
};

template <class T> class ACollection: public std::vector<T> {
    public:
    ACollection();
    void copyFrom(const VCollection<T> &p);
    void addEnd(const T &t);
    typedef typename ACollection<T>::iterator ItACollection;
};


template <class T>VCollection<T>::VCollection() {
    this->clear();
}

template <class T>VCollection<T>::~VCollection() {
    this->clear();
    clean();
}


template <class T> void VCollection<T>::clean() {
    for(ItVCollection i=this->begin();i!=this->end();i++) {
        if (*i) {delete *i; *i=NULL;}
    }
}

template <class T>void VCollection<T>::allocate(int n) {
    for(int i=0;i<n;i++) {
        push_back(new T);
    }
}

template <class T>void VCollection<T>::addEnd(T *t) {
	this->push_back(t);
}

template <class T>void VCollection<T>::copyFrom(const VCollection<T> &p) {
    for(int i=0;i<p.size();i++) {
        (*this)[i]->set(*p[i]);
    }
}

template <class T>T VCollection<T>::operator()(int i) {
    return *(*this)[i];
}


template <class T>ACollection<T>::ACollection() {
    this->clear();
}

template <class T>void ACollection<T>::copyFrom(const VCollection<T> &p) {
    this->clear();
    for(unsigned int i=0;i<p.size();i++) {
        this->push_back(*(p[i]));
    }
}

template <class T>void ACollection<T>::addEnd(const T &t) {
	this->push_back(t);
}


}

#endif // VECTORARRAY_H_INCLUDED
