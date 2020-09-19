#include<bits/stdc++.h>
using namespace std;

struct node{
  int key;
  node *next,*prev;
};

node *nil; //　番兵

void init(){
  nil = (node *)malloc(sizeof(node));
  cout << nil->key << endl;
  nil->next = nil;
  nil->prev = nil;
}

void print(){
  node *cur = nil->next;
  while(cur != nil){
    cout << cur->key << " ";
    cur = cur->next;
  }
  cout << endl;
}

void insert(int key){
  node *x = (node *)malloc(sizeof(node));
  x->key = key;
  x->next = nil->next; // nil-ロ-ロ-...-nil ↓
  nil->next->prev = x; // nil-x-ロ-ロ-...-nil
  nil->next = x;
  x->prev = nil;
}

signed main(){

  int n; cin >> n;
  init();
  for(int i = 0; i < n; i++){
    int key; cin >> key;
    insert(key);
  }
  print();

  return 0;
}
