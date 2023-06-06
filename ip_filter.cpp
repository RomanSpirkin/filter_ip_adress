#include <cassert>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

std::vector<std::string> split(const std::string &str, char d)
{
    std::vector<std::string> r;

    std::string::size_type start = 0;
    std::string::size_type stop = str.find_first_of(d);
    while(stop != std::string::npos)
    {
        r.push_back(str.substr(start, stop - start));

        start = stop + 1;
        stop = str.find_first_of(d, start);
    }

    r.push_back(str.substr(start));

    return r;
}

struct ip_adress{

    ip_adress() = delete;
    ip_adress(const std::vector<std::string>& vec_ip){
        for(int i=0;i<4;i++) {
            data[i]=atoi(vec_ip[i].c_str());
        } 
    }
    int data[4];
};

bool operator<(const ip_adress & lhs, const ip_adress & rhs){
    for(int i=0;i<4;i++) {
        if (lhs.data[i]<rhs.data[i]) return false;
        if (lhs.data[i]>rhs.data[i]) return true;
    }
    return false;
}

std::ostream& operator<<(std::ostream &os,const ip_adress &ip) {
    return (os<<ip.data[0]<<'.'<<ip.data[1]<<'.'<<ip.data[2]<<'.'<<ip.data[3]);
}

void filter(const std::vector<ip_adress>& ip_pool,std::vector<ip_adress>& result, int x0=-1,int x1=-1,int x2=-1,int x3=-1){
    for(const auto& tmp:ip_pool){
        if (x0!=-1 && x0!=tmp.data[0]) continue;
        if (x1!=-1 && x1!=tmp.data[1]) continue;
        if (x2!=-1 && x2!=tmp.data[2]) continue;
        if (x3!=-1 && x3!=tmp.data[3]) continue;
        result.push_back(tmp);
    }
}

void filter_any(const std::vector<ip_adress>& ip_pool,std::vector<ip_adress>& result,int x){
    for(const auto& tmp:ip_pool){
        if (x==tmp.data[0]) {result.push_back(tmp);continue;}
        if (x==tmp.data[1]) {result.push_back(tmp);continue;}
        if (x==tmp.data[2]) {result.push_back(tmp);continue;}
        if (x==tmp.data[3]) {result.push_back(tmp);continue;}
    }
}

int main(int argc, char const *argv[])
{
    std::vector<ip_adress> ip_pool,tmp;
    for(std::string line; std::getline(std::cin, line);){
        std::vector<std::string> v = split(line, '\t');
        ip_pool.push_back(ip_adress(split(v.at(0), '.')));
    }
    // reverse sort
    std::stable_sort(ip_pool.begin(),ip_pool.end());
    for(const auto& ip: ip_pool){
        std::cout<<ip<<std::endl;
    }
    // first byte 1
    filter(ip_pool,tmp,1);
    for(const auto& ip: tmp){
        std::cout<<ip<<std::endl;
    }
    tmp.clear();
    // first 46 and second 70 
    filter(ip_pool,tmp,46,70);
    for(const auto& ip: tmp){
        std::cout<<ip<<std::endl;
    }
    tmp.clear();
    // any byte 46
    filter_any(ip_pool,tmp,46);
    for(const auto& ip: tmp){
        std::cout<<ip<<std::endl;
    }
}
