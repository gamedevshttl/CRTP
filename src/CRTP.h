#include <iostream>
#include <string>
#include <functional>

namespace CRTP //Static	polymorphism with the curiously recurring template pattern
{

	template <typename T>
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

		void Render()
		{
			static_cast<T*>(this)->RenderImplement();
		}

		void Stub()
		{
			static_cast<T*>(this)->StubImplement();
		}



	private:
		int x, y;
		int width, height;
		std::string tag;
	};

	class Image : public Widget<Image>
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

		void RenderImplement()
		{
			std::cout << "[Image][Render] draw " << texture << std::endl;
		}

		void StubImplement(){}

	private:
		std::string texture;
	};

	class Label : public Widget<Label>
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

		void RenderImplement()
		{
			std::cout << "[Label][Render] draw " << text << std::endl;
		}

		void StubImplement() {}
	private:
		std::string text;
	};

	class Button : public Widget<Button>
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

		void RenderImplement()
		{
			std::cout << "[Label][Button] draw " << std::endl;
		}

		void StubImplement() {}

		void Press()
		{
			if (action)
				action();
		}

	private:
		std::function<void()> action;
	};
}