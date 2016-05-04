#include "stdafx.h"
#include "INode.h"


INode::INode()
{
	m_parent = nullptr;
	m_left = nullptr;
	m_right = nullptr;
}


INode::INode(double number)
{
	m_parent = nullptr;
	m_left = nullptr;
	m_right = nullptr;
	m_value = number;
}

INode::INode(OperatorType operatorType)
{
	m_parent = nullptr;
	m_left = nullptr;
	m_right = nullptr;
	m_operatorType = operatorType;
}

INode::~INode()
{
}
