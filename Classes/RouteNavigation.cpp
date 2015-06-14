#include "RouteNavigation.h"

USING_NS_CC;
using namespace std;

RouteNavigation* RouteNavigation::routeNav_Instance = NULL;

RouteNavigation::RouteNavigation()
{
	struct timeval now; 
	gettimeofday(&now, NULL); //����ʱ������
	unsigned rand_seed = (unsigned)(now.tv_sec*1000 + now.tv_usec/1000);     // ��ʼ�������   
	srand(rand_seed);
}

RouteNavigation::~RouteNavigation()
{
	routeNav_Instance = NULL;

	pathCols_vector.clear();   
	pathRows_vector.clear();

	std::vector<int>(pathCols_vector).swap(pathCols_vector);   //�ͷ��ڴ�
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

	//�����һ������
	pathCols_vector.clear();
	pathRows_vector.clear();	

	int currentRow;  //��ǰ��ɫ���ڵ�����
	int currentCol;  //��ǰ��ɫ���ڵ�����
	int nextRow;     //��һ��������
	int nextCol;     //��һ��������

	currentRow = (player->getPositionY() - tiledWidth) / tiledWidth;
	//����Ϊ���ý�ɫ������ʾ��������GameBaseScene:: addPlayer()�ķ����У�����ɫ����λ��+ tiledHeight,�˴�Ҫ���������ܵõ���ȷ���� 
	currentCol = player->getPositionX() / tiledHeight;
	//������λ�ü�¼��·������
	pathRows_vector.push_back(currentRow);
	pathCols_vector.push_back(currentCol);

	int lastRow = player->getComeFromRow();        //��¼��һ�����ڵ�����
	int lastCol = player->getComFromCol();         //��¼��һ�����ڵ�����

	if(lastRow <0 || lastCol <0)
	{
		player->setComeFromRow(currentRow);
		player->setComFromCol(currentCol);
	}

	//����ͼ·����ά���鸴������
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
		canPassGrid_copy[lastRow][lastCol] = false;    //�������ķ�������
	}

	//����һ��һά���飬���ڱ��浱ǰλ�õ����������ĸ������Ƿ��ܹ�ͨ��
	std::vector<bool> direction_4;

	//����һ��һά���飬���ڱ�������ܹ�ͨ���ķ���
	std::vector<int> canPassDirection_vector;

	//ѭ��������һ�������꣬����¼����
	for(int i=0;i<stepsCount;i++)
	{
		direction_4.clear();
		
		canPassDirection_vector.clear();

	    //�ж����������Ƿ�����,������
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
		switch(canPassDirection_vector[_rand])     //��������п����ߵķ�����ȡһ������
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
		//������һ����λ�õ�������
		pathRows_vector.push_back(nextRow);
		pathCols_vector.push_back(nextCol);		

		canPassGrid_copy[currentRow][currentCol] = false; //���õ�ǰλ�ò����ߣ���ֹ�߻�ͷ

		 //��������
		currentRow = nextRow;
		currentCol = nextCol;
	}
	//��ȡ��·��֮�󣬼�¼��ʱ�ķ���
	player->setComeFromRow(pathRows_vector[pathRows_vector.size() - 2]);
	player->setComFromCol(pathCols_vector[pathCols_vector.size() - 2]);

	//�ͷ��ڴ�
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