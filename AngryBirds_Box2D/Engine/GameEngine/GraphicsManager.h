#ifndef GRAPHICS_OBJECT_MANAGER_H
#define GRAPHICS_OBJECT_MANAGER_H

//#include "PCSTree.h"

// forward declare (get into the habit, it's good to use
//class GraphicsObject;

// Singleton
class GraphicsObjectManager
{
public:

	void addObject( GraphicsObject *p);
	void drawObjects( void );
	PCSTree *getTree( void );

	static GraphicsObjectManager * getInstance( void );

private:
	static GraphicsObjectManager *privGetInstance();
   void privDrawObjectsDepthFirst( GraphicsObject *node ) const;
   GraphicsObjectManager();

   // Data -----------------------------------------
   class PCSTree                 goTree;

};


#endif
