//
//  date.cpp
//  VCS
//
//  Created by Jin You on 4/7/17.
//  Copyright © 2017 Jin You. All rights reserved.
//

#include "date.hpp"
#include <stdlib.h>

Date::Date(void){
    day = 1;
    month = 1;
    year = 2000;
};
Date::Date(String date){
    if(date.len != 10)
        Date();
    
    day = date.subStringInt(0, 1);
    month = date.subStringInt(3, 4);
    year = date.subStringInt(6, 9);
    
    if((day < 1 || day > 31) ||
       (month < 1 || month > 12) ||
       (year < 1000 || month > 2018))
        Date();

};
Date::Date(char * date){
    String sDate = *new String(date);
    
    if(sDate.len != 10)
        Date();
    
    day = sDate.subStringInt(0, 1);
    month = sDate.subStringInt(3, 4);
    year = sDate.subStringInt(6, 9);
    
    if((day < 1 || day > 31) ||
       (month < 1 || month > 12) ||
       (year < 1000 || month > 2018))
        Date();
};

