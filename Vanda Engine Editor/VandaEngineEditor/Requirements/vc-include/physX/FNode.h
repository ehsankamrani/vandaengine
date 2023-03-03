/*----------------------------------------------------------------------------*\
|
|						    NVIDIA PhysX Technology
|
|							     www.nvidia.com
|
\*----------------------------------------------------------------------------*/


#ifndef __FNODE_H__
#define __FNODE_H__

/*
//FNode.h, Node class definiton, Mark 2
// by Adam Moravanszky (c) 1998
  */
/*-Revision----------------------*\
| At: 1/9/99 4:39:50 PM
|changed pragma once --> ifdefs
|
\*-------------------------------*/


template <class Content_Type> class clFNodeListIndex;


template <class Content_Type> class clFNode 
/*---------------------------*\
|Node class.
|A node deletes all its children
|and its contents (stored by reference)
|when its deleted.
|Data will be deleted at destruct unless
|bOwnData is false.
\*---------------------------*/
	{
	clFNode<Content_Type> * clopoNextNode;
	Content_Type * toData;
	bool bOwnData;							

	public:
	clFNode(clFNode<Content_Type> * clopOldHeadNode,Content_Type * Data,bool bOwnData=true);//makes passed Node be next node
	~clFNode();//deletes itself and subnodes
	inline Content_Type				*	GetData(void) {return toData; };
	inline clFNode<Content_Type>	*	GetNext(void) {return clopoNextNode; };
	inline void							SetNext(clFNode<Content_Type> * clopNewNext) {clopoNextNode = clopNewNext; };
	inline void							SetOwnership(bool bOwn) {bOwnData = bOwn;};
	inline bool							GetOwnership(void) {return bOwnData;};
	};




template <class Content_Type> class clFNodeList
/*---------------------------*\
|Linked List class.  Stores a bunch of
|Nodes, and supports basic stack operations.
|
|An Index Object can be obtained, 
|which must be deleted by the user.
\*---------------------------*/
	{
	clFNode<Content_Type> * clopoHead;
	unsigned NumNodes;

	public:
	clFNodeList(void);
	~clFNodeList();
	void Clear(void);
	void Push(Content_Type *Data,bool bOwnData=true);
	void Pop(void);
	unsigned GetNumNodes(void) {return NumNodes; };
	void IncNumNodes(int Delta) {NumNodes+=Delta; };					//this is not very pretty -- but if someone from the outside messes
	Content_Type	*	Peek(void);										//with the nodes directly, it would be nice if it could (would) update the count.
	clFNode<Content_Type>		*	NodePeek(void);
	clFNodeListIndex<Content_Type> * ObtainIndex(void);
	void InsertAfter(clFNode<Content_Type> *Node,Content_Type *Data,bool bOwnData=true)
		{
		NumNodes ++;
		clFNode<Content_Type> *  N=new clFNode<Content_Type> (Node->GetNext(),Data,bOwnData);
		Node->SetNext(N);
		}
	void Remove(Content_Type *Data);//removes first occurence of data in list
	};




template <class Content_Type> class clFNodeListIndex
/*---------------------------*\
|This is what is sometimes called
|an iterator.  With it one can traverse
|the list and do
|any kind of operation on a list which the
|above class doesn't implement.
|The list object is stored by reference --
|there may be several Index classes for one list.
\*---------------------------*/
	{
	clFNodeList<Content_Type> * cloprNodeList;
	clFNode<Content_Type> * cloprCurrentNode;
	clFNode<Content_Type> * cloprLastNode;					//not previous, but what was current before last change.
	public:
	clFNodeListIndex(clFNodeList<Content_Type> * clopNodeLista);
	~clFNodeListIndex();
	clFNode<Content_Type> * CurrentNode(void);
	clFNode<Content_Type> * LastNode(void);
	Content_Type * Current(void);
	Content_Type * GoNext(void);
	Content_Type * GoLast(void);
	Content_Type * GoHead(void);
	};


/*Usage example:
#include <FNode.cpp>
class X		--important -- class has to be a type that can be deleted, or ownership flag should be set to false.
	{
	char i;
	public:
	X(char q) {i=q;};
	};
void main (void)
	{
	clFNodeList<X> cloLinkedList;
	cloLinkedList.Push(new X('a'));
	cloLinkedList.Push(new X('b'));
	X * letter = cloLinkedList.Peek();
	cloLinkedList.Pop();
	letter = cloLinkedList.Peek();

	clFNode<X> * clopSomeNode=cloLinkedList.NodePeek();
	cloLinkedList.Push(new X('c'));
	cloLinkedList.Push(new X('d'));

	clFNodeListIndex<X> * Index=cloLinkedList.ObtainIndex();

clopSomeNode=Index->Current();
clopSomeNode=Index->GoNext();
clopSomeNode=Index->GoHead();
clopSomeNode=Index->GoLast();

delete Index;

	}


*/
#endif //__FNODE_H__
//NVIDIACOPYRIGHTBEGIN
///////////////////////////////////////////////////////////////////////////
// Copyright © 2010 NVIDIA Corporation.
// All rights reserved. www.nvidia.com
///////////////////////////////////////////////////////////////////////////
//NVIDIACOPYRIGHTEND