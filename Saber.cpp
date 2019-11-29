#include <iostream>

#include <fstream>

#include <vector>
#include <map>

/*
Даны 2 интерфейса: List и ListNode
Т.е. двухсторонний список, но в каждом элементе может содержать указатель на любой элемент в списке
Требуется реализовать сериализацию/десериализацию
С восстановлением полной структуры

1) Не ясно можно ли добавлять в структуру свои данные - например int содержащий номер случайного элемента

2) Если нет то усложняется - требуется дополнительный вектор, который придётся заполнять перед каждой операцией сериализации/десериализации
Или придётся пробегать каждый раз по списку - но это дает сложность O(n*n) 
*/

using namespace std;

//Преобразование int в бинарный формат
/*void int_to_binary()
{
int a;
std::cin >> a;
const int size=32;
unsigned int b=1<<(size-1);

for(int x=0;x<size;x++)
{
	if (a&b) std::cout << "1"; else std::cout << "0";
	b>>=1;
}
std::cout << "\n";
}

//Удаление дубликатов в строке без выделения новой строки
void RemoveDups()
{
char* s=new char[255];
scanf("%s",s);

printf("%s\n",s);

int i=0,y=1;
while(s[y]!=0)
{
	if(s[i]!=s[y])
	{
		i++;
		s[i]=s[y];
	}
	y++;
	printf("%s\n",s);
}
s[i+1]='\0';

std::cout << s;
}*/

//Сериализация, десериализация двухсвязного списка в бинарном формате в файл
struct ListNode
{
	//ListNode(ListNode* prev,const std::string& date,int n_rand) : prev(prev),next(nullptr),rand(nullptr),n_rand(n_rand),date(date) {};
	ListNode() : prev(nullptr),next(nullptr),rand(nullptr) {};
	
	ListNode* prev;
	ListNode* next;
	ListNode* rand;//Указатель на произвольный элемент данного списка либо NULL
	std::string date;
};

class List
{
public:
	List() : head(nullptr), tail(nullptr), count(0) {};
	void Serialize();
	void Deserialize();
	
	void print();
	
//private:
	ListNode* head;
	ListNode* tail;
	int count;
};

void List::Serialize()
{
	map<ListNode*,int> nodes;
	
	ListNode* n1=head;
	int i=1;
	while(n1)
	{
		nodes[n1]=i++;
		n1=n1->next;
	}

	ofstream file("test_out.txt",ios_base::out);
	n1=head;
	while(n1)
	{
		file << (n1->date) << "\t" << nodes[n1->rand] << endl;
		
		n1=n1->next;
	}	
}

void List::Deserialize()
{
	ifstream file("test.txt",ios_base::in);
	count=0;
	
	vector<int> n_rands;
	
	//Создание списка элементов и вектора содержащего номера элементов
	bool flag=true;
	ListNode* n_1=nullptr;// n-1 преведущий
	while(!file.eof())
	{
		ListNode* n1=new ListNode();
		int number;
		file >> (n1->date) >> number;
		n_rands.push_back(number);
		
		if(flag) {head=n1;flag=false;};

		if (n_1) n_1->next=n1;
		n1->prev=n_1;
		
		n_1=n1;
		
		++count;
	}	
	tail=n_1;
	
	//Вектор содержащий указатели на все элементы в списке
	//Нумерация в файле идёт с 1
	vector<ListNode*> nodes(count+1);
	ListNode* n1=head;
	int i=1;
	while(n1)
	{
		nodes[i++]=n1;
		n1=n1->next;
	}

	//Заполнение указателя на случайный элемент в списке	
	n1=head;
	i=0;
	while(n1)
	{
		int number=n_rands[i++];
		if (number!=0) n1->rand=nodes[number];
		n1=n1->next;
	}	
	
}

void List::print()
{	
	map<ListNode*,int> nodes;
	
	ListNode* n1=head;
	int i=1;
	while(n1)
	{
		nodes[n1]=i++;
		n1=n1->next;
	}

	n1=head;
	while(n1)
	{
		std::cout << (n1->date) << "\t";
		if (n1->rand) std::cout << nodes[n1->rand] << "\t" << (n1->rand->date);
		std::cout << std::endl;
		n1=n1->next;
	}
}

int main()
{
//int_to_binary();
//RemoveDups();

List list;
list.Deserialize();
list.Serialize();

list.print();

return 0;
}

/*void generator()
{
List* list=new List();

ListNode* node=new ListNode();

ListNode* _prev=NULL;

for(int i=0;i<10;i++)
{
	ListNode* next_node=new ListNode();
	node->prev=_prev;
	node->next=next_node;
	node->rand=NULL;
	node->date=std::string("TEXT")+char(i+65);
	std::cout << node->date;
	
	_prev=node;
	node=next_node;
}

list->head=node;

//delete(list);
}*/