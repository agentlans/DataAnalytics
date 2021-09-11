#include <sstream>
#include <algorithm>

#include "IO.hpp"

File::File(const char* filename, std::ios_base::openmode mode) {
    open(filename, mode);
}

File::~File() {
    file.close();
}

void File::open(const char* filename, std::ios_base::openmode mode) {
    file.open(filename, mode);
    if (!file.is_open()) {
        throw FileNotFoundError(filename);
    }
}

void File::close() {
    file.close();
}

// Go to beginning of file
void File::rewind() {
    file.seekg(0, file.beg);
}

bool File::eof() {
    return file.eof();
}

void File::flush() {
    file.flush();
}

std::string File::read_line() {
    std::string s;
    std::getline(file, s);
    return s;
}

std::vector<std::string> File::read_lines() {
    std::vector<std::string> lines;
    while (!file.eof()) {
        lines.push_back(read_line());
    }
    return lines;
}

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

void File::write_line(const std::string& line) {
    file << line << std::endl;
}

void File::write_lines(const std::vector<std::string>& lines) {
    for (const auto& line : lines) {
        write_line(line);
    }
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
