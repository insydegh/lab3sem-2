//
// Created by fokus on 09.11.2021.
//
#pragma once

#include "IDictionary.h"

#include "iostream"

template <class K, class T>
class DictionarySequence : public IDictionary<K, T> {
private:
    Sequence<Pair<K, T>>* items;
    int capacity;
    int count;

public:
    DictionarySequence(int capacity);

     int Count() const override;

     int Capacity() const override;

     T Get(const K key) const override;

     bool ContainsKey(const K key) const override;

     void Add(const K key, const T element) override;

     void Remove(const K key) override;

     void Change(const K key, T element) override;

     void Resize(int size) override;

     Sequence<K>* GetKeys() override;
     Sequence<T>* GetValues() override;

};

template<class K, class T>
DictionarySequence<K, T>::DictionarySequence(int capacity) {
    this->items = new ArraySequence<Pair<K, T>>(capacity);
    this->capacity = capacity;
    this->count = 0;
}

template<class K, class T>
int DictionarySequence<K, T>::Count() const {
    return this->count;
}

template<class K, class T>
int DictionarySequence<K, T>::Capacity() const {
    return this->capacity;
}

template<class K, class T>
T DictionarySequence<K, T>::Get(const K key) const {
    if (this->count <= 0) {
        throw out_of_range(INDEX_OUT_OF_RANGE);
    }

    for (int i = 0; i < this->count; ++i) {
        if (this->items->Get(i).GetFirst() == key) {
            return this->items->Get(i).GetSecond();
        }
    }

    throw logic_error(ELEMENT_DOESNT_EXIST);
}

template<class K, class T>
bool DictionarySequence<K, T>::ContainsKey(const K key) const {
    for (int i = 0; i < this->count; ++i) {
        if (this->items->Get(i).GetFirst() == key) {
            return true;
        }
    }
    return false;
}

template<class K, class T>
void DictionarySequence<K, T>::Add(const K key, const T element) {
    if (this->capacity==this->count) {
        this->Resize(this->capacity*2);
    }
    if (!(this->ContainsKey(key))) {
        this->items->Set(count, Pair<K, T>(key, element));
        this->count++;

    }
}

template<class K, class T>
void DictionarySequence<K, T>::Remove(const K key) {
    if (this->count <= 0) {
        throw length_error(NEGATIVE_SIZE);
    }

    for (int i = 0; i < this->count; ++i) {
        if (this->items->Get(i).GetFirst() == key) {
            this->items->RemoveAt(i);
            this->count--;

            return;
        }
    }

    //throw logic_error(ELEMENT_DOESNT_EXIST);
}

template<class K, class T>
void DictionarySequence<K, T>::Change(const K key, T element) {
    if (this->count <= 0) {
        throw length_error(NEGATIVE_SIZE);
    }

    for (int i = 0; i < this->count; ++i) {
        if (this->items->Get(i).GetFirst() == key) {
            this->items->Set(i,Pair<K, T>(key, element));
            return;
        }
    }

    //throw logic_error(ELEMENT_DOESNT_EXIST);
}

template<class K, class T>
Sequence<K> *DictionarySequence<K, T>::GetKeys() {
    if (this->count <= 0) {
        throw length_error(NEGATIVE_SIZE);
    }

    Sequence<K>* resultSequence = new ArraySequence<K>(this->count);
    for (int i = 0; i < this->count; ++i) {
        resultSequence->Set(i, this->items->Get(i).GetFirst());
    }

    return resultSequence;
}

template<class K, class T>
Sequence<T> *DictionarySequence<K, T>::GetValues() {
    if (this->count <= 0) {
        throw length_error(NEGATIVE_SIZE);
    }

    Sequence<T>* resultSequence = new ArraySequence<T>(this->count);
    for (int i = 0; i < this->count; ++i) {
        resultSequence->Set(i, this->items->Get(i).GetSecond());
    }

    return resultSequence;
}

template<class K, class T>
void DictionarySequence<K, T>::Resize(int size) {
    ArraySequence<Pair<K, T>>* newseq =new ArraySequence<Pair<K, T>>(size);
    for (int i =0; i<this->count; i++) {
        newseq->Set(i,Pair<K, T>(this->items->Get(i).GetFirst(), this->items->Get(i).GetSecond()));
    }
    this->capacity = size;
    delete items;
    items = newseq;
}


