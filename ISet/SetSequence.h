//
// Created by fokus on 10.11.2021.
//

#pragma once


#include "ListSequence.h"
#include "ISet.h"

template <class T>
class SetSequence : public ISet<T> {
private:
    Sequence<T>* items;
public:
    SetSequence();

     void Insert(T value) override;

     void Remove(T value) override;

     int Count() const override;

     T Get(const int index) const override;
};

template<class T>
SetSequence<T>::SetSequence() {
    this->items = new ListSequence<T>();
}

template<class T>
void SetSequence<T>::Insert(T value) {
    for (int i = 0; i < this->items->GetSize(); ++i) {
        if (this->items->Get(i) == value) {
            return;
        }
    }
    this->items->Append(value);
}

template<class T>
void SetSequence<T>::Remove(T value) {
    for (int i = 0; i < this->items->GetSize(); ++i) {
        if (this->items->Get(i) == value) {
            this->items->RemoveAt(i);
        }
    }
}

template<class T>
int SetSequence<T>::Count() const {
    return this->items->GetSize();
}

template<class T>
T SetSequence<T>::Get(const int index) const {
    return this->items->Get(index);
}