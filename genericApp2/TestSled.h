//
//  TestSled.h
//  genericApp2
//
//  Created by Arpin, Gregg on 8/6/15.
//  Copyright (c) 2015 Arpin, Gregg. All rights reserved.
//

#ifndef genericApp2_TestSled_h
#define genericApp2_TestSled_h

#include <iostream>

#define test_fail(msg) { std::cout << "FAILED in " << __FILE__ << " at " << __LINE__ << msg ; return;}
#define test_fail_if(cond, msg) if (cond) { test_fail(msg); }
#define test_pass {std::cout << "Test passed at " << __FILE__ << " at " << __LINE__;}

class TestSled
{
public:
    virtual void test() = 0;
};

#endif
