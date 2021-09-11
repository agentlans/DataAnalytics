#ifndef _IO
#define _IO

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <exception>

#include <Eigen/Dense>
using namespace Eigen;

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

#endif