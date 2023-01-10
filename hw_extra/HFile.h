//
// Created by Admin on 2/14/2022.
//

#ifndef HW_7_HFILE_H
#define HW_7_HFILE_H
#include <fstream>
#include <iostream>


class HFile : public std::fstream
{

private:
    int fileSize;
    std::string filename;
    int numLines;

public:

    /*HFile inherits from fstream, and does not contain object-type data members, therefore copy constructor, copy assignment operator and
     * destructor are not necessary*/

    /*Getter for numLines
     *
     * return : Returns the number of lines in the file*/
    int getNumLines() const {return this->numLines;}

    /*Getter for fileSize
     *
     * return : Returns the number of characters in the file*/
    int getFileSize() const {return fileSize;}

    /*Exception for file opening
     * contains error message signifying file could not be opened*/
    struct FileNotOpenException : public std::exception
    {
    private:
        const char* name;
    public:
        explicit FileNotOpenException(const char* fname):name(fname){}
        void printMessage()
        {
            std::cout<<"error: "<<name<<" does not exist or cannot be processed.\n";
        }
    };

    /*Exceptions for out of bounds indices
     * contains error message signifying file could not be processed*/
    struct OutOfBoundsException : public std::exception
    {
    private:
        const char* name;
    public:
        explicit OutOfBoundsException(const char* fname):name(fname){}
        void printMessage()
        {
            std::cout<<"error: "<<name<<" does not exist or cannot be processed.\n";
        }
    };

    /*Constructor
     *
     * name - file name*/
    explicit HFile(const char* name);

    /*Getter for name
     *
     * return : Returns file name*/
    const char* getName(){return filename.c_str();}

    /*Subscript operator
     * seeks within file to given position
     *
     * pos - given position in file
     *
     * throws OutOfBoundsException if pos is out of bounds for file*/
    HFile& operator[](int pos);

    /*Assignment operator
     * puts given character in current cursor position*/
    HFile& operator=(char c);

    /*Char conversion operator*/
    operator char();

    /*Creates file with given name if file does not already exist,
     * or updates timestamp for file if it exists
     *
     * filename - given file name
     *
     * throws FileNotOpenException if file could not be created*/
    static void touch(const char* filename);

    /*Prints first n lines in file, or first 10 lines by default
     *
     * n - number of lines to print*/
    void head(int n=10);

    /*Prints last n lines in file, or last 10 lines by default
     *
     * n - number of lines to print*/
    void tail(int n = 10);

    /*Copies file in given source directory to given destination directory
     *
     * source - source directory
     * destination - destination directory
     *
     * throws FileNotOpenException if source file does not exist or could not be opened*/
    static void copy(const char* source, const char* destination);

    /*Removes file in given directory
     *
     * filename - directory of given file*/
    static void remove(const char* filename);

    /*Moves file in given source directory to given destination directory
     *
     * source - given source directory
     * destination - given destination directory
     *
     * throws FileNotOpenException if source file does not exist or could not be opened*/
    static void move(const char* source, const char* destination);

    /*Prints contents of given file in ASCII format
     *
     * filename - given file name
     *
     * throws FileNotOpenException if file does not exist or could not be opened*/
    static void cat(const char* filename);
};


#endif //HW_7_HFILE_H
