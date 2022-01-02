#include<iostream>
#include <unordered_map>
using namespace std;


class LRUcache {
	
	int capacity;
public:

    LRUcache(int n)
	{
		capacity=n;
	}
	struct LL{

    int data;
	LL* next;
	LL* prev;
	LL(int n , LL* f=NULL,LL* p=NULL):data(n),next(f) , prev(p) {}

    };
    unordered_map< int , LL* > m;
	unordered_map< int , int > mp;
    struct LL* head=NULL;
    struct LL* tail=NULL;
	
	int get(int key)
	{
		if(mp.find(key)!=mp.end())
			{
				del(m[key]);
				++capacity;
				add(key);
				--capacity;
				return mp[key];
			}
		else
			{
				return -1;
			}

	}
	void set(int key,int value)
	{
	   
		
		if(mp.find(key)!=mp.end())
		{
		    
			mp[key]=value;
			del(m[key]);
			m.erase(key);
			++capacity;
			add(key);
			--capacity;
		}
		else
		{
		if(capacity>0)
		{
			{
			   
				--capacity;
			mp[key]=value;
				add(key);
			}
		}
		else
		{
		    if(tail!=NULL)
		    {
		    m.erase(tail->data);
	    	mp.erase(tail->data);
			del(tail);
			++capacity;
			mp[key]=value;
			add(key);
			--capacity;
		    }
		    else
		    return;
		}
		}
	}
		void del(LL* Node )
	{	

	if(Node->prev==NULL && Node->next==NULL)
	{
		head=NULL;
		tail=NULL;
	}
    else	if(tail==Node)
	{
		tail=tail->prev;
	}
	else if(head==Node)
	{
		head=head->next;
	}
	LL* temp=Node;
	if((Node->prev)!=NULL)
	(Node->prev)->next=(Node->next);
	if(Node->next !=NULL)
	(Node->next)->prev=Node->prev;

	//free(temp);
	}

	void add(int key)
	{
	LL* newnode=new LL(key,NULL,NULL);
	
	if(head==NULL)
	{
		
		head=newnode;
		tail=newnode;
	}
	else
	{
		newnode->next=head;
		head->prev=newnode;
		head=newnode;
	}
	m[key]=head;
	}
};

int main()
{
	
	int n=0;
	cout<<"Enter the Capacity of LRU cache\n";
	cin>>n;
	LRUcache obj(n);
	char e='y';
	int a,b;
	while(e!='n'){
	cout<<"Enter 1 for set \n 2 for get\n";
	int x=0;
	cin>>x;
	if(x==1)
	{
		cout<<"Enter Key and corresponding value\n";
		cin>>a>>b;
		obj.set(a,b);
	}
	else if(x==2)
	{
		cout<<"Enter Key \n";
		cin>>b;
	    cout<<obj.get(b);
	}
	cout<<"\nWant to continue? (y/n)\n";
	cin>>e;
	}
}