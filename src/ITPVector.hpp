#pragma once
#include <sstream>
#include <ostream>
#include <stdexcept>

template <typename T>
class ITPVector
{
	const unsigned INITIAL_CAPACITY = 10;
	const unsigned CAPACITY_MULTIPLIER = 2;
public:
	// Function: Constructor
	// Purpose: Initializes the ITP vector to have a
	// capacity of INITIAL_SIZE and a size of 0.
	// It also dynamically allocates the underlining array data
	// Input: None
	// Returns: Nothing
	ITPVector()
	{
        mSize = 0;
        mCapacity = INITIAL_CAPACITY;
        mArr = new T[mCapacity];
	}

	// Function: Constructor
	// Purpose: Initializes the ITP vector to have a
	// capacity of inputted value.
	// It also dynamically allocates the underlining array data
	// Input: Unsigned integer
	// Returns: Nothing
	ITPVector(unsigned inCapacity)
	{
        mSize = 0;
        mCapacity = inCapacity;
        mArr = new T[mCapacity];
        
	}

	// Function: Copy Constructor
	// Purpose: Initializes the ITP vector to have a
	// copy of the inputted vector
	// Input: Another ITPVector
	// Returns: Nothing
	ITPVector(const ITPVector<T>& other)
	{
        mSize = 0;
        mCapacity = other.size();
        mArr = new T[mCapacity];
        for(int i = 0; i < other.size(); i++)
        {
            this->push_back(other[i]);
        }
	}

	// Function: Assignment operator
	// Purpose: Clears the current vector and sets
	// the vector to have a copy of the inputted vector
	// Input: Another ITPVector
	// Returns: Nothing
	ITPVector<T>& operator=(const ITPVector<T>& other)
	{
        //calling clear on the current vector
        this->clear();
        //create a new array with the capacity equals exactly to the size of the copied array
        T* temp = new T[other.size()];
        //update the current vector
        mArr = temp;
        mCapacity = other.size();
        //copy each elements from the other array to this by using push_back
        for(int i = 0; i < other.size(); i++)
        {
            this->push_back(other[i]);
        }
        //default return value is *this
        return *this;
	}

	// Function: Destructor
	// Purpose: Deletes the underlying array and
	// sets size/capacity to zero
	// Input: None
	// Returns: Nothing
	~ITPVector()
	{
        delete [] mArr;
        mArr = nullptr;
        mSize = 0;
        mCapacity = 0;
	}

	// Function: clear
	// Purpose: Emptys the current vector
	// Input: None
	// Returns: None
	void clear()
	{
        //creating a new empty array with the same capacity
        T* temp = new T[mCapacity];
        //delete the old array and assign the new one to the array pointer
        delete[] mArr;
        mArr = temp;
        //reset size to zero
        mSize = 0;
	}

	// Function: empty
	// Purpose: Returns true if the vector is empty
	// Input: None
	// Returns: Boolean
	bool empty()
	{
		return mSize == 0;
	}
	
	// Function: capacity
	// Purpose: Returns the current capacity of the underlying array data
	// Input: None
	// Returns: Capacity of underlying array data
	unsigned capacity() const
	{
		return mCapacity;
	}

	// Function: size
	// Purpose: Returns the current size of the vector
	// Input: None
	// Returns: Size of vector
	unsigned size() const
	{
		return mSize;
	}

	// Function: data
	// Purpose: Returns the pointer to the underlying array
	// Input: None
	// Returns: T*
	T* data() const
	{
		return mArr;
	}

	// Function: Subscript operator (read/write version)
	// Purpose: Grabs the specified index from vector
	// Causes an error if the index is out of bounds
	// Input: Index to access
	// Returns: Value at index, by reference
	T& operator[](unsigned index)
	{
        if(index >= mSize)
        {
            throw std::out_of_range("You cannot use [] since the index you tried to access is out of bonds");
        }
        return mArr[index];
	}

	// Function: Subscript operator (read-only version)
	// Purpose: Grabs the specified index from vector
	// Causes an error if the index is out of bounds
	// Input: Index to access
	// Returns: Value at index, by reference
	const T& operator[](unsigned index) const
	{
        if(index >= mSize)
        {
            throw std::out_of_range("You cannot use [] since the index you tried to access is out of bonds");
        }
        return mArr[index];
	}

	// Function: insert_back
	// Purpose: Adds the specified element to the end of the ITPVector
	// It automatically reallocates the underlying array if we are
	// going over capacity
	// Input: Value to add (by const reference)
	// Returns: Nothing
	void push_back(const T& value)
	{
		//first check if reallocation is need
        if(mSize == mCapacity)
        {
            //create a new underlying array with enlarged capacity of the old one
            T* temp = new T[mCapacity * CAPACITY_MULTIPLIER];
            //update the new capacity
            mCapacity *= CAPACITY_MULTIPLIER;
            //copy elements in the old array one by one to the new array
            for(int i = 0; i < mSize; i++)
            {
                temp[i] = mArr[i];
            }
            //delete the old array after finished copying
            delete[] mArr;
            //assign the new array to the array pointer
            mArr = temp;
        }
        //putting the new value into the array
        mArr[mSize] = value;
        //increment the size by one
        mSize += 1;
        
	}

	// Function: get_back
	// Purpose: Returns the current last element in the vector
	// Does not remove this element from the vector
	// Causes an error if there are no elements in the vector
	// Input: Nothing
	// Returns: Value at back of vector, by reference
	T& back()
	{
		if(mSize == 0)
        {
            throw std::out_of_range("cannot back() since the vector is currently empty");
        }
        return mArr[size()-1];
	}

	// Function: remove_back
	// Purpose: Removes the last element from the ITPVector
	// Causes an error if there are no elements in the vector
	// Input: Nothing
	// Returns: Nothing
	void pop_back()
	{
        if(mSize == 0)
        {
            throw std::out_of_range("cannot pop_back since the vector is currently empty ");
        }
        mSize -= 1;
	}

	// Function: Output Stream Operator
	// Purpose: Prints the contents of the vector to the provided stream
	// Written in the format of {x, y, ..., z}
	// Input: Stream to write to, vector to write
	// Output: Stream after values are written
	friend std::ostream& operator<<(std::ostream& os, const ITPVector<T>& vector)
	{
        //add in the front {
        os << "{";
        //loop until the last element since all of them need to be prinited in a "ElEMENT, "formet
        for(int i = 0; i < vector.size()-1; i++)
        {
            os << vector[i] << ", ";
        }
        os << vector[vector.size()-1] << "}";
		return os;
	}
private:
    int mSize;
    int mCapacity;
    T* mArr;
    
};
