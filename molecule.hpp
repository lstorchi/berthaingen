#include <string>
#include <vector>

namespace  berthaingen
{
   class atom
   {
   
     private:
   
       float x_, y_, z_;
       std::string symbol_;
   
       void reset_ ()
       {
         x_ = y_ = z_ = 0.0d;
         symbol_ = "";
       }
   
     public:
   
       atom()
       {
         reset_ ();
       };
       
       ~atom()
       {
         reset_ ();
       };
   
       void set_x(double in)
       {
         x_ = in;
       };
   
       void set_y(double in)
       {
         y_ = in;
       };
   
       void set_z(double in)
       {
         z_ = in;
       };
   
       void set_symbol(const char * s)
       {
         symbol_ = s;
       };
   
       double get_x() const
       {
         return x_;
       };
   
       double get_y() const
       {
         return y_;
       };
   
       double get_z() const
       {
         return z_;
       };
   
       std::string get_symbol() const
       {
         return symbol_;
       };
   };
   
   
   class molecule 
   {
     private:
       std::string name_;
       std::vector<atom> atoms_;
   
       void reset_()
       {
         name_ = "";
         atoms_.clear();
       };
   
     public:
   
       molecule()
       {
         reset_ ();
       };
       
       ~molecule()
       {
         reset_ ();
       };
   };
}
