#include "visualizer.h"
#include <Siv3D.hpp>
using namespace std;

void Main() {
	Scene::SetBackground(ColorF(1.0));
	Window::Resize({ 672, 816 });

	Visualizer visualizer;

	while (System::Update()) visualizer.visualize();
}