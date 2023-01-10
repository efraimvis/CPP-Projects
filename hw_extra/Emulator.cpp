//
// Created by Admin on 2/13/2022.
//

#include <sstream>
#include "Emulator.h"

int Emulator::getNumericString(std::string str)
{
    std::string::const_iterator it = str.begin();
    while (it != str.end() && std::isdigit(*it)) ++it;
    if (!str.empty() && it == str.end())
    {
        std::stringstream ss(str);
        int retVal;
        ss >> retVal;
        return retVal;
    }
    return -1;
}

void Emulator::Run()
{
    std::string line = "";
    while(line != "exit")
    {
        std::getline(std::cin,line);
        std::stringstream ss(line);
        std::string command, arg1, arg2, arg3;
        ss >> command >> arg1 >> arg2 >> arg3;
        if(command == "read")
        {
            try
            {
                if (!(!arg1.empty() && !arg2.empty() && arg3.empty())) throw UsageException("read", "FILENAME POSITION");
                int pos = getNumericString(arg2);
                if(pos == -1) throw UsageException("read", "FILENAME POSITION");
                read(arg1.c_str(), pos);
            }
            catch(UsageException& ue)
            {
                ue.printMessage();
            }
        }
        else if(command == "write")
        {
            try
            {
                if (!(!arg1.empty() && !arg2.empty() && !arg3.empty())) throw UsageException("write", "FILENAME POSITION CHARACTER");
                int pos = getNumericString(arg2);
                if(pos == -1) throw UsageException("write", "FILENAME POSITION CHARACTER");
                if(arg3.size() != 1) throw UsageException("write", "FILENAME POSITION CHARACTER");
                write(arg1.c_str(), pos,arg3[0]);
            }
            catch(UsageException& ue)
            {
                ue.printMessage();
            }
        }

        else if(command == "touch")
        {
            try
            {
                if (!(!arg1.empty() && arg2.empty() && arg3.empty())) throw UsageException("touch", "FILENAME");
                HFile::touch(arg1.c_str());
            }
            catch(HFile::FileNotOpenException& fnoe)
            {
                fnoe.printMessage();
            }
            catch(UsageException& ue)
            {
                ue.printMessage();
            }
        }

        else if(command == "copy")
        {
            try
            {
                if (!(!arg1.empty() && !arg2.empty() && arg3.empty())) throw UsageException("copy", "SOURCE_FILENAME TARGET_FILENAME");
                HFile::copy(arg1.c_str(), arg2.c_str());
            }
            catch(HFile::FileNotOpenException& fnoe)
            {
                fnoe.printMessage();
            }
            catch(UsageException& ue)
            {
                ue.printMessage();
            }
        }

        else if(command == "remove")
        {
            try
            {
                if (!(!arg1.empty() && arg2.empty() && arg3.empty())) throw UsageException("remove", "FILENAME");
                HFile::remove(arg1.c_str());
            }
            catch(UsageException& ue)
            {
                ue.printMessage();
            }
        }

        else if(command == "move")
        {
            try
            {
                if (!(!arg1.empty() && !arg2.empty() && arg3.empty())) throw UsageException("move", "SOURCE_FILENAME TARGET_FILENAME");
                HFile::move(arg1.c_str(),arg2.c_str());
            }
            catch(HFile::FileNotOpenException& fnoe)
            {
                fnoe.printMessage();
            }
            catch(UsageException& ue)
            {
                ue.printMessage();
            }
        }

        else if(command == "cat")
        {
            try
            {
                if (!(!arg1.empty() && arg2.empty() && arg3.empty())) throw UsageException("cat", "FILENAME");
                HFile::cat(arg1.c_str());
            }
            catch(HFile::FileNotOpenException& fnoe)
            {
                fnoe.printMessage();
            }
            catch(UsageException& ue)
            {
                ue.printMessage();
            }
        }

        else if(command == "head")
        {
            try
            {
                if (!(!arg1.empty() && arg3.empty())) throw UsageException("head", "FILENAME [n]");
                HFile file(arg1.c_str());
            }
            catch(HFile::FileNotOpenException& fnoe)
            {
                fnoe.printMessage();
                continue;
            }
            catch(UsageException& ue)
            {
                ue.printMessage();
                continue;
            }
            HFile file(arg1.c_str());
            try
            {
                file.open(arg1.c_str());
                if(!arg2.empty())
                {
                    if (!(arg2[0] == '[' && arg2[arg2.size() - 1] == ']')) throw UsageException("head", "FILENAME [n]");
                    int numLines = getNumericString(arg2.substr(1, arg2.size() - 2));
                    if (numLines == -1) throw UsageException("head", "FILENAME [n]");
                    file.head(numLines);
                }
                else
                {
                    if(file.getNumLines() < 10) file.head(file.getNumLines());
                    else file.head();
                }
            }
            catch(UsageException& ue)
            {
                ue.printMessage();
            }
            catch(HFile::OutOfBoundsException& oobe)
            {
                oobe.printMessage();
            }
        }

        else if(command == "tail")
        {
            try
            {
                if (!(!arg1.empty() && arg3.empty())) throw UsageException("tail", "FILENAME [n]");
                HFile file(arg1.c_str());
            }
            catch(HFile::FileNotOpenException& fnoe)
            {
                fnoe.printMessage();
                continue;
            }
            catch(UsageException& ue)
            {
                ue.printMessage();
                continue;
            }

            HFile file(arg1.c_str());
            try
            {
                file.open(arg1.c_str());
                if(!arg2.empty())
                {
                    if (!(arg2[0] == '[' && arg2[arg2.size() - 1] == ']')) throw UsageException("tail", "FILENAME [n]");
                    int numLines = getNumericString(arg2.substr(1, arg2.size() - 2));
                    if (numLines == -1) throw UsageException("tail", "FILENAME [n]");
                    file.tail(numLines);
                }
                else
                {
                    if(file.getNumLines() < 10) file.tail(file.getNumLines());
                    else file.tail();
                }
            }
            catch(UsageException& ue)
            {
                ue.printMessage();
            }
            catch(HFile::OutOfBoundsException& oobe)
            {
                oobe.printMessage();
            }
        }

        else if(command == "exit")
        {
            break;
        }

        else
        {
            std::cout<<"error: command is not supported.\n";
        }
    }
}

void Emulator::read(const char* filename, unsigned int position)
{
    try
    {
        HFile file(filename);
    }
    catch(HFile::FileNotOpenException& fnoe)
    {
        fnoe.printMessage();
        return;
    }

    HFile file(filename);
    try
    {
        file.open(filename);
        if(file.getFileSize() == 0) return;
        char c = file[position];
        std::cout<<c<<std::endl;
    }
    catch(HFile::OutOfBoundsException& oobe)
    {
        oobe.printMessage();
    }
}

void Emulator::write(const char* filename,unsigned int position, char c)
{
    try
    {
        HFile file(filename);
    }
    catch(HFile::FileNotOpenException& fnoe)
    {
        fnoe.printMessage();
        return;
    }

    HFile file(filename);
    try
    {
        file.open(filename);
        file[position] = c;
    }
    catch(HFile::OutOfBoundsException& oobe)
    {
        oobe.printMessage();
    }
}

