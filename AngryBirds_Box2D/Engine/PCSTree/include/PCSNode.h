#ifndef PCSNODE_H
#define PCSNODE_H

#define PCSNODE_NAME_SIZE (16)
#define PCSNODE_VERSION 1.3

enum PCSNodeReturnCode
{
   PCSNode_SUCCESS,
   PCSNode_FAIL_NULL_PTR,
   PCSNode_FAIL_RETURN_NOT_INITIALIZED,
   PCSNode_DWORD = 0x7fffffff
};

class PCSNode
{
public:
   // constructor
   PCSNode();
   
   // copy constructor
   PCSNode(const PCSNode &in );

   // Specialize Constructor
   PCSNode( PCSNode * const inParent, PCSNode * const inChild, PCSNode * const inSibling, const char * const inName);
   PCSNode( const char * const inName );


   // destructor
   ~PCSNode();

   // assignment operator
  PCSNode &operator = (const PCSNode &in);

   // accessors
   void setParent( PCSNode * const in );
   void setChild( PCSNode * const in );
   void setSibling( PCSNode * const in );
   PCSNode *getParent( void ) const;
   PCSNode *getChild( void ) const;
   PCSNode *getSibling( void ) const;

   // name
   PCSNodeReturnCode setName(const char * const inName );
   PCSNodeReturnCode getName(char * const outBuffer, int sizeOutBuffer ) const;

   // dump
   void print() const;
   void dumpChildren() const;
   void dumpSiblings() const;

   // get number of children/siblings
   int getNumSiblings() const;
   int getNumChildren() const;

private:
   PCSNode *parent;
   PCSNode *child;
   PCSNode *sibling;

   char     name[PCSNODE_NAME_SIZE];
};


#endif