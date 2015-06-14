#include "RouteNavigation.h"

USING_NS_CC;
using namespace std;

RouteNavigation* RouteNavigation::routeNav_Instance = NULL;

RouteNavigation::RouteNavigation()
{
	struct timeval now; 
	gettimeofday(&now, NULL); //计算时间种子
	unsigned rand_seed = (unsigned)(now.tv_sec*1000 + now.tv_usec/1000);     // 初始化随机数   
	srand(rand_seed);
}

RouteNavigation::~RouteNavigation()
{
	routeNav_Instance = NULL;

	pathCols_vector.clear();   
	pathRows_vector.clear();

	std::vector<int>(pathCols_vector).swap(pathCols_vector);   //释放内存
	std::vector<int>(pathRows_vector).swap(pathRows_vector);
}

RouteNavigation *RouteNavigation::getInstance()
{
	if(!routeNav_Instance)
	{
		routeNav_Instance = new RouteNavigation();
	}
	return routeNav_Instance;
}

void RouteNavigation::getPath(RicherPlayer *player,int stepsCount,bool **canPassGrid,int gridRowsCount,int gridColsCount)
{

	//清除上一次数据
	pathCols_vector.clear();
	pathRows_vector.clear();	

	int currentRow;  //当前角色所在的行数
	int currentCol;  //当前角色所在的列数
	int nextRow;     //下一步的行数
	int nextCol;     //下一步的列数

	currentRow = (player->getPositionY() - tiledWidth) / tiledWidth;
	//我们为了让角色居中显示，曾经在GameBaseScene:: addPlayer()的方法中，给角色纵向位置+ tiledHeight,此处要减掉，才能得到正确行数 
	currentCol = player->getPositionX() / tiledHeight;
	//将当期位置记录到路径当中
	pathRows_vector.push_back(currentRow);
	pathCols_vector.push_back(currentCol);

	int lastRow = player->getComeFromRow();        //记录上一步所在的行数
	int lastCol = player->getComFromCol();         //记录上一步所在的列数

	if(lastRow <0 || lastCol <0)
	{
		player->setComeFromRow(currentRow);
		player->setComFromCol(currentCol);
	}

	//将地图路径二维数组复制下来
    bool **canPassGrid_copy = new bool *[gridRowsCount];
	for(int i=0;i<gridColsCount;i++)
	{
		canPassGrid_copy[i] = new bool[gridColsCount];
	}
	for(int i =0;i<gridRowsCount;i++)
	{
		for(int j=0;j<gridColsCount;j++)
		{
			canPassGrid_copy[i][j] = canPassGrid[i][j];
		}
	}
	if(lastRow>=0&&lastCol>=0)
	{
		canPassGrid_copy[lastRow][lastCol] = false;    //设置来的方向不能走
	}

	//定义一个一维数组，用于保存当前位置的上下左右四个方向是否能够通过
	std::vector<bool> direction_4;

	//定义一个一维数组，用于保存具体能够通过的方向
	std::vector<int> canPassDirection_vector;

	//循环查找下一步的坐标，并记录下来
	for(int i=0;i<stepsCount;i++)
	{
		direction_4.clear();
		
		canPassDirection_vector.clear();

	    //判断上下左右是否能走,并保存
		direction_4.push_back(isCanGoByRowCol(currentRow,currentCol,GO_UP,canPassGrid_copy));     //0
		direction_4.push_back(isCanGoByRowCol(currentRow,currentCol,GO_DOWN,canPassGrid_copy));    //1
		direction_4.push_back(isCanGoByRowCol(currentRow,currentCol,GO_LEFT,canPassGrid_copy));    //2
		direction_4.push_back(isCanGoByRowCol(currentRow,currentCol,GO_RIGHT,canPassGrid_copy));   //3

		for(int i=0;i<4;i++)
		{
			if(direction_4[i])
			{
				canPassDirection_vector.push_back(i);
			}
		}
		
		int _rand = rand()%(canPassDirection_vector.size());
		switch(canPassDirection_vector[_rand])     //随机从所有可以走的方向中取一个出来
		{
		case GO_UP:
			nextRow = currentRow -1;
			nextCol = currentCol;
			break;
		case GO_DOWN:
			nextRow = currentRow +1;
			nextCol = currentCol;
			break;
		case GO_LEFT:
			nextRow = currentRow;
			nextCol = currentCol - 1;
			break;
		case GO_RIGHT:
			nextRow = currentRow ;
			nextCol = currentCol + 1;
			break;
		}
		//保存下一步的位置到容器中
		pathRows_vector.push_back(nextRow);
		pathCols_vector.push_back(nextCol);		

		canPassGrid_copy[currentRow][currentCol] = false; //设置当前位置不能走，防止走回头

		 //更新坐标
		currentRow = nextRow;
		currentCol = nextCol;
	}
	//获取完路径之后，记录来时的方向
	player->setComeFromRow(pathRows_vector[pathRows_vector.size() - 2]);
	player->setComFromCol(pathCols_vector[pathCols_vector.size() - 2]);

	//释放内存
	direction_4.clear();
	canPassDirection_vector.clear();
	std::vector<bool>(direction_4).swap(direction_4);
	std::vector<int>(canPassDirection_vector).swap(canPassDirection_vector);
	
}

bool RouteNavigation::isCanGoByRowCol(int row,int col,int direction,bool **canPassGrid)
{
	
	switch(direction)
	{
	case GO_UP:
		return canPassGrid[row-1][col];
	case GO_DOWN:
		return canPassGrid[row+1][col];
	case GO_LEFT:
		return canPassGrid[row][col-1];
	case GO_RIGHT:
		return canPassGrid[row][col+1];
	}
	return false;
	

}