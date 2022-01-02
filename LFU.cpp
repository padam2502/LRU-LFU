#include<iostream>
#include <unordered_map>
using namespace std;

	struct node{
	int key;
    int data;
	node* next;
	node* prev;
	int f;
	node(int n ,int x,node* r =NULL,node* p=NULL):key(n),data(x),f(1),next(r) , prev(p) {}

    };

    struct LL{
   	node *head; 
    node *tail; 
    int total;
    LL() {
    	total=0;
        head = new node(0,0); 
        tail = new node(0,0); 
        head->next = tail;
        tail->prev = head; 
    }

    void move(node *Node) {
        total++; 
        Node->next = head->next;
        (head->next)->prev = Node;
        Node->prev = head;
        head->next = Node;
    }
    
    void remove(node* Node) {
    	total--; 
        (Node->prev)->next=Node->next;
        (Node->next)->prev=Node->prev;
        
    }

};
class LFUcache {
	
	int capacity;
	unordered_map< int , node*> m;
	unordered_map< int , LL* > mp;
	int minf;
	int cur;
public:

    LFUcache(int n)
	{
		capacity=n;
		minf=0;
		cur=0;
	}
	
	int get(int key)
	{
		 if(m.find(key) != m.end()) {
            node* Node = m[key]; 
            int t = Node->data; 
            update(Node); 
            return t; 
        }
        else
        {
        	return -1; 
        }
    }
    void update(node *Node) {
        m.erase(Node->key); 
        mp[Node->f]->remove(Node); 
        if(Node->f == minf && mp[Node->f]->total == 0) {
            minf++; 
        }
        LL* newlist = new LL();
        if(mp.find(Node->f +1) != mp.end()) {
            newlist = mp[Node->f +1];
        } 
        Node->f += 1; 
        newlist->move(Node); 
        mp[Node->f] = newlist; 
        m[Node->key] = Node;
    }
	void set(int key,int value)
	{
		if (capacity == 0) 
            return;
		if(m.find(key)!=m.end())
		{
		    node* Node = m[key]; 
            Node->data = value; 
            update(Node);
		}
		else
		{
		 if(cur==capacity) {
                LL* list = mp[minf]; 
                m.erase(list->tail->prev->key); 
                mp[minf]->remove(list->tail->prev);
                cur--; 
		}
		cur++; 
            minf = 1; 
            LL* newlist = new LL(); 
            if(mp.find(minf) != mp.end()) {
                newlist= mp[minf]; 
            }
            node* Node = new node(key, value); 
            newlist->move(Node);
            m[key] = Node; 
            mp[minf] = newlist; 
		}
	}
	

};

int main()
{
	
	int n=0;
	cout<<"Enter the Capacity of LFU cache\n";
	cin>>n;
	LFUcache obj(n);
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
	return 0;
}