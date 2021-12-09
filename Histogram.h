//
// Created by fokus on 12.11.2021.
//
#pragma once

#include "typeinfo"
#include "DictionaryTree.h"
#include "SetTree.h"
#include "Person.h"
#include <vector>
#include "string.h"
#include "strings.h"
using namespace std;
#include "iomanip"



inline string
to_string(string __val)
{
    return __val;
}


template <typename T, typename K>
Sequence<T>* SeqOfValues(Sequence<K>* list, T (K::*func)()){
    Sequence<T>* seq =new ArraySequence<T>();
    for (int i =0; i<list->GetSize(); i++) {
        seq->Append((list->Get(i).*func)());
    }
    return seq;
}

template <typename T>
class Interval {
private:
    //Sequence<T>* seq;
    T lower;
    T upper;
    int count;
    T sum;
    float avg;
    bool is_first;

public:
    Interval(T lower, T upper, bool is_first):lower(lower), upper(upper), is_first(is_first), count(0), sum(0), avg(0) { }

    void Add(T item) {
        if (is_first) {
            if (lower<=item & item<=upper) {
                count++;
                sum += item;
            }
        }
        else {
            if (lower<item & item<=upper) {
                count++;
                sum += item;
            }
        }
        avg = float(sum)/count;
    }

    T GetSum() { return this->sum; }
    float GetAverage()  {return this->avg;}
    int GetCount() { return this->count;}
    bool IsFirst() { return is_first; }




};


template <typename K>
class Histogram {
private:
    IDictionary<K,int>* dict;
    string table_info;

public:
    Histogram(IDictionary<K,int>* dict, string info) : dict(dict), table_info(info) { }
    Histogram(Sequence<K>* values, string info) {
        dict = VariableCountDict(values);
        table_info = info;
    }

    IDictionary<K,int>* GetDict() { return dict; }

    string GetInfo() { return table_info; }



};

template <typename K>
class Histogram<Interval<K>*> {
private:
    IDictionary<string,Interval<K>*>* dict;
    string table_info;
public:

    Histogram(IDictionary<string,Interval<K>*>* dict, string info) : dict(dict), table_info(info) { }

    Histogram(Sequence<K>* values, string info,  int interval_count, Sequence<K>* seps=NULL) {
        dict = RangeCountDict(values, interval_count, seps);
        table_info = info;
    }


    IDictionary<string,float>* AverageDict(){
        Sequence<string>* keys = dict->GetKeys();
        IDictionary<string ,float>* dict_avg = new DictionarySequence<string ,float>(10);
        for (int i=0; i<keys->GetSize(); i++) {
            dict_avg->Add(keys->Get(i), this->dict->Get(keys->Get(i))->GetAverage());
        }

        //Histogram<K,float>* avg = new Histogram<K,float>(dict, "average " + this->GetInfo());

        return dict_avg;
    };

    IDictionary<string,K>* SumDict() {
        Sequence<string> *keys = dict->GetKeys();
        IDictionary<string, K> *dict_sum = new DictionarySequence<string, K>(10);
        for (int i = 0; i < keys->GetSize(); i++) {
            dict_sum->Add(keys->Get(i), this->dict->Get(keys->Get(i))->GetSum());
        }

        //Histogram<K, V> *sum = new Histogram<K, V>(dict, "sum " + this > GetInfo());

        return dict_sum;
    }

    IDictionary<string,int>* CountDict() {
        Sequence<string>* keys = dict->GetKeys();
        IDictionary<string,int>* dict_cnt = new DictionarySequence<string,int>(10);
        for (int i=0; i<keys->GetSize(); i++) {
            dict_cnt->Add(keys->Get(i), this->dict->Get(keys->Get(i))->GetCount());
        }

        //Histogram<K,int>* count = new Histogram<K,int>(dict, "count " + this->GetInfo());


        return dict_cnt;
    }

    IDictionary<string,Interval<K>*>* GetDict() { return dict; }

    string GetInfo() { return table_info; }


};



template <typename V>
IDictionary<V, int>* VariableCountDict(Sequence<V>* list) {
    IDictionary<V,int>* dict = new DictionarySequence<V,int>(10);
    for (int i =0; i<list->GetSize(); i++) {
        V key = list->Get(i);
        if (dict->ContainsKey(key)) {
            dict->Change(key, dict->Get(key) + 1 );
        }
        else {
            dict->Add(key, 1);
        }
    }

    return dict;

}


template <typename T>
IDictionary<string, Interval<T>*>* RangeCountDict(Sequence<T>* values, int interval_count, Sequence<T>* seps = NULL) {
    IDictionary<string,Interval<T>*>* dict = new DictionarySequence<string,Interval<T>*>(10);

    T max=values->Get(0);
    T min=values->Get(0);
    for (int i =1; i<values->GetSize(); i++) {
        T value = values->Get(i);
        if (value>max) {
            max = value;
        }
        if (value<min) {
            min = value;
        }
    }

    T diff = (max - min) / interval_count;
    if (diff == 0) {
        throw length_error("DIFF IS ZERO");
    }
    T start = min;
    for (int i=0; i<interval_count; i++) {
        T begin = start;
        T end;

        if (seps == NULL) {
            end = start + diff;
            if (i == interval_count - 1) {
                end = max;
            }
        }

        else {
            if (i == interval_count-1) {
                end = max;
            }
            else {
                end = seps->Get(i);
            }
        }
        Interval<T>* interval;
        if (i ==0) {
            interval = new Interval<T>(begin,end,true);
        }
        else {
            interval = new Interval<T>(begin,end,false);
        }

        string key;
        if (interval->IsFirst()) {
            key += "[";
        }
        else {
            key += "(";
        }
        key += to_string(begin) + " ; " + to_string(end) + "]";

        for (int j = 0; j < values->GetSize(); j++) {
            T item = values->Get(j);
            interval->Add(item);
        }
        dict->Add(key, interval);

        start = end;
    }

    return dict;
}




template <typename K, typename V>
void ShowHystogram(IDictionary<K,V>* dict, string info) {

    Sequence<V>* values = dict->GetValues();

    Sequence<K>* keys = dict->GetKeys();
    int max_len =0;
    for (int i =0; i<keys->GetSize(); i++) {
        K key = keys->Get(i);
        string str = to_string(key);
        if (str.length() > max_len) {
            max_len = str.length();
        }
    }
    V maxcount=values->Get(0);
    for (int i =1; i<values->GetSize(); i++) {
        V value = values->Get(i);
        if (value>maxcount) {
            maxcount = value;
        }
    }
    cout<<internal<<setw(40)<<info<<endl;
    cout << setw(max_len) << " ";
    cout<<" | ";
    cout<<right<<setw(20) << maxcount/2;
    cout<<right<<setw(20) << maxcount;
    cout<<endl;

    cout << setw(max_len) << " ";
    cout<<" | ";

    for (int i=0; i<40; i++) {
        cout<<"-";
    }
    cout<<endl;

    for (int i=0; i<values->GetSize(); i++) {
        cout << std::setw(max_len) << keys->Get(i);
        cout<<" | ";
        int count = values->Get(i)*40/maxcount;
        for (int j=0; j<count; j++) {
            cout<<static_cast<char>(254);
        }
        cout<<" "<<values->Get(i);
        cout<<endl;
    }

    cout << setw(max_len) << " ";
    cout<<" | ";

    for (int i=0; i<40; i++) {
        cout<<"-";
    }
    cout<<endl;
}




template <typename T>
void ShowHystogramIntervals(Histogram<Interval<T>*>* hystogramm, string type) {
    if (type == "count") {
        ShowHystogram(hystogramm->CountDict(), hystogramm->GetInfo()+" "+type);
    }
    if (type == "average") {
        ShowHystogram(hystogramm->AverageDict(), hystogramm->GetInfo()+" "+type);
    }
    if (type == "sum") {
        ShowHystogram(hystogramm->SumDict(), hystogramm->GetInfo()+" "+type);
    }
}


template<typename T, typename K>
void ChooseParameter(Sequence<K>* seq, IDictionary<string, T (K::*)()>* funcs) {
    while (true) {
        Sequence<string> *names = funcs->GetKeys();
        for (int i = 0; i < funcs->Count(); i++) {
            cout << i << " - " << names->Get(i) << endl;
        }
        cout<<"9 - Go back"<<endl;
        cout << "Your choice:";
        int type;
        cin >> type;
        if (type == 9) {
            return;
        }
        T(K::*variable)() = funcs->Get(names->Get(type));
        string info = names->Get(type);


        cout<<"Auto split 1/0: ";
        int auto_split;
        cin>>auto_split;
        Sequence<T>* seps = NULL;
        Sequence<T>* values =  SeqOfValues(seq, variable);
        Histogram<Interval<T>*>* histo;
        if (auto_split) {
            cout<<"Number of intervals: ";
            int intverval_cnt;
            cin>>intverval_cnt;
            histo = new Histogram<Interval<T>*>(values, info, intverval_cnt,NULL);
        }
        else {
            cout<<"Delims (ends with 0)";
            Sequence<int>* seps = new ArraySequence<int>();

            while (true) {
                int sep;
                cin>>sep;
                if (sep != 0) {
                    seps->Append(sep);
                }
                else{
                    break;
                }
            }


            histo = new Histogram<Interval<T>*>(values, info, seps->GetSize()+1,seps);
        }

        while (true) {
            cout<<"What stats to plot? sum  average or count  (0-exit)";
            string ch;
            cin>>ch;
            if (ch == "0") {
                break;
            }
            else {
                ShowHystogramIntervals(histo,ch);
            }
        }


    }
}


template<typename T, typename K>
void ChooseParameterCount(Sequence<K>* seq, IDictionary<string, T (K::*)()>* funcs) {
    while (true) {
        Sequence<string> *names = funcs->GetKeys();
        for (int i = 0; i < funcs->Count(); i++) {
            cout << i << " - " << names->Get(i) << endl;
        }
        cout << "9 - Go back" << endl;
        cout << "Your choice:";
        int type;
        cin >> type;
        if (type == 9) {
            return;
        }
        T(K::*variable)() = funcs->Get(names->Get(type));
        string info = names->Get(type);

        Histogram<T>* histo = new Histogram<T>(SeqOfValues(seq,variable),info);
        ShowHystogram(histo->GetDict(), histo->GetInfo());
    }
}





template <typename K>
void HistogramMenu(Sequence<K>* seq, IDictionary<string, string (K::*)()>* cnt_str = NULL,
                   IDictionary<string, int (K::*)()>* cnt_int = NULL,
                   IDictionary<string,float (K::*)()>* cnt_float = NULL) {
    while (true) {
        if (cnt_str != NULL) {
            cout << "1 - STRING" << endl;
        }

        if (cnt_int != NULL) {
            cout << "2 - INT" << endl;
        }
        if (cnt_float != NULL) {
            cout << "3 - FLOAT" << endl;
        }
        cout << "0 - Exit" << endl;
        cout << "Your choice?:";
        int type;
        cin >> type;
        if (type == 0) {
            return;
        }

        cout << "Intervals - 1 (only for numbers)  or  basic counts? - 0: ";
        int inter;
        cin >> inter;
        if (inter) {
            if (type == 2) {
                ChooseParameter<int, K>(seq, cnt_int);
            } else if (type == 3) {
                //ChooseParameter<float,T>(seq, cnt_float);
            }
        } else {
            if (type == 1) {
                ChooseParameterCount<string, K>(seq, cnt_str);
            } else if (type == 2) {
                ChooseParameterCount<int, K>(seq, cnt_int);
            } else if (type == 3) {
                //ChooseParameter<float,T>(seq, cnt_float);
            }
        }

    }
}










