#pragma once
#ifndef MATRIX
#define MATRIX

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

template<typename T>
using Matrix = std::vector<std::vector<T>>;

template<typename T>
Matrix<T> operator *(const Matrix<T>&a, const Matrix<T>& b)
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
				c[i][j] += a[i][k] * b[k][j];
		}
	}

	return c;
}

template<typename T>
void read_file(Matrix<T>& matrix, const std::string& filepath)
{
	try
	{
		std::ifstream file;
		file.exceptions(std::ifstream::badbit);
		file.open(filepath);

		for (std::string buffer; getline(file, buffer); )
		{
			std::stringstream iss(buffer);

			T number;
			std::vector<T> temp;
			while (iss >> number)
				temp.push_back(number);

			matrix.push_back(temp);
		}
		file.close();

		if (matrix.empty())
		{
			throw std::logic_error("No matrix in file \"" + filepath + '\"');
		}
		
		const size_t size = matrix.begin()->size();
		for (auto iter = matrix.begin() + 1; iter != matrix.end(); iter++)
		{
			if (iter->size() != size)
				throw std::logic_error("Matrix dimmension mismatch in file \"" + filepath + '\"');
		}
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
}

template<typename T>
void write_file(const Matrix<T>& matrix, const double& runtime, const std::string& filepath)
{
	try
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
			file << '\n';
		}
		file << '\n';
		file << "Runtime: " << runtime << " microseconds\n";
		file << " Volume: " << (matrix.size() * matrix.begin()->size()) << '\n';

		file.close();
	}
	catch (std::ios_base::failure const& ex)
	{
		std::cout << "WRITING ERROR: " << ex.what() << '\n';
		_exit(EXIT_FAILURE);
	}
}
#endif