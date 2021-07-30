#include "Game.h"
#include <variant>

Game game;

bool Update(float dt)
{
	bool quit = Core::Input::IsPressed(Core::Input::KEY_ESCAPE);
	game.Update(dt);

	//int x, y;
	//Core::Input::GetMousePos(x, y);
	//psPosition.x = static_cast<float>(x);
	//psPosition.y = static_cast<float>(y);

	//if (Core::Input::IsPressed(Core::Input::BUTTON_LEFT))
	//{
	//	std::vector<dwb::Color> colors = { dwb::Color::white, dwb::Color::red, dwb::Color::green, dwb::Color::blue, dwb::Color::magenta, dwb::Color::cyan, dwb::Color::orange, dwb::Color::yellow };
	//	engine.Get<dwb::ParticleSystem>()->Create(psPosition, 50, 2, colors[dwb::RandomRangeInt(0, colors.size())], 150);
	//
	//	engine.Get<dwb::AudioSystem>()->PlayAudio("explosion");
	//}

	//scene.getActor<Player>()->shape->color = dwb::Color{dwb::Random(), dwb::Random(), dwb::Random()};
	//scene.getActor<Enemy>()->shape->color = dwb::Color{dwb::Random(), dwb::Random(), dwb::Random()};

	return quit;
}

void Draw(Core::Graphics& graphics)
{		
	game.Draw(graphics);
}

int inc(int i) { return ++i; }
int dec(int i) { return --i; }

union Data
{
	int i;
	char str[5];
	bool b;
};



int main()
{
	//Data data = {0};

	//data.b = true;
	//data.i = 534;
	//data.str[0] = '#';

	//std::cout << data.i << std::endl;
	//std::cout << data.b << std::endl;
	//std::cout << data.str << std::endl;

	//std::variant<int, std::string, float, bool> var;
	//var = 20;
	//var = 1;

	////std::cout << std::get<int>(var) << std::endl;
	//std::cout << std::get<bool>(var) << std::endl;
	//std::cout << std::get<3>(var) << std::endl;

	//int (*operation)(int);
	//operation = &dec;

	//std::cout << operation(5) << std::endl;

	char name[] = "CSC196";
	Core::Init(name, 800, 600, 120);

	Core::RegisterUpdateFn(Update);
	Core::RegisterDrawFn(Draw);

	game.Initialize();

	Core::GameLoop();
	Core::Shutdown();

	game.Shutdown();
}
