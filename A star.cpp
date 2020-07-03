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
	friend bool operator < (Node A, Node B) //����valueֵС�ķ����������ȼ�����
	{
		return A.value > B.value;
	}
};
priority_queue<Node> openTable;     //���ȼ�����open��
queue<Node> closeTable;     //close��
stack<Node> Path;     //����·��
int count1=0,count2=0;
int  read(Node& S,Node& G){
	/*��ʼ��*/
	S.parent=NULL;	S.depth=0;	S.value=0;
	G.parent=NULL;	G.depth=0;	G.value=0;
	 cout<<"�������ʼ״̬\n";
	 for(int i=0;i<num;i++)
		 cin>>S.state[i];
	 cout<<"������Ŀ��״̬\n";
	  for(int i=0;i<num;i++)
		  cin>>G.state[i];
	  for(int i=0;i<=num-2;i++)//��ʼ״̬�������� 
		  for(int j=i+1;j<num;j++)
			if(S.state[i]>S.state[j]&&S.state[i]*S.state[j]!=0)//�ų�0 
				count1++;
	   for(int i=0;i<=num-2;i++)//Ŀ��״̬�������� 
		  for(int j=i+1;j<num;j++)
			if(G.state[i]>G.state[j]&&G.state[i]*G.state[j]!=0)//�ų�0 
				count2++;
	   if(count1%2!=count2%2)//������������ż��ͬ���ܵ��� 
	   {
		   return 0;
	   }
		   return 1;
}
/*���۹��ƺ���*/ 
int value1(Node A,Node G){
	int count=9;
	for(int i=0;i<num;i++)
		if(A.state[i]==G.state[i])
			count--;
	return count +A.depth;
}
/*�ж��Ƿ񵽴�Ŀ��״̬*/ 
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
//�����½ڵ㣬����OPEN��
void creatNode(Node& S, Node G)
{
	/* ����ԭ״̬��,�ո����ڵ����������Ӷ��жϿո�������ĸ������ƶ� */
	int blank; //����ո��±�
	for(blank=0;blank<9&&S.state[blank]!=0;blank++) ;//�ҵ��հ׸�
	int x =blank / 3, y = blank % 3; //��ȡ�ո��������б��
	for (int d = 0; d < 4; d++) //�ҵ�S��չ���ӽڵ㣬����open����
	{   
		int newX=x,newY=y;//�¿հ׸�����
		Node tempNode;
		/*�ƶ��հ׸�*/
		if(d==0)  newX = x -1;//���� 
	    if(d==1)	 newY = y -1;//���� 
	    if(d==2)  newX = x +1;//���� 
	    if(d==3)	 newY = y +1;//���� 
		int newBlank = newX * 3 + newY; //�ո��µ�λ��
		if (newX >= 0 && newX < 3 && newY >= 0 && newY < 3) //��������ƶ�
		{
			/* �����¾ɿհ׸������*/
			tempNode = S;
			tempNode.state[blank] = S.state[newBlank];
			tempNode.state[newBlank] =0;
			if ( S.parent!=NULL&&(*S.parent).state[newBlank] == 0) //����½ڵ��үү�ڵ�һ���������ýڵ㣬��ֹһֱ��չ��ͬ�ڵ� 
			{
				continue;
			}
			/* ���ӽڵ㶼����open���� */
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
	cout<<"����֮�䲻�ɴ�";
	return 0;
	} 
		openTable.push(S0);//����ʼ״̬ѹ��open�� 
		while (1)
		{
			closeTable.push(openTable.top()); //��open�������ȼ���ߵ�Ԫ��ѹ��close����
			openTable.pop(); //ɾ��open�������ȼ���ߵ�Ԫ��
			if (!judge(closeTable.back(), Sg)) //�����ǰ״̬��Ŀ��״̬��ͬ������չ��ǰ�ڵ�
			{
			creatNode(closeTable.back(), Sg);
			}
			else
			{
				break;
			}
		}
		Node tempNode;   //��ʱ�������� 
		tempNode = closeTable.back();
		while (tempNode.parent != NULL)
		{
			Path.push(tempNode);//ѹ��
			tempNode = *(tempNode.parent);//ָ�򸸽ڵ�
		}
		Path.push(tempNode);
		cout << "����Ҫ�ƶ�" << Path.size() - 1 << "��" << endl;
		/* ������� */
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
