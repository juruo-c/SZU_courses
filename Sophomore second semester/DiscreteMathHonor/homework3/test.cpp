#include<iostream>

using namespace std;

class Vector
{
 int vec[10];
public:
 Vector(int v[10]);
 Vector();
 Vector(Vector&);
 
 friend Vector operator-(Vector v1, Vector v2);
 friend Vector operator+(Vector v1, Vector v2);
 friend ostream& operator<<(ostream& o, const Vector& v);
};

Vector::Vector(int v[10])
{
 for (int i = 0; i < 10; i++)
 {
  vec[i] = v[i];
 }
}

Vector::Vector()
{
 for(int i = 0; i < 10; i++)
  vec[i] = 0;
}

Vector::Vector(Vector& vv)
{
 for (int i = 0; i < 10; i++)
  vec[i] = vv.vec[i];
}

Vector operator+(Vector v1, Vector v2)
{
 Vector tv;
 for (int i = 0; i < 10; i++)
 {
  tv.vec[i] = v1.vec[i] + v2.vec[i];
 }
 return tv;
}

Vector operator-(Vector v1, Vector v2)
{
 Vector tv;
 for (int i = 0; i < 10; i++)
 {
  tv.vec[i] = v1.vec[i] - v2.vec[i];
 }
 return tv;
}

ostream& operator<<(ostream& out, const Vector& v)
{
 for (int i = 0; i < 10; i++)
  out << v.vec[i];
 return out;
}

int main()
{
 int a1[10];
 for (int i = 0; i < 10; i++)
  cin >> a1[i];
 Vector v1(a1);

 int a2[10];
 for (int i = 0; i < 10; i++)
  cin >> a2[i];
 Vector v2(a2);
 cout << v1 + v2 << endl;
 cout << v1 - v2 << endl;

 return 0;
}