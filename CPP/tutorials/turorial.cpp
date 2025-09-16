#include <iostream>

class TutoriaL
{
    public :
        void func(double r)
        {
            double a = 3.14*(r)*(r);
            std::cout << " The Circle has an area of " << a << " whose radius of " << r << std::endl;
        }
        void func(double r, double s)
        {
            double b = (r) * (s) ;
            std::cout << "The Rectangle has an area of " << b << " whose length and breadth is " << r << " and " << s << " respectively" << std::endl;
        }
        void func(double r, double s, double t)
        {
            double c = r * r;
            std::cout << " The Square has an area of " << c << " whose length is " << r << std::endl;
        }
};
int main()
{
    TutoriaL obj1;
    obj1.func(2.5);
    obj1.func(2.5,8.9);
    obj1.func(6.8);
    return 0;
}