#include <iostream>
#include <string>
#include <fstream>
#include <unordered_set>

class DomainNameLoader
{
public:
    DomainNameLoader(std::string filename);
    ~DomainNameLoader();
    virtual void load()=0;
    std::unordered_set<std::string> getDomainNameSet();
protected:
    std::string filename;
    std::unordered_set<std::string> domainNameSet;
};

class AlexaDomainNameLoader : public DomainNameLoader
{
public:
    AlexaDomainNameLoader(std::string filename);
    ~AlexaDomainNameLoader();
    void load();
};

