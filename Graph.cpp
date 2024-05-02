#include "Graph.h"

using namespace std;

bool account::operator<(const account &rhs){
  if(inDegree < rhs.inDegree) {
    return true;
  }
   else if(inDegree == rhs.inDegree) {
    return name > rhs.name;
  }else{
  return false;
  }
}