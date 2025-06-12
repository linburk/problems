#include <iostream>
int main(){
    int a,b,c;
    std::cin>>a>>b>>c;
    if(a>=b&&a>=c)std::cout<<a;
    else if(b>=a&&b>=c)std::cout<<b;
    else if(c>=b&&c>=a)std::cout<<c;}