#pragma once
#include <vector>
#include <iostream>
#include <tuple>
#include <utility>  //std::pair
#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"
#include "dsets.h"
using namespace std;
using namespace cs225;

class SquareMaze{
  public:
  SquareMaze();
  void makeMaze(int width, int height);
  void setWall(int x,int y,int dir,bool exists );
  vector<int> solveMaze();
  /*dir = 0 represents a rightward step (+1 to the x coordinate)
dir = 1 represents a downward step (+1 to the y coordinate)
dir = 2 represents a leftward step (-1 to the x coordinate)
dir = 3 represents an upward step (-1 to the y coordinate)*/
  bool canTravel(int x, int y, int dir) const;
  PNG* drawMaze()	const;
  PNG* drawMazeWithSolution	();

  DisjointSets getdset();
  PNG* draw_creativeMaze(PNG* maze1, PNG* maze2)	const;

  private:
  int w;
  int h;
  vector <  vector< vector<bool> >  > mazeX;//<x<y<dir>>>:  bool true->has a wall
  DisjointSets dSets;
  vector<tuple<int,int,int>> wallList;

  void en_wallList(int x, int y);
  //pair<unsigned int,vector<int>> find_path(int index);
  bool solved(int x, int y, int a, vector<int> &solution, int& pathlength);



};
