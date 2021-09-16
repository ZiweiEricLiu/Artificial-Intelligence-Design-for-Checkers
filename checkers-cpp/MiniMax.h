#ifndef MINIMAX_H
#define MINIMAX_H


class MiniMax
{
	struct Node
	{
		int value;
    	Node** childs;
    	Node* parent;
    	//Node* Best_Step;
    	int height;
    	Node(int new_value, int new_height, Node* p)
    		:value{new_value}, childs{nullptr}, parent{p}, height{new_height}{}
    	void addChilds(Node** c){
    		this->childs = c;
    	}
	};

public:
	MiniMax();
    void addChilds(int* inputs, )
};

#endif
