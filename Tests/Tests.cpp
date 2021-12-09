//
// Created by fokus on 26.11.2021.
//
#define UNIT_TESTING
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "../AlphabetPointer.h"


AVL<int> maketree(){
    AVL<int> tree = AVL<int>();
    tree.insert(50);
    tree.insert(55);
    tree.insert(45);
    tree.insert(77);
    tree.insert(48);
    tree.insert(53);
    tree.insert(90);
    tree.insert(100);
    tree.insert(110);
    return tree;
}

IDictionary<string,int>* makeDictSeq(){
    IDictionary<string,int>* dict = new DictionarySequence<string,int>(10);
    dict->Add("zebra", 1);
    dict->Add("hippo", 2);
    dict->Add("cat", 3);
    dict->Add("dog", 4);
    dict->Add("parrot", 5);
    return dict;
}


IDictionary<string,int>* makeDictTree(){
    IDictionary<string,int>* dict = new DictionaryTree<string,int>(10);
    dict->Add("zebra", 1);
    dict->Add("hippo", 2);
    dict->Add("cat", 3);
    dict->Add("dog", 4);
    dict->Add("parrot", 5);
    return dict;
}

ISet<int>* makeSetSeq(){
    ISet<int>* set = new SetSequence<int>();
    set->Insert(1);
    set->Insert(2);
    set->Insert(3);
    set->Insert(4);
    set->Insert(5);
    return set;
}

ISet<int>* makeSetTree(){
    ISet<int>* set = new SetTree<int>();
    set->Insert(1);
    set->Insert(2);
    set->Insert(3);
    set->Insert(4);
    set->Insert(5);
    return set;
}


TEST_CASE("AVL") {


    SECTION("ADD") {
       AVL<int> tree = maketree();

        REQUIRE(tree.getRoot()->key==50);
        REQUIRE(tree.getRoot()->rightChild-> key==90);
        REQUIRE(tree.getRoot()->leftChild->key==45);
        REQUIRE(tree.getRoot()->rightChild->rightChild->key==100);
        REQUIRE(tree.getRoot()->rightChild->leftChild->key==55);
        REQUIRE(tree.IsBalanced()==1);

        tree.insert(60);


        REQUIRE(tree.IsBalanced()==1);
    }

    SECTION("REMOVE") {
        AVL<int> tree = maketree();
        tree.deleteKey(55);

        REQUIRE(tree.getRoot()->rightChild->key==90);
        REQUIRE(tree.getRoot()->rightChild->leftChild->key==77);
        REQUIRE(tree.IsBalanced()==1);
    }

    SECTION("FIND") {
        AVL<int> tree = maketree();
        REQUIRE(tree.search(100)->key==100);
        REQUIRE(tree.search(90)->key==90);
        REQUIRE(tree.search(77)->key==77);
        REQUIRE(tree.search(45)->key==45);
    }

    SECTION("THREADING AND TO STRING") {
        AVL<int> tree = maketree();
        SECTION("NLR") {
            REQUIRE(tree.toString("NLR") == "50 45 48 90 55 53 77 100 110");
        }
        SECTION("NRL") {
            REQUIRE(tree.toString("NRL") == "50 90 100 110 55 77 53 45 48");
        }
        SECTION("RNL") {
            REQUIRE(tree.toString("RNL") == "110 100 90 77 55 53 50 48 45");
        }
        SECTION("RLN") {
            REQUIRE(tree.toString("RLN") == "110 100 77 53 55 90 48 45 50");
        }
        SECTION("LNR") {
            REQUIRE(tree.toString("LNR") == "45 48 50 53 55 77 90 100 110");
        }
        SECTION("LRN") {
            REQUIRE(tree.toString("LRN") == "48 45 53 77 55 110 100 90 50");
        }
    }

}


TEST_CASE ("DICTIONARY SEQUENCE") {
    SECTION("CONTAINS KEY") {
        IDictionary<string,int>* dict = makeDictSeq();
        REQUIRE(dict->ContainsKey("zebra")==1);
        REQUIRE(dict->ContainsKey("cat")==1);
        REQUIRE(dict->ContainsKey("dog")==1);
        REQUIRE(dict->ContainsKey("bebra")==0);

    }
    SECTION("GET") {
        IDictionary<string,int>* dict = makeDictSeq();
        REQUIRE(dict->Get("zebra")==1);
        REQUIRE(dict->Get("hippo")==2);
        REQUIRE(dict->Get("cat")==3);
        REQUIRE(dict->Get("dog")==4);
        REQUIRE(dict->Get("parrot")==5);

    }
    SECTION("ADD") {

   //  "zebra", 1
   //  "hippo", 2
    // "cat", 3
    // "dog", 4
    // "parrot", 5

        IDictionary<string,int>* dict = makeDictSeq();
        dict->Add("cat",8);
        REQUIRE(dict->Get("cat")==3);
    }


    SECTION("REMOVE") {
        IDictionary<string,int>* dict = makeDictSeq();
        dict->Remove("cat");
        REQUIRE(dict->ContainsKey("cat")==false);
    }

    SECTION("CHANGE") {
        IDictionary<string,int>* dict = makeDictSeq();
        dict->Change("cat",5);
        REQUIRE(dict->Get("cat")==5);
    }

    SECTION("GET KEYS") {
        IDictionary<string,int>* dict = makeDictSeq();
        Sequence<string>* keys = dict->GetKeys();
        REQUIRE(keys->Get(0)=="zebra");
        REQUIRE(keys->Get(1)=="hippo");
        REQUIRE(keys->Get(2)=="cat");
        REQUIRE(keys->Get(3)=="dog");
        REQUIRE(keys->Get(4)=="parrot");

    }

    SECTION("GET VALUES") {
        IDictionary<string,int>* dict = makeDictSeq();
        Sequence<int>* keys = dict->GetValues();
        REQUIRE(keys->Get(0)==1);
        REQUIRE(keys->Get(1)==2);
        REQUIRE(keys->Get(2)==3);
        REQUIRE(keys->Get(3)==4);
        REQUIRE(keys->Get(4)==5);

    }
}


TEST_CASE ("DICTIONARY TREE") {
    SECTION("CONTAINS KEY") {
        IDictionary<string,int>* dict = makeDictTree();
        REQUIRE(dict->ContainsKey("zebra")==1);
        REQUIRE(dict->ContainsKey("cat")==1);
        REQUIRE(dict->ContainsKey("dog")==1);
        REQUIRE(dict->ContainsKey("bebra")==0);

    }
    SECTION("GET") {
        IDictionary<string,int>* dict = makeDictTree();
        REQUIRE(dict->Get("zebra")==1);
        REQUIRE(dict->Get("hippo")==2);
        REQUIRE(dict->Get("cat")==3);
        REQUIRE(dict->Get("dog")==4);
        REQUIRE(dict->Get("parrot")==5);

    }
    SECTION("ADD") {

        IDictionary<string,int>* dict = makeDictTree();
        dict->Add("cat",8);
        REQUIRE(dict->Get("cat")==3);
    }


    SECTION("REMOVE") {
        IDictionary<string,int>* dict = makeDictTree();
        dict->Remove("cat");
        REQUIRE(dict->ContainsKey("cat")==false);
    }

    SECTION("CHANGE") {
        IDictionary<string,int>* dict = makeDictTree();
        dict->Change("cat",5);
        REQUIRE(dict->Get("cat")==5);
    }

    SECTION("GET KEYS") {
        IDictionary<string,int>* dict = makeDictTree();
        Sequence<string>* keys = dict->GetKeys();
        REQUIRE(keys->Get(0)=="cat");
        REQUIRE(keys->Get(1)=="dog");
        REQUIRE(keys->Get(2)=="hippo");
        REQUIRE(keys->Get(3)=="parrot");
        REQUIRE(keys->Get(4)=="zebra");

    }

    SECTION("GET VALUES") {

        IDictionary<string,int>* dict = makeDictTree();
        Sequence<int>* keys = dict->GetValues();
        REQUIRE(keys->Get(0)==3);
        REQUIRE(keys->Get(1)==4);
        REQUIRE(keys->Get(2)==2);
        REQUIRE(keys->Get(3)==5);
        REQUIRE(keys->Get(4)==1);

    }
}

TEST_CASE("SET SEQUENCE") {
    SECTION("Get"){
        ISet<int>* set = makeSetSeq();
        set->Insert(1);
        REQUIRE(set->Get(0)==1);
        REQUIRE(set->Get(1)==2);
        REQUIRE(set->Get(2)==3);


    }
    SECTION("Insert"){
        ISet<int>* set = makeSetSeq();
        set->Insert(1);
        REQUIRE(set->Count()==5);
        set->Insert(6);
        REQUIRE(set->Count()==6);
        REQUIRE(set->Get(5)==6);
    }
    SECTION("Remove") {
        ISet<int>* set = makeSetSeq();
        set->Remove(1);
        REQUIRE(set->Count()==4);
        REQUIRE(set->Get(0)==2);
    }

    SECTION("COUNT") {
        ISet<int>* set = makeSetSeq();
        REQUIRE(set->Count()==5);
    }

}


TEST_CASE("SET TREE") {
    SECTION("Get"){
        ISet<int>* set = makeSetTree();
        set->Insert(1);
        REQUIRE(set->Get(0)==1);
        REQUIRE(set->Get(1)==2);
        REQUIRE(set->Get(2)==3);


    }
    SECTION("Insert"){
        ISet<int>* set = makeSetTree();
        set->Insert(1);
        REQUIRE(set->Count()==5);
        set->Insert(6);
        REQUIRE(set->Count()==6);
        REQUIRE(set->Get(5)==6);
    }
    SECTION("Remove") {
        ISet<int>* set = makeSetTree();
        set->Remove(1);
        REQUIRE(set->Count()==4);
        REQUIRE(set->Get(0)==2);
    }
    SECTION("COUNT") {
        ISet<int>* set = makeSetTree();
        REQUIRE(set->Count()==5);
    }

}



/*


    SECTION("GET SUB TREE") {
        BinaryTree<int> tree = maketree();
        BinaryTree<int>* tree1 = tree.GetSubTree(55);
        REQUIRE(tree1->GiveRoot()->value==55);
        REQUIRE(tree1->GiveRoot()->right->value==77);
        REQUIRE(tree1->GiveRoot()->left->value==53);
    }

    SECTION("FIND SUB_TREE") {

        BinaryTree<int> tree = maketree();
        BinaryTree<int>* tree1 = tree.GetSubTree(55);
        BinaryTree<int>* tree2 = tree.GetSubTree(55);
        tree2->Add(44);
        REQUIRE(tree.IsSubTree(tree1) == 1);
        REQUIRE(tree.IsSubTree(tree2) == 0);
    }
*/
//printTree(tree.)