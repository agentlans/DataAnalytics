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

void File::write_line(const std::string& line) {
    file << line << std::endl;
}

void File::write_lines(const std::vector<std::string>& lines) {
    for (const auto& line : lines) {
        write_line(line);
    }
}

