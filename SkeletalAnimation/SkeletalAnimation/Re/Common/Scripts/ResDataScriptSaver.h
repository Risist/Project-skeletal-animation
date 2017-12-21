/// Code from ReEngine library
/// all rights belongs to Risist (Maciej Dominiak) (risistt@gmail.com)

#pragma once
#include <iostream>
#include <fstream>
#include <string>


/*
Simple class to save .res files

Data scripts are used to save & load constant data to files
No logic or any if statements should be included

typical workflow:

// open file to save
ofstream file("path")

ScriptSaver saver;

// prepare first line
saver.save( "trait1", 1);
saver.save( "trait2", 2.f);
saver.save( "trait3", "dadasd");
saver.save( "trait4", MyClass() ); // note MyClass has to have defined operator<<

// save the result to file
saver.nextLine(file);

// or decline the current work and start again
saver.clear();

file. close();

*/

namespace Res
{
	class DataScriptSaver
	{
	public:
		DataScriptSaver()
		{

		}

		void nextLine(std::ostream& stream)
		{
			// save the result
			stream << "<" << _line << ">\n";
			// clear the string
			clear();
		}
		void setEndLine()
		{
			_line = "\\";
		}

		// saves value in internal string _line
		// note that TY has to have defined operator<<
		template<typename TY>
		void save(const std::string& trait, const TY& valueToSave)
		{
			std::stringstream stream;
			stream << trait << "=" << valueToSave << ";";
			std::string _l;
			stream >> _l;
			_line += _l;
		}
		template<typename TY>
		void save(const std::string& trait, const TY& valueToSave, const TY& _default)
		{
			if (valueToSave != _default)
				save(trait, valueToSave);
		}

		void clear()
		{
			_line = "";
		}

		const std::string& getLine() const
		{
			return _line;
		}
		void insert(const char* s)
		{
			_line += s;
		}

	protected:
		std::string _line;
	};
}
