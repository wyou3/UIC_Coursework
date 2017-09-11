//
//  string.hpp
//  VCS
//
//  Created by Jin You on 4/7/17.
//  Copyright © 2017 Jin You. All rights reserved.
//

#ifndef string_hpp
#define string_hpp

# include <iostream>

using namespace std;

class String{
public:
    char* s;
    int len;

    String(void);
    String(const char*);
    String(const String&);
    ~String(void);
    char* getString();
    int subStringInt(int start, int end);
    friend ostream& operator <<(ostream & outStream, const String& String);
    bool operator ==(const String & comp);
};

#endif /* string_hpp */
