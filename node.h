/*This is the header for the node class
 *Trevor Horine
 *12/11/2017
 */
#ifndef NODE_H
#define NODE_H
#include <iostream>
#include <cstring>

using namespace std;

class node{
 public:
  //methods
  node();
  ~node();
  void setvalue(char*);
  char* getvalue();
  void setpres(int);
  int getpres();
  void setleft(node*);
  node* getleft();
  void setright(node*);
  node* getright();
  void setnext(node*);
  node* getnext();
  void setprev(node*);
  node* getprev();
 private:
  //varables
  char* dataptr;
  int pres;
  node* left;
  node* right;
  node* next;
  node* prev;
};
#endif
