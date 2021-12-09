#pragma once

#include "Histogram.h"
#include <string.h>
#include "ISorter.h"


class AlphabetPointer {


public:
    AlphabetPointer(const string str, int pageSize, bool inChars = false) {
        if (inChars) {
            storage = makeDictionary(pageDivideSymbols(str, pageSize));
        }
        else {
            storage = makeDictionary(pageDivideWords(str, pageSize));
        }


    }

    IDictionary<string, ISet<int>*>* GetStorage() {
        return storage;
    }



private:
    IDictionary<string, ISet<int> *> *storage = nullptr;

    static Sequence<string> *split(const string &str) {
        string word;
        Sequence<string> *result = new ListSequence<string>();

        for (int i = 0; i < str.length(); i++) {
            if (!(str[i] == ' ' && word.empty())) {
                if (str[i] != ' ') {
                    word.push_back(str[i]);
                    if (i == str.length() - 1) {
                        result->Append(word);
                    }
                } else {
                    result->Append(word);
                    word = "";
                }
            }
        }

        return result;
    }

    static Sequence<Sequence<string>*> *pageDivideWords(const string text, int pageSize) {
        int firstPageSize = pageSize / 2;
        int tenthPageSize = (pageSize * 3) / 4;
        int pageNumber = 0;
        Sequence<Sequence<string> *> *res = new ArraySequence<Sequence<string> *>();
        Sequence<string>* seq = split(text);

        int index = 0;
        int seqLength = seq->GetSize();
        while (seqLength > 0) {
            Sequence<string> *page = new ArraySequence<string>();

            int current_page_size;

            if (pageNumber == 0) { current_page_size = firstPageSize; }
            else if ((pageNumber + 1) % 10 == 0 ) { current_page_size = tenthPageSize; }
            else { current_page_size = pageSize;}

            if (seqLength < current_page_size) {
                for (int i = 0; i < seqLength; i++) {
                    page->Append(seq->Get(index));
                    index++;
                }
                seqLength = 0;
                pageNumber++;
            } else {
                seqLength -= current_page_size;
                for (int i = 0; i < current_page_size; i++) {
                    page->Append(seq->Get(index));
                    index++;
                }
            }

            res->Append(page);
            pageNumber++;

        }
        return res;
    }
    // разделяет список слов на страницы

    static Sequence<Sequence<string> *> *pageDivideSymbols(const string text_input, int pageSize) {
        int firstPageSize = pageSize / 2;
        int tenthPageSize = (pageSize * 3) / 4;
        int pageNumber = 0;

        int seqLengthInChars = text_input.length();

        string text = text_input ;

        Sequence<Sequence<string> *> *res = new ArraySequence<Sequence<string> *>();

        while (seqLengthInChars > 0) {
            Sequence<string> *seq;

            int current_page_size;

            if (pageNumber == 0) { current_page_size = firstPageSize; }
            else if ((pageNumber + 1) % 10 == 0 ) { current_page_size = tenthPageSize; }
            else { current_page_size = pageSize;}

            if (text.length() < current_page_size) {
                seq = split(text);
                pageNumber++;
                seqLengthInChars = 0;
            }
            else {
                if (text[current_page_size - 1] != ' ' && text[current_page_size] != ' ') {
                    int nearestSpace = current_page_size - 1;
                    while (text[nearestSpace] != ' ') {
                        nearestSpace--;
                    }
                    seqLengthInChars -= nearestSpace+1;
                    seq = split(text.substr(0, nearestSpace));
                    text = text.substr(nearestSpace + 1, text.length());
                }
                else if (text[current_page_size-1] == ' ') {
                    seqLengthInChars -= current_page_size;
                    seq = split(text.substr(0, current_page_size - 1));
                    text = text.substr(current_page_size, text.length());
                }
                else if (text[current_page_size - 1] != ' ' && text[current_page_size] == ' ') {
                    seqLengthInChars -= current_page_size+1;
                    seq = split(text.substr(0, current_page_size));
                    text = text.substr(current_page_size+1, text.length());

                }
                pageNumber++;
            }

            res->Append(seq);

        }

        return res;
    }

    static IDictionary<string, ISet<int> *> *makeDictionary(Sequence<Sequence<string> *> *dividedSeq) {
        IDictionary<string, ISet<int> *> *result = new DictionarySequence<string, ISet<int> *>(10);

        for (int i = 0; i < dividedSeq->GetSize(); i++) {
            Sequence<string> *page = dividedSeq->Get(i);
            for (int j = 0; j < page->GetSize(); j++) {
                string currentString = page->Get(j);

                if (result->ContainsKey(currentString)) {
                    ISet<int> *pages = result->Get(currentString);
                    pages->Insert(i);
                    result->Change(currentString, pages);


                } else {
                    ISet<int> *pages = new SetSequence<int>();
                    pages->Insert(i);
                    result->Add(currentString, pages);

                }
            }
        }


        return result;
    }
};














void PrintABP(AlphabetPointer alp) {
    IDictionary<string, ISet<int>*>* dict = alp.GetStorage();
    Sequence<Pair<string, ISet<int>*>>* pairs = new ArraySequence<Pair<string, ISet<int>*>>();
    Sequence<string>* keys = dict->GetKeys();
    Sequence<ISet<int>*> * values = dict->GetValues();
    for (int i =0; i<keys->GetSize(); i++) {
        Pair<string, ISet<int>*> pair = Pair<string, ISet<int>*>(keys->Get(i),values->Get(i));
        pairs->Append(pair);
    }
    ISorter<Pair<string,ISet<int>*>>* sorter = new QuickSorter<Pair<string, ISet<int>*>>;
    pairs = sorter->Sort(pairs, comp_pairs);

    for (int i = 0; i < pairs->GetSize(); i++) {
        string word = pairs->Get(i).GetFirst();
        ISet<int> *pages = pairs->Get(i).GetSecond();

        std::cout<< i+1 <<") " << word<<" ";
        string numbers;
        for (int j = 0; j < pages->Count(); j++) {
            numbers += to_string(pages->Get(j)+1);
            if (j != pages->Count() - 1) {
                numbers+= ", ";
            }
        }
        for (int k = 0; k<60-word.length()- to_string(i+1).length()-numbers.length(); k++) {
            cout<<".";
        }
        cout<<" "<<numbers<<endl;
        //cout<<setw(40-word.length()- to_string(i+1).length())<<right<<numbers<<endl;
    }
}

string get_text_from_file() {
    string text;
    ifstream myfile (R"(../text.txt)");
    while (myfile.good()) {
        char c = myfile.get();
        text += c;
    }
    myfile.close();

    return text;
}

void APMenu() {
    cout<<"Input page size: ";
    int pagesize;
    cin>>pagesize;
    cout<<"Page size in"<<endl;
    cout<<"1 - chars"<<endl;
    cout<<"0 - words"<<endl;
    int choice;
    cin>>choice;
    AlphabetPointer alp = AlphabetPointer(get_text_from_file(), pagesize, choice);
    PrintABP(alp);

}