//
//  date.hpp
//  VCS
//
//  Created by Jin You on 4/7/17.
//  Copyright © 2017 Jin You. All rights reserved.
//

#ifndef date_hpp
#define date_hpp

#include <iostream>
#include "string.hpp"

class Date{
private:
    int day;
    int month;
    int year;
    
public:
    Date(void);
    Date(String date);
    Date(char * date);    
};

#endif /* date_hpp */
