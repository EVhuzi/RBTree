#pragma once

#define BLACK true
#define RED false

struct CNode
{
	CNode(int val) : m_data(val),
		m_pParent(nullptr),
		m_pLeft(nullptr),
		m_pRight(nullptr),
		RBFlag(RED)
	{

	}

	int m_data;
	CNode* m_pParent;
	CNode* m_pLeft;
	CNode* m_pRight;
	bool RBFlag;	//TRUE表示黑色，FALSE表示红色
};

class CRBTree
{
public:
	CRBTree() : m_pRoot(nullptr),m_nSizeCount(0)
	{

	}

	void AddNode(int val)
	{
		CNode* pNewNode = new CNode(val);

		//如果现在是空树，节点直接作为根节点保存
		if (m_nSizeCount == 0)
		{
			m_pRoot = pNewNode;
		}
		else
		{
			//不是空树
			CNode* pCurNode = m_pRoot;
			while (pCurNode != nullptr)
			{
				if (pNewNode->m_data < pCurNode->m_data)
				{
					if(pCurNode->m_pLeft != nullptr)
						pCurNode = pCurNode->m_pLeft;
					else
					{
						pCurNode->m_pLeft = pNewNode;
						pNewNode->m_pParent = pCurNode;
						break;
					}
				}
				else if (pNewNode->m_data > pCurNode->m_data)
				{
					if (pCurNode->m_pRight != nullptr)
						pCurNode = pCurNode->m_pRight;
					else
					{
						pCurNode->m_pRight = pNewNode;
						pNewNode->m_pParent = pCurNode;
						break;
					}
				}
				else
				{
					//不支持
				}
			}
		}
		AdjustColor(pNewNode);
		m_nSizeCount++;
	}

	void AdjustColor(CNode* pNode)
	{
		//插入的节点是根节点,直接将根节点涂黑
		if (m_pRoot == pNode)
			m_pRoot->RBFlag = true;
		else
		{
			CNode* pParent = pNode->m_pParent;
			//插入节点的父节点是黑色：不违背任何性质，不用调整
			if (pParent->RBFlag == true)
				return;
			//插入节点的父节点是红色，那么分情况讨论：
			else if (pParent->RBFlag == RED)
			{
				while (pNode != nullptr && pNode != m_pRoot && pNode->m_pParent->RBFlag == RED)
				{
					pParent = pNode->m_pParent;
					//一、父节点是祖父节点的左孩子
					if (pParent == pParent->m_pParent->m_pLeft)
					{
						CNode* pUncle = pParent->m_pParent->m_pRight;
						//1. 祖父节点的另一个子节点（叔叔节点）是红色
						/*对策：将当前节点的父节点和叔叔节点涂黑，
						祖父节点涂红，把当前节点指向祖父节点，
						从新的当前节点开始算法*/

						if (pUncle != nullptr && pUncle->RBFlag == RED)
						{
							pParent->RBFlag = BLACK;
							pUncle->RBFlag = BLACK;
							if(pParent->m_pParent != m_pRoot)	
								pParent->m_pParent->RBFlag = RED;
							pNode = pParent->m_pParent;
							if(pNode->m_pParent != nullptr)
								pParent = pNode->m_pParent;
							else
							{
								pParent = nullptr;
							}
						}
						//2.叔叔节点是黑色，又分两种情况
						else if ((pUncle != nullptr && pUncle->RBFlag == BLACK) || 
							pUncle == nullptr)
						{
							//2.1当前节点是其父节点的右孩子
							/*对策：当前节点的父节点作为新的当前节点
									以当前节点为支点左旋*/
							if (pNode == pParent->m_pRight)
							{
								pNode = pParent;
								pParent = pNode->m_pParent;
								LeftRotate(pNode);
							}
							//2.2当前节点是其父节点的左孩子
							/*对策：父节点变为黑色，祖父节点变红色
									再父节点为支点进行右旋*/
							else if (pNode == pParent->m_pLeft)
							{
								pParent->RBFlag = BLACK;
								pParent->m_pParent->RBFlag = RED;
								RightRotate(pParent->m_pParent);
							}
						}

					}

					//二、父节点是祖父节点的右孩子
					else if (pParent == pParent->m_pParent->m_pRight)
					{
						CNode* pUncle = pParent->m_pParent->m_pLeft;
						//1. 祖父节点的另一个子节点（叔叔节点）是红色
						/*对策：将当前节点的父节点和叔叔节点涂黑，
						祖父节点涂红，把当前节点指向祖父节点，
						从新的当前节点开始算法*/

						if (pUncle != nullptr && pUncle->RBFlag == RED)
						{
							pParent->RBFlag = BLACK;
							pUncle->RBFlag = BLACK;
							if(pParent->m_pParent != m_pRoot)
								pParent->m_pParent->RBFlag = RED;
							pNode = pParent->m_pParent;
							if(pNode->m_pParent != nullptr)
								pParent = pNode->m_pParent;
							else
							{
								pParent = nullptr;
							}
						}
						//2.叔叔节点是黑色，又分两种情况
						else if ((pUncle != nullptr && pUncle->RBFlag == BLACK) ||
							pUncle == nullptr)
						{
							//2.1当前节点是其父节点的左孩子
							/*对策：当前节点的父节点作为新的当前节点
									以当前节点为支点右旋*/
							if (pNode == pParent->m_pLeft)
							{
								pNode = pParent;
								RightRotate(pNode);
								pParent = pNode->m_pParent;
							}
							//2.2当前节点是其父节点的右孩子
							/*对策：父节点变为黑色，祖父节点变红色
									再父节点为支点进行左旋*/
							else if (pNode == pParent->m_pRight)
							{
								pParent->RBFlag = BLACK;
								pParent->m_pParent->RBFlag = RED;
								LeftRotate(pParent->m_pParent);
							}
						}
					}
				}


			}
		}

	}

	void LeftRotate(CNode* pNode)
	{
		/*
			pP				   pP
			 pN	    		=>	 pR
		        pR			   pN   pB
		      pA   pB		     pA
		*/

		CNode* pRightChild = pNode->m_pRight;
		CNode* pA;

		if (pRightChild != nullptr)
		{
			pA = pRightChild->m_pLeft;
		}
		else
		{
			pA = nullptr;
		}

		if (pNode->m_pParent != nullptr)
		{
			CNode* pParent = pNode->m_pParent;
			//pP
			if(pNode == pParent->m_pLeft)
				pParent->m_pLeft = pRightChild;
			else
			{
				pParent->m_pRight = pRightChild;
			}
			//pN
			pNode->m_pRight = pA;
			pNode->m_pParent = pRightChild;
			//pR
			pRightChild->m_pLeft = pNode;
			pRightChild->m_pParent = pParent;
			//pA
			if(pA != nullptr)
				pA->m_pParent = pNode;
		}
		else
		{
			//pN
			pNode->m_pRight = pA;
			pNode->m_pParent = pRightChild;
			//pR
			pRightChild->m_pLeft = pNode;
			pRightChild->m_pParent = nullptr;
			//pA
			if(pA != nullptr)
				pA->m_pParent = pNode;
			m_pRoot = pRightChild;
		}

	}

	void RightRotate(CNode* pNode)
	{
		/*		  pP		  pP
				pN			pL
			  pL	=>	  pA  pN		
			pA  pB			 pB
		*/
		
		CNode* pLeftChild = pNode->m_pLeft;
		CNode* pA;
		CNode* pB;
		if (pLeftChild != nullptr)
		{
			pA = pLeftChild->m_pLeft;
			pB = pLeftChild->m_pRight;
		}
		else
		{
			pA = nullptr;
			pB = nullptr;
		}

		if (pNode->m_pParent == nullptr)
		{
			//pN
			pNode->m_pLeft = pB;
			pNode->m_pParent = pLeftChild;
			//pL
			pLeftChild->m_pRight = pNode;
			pLeftChild->m_pParent = nullptr;
			//pB
			if(pB != nullptr)
				pB->m_pParent = pNode;
			m_pRoot = pLeftChild;
		}
		else
		{
			CNode* pParent = pNode->m_pParent;
			//pP
			if(pNode == pParent->m_pLeft)
				pParent->m_pLeft = pLeftChild;
			else
			{
				pParent->m_pRight = pLeftChild;
			}
			//pN
			pNode->m_pLeft = pB;
			pNode->m_pParent = pLeftChild;
			//pL
			pLeftChild->m_pRight = pNode;
			pLeftChild->m_pParent = pParent;
			//pB
			if(pB != nullptr)
				pB->m_pParent = pNode;
		}
	}

	CNode* m_pRoot;
	int m_nSizeCount;
};