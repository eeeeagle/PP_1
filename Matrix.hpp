#pragma once
#ifndef MATRIX
#define MATRIX

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <chrono>

template<typename T>
class Matrix
{
	std::vector<std::vector<T>> matrix;
	double last_operation_runtime = 0.0;

public:
	Matrix(const std::vector<std::vector<T>>& matrix) 
		: matrix(matrix) 
	{}
	
	Matrix(const std::string& filepath)
	{
		read_file(filepath);
	}

	Matrix(const Matrix& matrix) 
		: matrix(matrix->matrix)
	{}

	~Matrix()
	{}

	Matrix<T> operator*(const Matrix<T>& b)
	{
		auto start_time = std::chrono::high_resolution_clock::now();

		const size_t n = matrix.size();
		const size_t m = matrix.begin()->size();
		const size_t p = b.matrix.begin()->size();

		std::vector <std::vector<T>> c(n, std::vector<T>(p, 0));
		for (size_t j = 0; j < p; ++j)
		{
			for (size_t k = 0; k < m; ++k)
			{
				for (size_t i = 0; i < n; ++i)
					c[i][j] += matrix[i][k] * b.matrix[k][j];
			}
		}

		auto end_time = std::chrono::high_resolution_clock::now();
		last_operation_runtime = std::chrono::duration<double, std::micro>(end_time - start_time).count();
		
		return Matrix(c);
	}

	void read_file(const std::string& filepath)
	{
		try
		{
			std::ifstream file;
			file.exceptions(std::ifstream::badbit);
			file.open(filepath);

			for(std::string buffer; getline(file, buffer); )
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
				const size_t size = matrix.begin()->size();
				for (auto iter = matrix.begin() + 1; iter != matrix.end(); iter++)
				{
					if (iter->size() != size)
						throw std::logic_error("Matrix dimmension mismatch in file \"" + filepath + '\"');
				}
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

	void write_file(const std::string& filepath = "output.txt")
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
			file << "Runtime: " << last_operation_runtime << " microseconds\n";
			file << " Volume: " << (matrix.size() * matrix.begin()->size()) << '\n';

			file.close();
		}
		catch (std::ios_base::failure const& ex)
		{
			std::cout << "WRITING ERROR: " << ex.what() << '\n';
			_exit(EXIT_FAILURE);
		}
	}

	Matrix operator = (const Matrix& matrix)
	{
		return Matrix(matrix);
	}
};
#endif