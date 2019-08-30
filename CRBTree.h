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
	bool RBFlag;	//TRUE��ʾ��ɫ��FALSE��ʾ��ɫ
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

		//��������ǿ������ڵ�ֱ����Ϊ���ڵ㱣��
		if (m_nSizeCount == 0)
		{
			m_pRoot = pNewNode;
		}
		else
		{
			//���ǿ���
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
					//��֧��
				}
			}
		}
		AdjustColor(pNewNode);
		m_nSizeCount++;
	}

	void AdjustColor(CNode* pNode)
	{
		//����Ľڵ��Ǹ��ڵ�,ֱ�ӽ����ڵ�Ϳ��
		if (m_pRoot == pNode)
			m_pRoot->RBFlag = true;
		else
		{
			CNode* pParent = pNode->m_pParent;
			//����ڵ�ĸ��ڵ��Ǻ�ɫ����Υ���κ����ʣ����õ���
			if (pParent->RBFlag == true)
				return;
			//����ڵ�ĸ��ڵ��Ǻ�ɫ����ô��������ۣ�
			else if (pParent->RBFlag == RED)
			{
				while (pNode != nullptr && pNode != m_pRoot && pNode->m_pParent->RBFlag == RED)
				{
					pParent = pNode->m_pParent;
					//һ�����ڵ����游�ڵ������
					if (pParent == pParent->m_pParent->m_pLeft)
					{
						CNode* pUncle = pParent->m_pParent->m_pRight;
						//1. �游�ڵ����һ���ӽڵ㣨����ڵ㣩�Ǻ�ɫ
						/*�Բߣ�����ǰ�ڵ�ĸ��ڵ������ڵ�Ϳ�ڣ�
						�游�ڵ�Ϳ�죬�ѵ�ǰ�ڵ�ָ���游�ڵ㣬
						���µĵ�ǰ�ڵ㿪ʼ�㷨*/

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
						//2.����ڵ��Ǻ�ɫ���ַ��������
						else if ((pUncle != nullptr && pUncle->RBFlag == BLACK) || 
							pUncle == nullptr)
						{
							//2.1��ǰ�ڵ����丸�ڵ���Һ���
							/*�Բߣ���ǰ�ڵ�ĸ��ڵ���Ϊ�µĵ�ǰ�ڵ�
									�Ե�ǰ�ڵ�Ϊ֧������*/
							if (pNode == pParent->m_pRight)
							{
								pNode = pParent;
								pParent = pNode->m_pParent;
								LeftRotate(pNode);
							}
							//2.2��ǰ�ڵ����丸�ڵ������
							/*�Բߣ����ڵ��Ϊ��ɫ���游�ڵ���ɫ
									�ٸ��ڵ�Ϊ֧���������*/
							else if (pNode == pParent->m_pLeft)
							{
								pParent->RBFlag = BLACK;
								pParent->m_pParent->RBFlag = RED;
								RightRotate(pParent->m_pParent);
							}
						}

					}

					//�������ڵ����游�ڵ���Һ���
					else if (pParent == pParent->m_pParent->m_pRight)
					{
						CNode* pUncle = pParent->m_pParent->m_pLeft;
						//1. �游�ڵ����һ���ӽڵ㣨����ڵ㣩�Ǻ�ɫ
						/*�Բߣ�����ǰ�ڵ�ĸ��ڵ������ڵ�Ϳ�ڣ�
						�游�ڵ�Ϳ�죬�ѵ�ǰ�ڵ�ָ���游�ڵ㣬
						���µĵ�ǰ�ڵ㿪ʼ�㷨*/

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
						//2.����ڵ��Ǻ�ɫ���ַ��������
						else if ((pUncle != nullptr && pUncle->RBFlag == BLACK) ||
							pUncle == nullptr)
						{
							//2.1��ǰ�ڵ����丸�ڵ������
							/*�Բߣ���ǰ�ڵ�ĸ��ڵ���Ϊ�µĵ�ǰ�ڵ�
									�Ե�ǰ�ڵ�Ϊ֧������*/
							if (pNode == pParent->m_pLeft)
							{
								pNode = pParent;
								RightRotate(pNode);
								pParent = pNode->m_pParent;
							}
							//2.2��ǰ�ڵ����丸�ڵ���Һ���
							/*�Բߣ����ڵ��Ϊ��ɫ���游�ڵ���ɫ
									�ٸ��ڵ�Ϊ֧���������*/
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