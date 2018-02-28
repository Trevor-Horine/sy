/*this is the node class
 *Trevor Horine
 *12/11/2017
 */
#include "node.h"
node::node(){
  right = NULL;
  left = NULL;
  next = NULL;
  prev = NULL;
}
//destructor
node::~node(){
  delete dataptr;
  left = NULL;
  right = NULL;
  next = NULL;
  prev = NULL;
}
//method to set value
void node::setvalue(char* newdata){
  dataptr = newdata;
}
//method to get value
char* node::getvalue(){
  return dataptr;
}
//method to set presedence
void node::setpres(int newpres){
  pres = newpres;
}
//method to get presedence
int node::getpres(){
  return pres;
}
//mehtod to set node
void node::setleft(node* newnext){
  left = newnext;
}
//mehtod to get next
node* node::getleft(){
  return left;
}
//method to set last
void node::setright(node* newnext){
  right = newnext;
}
//method to get last
node* node::getright(){
  return right;
}
// method to set next
void node::setnext(node* newnext){
  next = newnext;
}
//method to getnext
node* node::getnext(){
  return next;
}
//mehtod to set previous
void node::setprev(node* newnext){
  prev = newnext;
}
//method to get previous
node* node::getprev(){
  return prev;
}
