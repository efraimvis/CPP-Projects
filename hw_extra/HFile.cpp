//
// Created by Admin on 2/14/2022.
//

#include "HFile.h"
#include <utime.h>
#include <cstring>

HFile::HFile(const char *name)
{
    this->filename = name;
    this->open(name);
    if(!this->is_open()) throw FileNotOpenException(filename.c_str());
    numLines = 0;
    this->seekp(0,std::ios::end);
    this->fileSize = this->tellg();
    this->seekp(0,std::ios::beg);
    if(fileSize > 0) numLines = 1;
    for(int i =0 ; i<fileSize;i++)
    {
        char curr;
        curr = get();
        if(curr == '\n') this->numLines++;
    }
    this->seekp(0,std::ios::beg);
    this->close();
}

HFile& HFile::operator[](int pos)
{
    if (!(pos >= 0 && pos <= fileSize)) throw OutOfBoundsException(filename.c_str());
    if(!this->is_open()) throw FileNotOpenException(filename.c_str());
    seekp(pos);
    return *this;
}

HFile& HFile::operator=(char c)
{
    if(!this->is_open()) throw FileNotOpenException(filename.c_str());
    put(c);
    return *this;
}

HFile::operator char()
{
    if(!this->is_open()) throw FileNotOpenException(filename.c_str());
    return get();
}

void HFile::touch(const char* filename)
{
    std::ifstream file(filename);
    if(file.is_open())
    {
        file.close();
        utime(filename,0);
    }
    else
    {
        std::ofstream file(filename);
        if(!file.is_open()) throw FileNotOpenException(filename);
        file.close();
    }
}

void HFile::head(int n)
{
    if(!(n > 0 && n <= numLines)) throw OutOfBoundsException(filename.c_str());
    if(!this->is_open()) throw(FileNotOpenException(filename.c_str()));
    if(this->fileSize == 0) return;
    int lineCounter = 1;
    int i = 0;
    while(i < fileSize && lineCounter <= n)
    {
        seekp(i);
        char c = get();
        if(!(lineCounter == n && c=='\n'))std::cout<<c;
        if(c == '\n') lineCounter++;
        i++;
    }
    std::cout<<std::endl;
    seekp(0,std::ios::beg);
}

void HFile::tail(int n)
{
    if(!(n > 0 && n <= this->numLines)) throw OutOfBoundsException(filename.c_str());
    if(!this->is_open()) throw FileNotOpenException(filename.c_str());
    if(this->fileSize == 0) return;
    int i = fileSize-1;
    int l = 1;
    seekp(i);
    while(l <= n && i>=0)
    {
        seekg(i);
        char c = get();
        if(c == '\n') l++;
        i--;
    }
    i += 2;
    while(i<fileSize)
    {
        seekp(i);
        char c = get();
        std::cout<<c;
        i++;
    }
    seekp(0,std::ios::beg);
    std::cout<<std::endl;
}

void HFile::copy(const char* source, const char* destination)
{
    std::ifstream src(source);
    if(!src.is_open()) throw FileNotOpenException(source);
    std::string text = "";
    while(!src.eof())
    {
        text += src.get();
    }
    src.close();
    text.erase(text.end()-1);
    std::ofstream dest(destination);
    dest << text;
    dest.close();
}

void HFile::remove(const char* filename)
{
    std::remove(filename);
}

void HFile::move(const char* source, const char* destination)
{
    if(strcmp(source, destination) == 0) return;
    copy(source, destination);
    remove(source);
}

void HFile::cat(const char* filename)
{
    std::ifstream file(filename);
    if(!file.is_open()) throw FileNotOpenException(filename);
    file.seekg(0,std::ios::end);
    int size = file.tellg();
    file.seekg(0,std::ios::beg);
    for(int i =0 ;i<size;i++) std::cout<<(char)file.get();
    file.close();
    std::cout<<std::endl;
}