#include "java.h"

Java::Java(std::string name, double price, double cost, Darkness darkness)
    : Product{name, price, cost}, _darkness{darkness} { }

 Java::Java(std::istream& ist):Product{ist} {
 	int temp, shot_num;
    ist >> temp; ist.ignore();
    _darkness = (Darkness)temp;
    ist >> temp; ist.ignore();
    shot_num = temp;
    for(int i = 0;i<shot_num;i++)
    {
    	ist >> temp; ist.ignore();
    	_shots.push_back((Shot)temp);
    }
} 

void Java::save(std::ostream& ost) {
	ost<< "(JAVA)"<<std::endl;
    ost << _name << std::endl;
    ost << _price << std::endl;
    ost << _cost << std::endl;
    ost <<(int) _darkness << std::endl;
    ost << _shots.size()<<std::endl;
   	for(int i=0; i <_shots.size();i++)
   	{
   		ost <<(int) _shots[i] << std::endl;
   	}

}


void Java::add_shot(Shot shot) {_shots.push_back(shot);}

std::string Java::to_string() {
    std::string result =  Product::to_string() + " (" + darkness_to_string[_darkness]
        + ")";
    std::string separator = " with ";
    for (auto s : _shots) {result += separator + shot_to_string[s]; separator = ", ";}
    return result;
}



