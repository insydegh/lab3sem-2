
#include "AlphabetPointer.h"
#include "Printer.h"

int main() {

    IDictionary<string,int(Person::*)()>* countable = new DictionarySequence<string, int(Person::*)()>(2);
    countable->Add("age", age);
    countable->Add("income", inc);
    countable->Add("ID", id);


    IDictionary<string, string(Person::*)()>* categorical = new DictionarySequence<string, string(Person::*)()>(3);
    categorical->Add("name", name);
    categorical->Add("surname", sur);
    categorical->Add("region", reg);

    Sequence<Person>* list = ParseFile();

    cout<<"Histograms - 1 , AlphabetPoiner - 0 "<<endl;
    int c;
    cin>>c;
    if (c==1) {
        HistogramMenu<Person>(list, categorical, countable, NULL) ;
    }
    else {

        APMenu();
    }





}