/* Your code here! */
#include "dsets.h"

DisjointSets::DisjointSets(){

}

void DisjointSets::addelements(int num){
  for(int i=0; i<num; i++){
    sets.push_back(-1);
  }
}

int DisjointSets::find(int elem){
  if (sets[elem]<0){
    return elem;
  }
  else{
    return find(sets[elem]);
  }
}

void DisjointSets::setunion(int a, int b){
  int roota=find(a);
  int rootb=find(b);
  int sizea=size(a);
  int sizeb=size(b);
  if(roota==rootb)
  return;
  if(sizea>=sizeb)
  sets[rootb]=roota;
  else
  sets[roota]=rootb;
}

int DisjointSets::size(int elem){
  int root=find(elem);

  return count_offsprings(root)+1;
}

int DisjointSets::count_offsprings(int subroot){
  int numOfChildren=0;
  vector<int> children;
  for(size_t i=0; i<sets.size(); i++){
    if(sets[i]==subroot){
      numOfChildren++;
      int j=i;
      children.push_back(j);
    }
  }

  if(children.empty()) {return numOfChildren;}
//cout<<children[0]<<endl;
  for(int childi:children){
    int x=count_offsprings(childi);
    numOfChildren+=x;
  }
  return numOfChildren;
}

vector<int> DisjointSets::getsets(){
  return sets;
}




void DisjointSets::fastsetunion(int a, int b){
  if (findByRef(a)==findByRef(b)){
    return;
  }
  sets[findByRef(a)]=findByRef(b);
}

int DisjointSets::findparent(int index){
  return sets[index];
}

int DisjointSets::findByRef(int & elem){
  if (sets[elem]<0){
    return elem;
  }
  else{
    return find(sets[elem]);
  }
}
