#include "catch.hpp"

#include "Cards.h"
#include "ITPVector.hpp"

// Helper function declarations (don't change this)
extern bool CheckTextFilesSame(const std::string& fileNameA,
	const std::string& fileNameB);

// Your tests
TEST_CASE("Vector tests", "[student]") 
{
	// Complete tests are worth 2 points for each test
	
	SECTION("Default constructor, size, capacity, and destructor")
	{
        //test the constructor by creating an empty constructor to test size and empty
        ITPVector<int>myVec;
        //size should be 0
        REQUIRE(myVec.size() == 0);
        //empty should be true
        REQUIRE(myVec.empty());
        //capacity should be initialized to 10
        REQUIRE(myVec.capacity() == 10);
	}

	SECTION("Parameterized constructor, size, capacity, and destructor")
	{
        ITPVector<int>myVec(5);
        //size should be 0 since nothing is in it
        REQUIRE(myVec.size() == 0);
        //capacity shold be set to 5
        REQUIRE(myVec.capacity() == 5);
	}

	SECTION("Push_back x1, back, pop_back, destructor")
	{
        ITPVector<int>myVec;
        //push back one element
        myVec.push_back(999);
        //check if it's pushed to the correct spot
        REQUIRE(myVec[0] == 999);
        //check if size is updated
        REQUIRE(myVec.size() == 1);
        //check if back() gives the correct outpput
        REQUIRE(myVec.back() == 999);
        //empty should be false
        REQUIRE(!myVec.empty());
        //pop_back the element
        myVec.pop_back();
        //size should be set to 0
        REQUIRE(myVec.size() == 0);
        //empty should be true
        REQUIRE(myVec.empty());
	}

	SECTION("Push_back x3, operator[], destructor")
	{
        //use a for loop to push three elements into the vector
        ITPVector<int>myVec;
        for(int i = 0; i < 3; i++)
        {
            myVec.push_back(i+10);
            //after each push size should increament by 1
            REQUIRE(myVec.size() == i+1);
            //use back to check whether the pushed elements are correct or not
            REQUIRE(myVec.back() == i+10);
        }
        //a seperate for loop to check whehter [] functions normally
        for(int i = 0; i < 3; i++)
        {
            REQUIRE(myVec[i] == i+10);
        }
	}

	SECTION("Push_back (over capacity), size, capacity, destructor")
	{
        ITPVector<int> myVec;
        //get the initial capcity
        int initCapcity = myVec.capacity();
        //push 2 times over than initial capcity
        for(int i = 0; i < initCapcity; i++)
        {
            myVec.push_back(i+10);
            //ensure the size gets correctly incremented
            REQUIRE(myVec.size() == i+1);
            //ensure back() returns correct result
            REQUIRE(myVec.back() == i+10);
            REQUIRE(myVec.capacity() == initCapcity);
        }
        //at this point, size is equals capacity
        //furthur push will makes the capacity to become initCapcity x 2
        for(int i = initCapcity; i < 2*initCapcity; i++)
        {
            //after the first push_back the capacity should gets initCapcity x 2
            myVec.push_back(i+10);
            REQUIRE(myVec.capacity() == initCapcity*2);
            REQUIRE(myVec.back() == i+10);
        }
	}

	SECTION("Push_back (over capacity), operator[], destructor")
	{
        ITPVector<int> myVec;
        //get the initial capcity
        int initCapcity = myVec.capacity();
        //push until the initial capcity
        for(int i = 0; i < initCapcity; i++)
        {
            myVec.push_back(i+10);
            //ensure the size gets correctly incremented
            REQUIRE(myVec.size() == i+1);
            //ensure back() returns correct result
            REQUIRE(myVec.back() == i+10);
            REQUIRE(myVec.capacity() == initCapcity);
        }
        //at this point, size is equals capacity
        //furthur push will makes the capacity to become initCapcity x 2
        for(int i = initCapcity; i < 2*initCapcity; i++)
        {
            //after the first push_back the capacity should gets initCapcity x 2
            myVec.push_back(i+10);
            REQUIRE(myVec.capacity() == initCapcity*2);
            REQUIRE(myVec.back() == i+10);
        }
        //the third for loop will check whether [] gives out correct data
        for(int i = 0; i < myVec.size(); i++)
        {
            REQUIRE(myVec[i] == i + 10);
        }
	}

	SECTION("Push_back, pop_back, back, operator[], exceptions")
	{
        ITPVector<int> myVec;
        //push in 5 elements to the vector
        for(int i = 0; i < 5; i++)
        {
            myVec.push_back(i+10);
        }
        //get the inital size of the vector
        int prevSize = myVec.size();
        //try poping back see if the first five can be got rid of correctly
        try {
            for(int i = 0; i<5; i++)
            {
                myVec.pop_back();
                //the size should always decrement by 1
                REQUIRE(myVec.size() == prevSize-1);
                prevSize = myVec.size();
            }
            //we try poping one more item which should throw a exception
            myVec.pop_back();
            //will fail the test if exception is not thrown
            REQUIRE(false);
        }
        //explicitly catch the out_of_ran exception
        catch (std::out_of_range& e)
        {
            //test if the size of the vector is 0
            REQUIRE(myVec.size() == 0);
        }
        //catching any other exceptions should throw a false
        catch (std::exception& e)
        {
            REQUIRE(false);
        }
        
        //clear the vector and get prepared for the back() test
        myVec.clear();
        //make sure the vector is clean
        REQUIRE(myVec.size()==0);
        
        /*
         * teset for back() below
         */
        
        //start of by pushing 5 items into the vector
        for(int i = 0; i < 5; i++)
        {
            myVec.push_back(i+10);
        }
        //get the initial size of the vector
        prevSize = myVec.size();
        //try poping back see if the first five can get removed correctly
        try {
            //start from 4 and decrement to 1 so we can use index to produce the correct result
            for(int i = 4; i>-1; i--)
            {
                //result of each back should equals to index + 10
                REQUIRE(myVec.back() == i+10);
                myVec.pop_back();
                //size should always decrement by 1
                REQUIRE(myVec.size() == prevSize-1);
                prevSize = myVec.size();
            }
            //calling back() when vector is empty should throw a exception
            myVec.back();
            REQUIRE(false);
        }
        //explicitly catch the out_of_range exception
        catch (std::out_of_range& e)
        {
            //double check to see if the size equals 0
            REQUIRE(myVec.size() == 0);
        }
        //catching any other kinds of exceptions should be false
        catch (std::exception& e)
        {
            REQUIRE(false);
        }
        
        
        //clear the vector and get prepared for the operator[] test
        myVec.clear();
        //make sure the vector is clean
        REQUIRE(myVec.size()==0);
        
        /*
         * teset for operator[] below
         */
        
        //start of by pushing 5 items into the vector
        for(int i = 0; i < 5; i++)
        {
            myVec.push_back(i+10);
        }
        //get the initial size of the vector
        prevSize = myVec.size();
        //try poping back see if the first five can get removed correctly
        try {
            //start from 4 and decrement to 1 so we can use index to produce the correct result
            for(int i = 4; i>-1; i--)
            {
                //result of each back should equals to index + 10
                REQUIRE(myVec[i] == i+10);
                //each [i] should also equals to back()
                REQUIRE(myVec[i] == myVec.back());
                myVec.pop_back();
                //size should always decrement by 1
                REQUIRE(myVec.size() == prevSize-1);
                prevSize = myVec.size();
            }
            //the size of the vector should be 0 at this point
            REQUIRE(myVec.size() == 0);
            //try accessing the 0th index should throw an exception
            myVec[0] = 999;
            REQUIRE(false);
        }
        //explicitly catch the out_of_range exception
        catch (std::out_of_range& e)
        {
            //test pass if out_of_range is catched
            REQUIRE(true);
        }
        //catching any other kinds of exceptions should be false
        catch (std::exception& e)
        {
            REQUIRE(false);
        }
	}

	SECTION("Push_back (over capacity), operator[] (with assignment), destructor")
	{
        ITPVector<int> myVec;
        //get the initial capcity
        int initCapcity = myVec.capacity();
        //push until the initial capcity
        for(int i = 0; i < initCapcity; i++)
        {
            myVec.push_back(i+10);
            //ensure the size gets correctly incremented
            REQUIRE(myVec.size() == i+1);
            //ensure back() returns correct result
            REQUIRE(myVec.back() == i+10);
            REQUIRE(myVec.capacity() == initCapcity);
        }
        //at this point, size is equals capacity
        //furthur push will makes the capacity to become initCapcity x 2
        for(int i = initCapcity; i < 2*initCapcity; i++)
        {
            //after the first push_back the capacity should gets initCapcity x 2
            myVec.push_back(i+10);
            REQUIRE(myVec.capacity() == initCapcity*2);
            REQUIRE(myVec.back() == i+10);
        }
        //we save the size of vector before changing items with [] for later use
        int beforeIndexingSize = myVec.size();
        //the third for loop will change the value of each index
        for(int i = 0; i < myVec.size(); i++)
        {
            //change the data in each index to i*10
            myVec[i] = i*10;
        }
        //changing with [] should not change the size of the vector, thus myVec.size() should equal to beforeIndexingSize
        REQUIRE(myVec.size() == beforeIndexingSize);
        //test if each data gets correctly changed
        for(int i = 0; i < myVec.size(); i++)
        {
            REQUIRE(myVec[i] == i*10);
        }
	}

	SECTION("Clear")
	{
        ITPVector<int>myVec;
        //push 5 things into the vector
        for(int i = 0; i < 5; i++)
        {
            myVec.push_back(i+10);
            //check if all five elements are correctly pushed
            REQUIRE(myVec.back() == i+10);
            REQUIRE(myVec[i] == i+10);
        }
        //call clear function
        myVec.clear();
        //size should be 0
        REQUIRE(myVec.size() == 0);
        //empty should return true
        REQUIRE(myVec.empty());
	}

	SECTION("Destructor")
	{
        
        //create a vector on heap
        ITPVector<int>* myVec = new ITPVector<int>;
        //push couple elements into the vector
        for(int i = 0; i < 5; i++)
        {
            myVec->push_back(i+10);
        }
        //the vector should not be empty
        REQUIRE(!myVec->empty());
        //test if the vector's size is 5
        REQUIRE(myVec->size() == 5);
        //delete the ITPVector pointer -> ITPVector's destructor should be called
        delete myVec;
        //if the destructor is called, underlying array pointer should be nullptr
        REQUIRE(myVec->data() == nullptr);
        
	}

	SECTION("Copy constructor deep copies")
	{
        //testing the first way of copy constructor
        ITPVector<int> myVec;
        //fist pushing 10 elements into the vector
        for(int i = 0; i < 10; i++)
        {
            myVec.push_back(i+10);
            REQUIRE(myVec.size() == i+1);
            REQUIRE(myVec.back() == i+10);
        }
        //create a "copy" vector
        ITPVector<int> newVec = myVec;
        //check whether the copy vector has the correct size
        REQUIRE(newVec.size() == 10);
        //use [] to check whether the copy vector has correct values
        for(int i = 0; i < newVec.size(); i++)
        {
            REQUIRE(newVec[i] == i+10);
        }
        //clear the other vector
        myVec.clear();
        //check if vector is cleared
        REQUIRE(myVec.empty());
        //check if the copy vector's size is still correct
        REQUIRE(newVec.size() == 10);
        //check if the copy vector has all correct elements
        for(int i = 0; i < newVec.size(); i++)
        {
            REQUIRE(newVec[i] == i+10);
        }
        
       /*
         * testing the second way of copy constructor
         */
        ITPVector<int> myVec2;
        //put in 10 elements into the vector
        for(int i = 0; i < 10; i++)
        {
            myVec2.push_back(i+10);
            //check if elements are emplaced correctly
            REQUIRE(myVec2.size() == i+1);
            REQUIRE(myVec2.back() == i+10);
        }
        //create a copy vector and use contructor copy
        ITPVector<int> newVec2(myVec2);
        //see if size is correct
        REQUIRE(newVec2.size() == 10);
        //check if all elements are correct
        for(int i = 0; i < newVec2.size(); i++)
        {
            REQUIRE(newVec2[i] == i+10);
        }
        //call clear on the origianl vector
        myVec2.clear();
        //check if the origianl vector is cleared
        REQUIRE(myVec2.empty());
        //the copy vector's size should not changed
        REQUIRE(newVec2.size() == 10);
        //check whether elements in the copy vector are correct
        for(int i = 0; i < newVec2.size(); i++)
        {
            REQUIRE(newVec2[i] == i+10);
        }
	}

	SECTION("Assignment operator deep copies")
	{
        ITPVector<int>myVec;
        //push 10 elements into the vector
        for(int i = 0; i < 10; i++)
        {
            myVec.push_back(i+10);
            REQUIRE(myVec.size() == i+1);
            REQUIRE(myVec.back() == i+10);
        }
        //we create a new vector and fill it with twenty 999
        ITPVector<int> newVec;
        for(int i = 0; i < 20; i++)
        {
            newVec.push_back(999);
            REQUIRE(newVec.back() == 999);
        }
        //size of the copy vector shold be 20
        REQUIRE(newVec.size() == 20);
        //equite newVec with myVec
        newVec = myVec;
        //size of the two vectors should equal
        REQUIRE(myVec.size() == newVec.size());
        //check if the copy vector's elements are correctly copied
        for(int i = 0; i < newVec.size(); i++)
        {
            REQUIRE(newVec[i] == i+10);
        }
        //call clear on the orignial vector
        myVec.clear();
        //see if the origianl vector is emptied
        REQUIRE(myVec.empty());
        //copy vector's size should not change
        REQUIRE(newVec.size() == 10);
        //check if copy vector's elements are correct
        for(int i = 0; i < newVec.size(); i++)
        {
            REQUIRE(newVec[i] == i+10);
        }
	}

	// Complete tests for this section is worth 24 points
}


