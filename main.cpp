/* this is shunting yard and can print infix, postfix, and prefix
 *Trevor Horine
 *2/21/18
 */
#include <iostream>
#include <cstring>
#include "node.h"

using namespace std;
//methods
void maketree(node*, node*, node* &root);
void split(node*, char*, int);
void remspace(char*, int);
void print(node*);
void next(node*);
void lprint(node*);
void post(node*, node*, node*);
void left(node*, node* &last);
void pre(node*, node*, node* &prehead, node*);
void inf(node*, node*);
//main
int main(){
  //varables
  node* head = new node();
  node* phead = new node();
  node* shead = new node();
  node* prehead = new node();
  node* inhead = new node();
  node* last = new node();
  node* root = new node();
  //ask for a expression with spaces
    cout << "input a mathmatical expresion with a space betwen each term and operatior." << endl;
    char* infix = new char[50];
    memset(infix, 0, sizeof(infix));
    //read in expression
    cin.getline(infix, 50);
    int te = strlen(infix);
    //cout << te << endl;
    for (int i = te; i<50; i++){
    infix[i] = ' ';
    }
    //cout << infix << endl;
    //create nodes and remove spaces
    split(head, infix, te);
    //cout << "list" << endl;
    //print(head);
    //convert to postfix
    post(head, phead, shead);
    cout << "postfix" << endl;
    //print postfix
    print(phead);
    cout << endl;
    //left(phead, last);
    //cout << "backwards list" << endl;
    //lprint(last);
    //cout << endl;
    //cout << "endlist" << endl;
    shead = new node();
    // make expression tree
    maketree(phead, shead, root);
    // ask what form user wants
    cout << "do you want infix, postfix, or prefix?" << endl;
    char* in = new char[50];
    cin >> in;
    //get and print infix from tree
    if (strcmp(in, "infix") == 0){
      inf(root, inhead);
    }
    //get and print postfix from the tree
    else if(strcmp(in, "postfix") == 0){
      print(phead);
      cout << endl;
    }
    // get and print prefix from tree
    else if(strcmp(in, "prefix") == 0){
      pre(root, prehead, prehead, root);
      //cout << prehead -> getvalue() << endl;
      //cout << "prefix" << endl;
      while(prehead -> getleft() != NULL){
	prehead = prehead -> getleft();
      }
      print(prehead);
      cout << endl;
    }
}
//method to make nodes and remove spaces and assigh presedence
void split(node* n, char* infix, int l){
  char* temp = new char[50];
  int e = 0;
  memset(temp, 0, sizeof(temp));
  node* current = n;
  for (int i = 0; i < 50; i++){
    if(isspace(infix[0])){
      break;
    }
    else if (isgraph(infix[i])){
      temp[i] = infix[i];
      e++;
      //cout << temp << endl;
    }
    else if(isspace(infix[i])){
      e++;
      //cout << "s" << temp << endl;
      current -> setvalue(temp);
      //setp(temp, current);
      //set presedance
      if((temp[0] == '-') || (temp[0] == '+')){
        current -> setpres(2);
      }
      if((temp[0] == '*') || (temp[0] == '/')){
        current -> setpres(3);
      }
      if(temp[0] == '^'){
	current -> setpres(4);
      }
      if(isdigit(temp[0])){
	current -> setpres(1);
      }
      if(!isspace(infix[i+1])){
	current -> setright(new node());
      }
      for (int j = 0; j < (l); j++){
	infix[j] = infix[j+e];
      }
      split(current -> getright(), infix, l);
    }
  }
}
// method to make postfix form
void post(node* current, node* pcurrent, node* scurrent){
  if(current != NULL){
    if(isdigit((current -> getvalue())[0])){
      pcurrent -> setvalue(current -> getvalue());
      pcurrent -> setright(new node());
      post(current -> getright(), pcurrent -> getright(), scurrent);
    }
    else if(((current -> getvalue()[0]) == '(') || ((current -> getvalue()[0]) == '^')){
      node* g = new node();
      g-> setright(scurrent);
      g -> setvalue(current -> getvalue());
      g -> setpres(current -> getpres());
      post(current -> getright(), pcurrent, g);
    }
    else if((current -> getvalue()[0]) == ')'){
      //pop everything untill ( off stack and get rid of (
      while((scurrent -> getvalue()[0]) != '('){
	pcurrent -> setvalue(scurrent -> getvalue());
	pcurrent -> setright(new node());
	pcurrent = pcurrent -> getright();
	scurrent = scurrent -> getright();
	if((scurrent -> getvalue()[0]) == '('){
	  scurrent = scurrent -> getright();
	  break;
	}
	//scurrent = scurrent -> getright();
      }
      post(current -> getright(), pcurrent, scurrent);
    }
    else if(ispunct((current -> getvalue())[0])){
      if(scurrent -> getvalue() == NULL){
	scurrent -> setvalue(current-> getvalue());
	scurrent -> setpres(current -> getpres());
	post(current -> getright(), pcurrent, scurrent);
      }
      else{
	node* t = new node();
	node* u = new node();
	t -> setright(scurrent);
	if(scurrent -> getpres() < current -> getpres()){
	  t -> setvalue(current -> getvalue());
	  t -> setpres(current-> getpres());
	  post(current -> getright(), pcurrent, t);
	}
	else{
	  //if(scurrent != NULL){
	  while(scurrent -> getpres() >= current -> getpres()){
	    //if presedence of current is less or equal pop till not true or till stack empty
	    if(scurrent == NULL){
	      scurrent = new node();
		scurrent = current;
		cout << scurrent -> getpres() << endl; 
	    }
	    //pcurrent = pcurrent -> getright();
            //scurrent = scurrent -> getright();
	    pcurrent -> setvalue(scurrent -> getvalue());
	    pcurrent -> setright(new node());
	    pcurrent = pcurrent -> getright();
            scurrent = scurrent -> getright();
	    if(scurrent == NULL){
	      u -> setvalue(current -> getvalue());
	      u -> setpres(current -> getpres());
	      break;
	    }
	    if (scurrent -> getpres() < current -> getpres()){
	      u -> setright(scurrent);
	      u -> setvalue(current -> getvalue());
	      u -> setpres(current -> getpres());
	      //pcurrent = pcurrent -> getright();
	      break;
	    }
	    //pcurrent = pcurrent -> getright();
            //scurrent = scurrent -> getright();
	  }
	  post(current -> getright(), pcurrent, u);
	  //}
	}
      }
    }
  }
  else{
    while(scurrent != NULL){
      pcurrent -> setvalue(scurrent -> getvalue());
      if(scurrent -> getright() != NULL){
	pcurrent -> setright(new node());
	pcurrent = pcurrent -> getright();
      }
      scurrent = scurrent -> getright();
    }
  }
}
// method to make tree
void maketree(node* pcurrent, node* scurrent, node* &root){
  if (pcurrent != NULL){
    //isdigit put on stack
    if (isdigit((pcurrent -> getvalue()[0]))){
      node* h = new node();
      h -> setnext(scurrent);
      h -> setvalue(pcurrent -> getvalue());
      maketree(pcurrent -> getright(), h, root);
    }
    else{
      // is not digit set right and left to first 2 things on stack
      node* p = new node();
      p -> setvalue(pcurrent-> getvalue());
      p -> setright(scurrent);
      p -> getright() -> setprev(p);
      scurrent = scurrent -> getnext();
      p -> setleft(scurrent);
      p -> getleft() -> setprev(p);
      scurrent = scurrent -> getnext();
      p -> setnext(scurrent);
      maketree(pcurrent -> getright(), p, root);
    }
  }
  else{
    root = scurrent;
  }
}

//print ll
void print(node* next){
  //cout << "test" << endl;
  if(next != NULL){
    //cout << "test2 " << next -> getright() << endl;
    cout << next -> getvalue();
    //cout << "test3" << endl;
    if(next -> getright() != NULL){
      print(next -> getright());
    }
  }
}

void next(node* next){
  //cout << "test" << endl;
  if(next != NULL){
    //cout << "test2 " << next -> getright() << endl;
    cout << next -> getvalue();
    //cout << "test3" << endl;
    if(next -> getnext() != NULL){
      print(next -> getnext());
    }
  }
}

//link list backwards
void left(node* current, node* &last){
  node* l = current;
  while(current -> getright() != NULL){
    l = current;
    current = current -> getright();
    current -> setleft(l);
  }
  last = current;
}

//print ll backwards
void lprint(node* next){
  //cout << "test" << endl;
  if(next != NULL){
    //cout << "test2 " << next -> getright() << endl;
    cout << next -> getvalue();
    //cout << "test3" << endl;
    if(next -> getleft() != NULL){
      lprint(next -> getleft());
    }
  }
}
//create prefix from tree
void pre(node* treecurrent, node* precurrent, node* &prehead, node* root){
  if (treecurrent -> getleft() != NULL){
    if (precurrent -> getvalue() != NULL){
      precurrent -> getright()-> setleft (precurrent);
      precurrent = precurrent -> getright();
    }
    precurrent -> setvalue(treecurrent -> getvalue());
    treecurrent = treecurrent->getleft();
    precurrent -> setright(new node());
  }
  else{
    precurrent -> getright()-> setleft (precurrent);
    precurrent = precurrent -> getright();
    precurrent -> setvalue (treecurrent -> getvalue());
    treecurrent = treecurrent -> getprev();
    precurrent -> setright(new node());
    if (treecurrent -> getright() -> getvalue() == precurrent -> getvalue()){
      treecurrent = treecurrent -> getprev() -> getprev();
    }
    treecurrent = treecurrent -> getright();
  }
  if (treecurrent != root -> getright()){
    pre(treecurrent, precurrent, prehead, root);
  }
  else{
    precurrent -> getright()-> setleft (precurrent);
    precurrent = precurrent -> getright();
    precurrent -> setvalue(treecurrent -> getvalue());
    prehead = precurrent;
  }
}
//create and print infix
void inf(node* treecurrent, node*incurrent){
  if (treecurrent != NULL){
    cout << "("; 
    inf(treecurrent->getleft(), incurrent); 
    cout << "("; 
    cout << *(treecurrent->getvalue()); 
    cout << ")"; 
    inf(treecurrent->getright(), incurrent); 
    cout << ")"; 
  } 
}
