#pragma once
#include <halley/maths/vector2.h>
#include <halley/maths/rect.h>
#include <halley/text/halleystring.h>
#include <halley/file/path.h>
#include <halley/data_structures/maybe.h>

namespace Halley
{
	class String;

	enum class WindowType {
		None,
		Fullscreen,
		Window,
		ResizableWindow,
		BorderlessWindow
	};

	enum class WindowState
	{
		Normal,
		Minimized,
		Maximized
	};

	template <>
	struct EnumNames<WindowType> {
		constexpr std::array<const char*, 5> operator()() const {
			return {{
				"none",
				"fullscreen",
				"window",
				"resizeableWindow",
				"borderlessWindow",
			}};
		}
	};
	
	class WindowDefinition
	{
	public:
		WindowDefinition(WindowType windowType, Vector2i size, String title)
			: windowType(windowType)
			, size(size)
			, title(title)
		{}

		WindowDefinition(WindowType windowType, Maybe<Vector2i> position, Vector2i size, String title)
			: windowType(windowType)
			, position(position)
			, size(size)
			, title(title)
		{}

		WindowType getWindowType() const { return windowType; }
		WindowState getWindowState() const { return windowState; }
		Maybe<Vector2i> getPosition() const { return position; }
		Vector2i getSize() const { return size; }
		String getTitle() const { return title; }
		Maybe<Path> getIcon() const { return icon; }

		WindowDefinition withPosition(Maybe<Vector2i> newPos) const
		{
			auto w = *this;
			w.position = newPos;
			return w;
		}
		
		WindowDefinition withSize(Vector2i newSize) const
		{
			auto w = *this;
			w.size = newSize;
			return w;
		}

		WindowDefinition withState(WindowState newState) const
		{
			auto w = *this;
			w.windowState = newState;
			return w;
		}

		WindowDefinition withIcon(const Path& iconPath) const
		{
			auto w = *this;
			w.icon = iconPath;
			return w;
		}

	private:
		WindowType windowType = WindowType::Fullscreen;
		WindowState windowState = WindowState::Normal;
		Maybe<Vector2i> position;
		Vector2i size;
		String title;
		Maybe<Path> icon;
	};

	class Window
	{
	public:
		virtual ~Window() {}

		virtual void update(const WindowDefinition& definition) = 0;
		virtual void show() = 0;
		virtual void hide() = 0;
		virtual void setVsync(bool vsync) = 0;
		virtual void swap() = 0;
		virtual Rect4i getWindowRect() const = 0;
		virtual const WindowDefinition& getDefinition() const = 0;

		virtual void* getNativeHandle() { return nullptr; }
		virtual String getNativeHandleType() { return ""; }
	};
}
