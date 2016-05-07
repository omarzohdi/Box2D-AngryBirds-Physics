#include <string.h>
#include <stdio.h>
#include <assert.h>

#include "PCSTree.h"
#include "PCSNode.h"

// constructor
PCSNode::PCSNode()
   :parent(0),child(0),sibling(0)
{
   memset( this->name, 0, PCSNODE_NAME_SIZE);
}
   
// copy constructor
PCSNode::PCSNode(const PCSNode &in )
   :parent(in.parent),child(in.child),sibling(in.sibling)
{
  // copy the correct length
   memcpy( this->name, &in.name[0], PCSNODE_NAME_SIZE);
}

// Specialize Constructor
PCSNode::PCSNode( PCSNode * const inParent, PCSNode * const inChild, PCSNode * const inSibling, const char * const inName)
   : parent( inParent ), child(inChild), sibling(inSibling)
{
   this->setName( inName );
}
   
PCSNode::PCSNode( const char * const inName)
   :parent(0),child(0),sibling(0)
{
   this->setName( inName );
}
   
// destructor
PCSNode::~PCSNode()
{
}

// assignment operator
PCSNode &PCSNode::operator = (const PCSNode &in)
{
   this->child = in.child;
   this->parent = in.parent;
   this->sibling = in.sibling;

  // copy the correct length
   memcpy( this->name, &in.name[0], PCSNODE_NAME_SIZE);

   return *this;
}


void PCSNode::setParent( PCSNode * const in )
{
   this->parent = in;
}

void PCSNode::setChild( PCSNode * const in )
{
   this->child = in;
}

void PCSNode::setSibling( PCSNode * const in )
{
   this->sibling = in;
}


PCSNode *PCSNode::getParent( void ) const
{
   return this->parent;
}

PCSNode *PCSNode::getChild( void ) const
{
   return this->child;
}

PCSNode *PCSNode::getSibling( void ) const
{
   return this->sibling;
}


PCSNodeReturnCode PCSNode::setName(const char * const inName )
{
   PCSNodeReturnCode returnCode = PCSNode_FAIL_RETURN_NOT_INITIALIZED;

   if( inName == 0 )
   {
      returnCode = PCSNode_FAIL_NULL_PTR;
   }
   else
   {
      int strLength = strlen( inName );
      int copyLength(0);

      // zero the string
      memset( this->name, 0x00, PCSNODE_NAME_SIZE );

      // copy upto maximum
      if( strLength < PCSNODE_NAME_SIZE-1 )
      {
         copyLength = strLength;
      }
      else
      {
         copyLength = PCSNODE_NAME_SIZE-1;
      }

      // copy the correct length
      memcpy( this->name, inName, copyLength );

      // check the last byte for 0
      assert(this->name[PCSNODE_NAME_SIZE-1] == 0 );

      returnCode = PCSNode_SUCCESS;
   }

   return returnCode;
}


PCSNodeReturnCode PCSNode::getName(char * const outBuffer, int sizeOutBuffer ) const
{
   PCSNodeReturnCode returnCode = PCSNode_FAIL_RETURN_NOT_INITIALIZED;

   if(outBuffer == 0)
   {
      // always fail to alert programmer to problem
      returnCode = PCSNode_FAIL_NULL_PTR;
   }
   else
   {

      // zero the string
      memset( outBuffer, 0, sizeOutBuffer);

      if(this->name != 0)
      {
         // copy upto maximum
         if ( sizeOutBuffer < PCSNODE_NAME_SIZE )
         {
            memcpy( outBuffer, this->name, sizeOutBuffer-1 );
         }
         else
         {
            memcpy( outBuffer, this->name, PCSNODE_NAME_SIZE-1 );
         }

         // check the last byte for 0
         assert(outBuffer[sizeOutBuffer-1] == 0 );

         returnCode = PCSNode_SUCCESS;
      }
      else
      {
          // this->name is 0
          returnCode = PCSNode_FAIL_NULL_PTR;
      }
   }

   return returnCode;
}

void PCSNode::print() const
{
   char parentName[PCSNODE_NAME_SIZE];
   char childName[PCSNODE_NAME_SIZE];
   char siblingName[PCSNODE_NAME_SIZE];
   
   if( parent != 0)
   {
      this->parent->getName(parentName, PCSNODE_NAME_SIZE);
   }
   else 
   {
      memcpy( parentName, "0", 2 );
   }

   if( child != 0)
   {
      this->child->getName(childName, PCSNODE_NAME_SIZE);
   }
   else
   {
      memcpy( childName, "0", 2 );
   }

   if( sibling != 0 )
   {
      this->sibling->getName(siblingName, PCSNODE_NAME_SIZE);
   }
   else
   {
      memcpy( siblingName, "0",2 );
   }

   printf("\n");
   printf("   name: %s\n",this->name);
   printf("   addr: 0x%p\n",this);
   printf(" parent: %s (0x%p)\n", parentName, this->parent);
   printf("  child: %s (0x%p)\n", childName, this->child);
   printf("sibling: %s (0x%p)\n", siblingName, this->sibling);
}

void PCSNode::dumpChildren() const
{
   PCSNode *tmp = this->child;

   while( tmp != 0 )
   {
      tmp->print();
      tmp = tmp->getSibling(); 
   }
}


void PCSNode::dumpSiblings() const
{
   PCSNode *tmp = this->parent;

   // protection against root node
   if (this->parent != 0 )
   {
      tmp = tmp->child;
      while( tmp != 0 )
      {
         tmp->print();
         tmp = tmp->getSibling(); 
      }
   }
}

int PCSNode::getNumSiblings() const
{
   int count = 0;
   PCSNode *tmp = this->parent;

   // protection against root node
   if (this->parent != 0 )
   {
      tmp = tmp->child;
    
      while( tmp != 0 )
      {
         count++;
         tmp = tmp->getSibling(); 
      }
   }
   else
   {
      count++;
   }
   return count;
}

int PCSNode::getNumChildren() const
{
   int count = 0;

   PCSNode *tmp = this->child;

   while( tmp != 0 )
   {
      count++;
      tmp = tmp->getSibling(); 
   }

   return count;
}