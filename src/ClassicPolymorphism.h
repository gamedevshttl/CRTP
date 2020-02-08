#include <iostream>
#include <string>
#include <functional>

namespace CP //Classic Polymorphism
{

	class Widget
	{
	public:
		Widget()
		{}

		Widget(int xParam, int yParam, int widthParam, int heightParam)
			: x(xParam)
			, y(yParam)
			, width(widthParam)
			, height(heightParam)
		{}

		void setTag(const std::string& tagPram) {
			tag = tagPram;
		}

		const std::string& getTag() const noexcept {
			return tag;
		}

		virtual void Render() = 0;
		virtual void Stub() = 0;


	private:
		int x, y;
		int width, height;
		std::string tag;
	};

	class Image : public Widget
	{
	public:
		Image(int xParam,
			int yParam,
			int widthParam,
			int heightParam,
			const std::string& textureParam)
			: Widget(xParam, yParam, widthParam, heightParam)
			, texture(textureParam)
		{}

		void Render() override
		{
			std::cout << "[Image][Render] draw " << texture << std::endl;
		}

		void Stub() override {}

	private:
		std::string texture;
	};

	class Label : public Widget
	{
	public:
		Label(int xParam,
			int yParam,
			int widthParam,
			int heightParam,
			const std::string& textParam)
			: Widget(xParam, yParam, widthParam, heightParam)
			, text(textParam)
		{}

		void Render() override
		{
			std::cout << "[Label][Render] draw " << text << std::endl;
		}

		void Stub() override {}
	private:
		std::string text;
	};

	class Button : public Widget
	{
	public:
		Button(int xParam,
			int yParam,
			int widthParam,
			int heightParam,
			const std::function<void()>& actionParam)
			: Widget(xParam, yParam, widthParam, heightParam)
			, action(actionParam)
		{}

		void Render() override
		{
			std::cout << "[Label][Button] draw "<< std::endl;
		}

		void Stub() override {}

		void Press()
		{
			if (action)
				action();
		}

	private:
		std::function<void()> action;
	};

}