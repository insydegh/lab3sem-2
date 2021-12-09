//
// Created by fokus on 10.11.2021.
//

#pragma once

#include "SetSequence.h"

template <class T>
class SetTree : public ISet<T> {
private:
    AVL<T> *items;
public:
    SetTree();

    virtual void Insert(T value) override;

    virtual void Remove(T value) override;

    virtual int Count() const override;

    virtual T Get(const int index) const override;
};

template<class T>
SetTree<T>::SetTree() {
    this->items = new AVL<T>();
}

template<class T>
void SetTree<T>::Insert(T value) {
    if (!this->items->search(value)) {
        this->items->insert(value);
    }
}

template<class T>
T SetTree<T>::Get(const int index) const {
    return this->items->Threading()->Get(index)->key;
}

template<class T>
void SetTree<T>::Remove(T value) {
    this->items->deleteKey(value);
}

template<class T>
int SetTree<T>::Count() const {
    return this->items->Threading()->GetSize();
}