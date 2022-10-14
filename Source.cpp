#include <iostream>
//#include <fstream>
#include <string>
#include <vector>

bool is_exists(const std::string& name) 
{
	struct stat buffer;
	return (stat(name.c_str(), &buffer) == 0);
}

int main(int argc, char** argv)
{
	if (argc != 3)
	{
		std::cout	<< "Locate paths to matrix files in arguments"			<< std::endl
                    << "EXAMPLE:"											<< std::endl
                    << "    .../PP_2.exe <matrix_1_path> <matrix_2_path>"	<< std::endl;
        exit(EXIT_FAILURE);
	}

	try
	{
		for (int i = 1; i < 3; i++)
		{
			if (!is_exists(argv[i]))
				throw std::invalid_argument(std::to_string(i) + "]: " + argv[i] + " (File doesn't exist)");
		}
	}
	catch (std::invalid_argument const& ex)
	{
		std::cout << std::string("INVALID ARGUMENT [") << ex.what() << std::endl;
		exit(EXIT_FAILURE);
	}

	std::vector<std::vector<int>> matrix_1, matrix_2;
	

	return 0;
}