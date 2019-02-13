/*
 * Prova d'esame con aggregazione e composizione
 * Alessandro Lauria
 */

#include <iostream>
#include <cmath>
#include <sstream>
#include <string>
using namespace std;

#define DIM 50

class C{
private:
	float x;

public:
	C(float x){this->x = x;}

	virtual double f() = 0;

	float getX(){return x;}
};

class D : public C{
private:
	char c;

public:
	D(float x) : C(x){
		c = 'a' + (int)(rand()%10);
	}

	double f(){return pow(sin(getX()),2);}

	char getC(){return c;}
};

class E : public C{
private:
	int n;

public:
	E(float x) : C(x){
		n = (int)(rand()%10);
	}

	double f(){
		return pow(cos(getX()),2);
	}

	int getN(){return n;}
};



class A{
protected:
	C* obj1;
	C* obj2;

public:
	A(float x){
		obj1 = new D(x);
		obj2 = new E(x);
	}

	double g(){
		return (obj1->f() + obj2->f());
	}

	virtual ostream& put(ostream& os){
		stringstream ss;
		D* o1 = dynamic_cast<D*>(obj1);
		E* o2 = dynamic_cast<E*>(obj2);
		ss << "Class A: ["<< o1->f() <<" "<< o1->getC()<<"],["<<o2->f()<<" "<<o2->getN()<<"]"<< " g()="<<g()<<endl;
		return os << ss.str();
	}

};

class B : public A{
public:
	B(float x) : A(x){}
	string st(){
		stringstream ss;

		D* o1 = dynamic_cast<D*>(obj1);
		E* o2 = dynamic_cast<E*>(obj2);

		ss << g();
		for(int i=0; i<o2->getN(); i++) ss<<o1->getC();

		return ss.str();
	}

	ostream& put(ostream& os){
		stringstream ss;
		D* o1 = dynamic_cast<D*>(obj1);
		E* o2 = dynamic_cast<E*>(obj2);
		ss << "Class B: ["<< o1->f() <<" "<< o1->getC()<<"],["<<o2->f()<<" "<<o2->getN()<<"]"<< " g()="<<g()<<" st()="<<st()<<endl;
		return os << ss.str();
	}
};

ostream& operator<< (ostream& os, A* a){
	return a->put(os);
}

int main(){


	srand(82137209);
	A* vett [DIM];
	for (int i=0; i<DIM; i++) {
	  if (rand()%2==1)   vett[i] = new A((float)rand()/INT_MAX);
	              else   vett[i] = new B((float)rand()/INT_MAX);
	}

	//0
	cout<<endl;
	for(int i=0; i<DIM; i++) cout<<vett[i];
	cout<<endl;

	
	//1
	cout<<endl;
	double sum = 0.0;
	for(int i=0; i<DIM; i++) sum+=vett[i]->g();
	cout<<"sum="<<sum<<endl;

	//2
	cout<<endl;
	int sum2 = 0;
	for(int i=0; i<DIM; i++){
		if(B* obj = dynamic_cast<B*>(vett[i])){
			string tmp = obj->st();
			for(int j=0; j<tmp.size();j++){
				sum2+=(int)tmp[i];
			}
		}
	}
	cout<<"sum2:"<<sum2<<endl;


}