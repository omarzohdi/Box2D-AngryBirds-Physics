
#ifndef ENGINE_H
#define ENGINE_H

#define START_GAME() (Engine *p = AzulCore::getEngine();	p->running = true;)

//////////////////
// Engine
//		Abstract class that Azul Engine inherits from
// there are 5 abstract functions that Azul Engine must define:
//  --- Initialize, LoadContent, Update, Draw, UnLoadContent
//
// - Engine::Run()
//      This will run a game loop calling Initialize, LoadContent
//   (loop) Update and Draw, then upon exiting call UnloadContent
//
// - Engine::Quit()
//		This will end the loop of the Update and Draw methods.
///////////////////
class Engine
{

public:


	virtual void Initialize() = 0;
	virtual void LoadContent()= 0;
	virtual void Update()= 0;
	virtual void Draw()= 0;
	virtual void UnLoadContent()= 0;

	static void Run();

	
	void Quit() { running = false; };

protected:
	bool running;

private:
	bool isRunning() { return running; };

};


#endif