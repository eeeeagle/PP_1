#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <chrono>

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
void read_matrix(Matrix<T>& matrix, const std::string& filepath)
{
	std::ifstream file;
	file.exceptions(std::ifstream::badbit);
	file.open(filepath);

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

	if (!matrix.empty())
	{
		size_t dim = matrix.begin()->size();
		for (auto iter = matrix.begin() + 1; iter != matrix.end(); iter++)
		{
			if (iter->size() != dim)
				throw std::logic_error("Matrix dimmension mismatch in file \"" + filepath + '\"');
		}
	}
}

template<typename T>
void write_matrix(const Matrix<T>& matrix, const double& runtime, const size_t& volume, const std::string& filepath = "output.txt")
{
	std::ofstream file;
	file.exceptions(std::ofstream::badbit);
	file.open(filepath);
		
	for (auto iter_ = matrix.begin(); iter_ != matrix.end(); iter_++)
	{
		for (auto iter = iter_->begin(); iter != iter_->end(); iter++)
		{
			file << *iter;
			file << ' ';
		}
		file << std::endl;
	}
	file << std::endl;
	file << "Runtime: " << runtime << " microseconds\n";
	file << " Volume: " << volume << '\n';

	file.close();
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
	try
	{
		read_matrix(a, argv[1]);
		read_matrix(b, argv[2]);
	}
	catch (std::ios_base::failure const& ex)
	{
		std::cout << "READING ERROR: " << ex.what() << '\n';
		_exit(EXIT_FAILURE);
	}
	catch (std::logic_error const& ex)
	{
		std::cout << "LOGIC ERROR: " << ex.what() << '\n';
		_exit(EXIT_FAILURE);
	}

	auto start_time = std::chrono::high_resolution_clock::now();
	Matrix<int> c = multiply_matrix(a, b);
	auto end_time = std::chrono::high_resolution_clock::now();

	const size_t volume = c.size() * c.begin()->size();
	
	try
	{
		if (argc == 4)
			write_matrix(c, std::chrono::duration<double, std::micro>(end_time - start_time).count(), volume, argv[3]);
		else
			write_matrix(c, std::chrono::duration<double, std::micro>(end_time - start_time).count(), volume);
	}
	catch (std::ios_base::failure const& ex)
	{
		std::cout << "WRITING ERROR: " << ex.what() << '\n';
		_exit(EXIT_FAILURE);
	}

	std::cout << "DONE\n";
	return 0;
}