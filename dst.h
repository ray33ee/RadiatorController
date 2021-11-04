
#include "Particle.h"

class DST {
private:
    
    TCPClient _client;
    String _response;
    bool _brace;
    
public:

    void send() {
        _brace = false;
        _response = String();
            
        if (_client.connect("worldtimeapi.org", 80)) {
            
        
            _client.println("GET /api/ip HTTP/1.0");
            _client.println("Host: www.worldtimeapi.org");
            _client.println("Content-Length: 0");
            _client.println();
        } else {
            _response = String("could not connect");
        }
    }
    
    int recv() {
        if (_client.connected()) {
            if (_client.available()) {
                char c = _client.read();
                
                //The first(?) open brace represents the start of the JSON data
                if (c == '{') {
                    _brace = true;
                }
                
                if (_brace) {
                    _response += c;
                }
                
                //When we find the closing brace, parse the json data, extract the dst value then close the connection
                if (c == '}') {
                    JSONValue my_time = JSONValue::parseCopy(_response.c_str(), _response.length());
                    
                    JSONObjectIterator iter(my_time);
                    
                    while (iter.next()) {
                        if (iter.name() == "dst") {
                            return iter.value().toBool();
                        }
                    }
                    
                    _client.stop();
                    
                }
            }
        }
        
        return -1; //This iteration of recv did not find the dst value
    }
    
};