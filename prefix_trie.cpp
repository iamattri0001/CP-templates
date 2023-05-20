#include <bits/stdc++.h> 
class Node{
    int end, pre;
    Node *links[26];
    
    public:
        Node(){
            pre = end = 0;
            for(int i=0; i<26; i++)
                links[i] = nullptr;
        }
        
        void incPre(){
            pre++;
        }
        void decPre(){
            pre--;
        }
        int getPre(){
            return pre;
        }

        void incEnd(){
            end++;
        }
        void decEnd(){
            end--;
        }
        int getEnd(){
            return end;
        }

        Node* getNode(char ch){
            return links[ch-'a'];
        }

        void setNode(char ch, Node *node){
            links[ch-'a'] = node;
        }
};

class Trie{
    Node *root;
    public:

    Trie(){
        root = new Node();
    }

    void insert(string &word){
        Node *node = root;
        for(char ch: word){
            if(node->getNode(ch) == nullptr)
                node->setNode(ch, new Node());
                
            node = node->getNode(ch);
            node->incPre();
        }
        node->incEnd();
    }

    int countWordsEqualTo(string &word){
        Node *node = root;
        for(char ch: word){
            if(node->getNode(ch) == nullptr)
                return 0;
            node = node->getNode(ch);
        }
        return node->getEnd();
    }

    int countWordsStartingWith(string &word){
        Node *node = root;
        for(char ch: word){
            if(node->getNode(ch) == nullptr)
                return 0;
            node = node->getNode(ch);
        }
        return node->getPre();
    }

    void erase(string &word){
        if(countWordsEqualTo(word) == 0)
           return;
        Node *node = root;
        for(char ch: word){
            node = node->getNode(ch);
            node->decPre();
        }
        node->decEnd();
    }
};
