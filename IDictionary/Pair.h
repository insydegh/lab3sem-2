//
// Created by fokus on 09.11.2021.
//
#pragma once

#include "string"
using namespace std;

template <class K, class T>
class Pair {
private:
    K first;
    T second;

public:
    Pair();
    Pair(K first, T second);

    K GetFirst();

    T GetSecond();

    bool operator ==(const Pair<K, T> &pair);
    bool operator !=(const Pair<K, T> &pair);
    bool operator <(const Pair<K, T> &pair);
    bool operator >(const Pair<K, T> &pair);
    bool operator <=(const Pair<K, T> &pair);
    bool operator >=(const Pair<K, T> &pair);

    Pair<K, T> & operator = (const Pair<K, T> & other);
};

template<class K, class T>
Pair<K, T>::Pair() {
    this->first = K();
    this->second = T();
}

template<class K, class T>
Pair<K, T>::Pair(K first, T second) {
    this->first = first;
    this->second = second;
}

template<class K, class T>
K Pair<K, T>::GetFirst() {
    return this->first;
}

template<class K, class T>
T Pair<K, T>::GetSecond() {
    return this->second;
}

template<class K, class T>
bool Pair<K, T>::operator==(const Pair<K, T> &pair) {
    return (this->first == pair.first);
    //return (this->second == pair.second);
}

template<class K, class T>
bool Pair<K, T>::operator!=(const Pair<K, T> &pair) {
    return !(this->first == pair.first);
    //return !(this->second != pair.second);
}

template<class K, class T>
bool Pair<K, T>::operator<(const Pair<K, T> &pair) {
    return (this->first < pair.first);
    //return (this->second < pair.second);
}

template<class K, class T>
bool Pair<K, T>::operator>(const Pair<K, T> &pair) {
    return (this->first > pair.first);
    //return (this->second > pair.second);
}

template<class K, class T>
bool Pair<K, T>::operator<=(const Pair<K, T> &pair) {
    return (this->first <= pair.first);
    //return (this->second <= pair.second);
}

template<class K, class T>
bool Pair<K, T>::operator>=(const Pair<K, T> &pair) {
    return (this->first >= pair.first);
    //return (this->second >= pair.second);
}

template<class K, class T>
Pair<K, T> &Pair<K, T>::operator=(const Pair<K, T> &other) {
    this->first = K();
    this->first = other.first;

    this->second = T();
    this->second = other.second;

    return *this;
}