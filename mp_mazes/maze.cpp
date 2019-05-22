#include "maze.h"
#include <stdio.h>
#include <stdlib.h>

SquareMaze::SquareMaze(){

}

bool SquareMaze::canTravel(int x, int y, int dir) const{
  bool can = !mazeX[x][y][dir];
	return can;
}

void SquareMaze::makeMaze(int width, int height){
  srand(time(NULL));
  w=width;
  h=height;
  vector<bool> dir;
  for(int i=0; i<4; i++){
    dir.push_back(true);
  }
  vector<vector<bool>> mazeY;
  for(int i=0; i<height; i++){
    mazeY.push_back(dir);
  }
  for(int i=0; i<width; i++){
    mazeX.push_back(mazeY);
  }
  dSets.addelements(w*h);


  int i=rand()%w; int j=rand()%h; //randomly pick a cell in the graph and put it into maze
  //cout<<i<<" "<<j<<endl;
  en_wallList(i,j);


  /****************************/
  //start removing walls

  while(!wallList.empty()){
    int wallIndex=rand()%wallList.size();
    tuple<int,int,int> wall_to_remove=wallList[wallIndex];
    int x=get<0>(wall_to_remove);
    int y=get<1>(wall_to_remove);
    int dir=get<2>(wall_to_remove);

  //  cout<<"remove<"<<x<<" "<<y<<" "<<dir<<">"<<endl;
    wallList.erase(wallList.begin()+wallIndex);//remove from wallList

      mazeX[x][y][dir]=false; //no wall over there
      //remove the corresponding wall in the neighbor cell
      if(dir==0) {
                   mazeX [x+1] [y]   [2]=false;
                //   dSets.setunion(y*w+x, y*w+x+1);
                   en_wallList(x+1,y);
                  }

      if(dir==1) {
                   mazeX [x]   [y+1] [3]=false;
                //   dSets.setunion(y*w+x, (y+1)*w+x);
                   en_wallList(x,y+1);
                  }

      if(dir==2) {
                   mazeX [x-1] [y]   [0]=false;
                //  dSets.setunion(y*w+x, (y+1)*w+x);
                   en_wallList(x-1,y);
                  }

      if(dir==3) {
                   mazeX [x]   [y-1] [1]=false;
              //     dSets.setunion(y*w+x,(y-1)*w+x);
                   en_wallList(x,y-1);
                  }
  }
}

void SquareMaze::en_wallList(int x, int y){
  int a=y*w+x;
  int b=y*w+x+1;
  int c=(y+1)*w+x;
  int d=y*w+x-1;
  int e=(y-1)*w+x;

  if(x!=w-1 && dSets.findByRef(a)!=dSets.findByRef(b) && mazeX[x][y][0]==true)//right
  {
    tuple<int,int,int> t0(x,y,0);
  //  cout<<"enlist<"<<x<<" "<<y<<" "<<"0>"<<endl;
    wallList.push_back(t0);
    dSets.fastsetunion(y*w+x, y*w+x+1);
  }


  if(y!=h-1 && dSets.findByRef(a)!=dSets.findByRef(c) && mazeX[x][y][1]==true)//down
  {
    tuple<int,int,int> t1(x,y,1);
    wallList.push_back(t1);
  //  cout<<"enlist<"<<x<<" "<<y<<" "<<"1>"<<endl;
    dSets.fastsetunion(y*w+x, (y+1)*w+x);
  }


  if(x!=0 && dSets.findByRef(a)!=dSets.findByRef(d) && mazeX[x][y][2]==true)//left
  {
    tuple<int,int,int> t2(x,y,2);
    wallList.push_back(t2);
//    cout<<"enlist<"<<x<<" "<<y<<" "<<"2>"<<endl;
    dSets.fastsetunion(y*w+x-1, y*w+x);
  }

  if(y!=0 && dSets.findByRef(a)!=dSets.findByRef(e) && mazeX[x][y][3]==true)//up
  {
    tuple<int,int,int> t3(x,y,3);
    wallList.push_back(t3);
//    cout<<"enlist<"<<x<<" "<<y<<" "<<"3>"<<endl;
    dSets.fastsetunion(y*w+x,(y-1)*w+x);
  }

}




void SquareMaze::setWall(int x,int y,int dir,bool exists ) {
  mazeX[x][y][dir] = exists;
	if (dir == 0 && x != w - 1) {
		mazeX[x+1][y][2] = exists;
	}
	if (dir == 1 && y != h - 1) {
		mazeX[x][y+1][3] = exists;
	}
	if (dir == 2 && x != 0) {
		mazeX[x-1][y][0] = exists;
	}
	if (dir == 3 && y != 0) {
		mazeX[x][y-1][1] = exists;
	}

}

PNG* SquareMaze::drawMaze()	const{
  PNG *mazePNG = new PNG(w*10+1, h*10+1);
 for (unsigned int j = 0; j < mazePNG->height(); j++) {
   mazePNG->getPixel(0, j).l = 0;
 }
 for (unsigned int i = 10; i < mazePNG->width(); i++) {
   mazePNG->getPixel(i, 0).l = 0;
 }
 for (int i = 0; i < w; i++) {
   for (int j = 0; j < h; j++) {
     if (mazeX[i][j][0] == true) {
       for (int k = 0; k <= 10; k++) {
         mazePNG->getPixel((i+1)*10, j*10+k).l = 0;
       }
     }
     if (mazeX[i][j][1] == true) {
       for (int k = 0; k <= 10; k++) {
         mazePNG->getPixel(i*10+k, (j+1)*10).l = 0;
       }
     }
   }
 }

 return mazePNG;
}


PNG* SquareMaze::drawMazeWithSolution	(){
  PNG *mazePNG = drawMaze();
	std::vector<int> solution = solveMaze();
	int x = 5;
	int y = 5;
	int a = 0;
	int b = 0;
  HSLAPixel &pixel = mazePNG->getPixel(x, y);
  pixel.h = 0;
  pixel.s = 1;
  pixel.l = 0.5;
  pixel.a = 1;


	for (int &dir : solution) {
		if (dir == 0) {
			a++;
			for (int i = 0; i < 10; i++) {
        x++;
				HSLAPixel &pixel = mazePNG->getPixel(x, y);
				pixel.h = 0;
				pixel.s = 1;
				pixel.l = 0.5;
				pixel.a = 1;

			}
		}
		if (dir == 1) {
			b++;
			for (int i = 0; i < 10; i++) {
        y++;
				HSLAPixel &pixel = mazePNG->getPixel(x, y);
				pixel.h = 0;
				pixel.s = 1;
				pixel.l = 0.5;
				pixel.a = 1;

			}
		}
		if (dir == 2) {
			a--;
			for (int i = 0; i < 10; i++) {
        x--;
				HSLAPixel &pixel = mazePNG->getPixel(x, y);
				pixel.h = 0;
				pixel.s = 1;
				pixel.l = 0.5;
				pixel.a = 1;

			}
		}
		if (dir == 3) {
			b--;
			for (int i = 0; i < 10; i++) {
        	y--;
				HSLAPixel &pixel = mazePNG->getPixel(x, y);
				pixel.h = 0;
				pixel.s = 1;
				pixel.l = 0.5;
				pixel.a = 1;

			}
		}
	}
	for (int k = 1; k < 10; k++) {
		mazePNG->getPixel(a*10+k, (b+1)*10).l = 1;
	}
	return mazePNG;
}

vector<int> SquareMaze::solveMaze(){

  vector<int> longestpath;
  vector<int> path;
  int large =0;
	for (int i = 0; i < w; i++) {
    int pathlength=0;
		solved(0, 0, i, path, pathlength);
  //  cout<<"pathlength "<<pathlength<<"large "<<large<<endl;
		if(pathlength>large){
      large=pathlength;
      longestpath=path;
    }
    path.clear();
	}

	return longestpath;
}



bool SquareMaze::solved(int x, int y, int a, vector<int> &solution, int& pathlength) {
	if (x < 0 || y < 0 || x >= w || y >= h) {
		return false;
	}
	if (y == h - 1 && x == a) {

		return true;
	}


	if (mazeX[x][y][0] == false && (solution.empty() || 2 != solution.back())) {
		solution.push_back(0);
    pathlength++;
		if (solved(x+1, y, a, solution, pathlength)) {
			return true;
		} else {
			solution.erase(solution.end() - 1);
      pathlength--;
		}
	}
	if (mazeX[x][y][1] == false && (solution.empty() || 3 != solution.back())) {
		solution.push_back(1);
    pathlength++;
		if (solved(x, y+1, a, solution, pathlength)) {
			return true;
		} else {
			solution.erase(solution.end() - 1);
      pathlength--;
		}
	}
	if (mazeX[x][y][2] == false && (solution.empty() || 0 != solution.back())) {
		solution.push_back(2);
    pathlength++;
		if (solved(x-1, y, a, solution, pathlength)) {
			return true;
		} else {
			solution.erase(solution.end() - 1);
      pathlength--;
		}
	}
	if (mazeX[x][y][3] == false && (solution.empty() || 1 != solution.back())) {
		solution.push_back(3);
    pathlength++;
		if (solved(x, y-1, a, solution, pathlength)) {
			return true;
		} else {
			solution.erase(solution.end() - 1);
      pathlength--;
		}
	}
	return false;
}






DisjointSets SquareMaze::getdset(){
  return dSets;
}





















//part3
PNG* SquareMaze::draw_creativeMaze(PNG* maze1, PNG* maze2)	const{
   unsigned w1=maze1->width();
   unsigned w2=maze2->width();
   unsigned h1=maze1->height();
   unsigned h2=maze2->height();
   PNG *mazePNG = new PNG(w2,h1+h2);

   for (unsigned i = 0; i < w1; i++) {
     for (unsigned j = 0; j < h1; j++) {
       mazePNG->getPixel(i,j)=maze1->getPixel(i,j);
     }
   }
   for (unsigned i=w1; i<w2; i++){
     for(unsigned j=0; j<h1; j++){
       mazePNG->getPixel(i,j).l=1;
     }
   }
   for(unsigned i=0; i<w2; i++){
     for(unsigned j=h1-1; j<h1+h2-1; j++){
       mazePNG->getPixel(i,j)=maze2->getPixel(i,j-h1+1);
     }
   }
   return mazePNG;
 }
