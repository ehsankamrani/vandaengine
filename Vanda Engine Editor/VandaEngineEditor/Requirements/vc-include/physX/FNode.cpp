/*
//FNode.cpp, Node class, Mark 2
// by Adam Moravanszky (c) 1998
  */
#include "FNode.h"
#include <stdlib.h>										//defines NULL
#include <assert.h>
/*-Revision----------------------*\
| At: 11/13/98 3:13:32 PM
|Created class.
|
\*-------------------------------*/
/*-Revision----------------------*\
| At: 11/14/98 5:06:56 PM
| Changed Iterator functs to return
| the data instead of the node.
\*-------------------------------*///smart delete
#define sdelete(a) if (a!=NULL) {delete a; a = NULL;}



template <class Content_Type> 
clFNode<Content_Type>::clFNode(clFNode<Content_Type> * clopOldHeadNode,Content_Type * Dataa,bool bOwnDataa)//makes passed Node be next node
	{
	toData=Dataa;
	clopoNextNode=clopOldHeadNode;
	bOwnData=bOwnDataa;
	}

template <class Content_Type> 
clFNode<Content_Type>::~clFNode()
//deletes itself and subnodes
	{
	sdelete (clopoNextNode);
	if (bOwnData)
		sdelete (toData);
	}




template <class Content_Type> 
clFNodeList<Content_Type>::clFNodeList(void)
	{
	clopoHead=NULL;
	NumNodes=0;
	}

template <class Content_Type> 
clFNodeList<Content_Type>::~clFNodeList()
	{
	Clear();
	}


template <class Content_Type> 
void clFNodeList<Content_Type>::Clear(void)
	{
	sdelete (clopoHead);
	NumNodes=0;
	}

template <class Content_Type>
void clFNodeList<Content_Type>::Push(Content_Type *Data,bool bOwned)
	{
	assert(Data);
	clopoHead=new clFNode<Content_Type> (clopoHead,Data,bOwned);
	NumNodes++;
	}

template <class Content_Type> 
void clFNodeList<Content_Type>::Pop(void)
	{
	if (clopoHead)
		{
		clFNode<Content_Type> * clopTemp = clopoHead->GetNext();
		clopoHead->SetNext(NULL);
		delete clopoHead;
		clopoHead=clopTemp;
		NumNodes--;
		}
	}

template <class Content_Type>
Content_Type * clFNodeList<Content_Type>::Peek(void)
	{
	if (clopoHead)
		return clopoHead->GetData();
	else 
		return NULL;
	}

template <class Content_Type>
clFNode<Content_Type>	*	clFNodeList<Content_Type>::NodePeek(void)
	{
	return clopoHead;
	}

template <class Content_Type>
clFNodeListIndex<Content_Type> *  clFNodeList<Content_Type>::ObtainIndex(void)
	{
	return new clFNodeListIndex<Content_Type>(this);
	}

template <class Content_Type> 
void clFNodeList<Content_Type>::Remove(Content_Type *Data)
	{
	clFNode<Content_Type> * CurrNode = clopoHead;
	clFNode<Content_Type> * PrevNode = NULL;
	while (CurrNode)
		{
		if (CurrNode->GetData() == Data)
			{
			if (PrevNode == NULL)
				Pop();
			else
				{
				PrevNode->SetNext(CurrNode->GetNext());
				CurrNode->SetNext(NULL);
				delete CurrNode;
				NumNodes--;
				}
			return;
			}
		PrevNode = CurrNode;
		CurrNode=CurrNode->GetNext();
		}
	}




template <class Content_Type> 
clFNodeListIndex<Content_Type>::clFNodeListIndex(clFNodeList<Content_Type> * clopNodeLista)
	{
	assert(clopNodeLista);
	cloprNodeList=clopNodeLista;
	cloprLastNode=cloprCurrentNode=cloprNodeList->NodePeek();
	}

template <class Content_Type> 
clFNodeListIndex<Content_Type>::~clFNodeListIndex()
	{
	//nothing.
	}

template <class Content_Type> 
clFNode<Content_Type> * clFNodeListIndex<Content_Type>::CurrentNode(void)
	{
	return cloprCurrentNode;
	}
template <class Content_Type> 
clFNode<Content_Type> * clFNodeListIndex<Content_Type>::LastNode(void)
	{
	return cloprLastNode;
	}


template <class Content_Type> 
Content_Type * clFNodeListIndex<Content_Type>::Current(void)
	{
	if (cloprCurrentNode)
		return cloprCurrentNode->GetData();
	else return NULL;
	}

template <class Content_Type> 
Content_Type * clFNodeListIndex<Content_Type>::GoNext(void)
//returns NULL at end of list, but current is never updated to NULL.
	{
	cloprLastNode=cloprCurrentNode;
	if (cloprCurrentNode)
		if (cloprCurrentNode->GetNext())
			{
			cloprCurrentNode=cloprCurrentNode->GetNext();
			return cloprCurrentNode->GetData();
			}
	return NULL;
	}

template <class Content_Type> 
Content_Type * clFNodeListIndex<Content_Type>::GoLast(void)
	{
	clFNode<Content_Type> * cloprTempNode=cloprLastNode;
	cloprLastNode=cloprCurrentNode;
	cloprCurrentNode=cloprTempNode;
	if (cloprCurrentNode)
		return cloprCurrentNode->GetData();
	else 
		return NULL;
	}

template <class Content_Type> 
Content_Type * clFNodeListIndex<Content_Type>::GoHead(void)
	{
	cloprLastNode=cloprCurrentNode;
	cloprCurrentNode=cloprNodeList->NodePeek();
	if (cloprCurrentNode)
		return cloprCurrentNode->GetData();
	else return NULL;
	}

