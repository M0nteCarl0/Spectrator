// Spectrator.cpp: главный файл проекта.

#include "stdafx.h"
#include "MainView.h"

using namespace Spectrator;

[STAThreadAttribute]
int main(array<System::String ^> ^args)
{
	// Включение визуальных эффектов Windows XP до создания каких-либо элементов управления
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false); 

	// Создание главного окна и его запуск
	Application::Run(gcnew MainView());
	return 0;
}
