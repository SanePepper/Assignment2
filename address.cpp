#include <iostream>
#include "address.h"

using namespace std;

std::vector<Entry> Address::entries;

bool Address::parse_arg(const std::vector<std::string>& arguments){
	if (arguments.size() == 0) {return 0;}
	else{
		if ((arguments.size() == 3) && (arguments[0] == "add")){
			if (strtoint(arguments[2],0).second == 0){
				return 0;
			}
			return Address::add_entry(arguments[1],strtoint(arguments[2],0).first);
		}
		else if ((arguments.size() == 2) && (arguments[0] == "del")){
			if ((strtoint(arguments[1],1).second == 0) && (arguments[1] != "*")){
				return 0;
			}
			return Address::del_entry((int*)strtoint(arguments[1],1).first);
		}
		else if ((arguments.size() == 3) && (arguments[0] == "chg")){
			if ((strtoint(arguments[1],1).second == 0) || (strtoint(arguments[2],0).second == 0)){
				return 0;
			}
			return Address::chg_entry((int*)strtoint(arguments[1],1).first,strtoint(arguments[2],0).first);
		}
		else {return 0;}
	}
}

bool Address::add_entry(const std::string& name, const int& value){
	int* address = new int(value);
	entries.emplace_back(name,address);
	return 1;
}

bool Address::del_entry(int* address){
	if (address == 0){
		entries.clear();
		return 1;
	}
	else{
		bool found = 0;
		int i = 0;
		for (; i < entries.size(); i++){
			if (entries[i].addr_ == address){
				found = 1;
				break;
			}
		}
		if (!found){
			return 0;
		}
		else{
			delete entries[i].addr_;
			entries.erase(entries.begin()+i);
			return 1;
		}
	}

}

bool Address::chg_entry(int* address, const int& value){
	bool found = 0;
	int i = 0;
	for (; i < entries.size(); i++){
		if (entries[i].addr_ == address){
			found = 1;
			break;
		}
	}
	if (!found){
		return 0;
	}
	else{
		*entries[i].addr_ = value;
		return 1;
	}
}

void Address::print_data(){
	cout << "Address\t\tName\tValue" << endl;
	for (int i = 0; i < entries.size(); i++){
		cout << entries[i].addr_ << "\t" << entries[i].name_ << "\t" << *entries[i].addr_ << endl;
	}
}
