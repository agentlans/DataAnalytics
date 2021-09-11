#ifndef _IO
#define _IO

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <exception>

#include "Eigen.hpp"

class FileNotFoundError : public std::exception {
public:
    FileNotFoundError(const char* filename) : filename(filename) {}
    const char* what() const throw() {
        return filename;
    }
private:
    const char* filename;
};

struct MatrixReadingError : public std::exception {
    const char* what() const throw() {
        return "Matrix has uneven number of columns.";
    }
};

// Text file that can be read from or written to
class File {
public:
    File(const char* filename, std::ios_base::openmode mode = std::fstream::in);
    ~File();

    // Open and close the file
    void open(const char* filename, std::ios_base::openmode mode);
    void close();

    // Seek
    void rewind();
    bool eof();
    void flush();

    // Kinds of reads
    template <class T> T read(); // read value of type T
    std::string read_line(); // read one line
    std::vector<std::string> read_lines(); // read lines to end of the file
    // Kinds of writes
    template <class T> void write(const T& x);
    void write_line(const std::string& line);
    void write_lines(const std::vector<std::string>& lines);

    // Matrix operations
    template <class T> Matrix<T,Dynamic,Dynamic> read_matrix();
    template <class T> void write_matrix(const Matrix<T,Dynamic,Dynamic>& m);
private:
    std::fstream file;
};


template <class T>
T File::read() {
    T x;
    file >> x;
    return x;
}

template <class T>
void File::write(const T& x) {
    file << x;
}

// Reads a string and returns the elements in the string
template <class T>
std::vector<T> read_vector(const std::string& line) {
    std::vector<T> v;
    std::stringstream ss(line);
    while (!ss.eof()) {
        T x;
        ss >> x;
        v.push_back(x);
    }
    return v;
}

// Writes matrix to file
template <class T>
void File::write_matrix(const Matrix<T,Dynamic,Dynamic>& m) {
    file << m;
    file.flush();
}

// Reads matrix from file. Also checks that it's a rectangular matrix.
// Note: Every line must have exactly the same number of elements (including the final line!)
// So can't have newline by itself.
template <class T>
Matrix<T,Dynamic,Dynamic> File::read_matrix() {
    rewind();
    std::vector<T> data; // Holds elements of matrix
    int cols = -1;
    int rows = 0;
    while (!eof()) {
        std::string line = read_line();
        rows++;
        auto v = read_vector<T>(line);
        if (cols == -1) {
            // How many columns on this line
            cols = v.size();
        } else if (v.size() != cols) {
            // Uneven number of columns
            throw MatrixReadingError();
        }
        // Append to the data read so far
        std::copy(v.begin(), v.end(), std::back_inserter(data));
    }
    // Return in matrix format
    Map<Matrix<T,Dynamic,Dynamic,RowMajor>> m(&data[0], rows, cols);
    return m;
}

#endif
