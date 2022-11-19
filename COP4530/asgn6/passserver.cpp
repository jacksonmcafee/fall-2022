#include "hashtable.h"
#include "passserver.h"
#include "base64.h"
#include <cstddef>
#include <cstring>

const size_t MAXSIZE = 100;

// PassServer constructor
PassServer::PassServer(size_t size) {
    // create hashtable
    passServer = cop4530::HashTable<std::string, std::string>(size);
    size = 0;
}

// PassServer destructor
PassServer::~PassServer() {
    // use clear() to empty passServer
    passServer.clear();
}   

// encrypt password from filename and populate hashtable
bool PassServer::load(const char* filename) {
    // populate passServer with username & unencrypted pswd
    return passServer.load(filename);

    // TODO: iterate through passServer and encrypt each pswd
}

// add user given a pair of username and plaintext pswd
bool PassServer::addUser(std::pair<std::string, std::string>& kv) {
	return passServer.insert(make_pair(kv.first,encrypt(kv.second)));
}

// move alternative to addUser
bool PassServer::addUser(std::pair<std::string, std::string>&& kv) {
	return passServer.insert(std::move(make_pair(kv.first,encrypt(kv.second))));
}

// remove user given key K
bool PassServer::removeUser(const std::string& k) {
    return passServer.remove(k);
}

// change user password if given password != old password and user exists
bool PassServer::changePassword(const std::pair<std::string, std::string>& p, const std::string& newpassword) {
    // first, check if pair MATCHES existing pair in passServer
    // second, check that pair.password != newpassword WHEN ENCRYPTED
	if(passServer.match(make_pair(p.first, encrypt(p.second))) == true && encrypt(p.second) != encrypt(newpassword)) { 
		passServer.insert(make_pair(p.first, encrypt(newpassword)));
		return true;
	}
    // password cannot be changed because user doesn't exist OR because newpassword == oldpassword
	return false;
}

bool PassServer::find(const std::string& user) {
    return passServer.contains(user);
}

// calls HashTable.dump()
void PassServer::dump() {
    passServer.dump();
}

// calls HashTable.getSize()
size_t PassServer::getSize() {
    return passServer.getSize();
}

// calls HashTable.write_to_file()
bool PassServer::write_to_file(const char* filename) {
    return(passServer.write_to_file(filename));
}

// encrypts password
std::string PassServer::encrypt(const std::string& str) {
    size_t n = str.length();
    BYTE c_in[MAXSIZE];
    BYTE c_out[MAXSIZE]; 
    strcpy(c_in, str.c_str());
    base64_encode(c_in, c_out, n, 1);
    std::string s(c_out);
    return s;
}