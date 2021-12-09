//
// Created by fokus on 10.11.2021.
//
#pragma once

#include "DictionarySequence.h"

#include "AVLTree.h"


template <class K, class T>
class DictionaryTree : public IDictionary<K, T> {
private:
        AVL<Pair<K, T>>* items;

    int capacity;
    int count;

public:
    DictionaryTree(int capacity);

     int Count() const override;

     int Capacity() const override;

     T Get(const K key) const override;

     bool ContainsKey(const K key) const override;

     void Add(const K key, const T element) override;

     void Remove(const K key) override;

     void Change(const K key, T element) override;

     Sequence<K>* GetKeys() override;
     Sequence<T>* GetValues() override;



     void Resize(int size);

};

template<class K, class T>
DictionaryTree<K, T>::DictionaryTree(int capacity) {
    this->items = new AVL<Pair<K, T>>();
    this->capacity = capacity;
    this->count = 0;
}

template<class K, class T>
int DictionaryTree<K, T>::Count() const {
    return this->count;
}

template<class K, class T>
int DictionaryTree<K, T>::Capacity() const {
    return this->capacity;
}

template<class K, class T>
T DictionaryTree<K, T>::Get(const K key) const {
    if (this->count <= 0) {
        throw out_of_range(INDEX_OUT_OF_RANGE);
    }

    Node<Pair<K, T>>* resultNode = this->items->search(Pair<K, T>(key, T()));
    if (resultNode) {
        return resultNode->key.GetSecond();
    }

    throw logic_error(ELEMENT_DOESNT_EXIST);
}

template<class K, class T>
bool DictionaryTree<K, T>::ContainsKey(const K key) const {
    return (this->items->search(Pair<K, T>(key, T())) != NULL);
}

template<class K, class T>
void DictionaryTree<K, T>::Add(const K key, const T element) {
    if (!(this->ContainsKey(key)) && (this->count != this->capacity)) {
        this->items->insert(Pair<K, T>(key, element));
        this->count++;
    }
}

template<class K, class T>
void DictionaryTree<K, T>::Remove(const K key) {
    if (this->count <= 0) {
        throw out_of_range(INDEX_OUT_OF_RANGE);
    }

    this->items->deleteKey(Pair<K, T>(key, T()));
    this->count--;
}

template<class K, class T>
void DictionaryTree<K, T>::Change(const K key, T element) {
    if (this->count <= 0) {
        throw logic_error(ELEMENT_DOESNT_EXIST);
    }

    Node<Pair<K, T>>* node = this->items->search(Pair<K, T>(key, T()));
    if (node) {
        node->key =  Pair<K, T>(key, element);
        return;
    }

    throw logic_error(ELEMENT_DOESNT_EXIST);
}

template<class K, class T>
Sequence<K> *DictionaryTree<K, T>::GetKeys() {
    if (this->count <= 0) {
        throw logic_error(ELEMENT_DOESNT_EXIST);
    }

    Sequence<Node<Pair<K,T>>*>* tmpSequence = this->items->Threading("LNR");
    Sequence<K>* resultSequence = new ArraySequence<K>(tmpSequence->GetSize());
    for (int i = 0; i < tmpSequence->GetSize(); ++i) {
        resultSequence->Set(i,tmpSequence->Get(i)->key.GetFirst());
    }

    return resultSequence;
}

template<class K, class T>
Sequence<T> *DictionaryTree<K, T>::GetValues() {
    if (this->count <= 0) {
        throw logic_error(ELEMENT_DOESNT_EXIST);
    }

    Sequence<Node<Pair<K,T>>*>* tmpSequence = this->items->Threading("LNR");
    Sequence<T>* resultSequence = new ArraySequence<T>(tmpSequence->GetSize());
    for (int i = 0; i < tmpSequence->GetSize(); ++i) {
        resultSequence->Set(i,tmpSequence->Get(i)->key.GetSecond());
    }

    return resultSequence;
}


template<class K, class T>
void DictionaryTree<K, T>::Resize(int size) {
    this->capacity = size;
}



