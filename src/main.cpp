#include <iostream>
#include <vector>
#include "ClassicPolymorphism.h"
#include "CRTP.h"
#include <any>
#include <variant>
#include <chrono>

template <typename Type, typename... Ts>
auto makeWidget(Ts&&... params)
{
	return std::make_unique<Type>(std::forward<Ts>(params)...);
}

auto logicWidgetCP()
{
	using namespace CP;

	std::cout << "Classic Polymorphism" << std::endl;

	std::vector<std::unique_ptr<Widget>> widgetVector;

	widgetVector.emplace_back(makeWidget<Image>(100, 100, 50, 50, "bg.png"));
	widgetVector.emplace_back(makeWidget<Label>(100, 100, 50, 50, "text"));
	widgetVector.emplace_back(makeWidget<Button>(100, 100, 50, 50, []() {
		std::cout << " Execute button action" << std::endl;
	}));

	for (auto&& widget : widgetVector)
		if(widget)
			widget->Render();


	std::cout << "meashuring execution time" << std::endl;
	{
		auto image = makeWidget<Image>(100, 100, 50, 50, "bg.png");
		auto start = std::chrono::high_resolution_clock::now();

		for (int i = 0; i < 10000000; ++i)
			if (image)
				image->Stub();

		auto diff = std::chrono::high_resolution_clock::now() - start;
		std::cout << "unique_ptr<Derrived> on Derrived class" << std::endl;
		std::cout << "execute time duration = " << std::chrono::duration<double, std::milli>(diff).count() << " milliseconds" << std::endl;
	}

	{
		auto start = std::chrono::high_resolution_clock::now();

		for (int i = 0; i < 10000000; ++i)
			for (auto&& widget : widgetVector)
				if(widget)
					widget->Stub();

		auto diff = std::chrono::high_resolution_clock::now() - start;
		std::cout << "vector unique_ptr<Parent> on Derrived class" << std::endl;
		std::cout << "execute time duration = " << std::chrono::duration<double, std::milli>(diff).count() << " milliseconds" << std::endl;
	}

	std::cout << std::endl;
}

auto logicWidgetCRTP()
{
	using namespace CRTP;

	std::cout << "CRTP Polymorphism" << std::endl;

	using variantWidgetType = std::variant<std::unique_ptr<Image>, std::unique_ptr<Label>, std::unique_ptr<Button>>;
	std::vector < variantWidgetType> widgetVariantVector;

	widgetVariantVector.emplace_back(makeWidget<Image>(100, 100, 50, 50, "bg.png"));
	widgetVariantVector.emplace_back(makeWidget<Label>(100, 100, 50, 50, "text"));
	widgetVariantVector.emplace_back(makeWidget<Button>(100, 100, 50, 50, []() {
		std::cout << " Execute button action" << std::endl;
	}));

	for (auto&& widgetVariant : widgetVariantVector)
		std::visit([](auto&& widget) {if (widget) widget->Render(); }, widgetVariant);

	
	std::cout << "meashuring execution time" << std::endl;
	{
		auto image = makeWidget<Image>(100, 100, 50, 50, "bg.png");
		auto start = std::chrono::high_resolution_clock::now();

		for (int i = 0; i < 10000000; ++i)
			if (image)
				image->Stub();

		auto diff = std::chrono::high_resolution_clock::now() - start;
		std::cout << "unique_ptr<Derrived> on Derrived class" << std::endl;
		std::cout << "execute time duration = " << std::chrono::duration<double, std::milli>(diff).count() << " milliseconds" << std::endl;
	}
	
	{
		auto start = std::chrono::high_resolution_clock::now();
		
		for (int i = 0; i < 10000000; ++i)
			for (auto&& widgetVariant : widgetVariantVector)
				std::visit([](auto&& widget) {if (widget) widget->Stub(); }, widgetVariant);

		auto diff = std::chrono::high_resolution_clock::now() - start;
		std::cout << "vector unique_ptr<Parent> on Derrived class" << std::endl;
		std::cout << "execute time duration = " << std::chrono::duration<double, std::milli>(diff).count() << " milliseconds" << std::endl;
	}

	std::cout << std::endl;
}


int main(int argc, char** argv)
{
	logicWidgetCP();
	logicWidgetCRTP();
	return 0;
}