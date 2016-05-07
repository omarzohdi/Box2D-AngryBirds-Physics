#include "Engine.h"
#include "AzulCore.h"

//-----------------------------------------------------------------------------
// Engine::Run()
//		Game flow and loops
//-----------------------------------------------------------------------------
void Engine::Run(    )
{
	// Get the instance
	Engine *p = AzulCore::getEngine();

	// perform any initialization
	p->Initialize();

	// load all content such as objects, graphics, etc. Setup data before game loop
	p->LoadContent();

	// Game Loop until an exit
	while( p->isRunning() )
	{
		// called once per frame, update data, tranformations, etc
		p->Update();

		// called once per frame, only do rendering here
		p->Draw();
	}

	// unload content (resources loaded above)
	p->UnLoadContent();
}



