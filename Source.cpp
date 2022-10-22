#include "Matrix.hpp"
#include <conio.h>

bool is_exists(const std::string& name)
{
	struct stat buffer;
	return (stat(name.c_str(), &buffer) == 0);
}

int main(int argc, char** argv)
{
	system("title Parallel Programming [Lab ¹ 2]");

	if (argc > 4 || (argc == 2 && std::string(argv[1]) == "-help"))
	{
		std::cout << "Locate paths to matrix files in arguments and to output file (optional)\n"
			<< "EXAMPLE:\n"
			<< "    .../PP_1.exe <matrix_1_path> <matrix_2_path> <output_path>\n";
		_exit(EXIT_FAILURE);
	}

	std::string str[3];
	try
	{
		if (argc > 1)
		{
			for (int i = 1; i < 3; i++)
			{
				if (!is_exists(argv[i]))
					throw std::invalid_argument(std::to_string(i) + "]: " + argv[i] + " (File doesn't exist)");
				str[i - 1] = argv[i];
			}
		}
		else
		{
			std::cout << "Locate path to matrix A: ";
			std::cin >> str[0];
			std::cout << "Locate path to matrix B: ";
			std::cin >> str[1];
		}

		if (argc != 4)
		{
			std::cout << "\nLocate path to output file? (Y/N)";
			int key;
			do
			{
				key = _getch();
				key = toupper(key);
			} while (key != 'Y' && key != 'N');
			std::cout << "\r                                       \r";
			if (key == 'Y')
			{
				std::cout << "Locate path to output file: ";
				std::cin >> str[2];
			}
			else
				str[2] = "output.txt";
		}
		else
			str[2] = argv[3];
	}
	catch (std::invalid_argument const& ex)
	{
		std::cout << std::string("INVALID ARGUMENT [") << ex.what() << '\n';
		_exit(EXIT_FAILURE);
	}

	Matrix<unsigned long> a, b, c;

	std::cout << "Reading matrix A";
	read_file(a, str[0]);

	std::cout << "\rReading matrix B";
	read_file(b, str[1]);

	std::cout << "\rPerforming C = A * B";
	double runtime = multiply_matrix(a, b, c);

	std::cout << "\rWriting matrix C to file [" << str[2] << "]";
	write_file(c, runtime, str[2]);
	std::cout << "\r                                ";
	for (size_t i = str[2].size(); i > 0; i--)
		std::cout << ' ';

	std::cout << "\rSaved matrix in file [" << str[2] << "]\n";
	system("pause > nul");
	return 0;
}