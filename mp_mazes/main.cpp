#include <iostream>
#include "dsets.h"
#include "maze.h"

#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"

using cs225::PNG;
using cs225::HSLAPixel;


using namespace std;

/*int main()
{
    // Write your own main here
    cout << "Add your own tests here! Modify main.cpp" << endl;
    SquareMaze mymaze;
    mymaze.makeMaze(700,700);
    PNG* maze=mymaze.drawMaze();
    PNG* sol=mymaze.drawMazeWithSolution();
    sol->writeToFile("ltq_sol.png");
    maze->writeToFile("ltq_maze.png");
    vector<int> set=mymaze.getdset().getsets();

    return 0;
}
*/

int main(){
  SquareMaze maze1;
  SquareMaze maze2;
  maze1.makeMaze(50,50);
  maze2.makeMaze(100,100);
  SquareMaze mymaze;
  mymaze.makeMaze(100,150);
  PNG* p1=maze1.drawMaze();
  PNG* p2=maze2.drawMaze();
  PNG* p3=mymaze.draw_creativeMaze(p1,p2);
  p3->writeToFile("mymaze.png");
  return 0;

}
