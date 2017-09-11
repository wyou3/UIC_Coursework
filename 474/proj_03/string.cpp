//
//  string.cpp
//  VCS
//
//  Created by Jin You on 4/7/17.
//  Copyright © 2017 Jin You. All rights reserved.
//

#include "string.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>


String::String(const char* input){
    len = (int) strlen(input)+1 ;
    s = new char[len];
    
    for(int i = 0; i < (len - 1); i++)
        s[i] = input[i];
    
    s[(len-1)] = '\0';
}
String::String(){
    s = NULL;
}
String::String(const String & S){
    len = S.len;
    s = new char[len];
    strcpy(s, S.s);
}
String::~String(){
    if(s != NULL)
        delete s;
}

char* String::getString(){
    return s;
}


int String::subStringInt(int start, int end){
    int num = 0;
    if(start >= 0 && end < len){
        for(int i=start; i<end; i++){
            if(isdigit(s[i])){
                int digit = s[i] - '0';
                num = num * 10 + digit;
            }else
                return -1;
        }
    }
    
    return num;
}


bool String::operator ==(const String& comp){
    
    if( (int) strlen(comp.s) != len)
        return false;
    
    for(int i=0; i<len; i++)
        if(s[i] != comp.s[i])
            return false;
   
    return true;
};


ostream& operator <<(std::ostream & outStream, const String& String){
    outStream << String.s;
    return outStream;
}


