class Node 
{ 	
    int value;
    Node** childs;
    Node* parent;
    Node* Best_Step;
    bool step;




    Node(Node* parent==NULL,bool step)
	{
		childs = NULL;
		this.parent=parent;
		this.step=step;
		Best_Step=NULL;
		value=current_state_number();


	}
    void add_node() 
    { 
       	childs=Just_get_Steps()//new Node(this,!step)
       	if(step)
       	{
       		node_number=min(steps.value for steps in childs);
       		update(node_number,Node);
       	}
       	else
       	{
       		node_number=max(steps.value for steps in childs);
       		update(node_number,Node);
       	}
    } 
    void update(num,Node)
    {
    	if(step&&num<value||!step&&num>value)
    	{
    		Best_Step=Node;
    		value=num;
    		parent.update(num,self);
    	}
    }
}; 