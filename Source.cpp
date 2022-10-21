#include "Matrix.hpp"
#include <chrono>

bool is_exists(const std::string& name) 
{
	struct stat buffer;
	return (stat(name.c_str(), &buffer) == 0);
}

int main(int argc, char** argv)
{
	if (argc < 3 || argc > 4)
	{
		std::cout	<< "Locate paths to matrix files in arguments and to output file (optional)\n"
					<< "EXAMPLE:\n"
					<< "    .../PP_1.exe <matrix_1_path> <matrix_2_path> <output_path>\n";
        _exit(EXIT_FAILURE);
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
		std::cout << std::string("INVALID ARGUMENT [") << ex.what() << '\n';
		_exit(EXIT_FAILURE);
	}


	Matrix<int> a, b;
	read_file(a, argv[1]);
	read_file(b, argv[2]);

	auto start_time = std::chrono::high_resolution_clock::now();
	Matrix<int> c = a * b;
	auto end_time = std::chrono::high_resolution_clock::now();
	
	if (argc == 4)
		write_file(c, std::chrono::duration<double, std::micro>(end_time - start_time).count(), argv[3]);
	else
		write_file(c, std::chrono::duration<double, std::micro>(end_time - start_time).count());


	std::cout << "DONE\n";
	return 0;
}