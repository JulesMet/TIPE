#include "Logger.h"

#ifdef __unix__                    /* __unix__ is usually defined by compilers targeting Unix systems */
    #define OS_Windows 0

#elif defined(_WIN32) || defined(WIN32)     /* _Win32 is usually defined by compilers targeting 32 or   64 bit Windows systems */
    #define OS_Windows 1
#endif




#if OS_Windows==0
    #define CLEAR_SCREEN() std::cout << "\33[H\33[2J"
#else 
    #define CLEAR_SCREEN() system("cls")
#endif


/*
//#define CLEAR_SCREEN() Log("\33[H\33[2J")
#define CLEAR_SCREEN() system("cls")
//#define CLEAR_SCREEN() printf("\e[1;1H\e[2J")

		// "\033[38;5;{ID}m" foreground color
		// "\033[48;5;{ID}m" background color

		// ID : (see ANSI table)
		// 196 red
		// 81 blue
		// 226 yellow
		// 118 green
		// 8 grey
*/

/*Logger_Color m_Color;

	bool m_InTerminal;

    bool m_InFile;
    const char* m_Filepath;

	Log_filter m_Filter;
*/


Logger::Logger(Filter filter, Logger_Color _color)
	: 	m_Color(_color),
		m_InTerminal(true),
		m_InFile(false),
		m_Filepath("\0"),
		m_Filter(filter)
{

}

Logger::Logger(const char* filepath)
	: 	m_Color(Logger_Color{ Logger_Color::Colors::WHITE, Logger_Color::Colors::BLACK}),
		m_InTerminal(true),
		m_InFile(true),
		m_Filepath(filepath),
		m_Filter(FILTER_INFO)
{

}

Logger::~Logger()
{
	std::cout << "\033[0m";
}


		// "\033[38;5;{ID}m" foreground color
		// "\033[48;5;{ID}m" background color

		// ID : (see ANSI table : https://raw.githubusercontent.com/fidian/ansi/master/images/color-codes.png)
		// 196 red
		// 81 blue
		// 226 yellow
		// 118 green
		// 8 grey


void Logger::SetColor(Logger_Color color) const
{
	Logger_Color::Colors font = color.font_color;
	Logger_Color::Colors bck = color.background_color;

	switch(font)
	{
		case Logger_Color::Colors::RED :
			std::cout << "\033[38;5;196m";
			break;
		
		case Logger_Color::Colors::GREEN :
			std::cout << "\033[38;5;118m";
			break;

		case Logger_Color::Colors::BLUE :
			std::cout << "\033[38;5;81m";
			break;

		case Logger_Color::Colors::YELLOW :
			std::cout << "\033[38;5;226m";
			break;		 
						 
		case Logger_Color::Colors::WHITE :
			std::cout << "\033[38;5;7m";
			break;		 
						 
		case Logger_Color::Colors::BLACK :
			std::cout << "\033[38;5;232m";
			break;		 
						 
		case Logger_Color::Colors::PURPLE :
			std::cout << "\033[38;5;135m";
			break;		 
						 
		case Logger_Color::Colors::BROWN :
			std::cout << "\033[38;5;94m";
			break;

		default:
			break;		 
	}

	switch (bck)
	{					 
		case Logger_Color::Colors::RED:
			std::cout << "\033[48;5;196m";
			break;			 

		case Logger_Color::Colors::GREEN:
			std::cout << "\033[48;5;118m";
			break;			 

		case Logger_Color::Colors::BLUE:
			std::cout << "\033[48;5;81m";
			break;			 
						 
		case Logger_Color::Colors::YELLOW:
			std::cout << "\033[48;5;226m";
			break;			 
						 
		case Logger_Color::Colors::WHITE:
			std::cout << "\033[48;5;255m";
			break;			 
						 
		case Logger_Color::Colors::BLACK:
			std::cout << "\033[48;5;232m";
			break;			 
						 
		case Logger_Color::Colors::PURPLE:
			std::cout << "\033[48;5;135m";
			break;			 
						 
		case Logger_Color::Colors::BROWN:
			std::cout << "\033[48;5;94m";
			break;			 
						 
		default:			 
			break;			 
	}
}

void Logger::SetFilterLevel(Filter filter)
{
	m_Filter = filter;
}

void Logger::SetFilepath(const char* filepath)
{
	m_Filepath = filepath;
}