#include<queue>
#include<iostream>
#include<stack>
using namespace std;
#define num 9
struct Node{
	int state[9];
	struct Node* parent;
	int value;
	int depth;
	friend bool operator < (Node A, Node B) //按照value值小的方案构造优先级队列
	{
		return A.value > B.value;
	}
};
priority_queue<Node> openTable;     //优先级队列open表
queue<Node> closeTable;     //close表
stack<Node> Path;     //最终路径
int count1=0,count2=0;
int  read(Node& S,Node& G){
	/*初始化*/
	S.parent=NULL;	S.depth=0;	S.value=0;
	G.parent=NULL;	G.depth=0;	G.value=0;
	 cout<<"请输入初始状态\n";
	 for(int i=0;i<num;i++)
		 cin>>S.state[i];
	 cout<<"请输入目标状态\n";
	  for(int i=0;i<num;i++)
		  cin>>G.state[i];
	  for(int i=0;i<=num-2;i++)//初始状态的逆序数 
		  for(int j=i+1;j<num;j++)
			if(S.state[i]>S.state[j]&&S.state[i]*S.state[j]!=0)//排除0 
				count1++;
	   for(int i=0;i<=num-2;i++)//目标状态的逆序数 
		  for(int j=i+1;j<num;j++)
			if(G.state[i]>G.state[j]&&G.state[i]*G.state[j]!=0)//排除0 
				count2++;
	   if(count1%2!=count2%2)//两者逆序数奇偶不同则不能到达 
	   {
		   return 0;
	   }
		   return 1;
}
/*代价估计函数*/ 
int value1(Node A,Node G){
	int count=9;
	for(int i=0;i<num;i++)
		if(A.state[i]==G.state[i])
			count--;
	return count +A.depth;
}
/*判断是否到达目标状态*/ 
bool judge(Node S, Node G)
{
	for (int i = 0; i <= 8; i++)
	{
		if (S.state[i] != G.state[i])
		{
			return false;
		}
	}
	return true;
}
//产生新节点，加入OPEN表
void creatNode(Node& S, Node G)
{
	/* 计算原状态下,空格所在的行列数，从而判断空格可以往哪个方向移动 */
	int blank; //定义空格下标
	for(blank=0;blank<9&&S.state[blank]!=0;blank++) ;//找到空白格
	int x =blank / 3, y = blank % 3; //获取空格所在行列编号
	for (int d = 0; d < 4; d++) //找到S扩展的子节点，加入open表中
	{   
		int newX=x,newY=y;//新空白格坐标
		Node tempNode;
		/*移动空白格*/
		if(d==0)  newX = x -1;//左移 
	    if(d==1)	 newY = y -1;//下移 
	    if(d==2)  newX = x +1;//右移 
	    if(d==3)	 newY = y +1;//上移 
		int newBlank = newX * 3 + newY; //空格新的位置
		if (newX >= 0 && newX < 3 && newY >= 0 && newY < 3) //如果可以移动
		{
			/* 交换新旧空白格的内容*/
			tempNode = S;
			tempNode.state[blank] = S.state[newBlank];
			tempNode.state[newBlank] =0;
			if ( S.parent!=NULL&&(*S.parent).state[newBlank] == 0) //如果新节点和爷爷节点一样，舍弃该节点，防止一直扩展相同节点 
			{
				continue;
			}
			/* 把子节点都加入open表中 */
			tempNode.parent = &S;
			tempNode.value = value1(tempNode, G);
			tempNode.depth = S.depth + 1;
			openTable.push(tempNode);
		}
	}
}	
int main()
{
	Node S0,Sg;
	if(!read(S0,Sg))
	{
	cout<<"两点之间不可达";
	return 0;
	} 
		openTable.push(S0);//将初始状态压入open表 
		while (1)
		{
			closeTable.push(openTable.top()); //将open表中优先级最高的元素压入close表中
			openTable.pop(); //删除open表中优先级最高的元素
			if (!judge(closeTable.back(), Sg)) //如果当前状态与目标状态不同，则拓展当前节点
			{
			creatNode(closeTable.back(), Sg);
			}
			else
			{
				break;
			}
		}
		Node tempNode;   //临时棋盘数据 
		tempNode = closeTable.back();
		while (tempNode.parent != NULL)
		{
			Path.push(tempNode);//压入
			tempNode = *(tempNode.parent);//指向父节点
		}
		Path.push(tempNode);
		cout << "至少要移动" << Path.size() - 1 << "步" << endl;
		/* 输出方案 */
		while (Path.size() != 0)
		{
			for (int i = 0; i <= 8; i++)
			{
				cout << Path.top().state[i]<<" ";
				if((i+1)%3==0)
					cout <<endl;
			}
			Path.pop();
			cout << "\n";
		}
	return 0;
}

