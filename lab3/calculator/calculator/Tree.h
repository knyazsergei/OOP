#pragma once
#include "INode.h"
#include "Func.h"

class CTree
{
public:
	CTree();
	~CTree();
	void Push(double number);
	void Push(OperatorType operatorType);
	void print();
private:
	void printTree(std::shared_ptr<INode> p, int level);
	std::shared_ptr<INode> m_head;
	std::shared_ptr<INode> m_current;
};

