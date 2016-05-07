#include "AzulCore.h"

PCSTree *GraphicsObjectManager::getTree( void )
{
	return &this->goTree;
}

GraphicsObjectManager::GraphicsObjectManager()
{
   // Get Node 
   PCSNode  *root = this->goTree.getRoot();

   // This should be the first time initializing it.
   assert(root == 0 );

   // Create a Dummy root object, it does nothing
   // remember you need to remove this in the destructor
   // gets trickly with singletons
   NullObject *nodeRoot = new NullObject("Root");

   // insert it into tree
   this->goTree.insert( nodeRoot, root );

}


void GraphicsObjectManager::addObject(GraphicsObject *p)
{
   // Attach new node to the root
   // later we will expose more hierarchy

       // Get Node 
      PCSNode  *root = this->goTree.getRoot();

      // This should NOT be the first time using the tree.
      assert(root != 0 );

      // insert it into tree
      this->goTree.insert( p, root );
}


void GraphicsObjectManager::drawObjects()
{
   // Get Node 
   GraphicsObject  *root = (GraphicsObject  *)this->goTree.getRoot();
   this->privDrawObjectsDepthFirst( root );

}


void GraphicsObjectManager::privDrawObjectsDepthFirst( GraphicsObject *node ) const
{
   GraphicsObject *child = 0;

   // --------- Do draw stuff here -----------------------
   
    //  node->print();
       node->transform();
	   node->setRenderState();
	   node->draw();
   
   // --------- Do draw stuff here -----------------------


   // iterate through all of the active children 
   if (node->getChild() != 0)
	{  
	   child =	(GraphicsObject *)node->getChild();
	   // make sure that allocation is not a child node 
	   while (child != 0)
	   {
         privDrawObjectsDepthFirst( child );
         // goto next sibling
         child = (GraphicsObject *)child->getSibling();
	   }
   }
   else
	{
      // bye bye exit condition
	}

}



GraphicsObjectManager * GraphicsObjectManager::getInstance( void )
{
	return privGetInstance();
}


GraphicsObjectManager * GraphicsObjectManager::privGetInstance( void )
{
	static GraphicsObjectManager gom;
	return &gom;
}
