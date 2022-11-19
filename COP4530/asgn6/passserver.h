#include "base64.h"
#include "hashtable.h"

class PassServer {
	
	public:
        // constructor and destructor
		PassServer(size_t size = 101);
		~PassServer();				
        
        // encrypt password from filename and populate hashtable
    	bool load(const char* filename);
		bool addUser(std::pair<std::string, std::string>& kv);
		bool addUser(std::pair<std::string, std::string>&& kv);
		bool removeUser(const std::string& k); 				
		bool changePassword(const std::pair<std::string, std::string>& p, const std::string& newpassword); 
		bool find(const std::string& user); 				
		void dump(); 										
		size_t getSize();										
		bool write_to_file(const char* filename);
	
	private:
		std::string encrypt(const std::string& str);
		cop4530::HashTable<std::string, std::string> passServer;
};