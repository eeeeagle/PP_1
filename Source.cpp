#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

#include <windows.h>
#include <shlobj.h>

template<typename T>
using Matrix = std::vector<std::vector<T>>;

bool is_exists(const std::string& name) 
{
	struct stat buffer;
	return (stat(name.c_str(), &buffer) == 0);
}

template<typename T>
Matrix<T> multiply_matrix(const Matrix<T>& a, const Matrix<T>& b)
{
	const size_t n = a.size();
	const size_t m = a.begin()->size();
	const size_t p = b.begin()->size();

	Matrix<T> c(n, std::vector<T>(p, 0));
	for (size_t j = 0; j < p; ++j)
	{
		for (size_t k = 0; k < m; ++k)
		{
			for (size_t i = 0; i < n; ++i)
			{
				c[i][j] += a[i][k] * b[k][j];
			}
		}
	}
	return c;
}

template<typename T>
int read_matrix(Matrix<T>& matrix, const std::string& filepath)
{
	std::ifstream file(filepath);
	if (!file.is_open())
		return -1;

	std::string buffer;
	while (getline(file, buffer))
	{
		std::stringstream iss(buffer);
		
		int number;
		std::vector<int> temp;
		while (iss >> number)
			temp.push_back(number);

		matrix.push_back(temp);
	}

	file.close();
	return 0;
}

template<typename T>
int write_matrix(	const Matrix<T>&	matrix,
					const unsigned&		runtime, 
					const unsigned&		volume,
					const std::string&	filepath = "output.txt")
{
	std::ofstream file(filepath);
	if (!file.is_open())
		return -1;
		
	for (auto iter_ = matrix.begin(); iter_ != matrix.end(); iter_++)
	{
		for (auto iter = iter_->begin(); iter != iter_->end(); iter++)
		{
			file << *iter;
			file << (iter != (iter_->end() - 1) ? ' ' : '\n');
		}
	}
	file << std::endl << std::endl;
	file << "Runtime: " << runtime << " ms" << std::endl;
	file << " Volume: " << volume << std::endl;

	file.close();
	return 0;
}

int main(int argc, char** argv)
{
	if (argc != 3)
	{
		std::cout	<< "Locate paths to matrix files in arguments"			<< std::endl
                    << "EXAMPLE:"											<< std::endl
                    << "    .../PP_1.exe <matrix_1_path> <matrix_2_path>"	<< std::endl;
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

	Matrix<int> a, b;
	read_matrix(a, argv[1]);
	read_matrix(b, argv[2]);

	unsigned volume = 0; /* ??? */

	clock_t start_time = clock();
	Matrix<int> c = multiply_matrix(a, b);
	clock_t end_time = clock();

	write_matrix(c, end_time - start_time, volume);

	return 0;
}