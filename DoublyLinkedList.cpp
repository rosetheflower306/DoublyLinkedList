//Rose Tran - Assignment 2
#include <iostream>
#include <vector>
#include <string>
using namespace std;

template <class T>
class DoublyLinked
{
  private:
    struct Node
    {
      T data;
      Node *next;
      Node *prev;
    };
    
    Node *head;
    Node *tail;
    int count;

  public:
    //Default Constructor
    DoublyLinked()
    {
      head = tail = nullptr;
      count = 0;
    }

    //Copy constructor
    DoublyLinked(const DoublyLinked &list)
    {
      Node * currentNode = list.head;
      while (currentNode != nullptr)
      {
        push_back(currentNode->data);
        currentNode = currentNode->next;
      }
    }

    //Destructor
    ~DoublyLinked()
    {
      Node * currentPtr = head;
      Node * temp = nullptr;
      while (currentPtr != nullptr)
      {
        temp = currentPtr->next;
        delete currentPtr;
        currentPtr = temp;
        count--;
      }
      head = tail = nullptr;
      count = 0;
    }
  
    /**
     * This function will push the T type value at the tail of the list
     * @param value A T type value that will be add to the list
    */
    void push_back(T value)
    {
      Node * newNode = new Node();
      newNode->data = value;
      if (tail != nullptr) //list is not empty
      {
        tail->next = newNode; // tail should point to newNode
        newNode->prev = tail; //newNode now is the last node
        newNode->next = NULL;
        tail = newNode;
      }
      else //the list is empty
      {
        head = newNode;
        tail = newNode;
      }
      count++;
    }
  
    /**
     * This function display all the node's values in the list
    */
    void displayNode()
    {
      Node * currentPtr = head;
      while (currentPtr != nullptr)
      {
        cout << currentPtr->data; //display node's value
        currentPtr = currentPtr->next; //move to the next node
      }
    }
    
    /**
     * This function delete all in the instances of the matched item
     * @param item A T type item that need to be deleted
     * @return true if item is deleted, false if item not found
    */
    bool deleteItem(T &item)
    {
      if (count == 0) // list is empty, no items to delete
      {
        return false;
      }
      int position = 0; //to retrive the index of the matched item
      Node * currentNode = head;
      Node * temp = nullptr;
      while (currentNode != nullptr)
      {
        temp = currentNode->next;
        if (currentNode->data == item)
        {
          deleteNode(position);
          position--;
        }
        currentNode = temp;
        position++;
      }
      return true; 
    }

    /**
     * This function use to delete the node after a previous node
     * @param prevNode a Node type 
    */
    void deleteAfter(Node * prevNode)
    {
      Node * del = prevNode->next; //get the delete node
      prevNode->next = del->next; //adjust the link
      if (del->next != nullptr)
      {
        del->next->prev = prevNode;
      }
      delete del;
      count--;
    }

    /**
     * This function delete in node respect to the matched index
     * @param index a int value, which is the index of the deleted node
    */
    void deleteNode(int index)
    {
      if (index < 0 || index >= count || head == nullptr)
      {
        cout << "Invalid index.\n";
      }
      else if (index == 0) // this is the first node
      {
        cout <<"\nDeleteing from head...\n";
        Node * prevHead = head;
        head = head->next;
        head->prev = nullptr; //new head's prev now points to null
        delete prevHead; //the original head would be deleted
        count--; //update count
      }
      else if (index < count/2) //Index is closer to the beginning, navigate from head
      {
        cout <<"\nDeleteing from head...\n";
        Node * current = head;
        for(int i = 0; i < index-1; i++)
        {
          current = current->next;
        }
        // delete value after the node at index position
        deleteAfter(current);
      }
      else //Index is closer to the end, navigate from tail
      {
        cout <<"\nDeleteing from tail...\n";
        Node * current = tail;
        for(int i = count - 1; i >= index; i--)
        {
          current = current->prev;
        }
        // delete value after the node at index position
        deleteAfter(current);
      }
      //return true;  
    }

    /**
     * This function reveres the order of the nodes in the list
    */
    void reverse()
    {
      Node* hNode = head;
      Node* tNode = tail;
      for (int i = 0; i < count/2; i++) 
      {
        T temp = hNode->data;
        hNode->data = tNode->data;
        tNode->data = temp;
        hNode = hNode->next;
        tNode = tNode->prev;
      }
    }

    /**
     * This function search the node and return its index positions into a vector variable
     * @param item an T type of the node that needed to search for
     * @return a vector varable stores all the matched index positions
    */
    vector<int> search(T item)
    {
      vector<int> positions;
      int index = 0;
      if (count == 0 || head == NULL)
      {
        cout << "List is empty.\n";
      }
      else
      {
        Node * currentNode = head;
        while (currentNode != nullptr)
        {
          if (currentNode->data == item)
          {
            positions.push_back(index);
          }
          currentNode = currentNode->next;
          index++;
        }
      }
      return positions;
    }
};

class Movie 
{
  private:
    string title;
    string director_name;
    int release_year;
  public:
    //default constructor
    Movie()
    {
      title = " ";
      director_name = " ";
      release_year = 0;
    }

    //Constructor
    Movie(string t, string dn, int ry)
    {
      this->title = t;
      this->director_name = dn;
      this->release_year = ry;
    }

    //copy constructor
    Movie(const Movie &obj)
    {
      this->title = obj.title;
      this->director_name = obj.director_name;
      this->release_year = obj.release_year;
    }

    // Overloaded == operator for Movie comparison
    bool operator == (const Movie& obj) const 
    {
      return (title == obj.title) && (director_name == obj.director_name) && (release_year == obj.release_year);
    }

    // Convert the Movie object to a string
    std::string to_string() const 
    {
      return "Title: " + title + ", Director: " + director_name + ", Year: " + std::to_string(release_year) + "\n";
    }

    // Overloaded << operator to display a Movie
    friend ostream & operator << (ostream &out, const Movie &movie) 
    {
      out << movie.to_string();
      return out;
    }
};

int main()
{
  // Declare a DoublyLinkedList of Movie objects
  DoublyLinked<Movie> movCollection;

  //a) Declare 10 Movie objects and add them to the movCollection variable.
  Movie obj1 = Movie("The Little Prince", "Mark Osborne", 2015);
  Movie obj2 = Movie("Doona", "Min Song-ah", 2023);
  Movie obj3 = Movie("My Liberation Note", "Kim Seok Yoon", 2022);
  Movie obj4 = Movie("Our Beloved Summer", "Kim Yoon Jin", 2021);
  Movie obj5 = Movie("It's Okay to Not Be Okay", "Jung Dong Yoon", 2020);
  Movie obj6 = Movie("It's Okay to Not Be Okay", "Park Shin Woo", 2020);
  Movie obj7 = Movie("Alchemy of Souls", "Park Joon Hwa", 2022);
  Movie obj8 = Movie("Coffee Prince", "Lee Yoon Jung", 2007);
  Movie obj9 = Movie("While You Were Sleeping ", "Park Soo Jin", 2017);
  Movie obj10 = Movie("Mr. Sunshine", "Lee Eung Bok", 2018);
  movCollection.push_back(obj1);
  movCollection.push_back(obj2);
  movCollection.push_back(obj3);
  movCollection.push_back(obj4);
  movCollection.push_back(obj5);
  movCollection.push_back(obj6);
  movCollection.push_back(obj7);
  movCollection.push_back(obj8);
  movCollection.push_back(obj9);
  movCollection.push_back(obj10);
  
  //b) Display all the Movie objects using cout
  cout << "The original movie collection: \n";
  cout << obj1 << obj2 << obj3 << obj4 << obj5 << obj6
       << obj7 << obj8 << obj9 << obj10 << endl;
  
  //c) Create a copy of movCollection named myMovCollection
  //and Display the content of myMovCollection
  DoublyLinked<Movie> myMovCollection(movCollection);
  cout << "My Movie Collection (Copy of the Original):" << endl;
  myMovCollection.displayNode();

  //d) Reverse movies in movCollection and display contents
  movCollection.reverse();
  cout << "\nMy Movie Collection (Reversed Version):" << endl;
  movCollection.displayNode();

  //e) Declare a Movie object and demonstrate the searchItem(movObj) function. Display all the index
  // positions where this Movie object is found in the movCollection variable.
  Movie movObj = Movie("Coffee Prince", "Lee Yoon Jung", 2007);
  movCollection.push_back(movObj);
  vector<int> c = movCollection.search(movObj);
  cout << "\nPositions of the searched item:\n";
  for (int i : c)
  {
    cout << i << endl;
  }

  //f) Declare a Movie object and demonstrate the deleteItem(movObj) function. Display the content of
  //the movCollection variable to ensure that the delete operation has taken place.
  Movie movObj2 = Movie("Ha Lan", "Victor Vu", 2019);
  movCollection.push_back(movObj2);
  movCollection.deleteItem(movObj2);
  cout << "Movie collection after deletation:\n";
  movCollection.displayNode();
  return 0;
}