#pragma once
#include "Func.h"
class CTree;

class INode
{
	friend CTree;
public:
	INode();
	INode(double number);
	INode(OperatorType operatorType);
	~INode();
private:
	std::shared_ptr<INode> m_parent;
	std::shared_ptr<INode> m_left;
	std::shared_ptr<INode> m_right;
	bool m_leftActive = true;
	double m_value = NAN;
	OperatorType m_operatorType;
};