#include <iostream>
#include <fstream>
#include <string>
#include <vector>

typedef std::vector<std::vector<int>> Matrix;

bool is_exists(const std::string& name) 
{
	struct stat buffer;
	return (stat(name.c_str(), &buffer) == 0);
}

Matrix multiply_matrix(const Matrix& a, const Matrix& b)
{
	Matrix c;

	/* Допилить */

	return c;
}

int read_matrix(Matrix& matrix, const std::string& filepath)
{
	std::ifstream file(filepath);
	if (!file)
		return -1;

	/* допилить */

	file.close();
	return 0;
}

int write_matrix(	const Matrix&		matrix,
					const unsigned&		runtime, 
					const unsigned&		volume,
					const std::string&	filepath = "%USERPROFILE%/Documents/output.txt")
{
	/* допилить */

	return 0;
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

	Matrix a, b;
	read_matrix(a, argv[1]);
	read_matrix(b, argv[2]);

	unsigned volume = 0; /* ??? */

	clock_t start_time = clock();
	Matrix с = multiply_matrix(a, b);
	clock_t end_time = clock();

	write_matrix(с, end_time - start_time, volume);
	return 0;
}