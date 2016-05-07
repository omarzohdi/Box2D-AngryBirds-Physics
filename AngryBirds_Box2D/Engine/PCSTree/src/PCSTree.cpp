#include <stdio.h>
#include <assert.h>
#include <string.h>

#include "PCSTree.h"
#include "PCSNode.h"


// constructor
PCSTree::PCSTree()
   : root(0)
{
   this->info.numNodes = 0;
   this->info.maxNodeCount = 0;
   this->info.numLevels = 0;
   this->info.maxLevelCount = 0;

  // printf("PCSTree: constructor()\n");
};

// destructor
PCSTree::~PCSTree()
{
 //  printf("PCSTree: destructor()\n");
};


// get Root
PCSNode *PCSTree::getRoot( void ) const
{
   return root;
}


// insert
void PCSTree::insert(PCSNode *inNode, PCSNode *parent)
{
   assert( inNode );

   // insert to root
   if( 0 == parent )
   {
      this->root = inNode;
      inNode->setChild(0);
      inNode->setParent(0);
      inNode->setSibling(0);

      this->InfoAddNode();
      this->InfoAddNewLevel( inNode );
   }
   else  // insert inside the tree
   {
      if ( parent->getChild() == 0)
      { // child is 0, just add child
         parent->setChild( inNode );
         
         inNode->setParent( parent );
         inNode->setChild( 0 );
         inNode->setSibling( 0 );

         this->InfoAddNode();
         this->InfoAddNewLevel( inNode );
      }
      else
      { // add as sibling
       
         // Get first child
         PCSNode *first = parent->getChild();

         inNode->setParent( parent );
         inNode->setChild( 0 );
         inNode->setSibling( first );

         parent->setChild( inNode );

         this->InfoAddNode();
      }

   }

}

// info helper functions
void PCSTree::InfoAddNode()
{
   info.numNodes += 1;

   if( info.numNodes > info.maxNodeCount )
   {
      info.maxNodeCount += 1;
   }
}

// info helper functions
void PCSTree::InfoRemoveNode()
{
   info.numNodes -= 1;

}

// info helper functions
void PCSTree::InfoAddNewLevel( PCSNode *inNode )
{
   PCSNode *n = inNode;
   int count = 1;

   // count your way back up
   while( n != root )
   {
      n = n->getParent();
      count++;
   }

   // new level count?
   if( count > info.numLevels )
   {
      info.numLevels = count;
   }

   // new max count?
   if( info.numLevels > info.maxLevelCount )
   {
      info.maxLevelCount = info.numLevels;
   }

}

void PCSTree::InfoRemoveNewLevel( PCSNode *inNode )
{
	inNode;
   info.numLevels = 0;
   
   this->privRecalculateLevel( root );

}

void PCSTree::privRecalculateLevel( PCSNode *node ) 
{
   PCSNode *child = 0;

   if( node != 0 )
   {
      // get level count
      {
         PCSNode *n = node;
         int count = 1;

         // count your way back up
         while( n != root )
         {
            n = n->getParent();
            count++;
         }

         // new level count?
         if( count > info.numLevels )
         {
            info.numLevels = count;
         }
      }




      // iterate through all of the active children 
      if (node->getChild() != 0)
	   {  
	      child =	node->getChild();
	      // make sure that allocation is not a child node 
	      while (child != 0)
	      {
            privRecalculateLevel( child );
            // goto next sibling
            child = child->getSibling();
	      }
      }
      else
	   {
         // bye bye exit condition
	   }
   }
}

// Remove
 void PCSTree::remove(PCSNode * const inNode)
 {
    assert( inNode );

    if( inNode->getChild() == 0 )
    {
       // last node
       if( inNode->getSibling() == 0 )
       {
          // find the previous child
          PCSNode *parent;
          parent = inNode->getParent();

          // special case root
          if(parent == 0)
          {
             this->root = 0;
          }
          else
          {
             assert( parent != 0 );

             PCSNode *tmp;
             // goto eldest child
             tmp = parent->getChild();
             assert( tmp != 0 );

             if( tmp->getSibling() == 0 )
             {
                // delete inNode so it's parent is 0
                // in child has no siblings
                parent->setChild( 0 );
             }
             else
             {
                // now iterate until child
                while ( tmp->getSibling() != inNode )
                {
                   tmp = tmp->getSibling();
                }
                // this point we found the sibling
                PCSNode *prev = tmp;
                prev->setSibling(0);
             }

             // at this point, child,sibling are 0
             // we could potentially have different levels
             // recalculate
             InfoRemoveNewLevel( inNode );
          }
      }
      else
      {   // I have a sibling to the right of me
          // find the previous child
          PCSNode *parent;
          parent = inNode->getParent();
          assert( parent != 0 );

          PCSNode *tmp;

          // goto eldest child
          tmp = parent->getChild();
          assert( tmp != 0 );

          if( tmp == inNode )
          { 
             // we are deleting a eldest child with siblings
             parent->setChild( tmp->getSibling() );
          }
          else
          {
             // now iterate until child
             while ( tmp->getSibling() != inNode )
             {
                tmp = tmp->getSibling();
             }

             // this point we found the sibling
             PCSNode *prev = tmp;
             prev->setSibling(inNode->getSibling());
          }
      }

       inNode->setChild(0);
       inNode->setParent(0);
       inNode->setSibling(0);
       this->InfoRemoveNode();
       return;
    }
    else
    {
       // If we are here, recursively call
       PCSNode *tmp = inNode->getChild();
       assert( tmp != 0);

       remove( tmp );
       remove( inNode );
    }

 }

 // get tree info
 void PCSTree::getInfo( PCSTreeInfo &infoContainer )
 {
   this->InfoRemoveNewLevel( this->root );

    infoContainer = this->info;
 }

void PCSTree::depthFirst( PCSNode *heap )
{
   PCSNode *child = 0;
   char name[PCSNODE_NAME_SIZE];

   heap->getName( name, PCSNODE_NAME_SIZE );
   printf("->>> depthFirst( %s )\n",name);


   // iterate through all of the active children 
   if (heap->getChild() != 0)
	{  
	   child =	heap->getChild();
	   // make sure that allocation is not a child heap 
	   while (child != 0)
	   {
         depthFirst( child );
         // goto next sibling
         child = child->getSibling();
	   }
   }
   else
	{
      // bye bye exit condition
	}

}

void PCSTree::dumpTree( ) const
{
   printf("\n");
   printf("dumpTree () -------------------------------\n");
   this->privDumpTreeDepthFirst( root );


}

void PCSTree::privDumpTreeDepthFirst( PCSNode *node ) const
{
   PCSNode *child = 0;

   // dump
   node->print();

   // iterate through all of the active children 
   if (node->getChild() != 0)
	{  
	   child =	node->getChild();
	   // make sure that allocation is not a child node 
	   while (child != 0)
	   {
         privDumpTreeDepthFirst( child );
         // goto next sibling
         child = child->getSibling();
	   }
   }
   else
	{
      // bye bye exit condition
	}

}

