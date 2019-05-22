#pragma once
#include <vector>
#include <iostream>
using namespace std;


class DisjointSets{
  private:
    vector<int> sets;
    int count_offsprings(int subroot);



  public:
    DisjointSets();
    void addelements(int elem);
    int find(int elem);//find root
    void setunion(int a, int b);
    int size(int elem);
    vector<int> getsets();


    void fastsetunion(int a, int b);
    int findparent(int index);
    int findByRef(int & elem);

};
