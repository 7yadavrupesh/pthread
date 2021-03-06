/*
   main.cpp

   Test application for the mutex class in C++.
  
   ------------------------------------------

   Copyright @ 2013 [Vic Hargrave - http://vichargrave.com]

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include "thread.h"
#include <unistd.h>
#include "mutex.h"
#include <iostream>
 
using namespace std;

class MutexTest : public Thread
{
    Mutex &m_mutex;
    char c;
    public:
    MutexTest(char chr, Mutex& mutex) :c(chr), m_mutex(mutex) {}
    void* run() {
        
        m_mutex.lock();
        
        for(int i=0; i<5; i++)
          cout << c;
        // hold lock for awhile to make main thread wait
        sleep(3);
        m_mutex.unlock();
        return NULL;
    }
};

int main(int argc, char** argv)
{
    Mutex mutex;
    MutexTest test1('A',mutex), test2('B',mutex);

    test1.start();
    sleep(1);
    test2.start();

    // give thread a chance to acquire lock first
    

    // now it's main threads turn 
    test1.join();
    test2.join();
    
    exit(0);
}
