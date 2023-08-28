#include <stdio.h>
#include <unordered_map>
#include <string>
#include <adns.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

#include "namelookup.h"
#include "domainNameLoader.h"

using namespace std;

void adnsloopup(unordered_set<string> &domainSet);

int main(int argc, char *argv[])
{
    // 1. read domain list
    AlexaDomainNameLoader alexaDomainNameLoader("./data/alexa-top-10.csv");
    alexaDomainNameLoader.load();

    // 3. aggregate domain name
    unordered_set<string> domainNameSet = alexaDomainNameLoader.getDomainNameSet();

    // 2. lookup domain name
    adnsloopup(domainNameSet);

    return 0;
}

void adnsloopup(unordered_set<string> &domainSet)
{
    for (auto domain : domainSet)
    {
        adns_state ads;
        adns_initflags initflags = (adns_initflags)(adns_if_nosigpipe | adns_if_noerrprint);
        adns_init(&ads, initflags, NULL);
        adns_query query;
        adns_queryflags flags = adns_qf_owner;
        adns_submit(ads, domain.c_str(), adns_r_a, flags, NULL, &query);
        adns_answer *answer;
        adns_wait(ads, &query, &answer, NULL);
        if (answer->status == adns_s_ok)
        {
            int res_num = answer->nrrs;
            cout<<"res_num: "<<res_num<<endl;

            for (int i = 0; i < res_num; i++)
            {
                struct in_addr addr;
                addr.s_addr = answer->rrs.addr[i].addr.inet.sin_addr.s_addr;
                cout<<"domain: "<<domain<<", ip: "<<inet_ntoa(addr)<<endl;
            }
        }
        adns_finish(ads);
    }
}