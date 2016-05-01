#include "stdafx.h"
#include "Tree.h"


CTree::CTree()
{
	m_head = nullptr;
}


CTree::~CTree()
{
}

void CTree::Push(double number)
{
	std::cout << "push " << number << std::endl;
	//if fully UP
	if (m_current->m_right != nullptr)
	{
		assert(m_current->m_parent != nullptr);
		m_current = m_current->m_parent;
		Push(number);
		return;
	}

	//set left and right number
	if (m_current->m_leftActive)
	{
		m_current->m_left = std::make_shared<INode>(number);
		m_current->m_leftActive = false;
	}
	else
	{
		m_current->m_right = std::make_shared<INode>(number);
	}
}

void CTree::Push(OperatorType operatorType)
{
	//set head
	if (m_head.get() == nullptr)
	{
		m_head = std::make_shared<INode>(operatorType);
		m_current = m_head;
		m_head->m_parent = nullptr;
		return;
	}

	//if fully UP
	if (m_current->m_right != nullptr)
	{
		assert(m_current->m_parent.get() != nullptr);
		m_current = m_current->m_parent;
		Push(operatorType);
		return;
	}

	//left and right nodes
	if (m_current->m_leftActive)
	{
		m_current->m_left = std::make_shared<INode>(operatorType);
		m_current->m_left->m_parent = m_current;
		m_current->m_leftActive = false;
		m_current = m_current->m_left;
	}
	else
	{
		m_current->m_right = std::make_shared<INode>(operatorType);
		m_current->m_right->m_parent = m_current;
		m_current = m_current->m_right;
	}
}

void CTree::print()
{
	printTree(m_head, 0);
}

void CTree::printTree(std::shared_ptr<INode> p, int level)
{
	if (p.get() != nullptr) {
		printTree(p->m_left, level + 1);
		for (int i = 0; i < level; i++) std::cout << "   ";
		std::cout << p->m_value << std::endl;
		printTree(p->m_right, level + 1);
		std::cout << " " << std::endl;
	}
}
