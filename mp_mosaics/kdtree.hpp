/**
 * @file kdtree.cpp
 * Implementation of KDTree class.
 */

#include <utility>
#include <algorithm>

using namespace std;

template <int Dim>
bool KDTree<Dim>::smallerDimVal(const Point<Dim>& first,
                                const Point<Dim>& second, int curDim) const
{
    /**
     * @todo Implement this function!
     */
     if(first[curDim]<second[curDim]){
       return true;
     }
     if(first[curDim]>second[curDim]){
       return false;
     }

     return (first<second);
}

template <int Dim>
bool KDTree<Dim>::shouldReplace(const Point<Dim>& target,
                                const Point<Dim>& currentBest,
                                const Point<Dim>& potential) const
{
    /**
     * @todo Implement this function!
     */
     int tar_cur=0;//squared distance from target to currentBest
     int tar_po=0;//squared distance from target to potential
     for(int i=0; i<Dim; i++){
       tar_cur+=(target[i]-currentBest[i])*(target[i]-currentBest[i]);
       tar_po+=(target[i]-potential[i])*(target[i]-potential[i]);
     }
     if(tar_cur<tar_po){  return false;  }
     if(tar_cur>tar_po){  return true;  }
     return potential<currentBest;
}




//helper function
//return true if potential has smaller or equal distance to target as currentBest
template <int Dim>
bool KDTree<Dim>::distance_check_only(const Point<Dim>& target,
                                const Point<Dim>& currentBest,
                                const Point<Dim>& potential) const
{
     int tar_cur=0;//squared distance from target to currentBest
     int tar_po=0;//squared distance from target to potential
     for(int i=0; i<Dim; i++){
       tar_cur+=(target[i]-currentBest[i])*(target[i]-currentBest[i]);
       tar_po+=(target[i]-potential[i])*(target[i]-potential[i]);
     }
     if(tar_cur<tar_po){  return false;  }
     if(tar_cur>tar_po){  return true;  }
     return true;
}

template <int Dim>
KDTree<Dim>::KDTree(const vector<Point<Dim>>& newPoints)
{
    /**
     * @todo Implement this function!
     */

/*
     if(newPoints.empty()){
       root=NULL;
       size=0;
       return;
     }
     size=newPoints.size();
     vector<Point<Dim>> copy;
     copy=sort(newPoints);
     root=new KDTreeNode(copy[copy.size()/2]);
     build_KDTree(root,copy);
*/
     if(newPoints.empty()){
       root=NULL;
       size=0;
       return;
     }
     root=NULL;
     size=newPoints.size();
     vector<Point<Dim>> copy;
     copy.assign(newPoints.begin(),newPoints.end());
     int right=size-1;
     build_KDTree(root, copy, 0, right, 0/*dimension start from 0*/);


}

template <int Dim>
void KDTree<Dim>::build_KDTree(KDTreeNode*& subroot,  vector<Point<Dim>>& newPoints,
                                int left, int right, int curdim){
/*
  if(copy.empty()){
    return;
  }
  int midx=copy.size()/2;
//  root=new KDTreeNode(copy[midx]);//allocate root node
//  root->point=copy[midx];//point = middle of copy
  auto mid_itr=copy.begin()+midx;
  vector<Point<Dim>> left_vec;
  vector<Point<Dim>> right_vec;
  left_vec.assign(copy.begin(),mid_itr);
  right_vec.assign(mid_itr+1,copy.end());
  if(!left_vec.empty()){
    subroot->left=new KDTreeNode(left_vec[left_vec.size()/2]);

  }
  if(!right_vec.empty()){
    subroot->right=new KDTreeNode(right_vec[right_vec.size()/2]);
  }
  build_KDTree(subroot->left,left_vec);
  build_KDTree(subroot->right,right_vec);
*/


       if(left>right){
         subroot=NULL;
         return;
       }
       Point<Dim> kdNode;
       int median=(left+right)/2; //index of median

       kdNode=select(newPoints,left,right,median,curdim);


       subroot=new KDTreeNode(kdNode);
       curdim=(curdim+1)%Dim;
       build_KDTree(subroot->left, newPoints, left, median-1, curdim);

       build_KDTree(subroot->right, newPoints, median+1, right, curdim);



}
template <int Dim>
Point<Dim> KDTree<Dim>::select( vector<Point<Dim>>& newPoints,
                               int left, int right, int median, int curdim){


  if(left==right){
    return newPoints[left];
  }
  int pivotIndex=left;
  Point<Dim> pivot=newPoints[left];
  for(int i=left+1; i<=right; i++){

    if(smallerDimVal(newPoints[i],pivot,curdim)){ //pivot val is fixed

      Point<Dim> small=newPoints[i];
      size_t i1=i;
      if(i1==newPoints.size()-1){
        newPoints.pop_back();
      }

      else{
        newPoints.erase(newPoints.begin()+i);
      }


      newPoints.insert(newPoints.begin()+left,small);
      pivotIndex++;
    }
  }//all small at the left
  if (median==pivotIndex){
    return newPoints[median];
  }
  else if (median<pivotIndex){
    return select(newPoints, left, pivotIndex-1, median, curdim);
  }
  else{
    return select(newPoints, pivotIndex+1, right, median, curdim);
  }





}
/*template <int Dim>
vector<Point<Dim>> KDTree<Dim>::sort(const vector<Point<Dim>>& newPoints){
  Point<Dim> origin;
  vector<Point<Dim>> sorted_copy;
  vector<Point<Dim>> copy;
  copy.assign(newPoints.begin(),newPoints.end());//copy newpoints
  Point<Dim> small=copy[0];
//  size_t size=copy.size();
  size_t small_idx=0;
  while(!copy.empty()){
    for(size_t i=0; i<copy.size(); i++){
      if(copy[i]<small){
          small=copy[i];
          small_idx=i;

      }
    }
    //now small is the smallest point in Copy
    sorted_copy.push_back(small);

    if(small_idx==copy.size()-1){

      copy.pop_back();

    }
    else{
      copy.erase(copy.begin()+small_idx);
    }
    small=copy[0];
    small_idx=0;

  }
  return sorted_copy;

}*/




template <int Dim>
KDTree<Dim>::KDTree(const KDTree<Dim>& other) {
  /**
   * @todo Implement this function!
   */
   clear(root);
   copy(root, other.root);
}

template <int Dim>
void KDTree<Dim>::copy(KDTreeNode*& subroot, KDTreeNode* otherRoot){
  if(otherRoot!=NULL)
    subroot->point=otherRoot->point;
  if(otherRoot->left!=NULL){
    copy(subroot->left,otherRoot->left);
  }
  if(otherRoot->right!=NULL){
    copy(subroot->right, otherRoot->right);
  }
}

template <int Dim>
const KDTree<Dim>& KDTree<Dim>::operator=(const KDTree<Dim>& rhs) {
  /**
   * @todo Implement this function!
   */
  clear(root);
  copy(root,rhs.root);
  return *this;
}

template <int Dim>
KDTree<Dim>::~KDTree() {
  /**
   * @todo Implement this function!
   */
   if(root!=NULL){
     clear(root);
   }
}

template <int Dim>
void KDTree<Dim>::clear(KDTreeNode*& subroot){
  if(subroot==NULL){
    return;
  }
  if(subroot->left==NULL &&subroot->right==NULL){
    delete subroot;
  }
  if(subroot->left!=NULL){
    clear(subroot->left);
  }
  if(subroot->right!=NULL){
    clear(subroot->right);
  }
}













template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim>& query) const
{
    /**
     * @todo Implement this function!
     */
    std::stack<KDTreeNode*> initialPath;
    initialPath = search(root, query, initialPath, 0);
    return findNeighbor(query, initialPath, root->point);
}

template <int Dim>
Point<Dim> KDTree<Dim>::findNeighbor(const Point<Dim>& query, std::stack<KDTreeNode*>& path, const Point<Dim> cBest) const
{
    /**
     * @todo Implement this function!
     */
    Point<Dim> best = cBest;
    int cDim = (path.size()-1+Dim) % Dim;
    while (!path.empty()) {

      if (shouldReplace(query, best, path.top()->point) || distance_check_only(query, best, path.top()->point)) {
        if (shouldReplace(query, best, path.top()->point)) {
          best = path.top()->point;
        }

    }

    //check whether the parent is out of the boundry
    double boundry=0; //radius of the sphere
    for(int i=0; i<Dim; i++){
      boundry+=(best[i]-query[i])*(best[i]-query[i]);
    }
    double dist=(query[cDim]-path.top()->point[cDim])*(query[cDim]-path.top()->point[cDim]);


    if(boundry>=dist){
      std::stack<KDTreeNode*> newPath;
      if (smallerDimVal(query, path.top()->point, cDim)) {
        newPath = search(path.top()->right, query, newPath, (cDim + 1) % Dim);
      }
      else{
        newPath = search(path.top()->left, query, newPath, (cDim + 1) % Dim);
      }

      Point<Dim> possibleBest = findNeighbor(query, newPath, best);
      if (shouldReplace(query, best, possibleBest)) {
        best = possibleBest;
      }
    }

    cDim--;
    if (cDim < 0) {
      cDim += Dim;
    }



    path.pop();
  }
  return best;
}


template <int Dim>
std::stack<typename KDTree<Dim>::KDTreeNode*> KDTree<Dim>::search(KDTreeNode* subroot, const Point<Dim>& query,
              std::stack<KDTreeNode*>& path, unsigned cdim) const
{
    /**
     * @todo Implement this function!
     */
    if (subroot == NULL) {
      return path;
    }
    path.push(subroot);
    if (smallerDimVal(query, subroot->point, cdim)) {
      cdim = (cdim + 1) % Dim;
      search(subroot->left, query, path, cdim);
    } else {
      cdim = (cdim + 1) % Dim;
      search(subroot->right, query, path, cdim);
    }
    return path;
}







/*****
template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim>& query) const
{

     Point<Dim> p;
     return updateCurBest(root,p,query);



}

template <int Dim>
Point<Dim> KDTree<Dim>::updateCurBest(KDTreeNode* node, Point<Dim> curBest, const Point<Dim>& query) const
{
  stack<KDTreeNode*> s;
  stack<int> child; //push:   0=left 1=right;

  int leftORright;
  Point<Dim> potentialBest=findcurBest(query,root,0,s,child);

  while(!s.empty()){
    KDTreeNode* parent=s.top();
    leftORright=child.top();
    s.pop();child.pop();
    if(shouldReplace(query,curBest,parent->point)||distance_check_only(query,curBest,parent->point)){
      if(shouldReplace(query,curBest,parent->point))
      {curBest=parent->point;}
      //traverse the other child of this parent
      if(leftORright==0){//left has been traversed, now it is turn to right

      }
      else{
        curBest=std::min(curBest,updateCurBest(parent->left,curBest,query));
      }

    }
  }
  return curBest;
}



template <int Dim>
Point<Dim> KDTree<Dim>::findcurBest(const Point<Dim>& query, KDTreeNode* subroot, int curdim, stack<KDTreeNode*>& s, stack<int>& child) const
{
  if(subroot==NULL)
    return Point<Dim>();

  if(subroot->left==NULL && subroot->right==NULL){
    return subroot->point;
  }
  if(subroot->point==query){
    return subroot->point;
  }
  //now the root is not a leaf and is not equal to target
  if(smallerDimVal(query,subroot->point,curdim)){
    s.push(subroot);
    child.push(0);
    return findcurBest(query, subroot->left, (curdim+1)%Dim, s, child);
  }
  else{
    s.push(subroot);
    child.push(1);
    return findcurBest(query, subroot->right, (curdim+1)%Dim, s, child);
  }



}
*****/
