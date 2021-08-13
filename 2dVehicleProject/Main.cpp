
#include <iostream>
#include <chrono>
#include <memory>
#include <thread>

#include <FL/Fl_Double_Window.H>

#include "Utilities.h"
#include "Car.h"

#include <tuple>

int main() {
	//Test section
	
	//end test section 

	auto win = std::make_unique<Fl_Double_Window>(screenWidth, screenHeight, "2dCar");
	win->color(FL_WHITE);
	


	Car c{ 1000, carLength, carWidth, Vec2d{300,300} };

	win->end();
	win->show();

	using namespace std::literals::chrono_literals;
	auto nextDrawing = std::chrono::steady_clock::now();
	int n{ 0 };
	while (win->shown()) {
		std::this_thread::sleep_until(nextDrawing);
		nextDrawing += std::chrono::microseconds(16ms); //hopefully 60 fps
		std::cout << n++ << std::endl;

		Fl::check();
		Fl::redraw();
	}
	
	
	
}