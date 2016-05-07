#ifndef PCSTREE_H
#define PCSTREE_H

// Simple data structure
struct PCSTreeInfo
{
   int numNodes;
   int maxNodeCount;
   int numLevels;
   int maxLevelCount;
};

// forward declare
class PCSNode;

// PCSTree class 
class PCSTree
{
public:

   // constructor
   PCSTree();

   // destructor
   ~PCSTree();

   // get Root
   PCSNode *getRoot( void ) const;

   // insert
   void insert(PCSNode * const inNode, PCSNode * const parent);

   // remove
   void remove(PCSNode * const inNode);

   // get info
   void getInfo( PCSTreeInfo &infoContainer );
   void dumpTree( ) const;   

private:
   // update info
   void InfoAddNode();
   void InfoRemoveNode();
   void InfoAddNewLevel( PCSNode *inNode );
   void InfoRemoveNewLevel( PCSNode *inNode );

   // copy constructor 
   PCSTree( PCSTree &in );

   // assignment operator
   PCSTree & operator = (const PCSTree &in);

   // Data
   PCSTreeInfo info;
   PCSNode     *root;

   // safety
   void depthFirst( PCSNode *tmp);
   void privDumpTreeDepthFirst( PCSNode *node ) const;
   void privRecalculateLevel( PCSNode *node );
};



#endif