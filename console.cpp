/**************************************************
console.cpp
console

by Jeong Kim (23 Jan 2007)

Required libraries:
D3D8.LIB, D3DX8.LIB, D3DXOF.LIB, and DXGUID.LIB 
**************************************************/

#define _CONSOLE
//#define _WINDOWS
// 	#define _WINDOWS_STORMWARNING_SPRITE

#include <vector>

#include "../../core/directx/jimAdams/D3D8or9.h"

#pragma comment(lib,"../../core/directx/DirectX 8 SDK/lib/d3d8.lib")
#pragma comment(lib,"../../core/directx/DirectX 8 SDK/lib/d3dx8.lib")
#pragma comment(lib,"../../core/directx/DirectX 8 SDK/lib/dxguid.lib")
#pragma comment(lib,"../../core/directx/DirectX 8 SDK/lib/d3dxof.lib")
#pragma comment(lib,"../../core/directx/DirectX 8 SDK/lib/dinput8.lib")
#pragma comment(lib,"../../core/directx/DirectX 8 SDK/lib/dsound.lib")
#pragma comment(lib,"../../core/directx/DirectX 8 SDK/lib/dxerr8.lib")
//#pragma comment(lib,"odbc32.lib")
//#pragma comment(lib,"odbccp32.lib")
#pragma comment(lib,"winmm.lib")
#pragma comment(lib,"../../core/directx/DirectX 8 SDK/lib/ddraw.lib")

#if defined(_DEBUG)
#pragma comment(lib,"../../core/lib/corej_d.lib")
#elif defined(NDEBUG)
#pragma comment(lib,"../../core/lib/corej.lib")
#endif

#include "Core_Graphics.h"
using namespace core::graphics;
#include "./tools/tools2d/resource.h"

#include "./sample/sample.h"
#include "./sample/battle.h"
#include "./tools/tools2d/spritetool.h"
#include "./tools/tools2d/maptool.h"
#include "./the tower/App.h"

#include "./sample/2002 tetris/C_Code_Me/tetris2002_c_code_me.h"
#include "./sample/2002 tetris/CPP_Code/tetris2002_cpp_code.h"
#include "./sample/2001 kenny/source/kenny/kennymain.h"
#include "../device/system/win32/win32.h"
#include "../basic/math dynamics/_Movement Technique-cyber/DxWFrame.h"

#include <iostream>
#include "./sample/language/language.h"

#include "./sample/testD3D/testSolar.h"

// 함수포인터들을 union이나 struct로 만들고 다중 벡터에 담아서 실행시에 타입을 판단하여 실행한다.
// class_default_constructor cApplication cApplication_process_member winmain_function

#if defined(_WINDOWS)
#pragma comment(linker,"/SUBSYSTEM:WINDOWS")
#endif

#include <io.h>

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	using namespace std;
	string help = " \n\
	console_dx8 0 0 0~28 \n\
	console_dx8 0 0 0  = (default)graphics::Effects::Alpha; \n\
	console_dx8 0 0 1  = graphics::Font::Font; \n\
	console_dx8 0 0 2  = graphics::Font::Font2; \n\
	console_dx8 0 0 3  = graphics::Geometry::Line2D; \n\
	console_dx8 0 0 4  = graphics::Geometry::Line3D; \n\
	console_dx8 0 0 5  = graphics::Geometry::Draw2D; \n\
	console_dx8 0 0 6  = graphics::Geometry::Draw3D; \n\
	console_dx8 0 0 7  = graphics::Effects::Billboard; \n\
	console_dx8 0 0 8  = graphics::Effects::Lights; \n\
	console_dx8 0 0 9  = graphics::Device::ZBuffer; \n\
	console_dx8 0 0 10 = graphics::Effects::Particles; \n\
	console_dx8 0 0 11 = graphics::Transform::Transform2D; \n\
	console_dx8 0 0 12 = graphics::Transform::Transform; \n\
	console_dx8 0 0 13 = graphics::Transform::FixedPipeline; \n\
	console_dx8 0 0 28 = graphics::Image::SpriteTool; \n\
	\n\
	console_dx8 0 0 14 = math::CircleCollision; \n\
	console_dx8 0 0 15 = math::Triangle; \n\
	console_dx8 0 0 16 = math::RotationByMouse; \n\
	console_dx8 0 0 25 = math::DotPlaneCollision; \n\
	console_dx8 0 0 27 = math::MatrixVector; \n\
	\n\
	console_dx8 0 0 17 = system::Timers; \n\
	console_dx8 0 0 18 = system::PopupMove; \n\
	console_dx8 0 0 19 = system::DataPackage; \n\
	console_dx8 0 0 26 = system::ThreadSemaphore; \n\
	\n\
	console_dx8 0 0 20 = language::BitOperator; \n\
	\n\
	console_dx8 0 0 21 = engine::Frustum; \n\
	console_dx8 0 0 22 = engine::Objects; \n\
	console_dx8 0 0 23 = engine::Coordinate; \n\
	console_dx8 0 0 24 = engine::flight_solar; \n\
	\n\
	console_dx8 1 0    = kenny2001 \n\
	console_dx8 1 1    = winmain_32 (내부연구자료 파라메터로 빼야됨) \n\
	console_dx8 1 2    = tetris2002_gdi \n\
	console_dx8 1 3    = tetris2002_ddraw \n\
	console_dx8 2      = cpp language test (내부연구자료 파라메터로 빼야됨)";

		cout << help << endl;

	std::vector<unsigned int> commands;
	char * pch = strtok (lpCmdLine, " ,.-");
	while (pch != NULL)
	{
		commands.push_back((unsigned int)atoi(pch));
		pch = strtok (NULL, " ,.-");
	}
	while(commands.size()<3) commands.push_back(0);
	int ret = 0;

#ifdef _WINDOWS
#ifdef _DEBUG
	AllocConsole();
	freopen("CONOUT$", "w", stdout);
	freopen("CONIN$", "r", stdin);
#endif
#endif
	std::cout << "console start" << std::endl;

	if(commands[0]==2)
	{
		ret = language_main();
#ifdef _WINDOWS
		std::cout << "please input anykey" << std::endl; std::string a; std::cin >> a;
#endif
	}

	if(commands[0]==1)
	{
		int (__stdcall *Process2[6])(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd);
		Process2[0] = kenny2001::kennyMain;
		Process2[1] = WinMain_32;
		Process2[2] = WinMain_Tetris2002_C_Code_Me;
		Process2[3] = WinMain_Tetris2002_CPP_Code;
		Process2[4] = WinMain_Movement09;
		Process2[5] = WinMain_testD3D;
		ret = Process2[commands[1]](hInstance, hPrevInstance, lpCmdLine, nShowCmd);
	}

	if(commands[0]==0)
	{
		#ifdef _WINDOWS_STORMWARNING_SPRITE
		commands.clear(); commands.push_back(0); commands.push_back(0); commands.push_back(28);
		#endif

		HRESULT hr=S_OK;
		DXTrace("trace.txt", 1, hr, "aaa", FALSE);

		// app 등록 및 실행
		std::vector<cApplication *> vApp;
		vApp.push_back(new sample::cApp(commands[2]));					// 0 0 0~28
		vApp.push_back(new Tools2D::tilemap::cMapTool());				// 0 1 0
		vApp.push_back(new Tools2D::spriteanimation::cAnimationTool());	// 0 2 0
		vApp.push_back(new sample::battle::cApp());						// 0 3 0
		vApp.push_back(new theTower::cApp());							// 0 4 0

		ret = vApp[commands[1]]->Run();

		for(int i=0; i<vApp.size(); i++) {
			delete vApp[i]; vApp[i] = NULL;
		}
		vApp.clear();
	}

	std::cout << "console end : " << ret << std::endl;

	return ret; // return to OS(0=정상종료)
	// return; 반환값없는 강제종료
}

//#elif defined(_CONSOLE)
#if defined(_CONSOLE)
#pragma comment(linker,"/SUBSYSTEM:CONSOLE")
// www.winapi.co.kr
int main(int argc,char *argv[])
{
	std::string command = "";
	
	std::vector<std::string> commands;
	for(int i=1; i<argc; i++) {
		commands.push_back(argv[i]);
		command += argv[i];
		command += ", ";
	}

	WinMain(GetModuleHandle(NULL),NULL,const_cast<char*>(command.c_str()),SW_SHOW);

	return 0;
}
#endif