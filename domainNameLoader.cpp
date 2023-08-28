#include "domainNameLoader.h"

//************************************************
// *            DomainNameLoader                 *
//************************************************
DomainNameLoader::DomainNameLoader(std::string filename)
{
    this->filename = filename;
}

DomainNameLoader::~DomainNameLoader()
{
}

std::unordered_set<std::string> DomainNameLoader::getDomainNameSet()
{
    return this->domainNameSet;
}

//************************************************
// *            AlexaDomainNameLoader            *
//************************************************
AlexaDomainNameLoader::AlexaDomainNameLoader(std::string filename) : DomainNameLoader(filename)
{
}

AlexaDomainNameLoader::~AlexaDomainNameLoader()
{
}

void AlexaDomainNameLoader::load()
{
    std::ifstream fin(this->filename);
    if (!fin)
    {
        std::cout << "open file error" << std::endl;
        return;
    }
    std::string line;
    while (getline(fin, line))
    {
        std::string domainName = line.substr(line.find(",") + 1);
        this->domainNameSet.insert(domainName);
    }
    fin.close();

    std::cout << "load " << this->domainNameSet.size() << " domain names from " << this->filename << std::endl;
}