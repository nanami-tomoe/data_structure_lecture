#include <iostream>
#include <cstdlib>
using namespace std;
typedef int Data;
const int NONE = 0; // empty node
const int ROOT = 1;
const int TREE_HEIGHT = 8;
const int TREE_SIZE = 1 << TREE_HEIGHT;
void Error(string s) {cerr << s; exit(-1);}

class ArrayTree{
  Data data[TREE_SIZE];
  int NumNode(int pos){
    if(IsNone(pos)) return 0;
    int left = pos*2, right = pos*2 + 1;
    return 1 + NumNode(left) + NumNode(right);
  }
  int NumLeaf(int pos){
    if(IsNone(pos)) return 0;
    if(IsLeaf(pos)) return 1;
    int left = pos*2, right = pos*2 + 1;
    return NumLeaf(left) + NumLeaf(right);
  }
  int Height(int pos){
    if(IsNone(pos)) return 0;
    int left = pos*2, right = pos*2 + 1;
    return 1 + max(Height(left), Height(right));
  }
public:
  ArrayTree(){
    for(int pos = 1; pos < TREE_SIZE; pos++)
      data[pos] = NONE;
  } // constructor
  void InsertPos(int pos, Data d){
    if(pos <= 0 || pos >= TREE_SIZE || (pos != ROOT && IsNone(pos/2)))
      Error("Cannot insert");
    data[pos] = d;
  }
  Data DeletePos(int pos){
    if(IsNone(pos) || ! IsLeaf(pos))
      Error("Cannot delete");
    Data d = data[pos]; data[pos] = NONE;
    return d;
  }
  Data PeekPos(int pos){
    if(IsNone(pos)) Error("Cannot pook");
    return data[pos];
  }
  int NumNode() {return NumNode(ROOT);}
  int NumLeaf() {return NumLeaf(ROOT);}
  int Height() {return Height(ROOT);}
  void PrintTree(){
    for(int pos = 1; pos < TREE_SIZE; pos ++){
      if(IsNone(pos)) continue;
      int left = pos*2, right = pos*2 + 1;
      cout << "node " << pos << ": value = " << data[pos] << ", # of children = " << ! IsNone(left) + ! IsNone(right) << endl;
    }
  }
  void PrintLevelOrder(){
    int numNode = NumNode();
    for(int level = 1; numNode > 0; level++){
      cout << "Level " << level << ": ";
      int pos, length = 1 << (level-1);
      for(pos = length; pos < 2*length; pos++){
        if(IsNone(pos) == false){
          cout << data[pos] << " ";
          numNode--;
        }
      }
      cout << endl;
    }
  }
  bool IsNone(int pos){
    return pos <= 0 || pos >= TREE_SIZE || data[pos] == NONE;
  }
  bool IsLeaf(int pos){
    if(IsNone(pos)) return false;
    int left = pos*2, right = pos*2 + 1;
    return IsNone(left) && IsNone(right);
  }
};

