#include<iostream>
#include<string>
#include<fstream>
using namespace std;
template<typename T1>

class Car_Rental {
private:
T1 ID;
string name;
double price;
bool available;
public:
Car_Rental(){
    ID= T1();
    name=" ";
    price= 0.0;
    available = false;
}
Car_Rental( T1 d,const string& n,double p, bool av){
    ID=d;
    name=n;
    price=p;
    available=av;
}
void setID(T1 d){
    this->ID=d;
}
void setName(const string& n){
    this->name=n;
}
void setPrice(double p){
    this->price=p;
}
void setAvailable( bool av){
    this-> available=av;
}

T1 getID() const{
    return this->ID;
}
string getName() const{
    return this->name;
}
double getPrice() const{
    return this-> price;
}
bool getAvailable()const{
    return this-> available;
}
void display() const {
    cout<<"ID: "<<ID<<endl;
    cout<<"Name "<<name<<endl;
    cout<<"price: "<<price<<endl;
    cout<<"availablity: "<<(available? "Yes": "No")<<endl;
}
};



// LL class Node 
template<typename T > 
class LLnode{
    public: 
    Car_Rental<T> car;
    LLnode* next;
    LLnode(Car_Rental<T> c){
        car = c;
        next =nullptr;
    }
};
// LL class 
template<typename T>
class LL{
    private:
    LLnode<T>* head;
    public:
    LL(){
        head = nullptr;
    }

    void addCar( Car_Rental<T> car){
        LLnode<T>*newNode = new LLnode<T> (car);

        if (head==nullptr){
            head=newNode;
            return;
        }
        LLnode<T>* temp =head;
        while(temp->next!=nullptr)
        temp=temp->next;
    temp->next=newNode;
    }

//delete car by name
void deleteCar( const string& name){
    if(head==nullptr){
        cout<<"Storage is empty, There is no cars"<<endl;
        return ;
    }
    if(head->car.getName() ==name){
        LLnode<T>* temp =head;
        head=head->next;
        delete temp;
        cout<<" car deleted"<<endl;
        return ;
    }
    LLnode<T>* current= head;
    LLnode<T>* prev = nullptr;
    while (current != nullptr && current->car.getName() != name){
        prev= current;
        current=current->next;
    }
    if(current==nullptr){
        cout<<" car not found"<<endl;
        return ;
    }
    prev->next = current-> next;
    delete current;
    cout<<" car deleted"<<endl;
}
// display cars 
void display()const{
    if(head==nullptr){
        cout<<" No cars available"<<endl;
        return ;
    }
    LLnode<T>* temp=head;
    while(temp!=nullptr){
        temp->car.display();
        cout<<"-----------"<<endl;
        temp=temp-> next;
    }
}

// sort by price 
void sortByPrice(){
    if(!head || !head->next) return;

    bool swapped;
    LLnode<T>* ptr;
    LLnode<T>* last = nullptr;

    do{
        swapped = false;
        ptr = head;

        while(ptr->next != last){
            if(ptr->car.getPrice() > ptr->next->car.getPrice()){
                swap(ptr->car, ptr->next->car);
                swapped = true;
            }
            ptr = ptr->next;
        }
        last = ptr;
    }while(swapped);

    cout << "Cars sorted by price!\n";
}



// sort by name 
void sortByName(){
    if(!head || !head->next) return;

    bool swapped;
    LLnode<T>* ptr;
    LLnode<T>* last = nullptr;

    do{
        swapped = false;
        ptr = head;

        while(ptr->next != last){
            if(ptr->car.getName() > ptr->next->car.getName()){
                swap(ptr->car, ptr->next->car);
                swapped = true;
            }
            ptr = ptr->next;
        }
        last = ptr;
    }while(swapped);

    cout << "Cars sorted by name!\n";
}
// search by ID
Car_Rental<T>* findByID(T id){
    LLnode<T>* temp = head;
    while(temp != nullptr){
        if(temp->car.getID() == id){
            return &(temp->car);
        }
        temp = temp->next;
    }
    return nullptr;
}

//write to files 
void writeToFile(ofstream &file) const {
    LLnode<T>* temp = head;  
    while(temp) {
        file << temp->car.getID() << " "
            << temp->car.getPrice() << " "
            << temp->car.getAvailable() << " "
            << temp->car.getName() << endl;
        temp = temp->next;
    }
}
};



// BST
template <typename T> 
class BSTNode{
    public:
    Car_Rental<T> data;
    BSTNode* left;
    BSTNode* right;
    BSTNode(const Car_Rental<T>& vehicle){
        this-> data = vehicle;
        left=nullptr;
        right= nullptr;
    }
};
template<typename T> 
class BST{
public: 
BSTNode<T>* root; // for public delete function 
BST(){
    root= nullptr;
}
// Insert car into the BST ( sort data by ID)
bool insert ( Car_Rental<T> vehicle){
    // case 1 : if the tree is empty 
    if( root == nullptr){
        root = new BSTNode<T>(vehicle);
        return true;
    }
    BSTNode<T>* current = root;
    BSTNode<T>* parent = nullptr;

    while(current != nullptr){
        parent= current;
        if(vehicle.getID()<current->data.getID()){
            current = current-> left;
        }
        else if ( vehicle.getID()> current-> data.getID()){
            current=current-> right;
        }
        else {
            // duplication of ID are not allowed
            return false;
        }
    }
    if(vehicle.getID()<parent->data.getID())
    parent->left=new BSTNode<T>(vehicle);
    else 
    parent->right = new BSTNode<T>(vehicle);
    return true;
}



// inorder traversal

void inOrder(BSTNode<T>* r){
    if( r ==nullptr)
    return;
    inOrder(r->left);
    r->data.display();
    inOrder(r->right);
}

// public function
void displaySorted(){
    inOrder(root);
}
// search by ID
BSTNode<T>* SearchById(T id){
    BSTNode<T>* current=root;
    while(current!=nullptr){
        if(id==current->data.getID()){
            return current;
        }
        else if (id<current->data.getID()){
        current = current-> left; 
    }
    else{
        current=current->right;
    }
}
    return nullptr;// car not found
}


// delete by ID

// helpful function 
BSTNode<T>* findMin(BSTNode<T>* node){
    while(node &&node->left != nullptr)
    node=node->left;
return node;
}
//delete by ID
BSTNode<T>* deleteNode(BSTNode<T>* root, T id){
    if( root ==nullptr){
        return root;
    }
        if(id< root->data.getID()){
            root-> left = deleteNode(root->left,id);
        }
        else if (id >root->data.getID()){
            root->right = deleteNode(root->right,id);
        } 
        else {
// case 1 & 2 : zero or one child
            if(root->left==nullptr){
                BSTNode<T>* temp =root->right;
                delete root;
                return temp;
            }
        else if ( root->right == nullptr){
                BSTNode<T>* temp= root->left;
                delete root;
                return temp;
            }
//  case 3: two children
        BSTNode<T>*temp = findMin(root->right);
        root->data = temp-> data;
        root->right=deleteNode(root->right,temp->data.getID());
        }
        return root;
        }
    // public delete function
void deleteByID(T id){
    root =deleteNode(root,id);
}
};


// stack Node

template<typename S>
class STnode{
    public:
    S element;
    STnode<S>* next;
    STnode(){
        next = nullptr;
    }
    STnode(const S& element){
        this->element=element;
        next=nullptr;
    }
};

//stack
template<typename S>
class stack{
    private: 
    int size;
    STnode<S>*top;
    public:
    stack(){
        size=0;
        top=nullptr;
    }
    void push(const S& item){
        STnode<S>*newCAR= new STnode<S>(item);
        if(top==nullptr){
            newCAR->next=nullptr;
            top=newCAR;
        }
        else{
            newCAR->next=top;
            top=newCAR;
        }
        size++;
    }
    S pop(){
        if(size==0){
            throw runtime_error("Stack is empty, nothing to remove");
        }
        else{
            STnode<S>*delptr=top;
            top=top->next;
            S element = delptr->element;
            delete delptr;
            size--;
            return element;
        }
    }
    S peek() const { 
        if(isempty()){
            throw runtime_error("there is no rented cars");
        }
        return top->element;
    }
    bool isempty()const{
        return top ==nullptr;
    }
    void display() const{// 3lshan display last rented cars
        STnode<S>* temp =top;
        while(temp!=nullptr){
            temp->element.display();
            cout<<"---------"<<endl;
            temp=temp->next;
        }
    }
};



// customers 
template<typename Q>
class Customer_Information{
    private: 
    string fullName;
    int PhoneNo;
    string CarName;
    public:
    Customer_Information():fullName(" "),PhoneNo(0),CarName(" "){}

Customer_Information(string fullName, int phoneNo, string CarName){
    this->fullName=fullName;
    this->PhoneNo=phoneNo;
    this-> CarName=CarName;
}
void set_fullName(string fullName)
{
    this->fullName=fullName;
}
void set_PhoneNo(int phoneNo)
{
    this-> PhoneNo=phoneNo;
}
void set_CarName(const Car_Rental<Q>& car)
{
    CarName=car.getName()+ " - ID: " + to_string(car.getID()); // hna 3mlt en lma na5od el name mn el customer ygeb el id bta3ha automatic 3lshan lma n3ml search by id ykon ashl 3lshan hyzhrlna el id gnb el 3rbya f n2dr n3ml remove mn el bst btare2a ashl
}
string get_fullName() const
{
    return fullName;
}
int get_phoneNo() const 
{
    return PhoneNo;
}
string get_carName() const
{
    return CarName;
}
};
// queue for customers
template <typename Q>
class QueueNode{
    public: 
    Customer_Information<Q> element;
    QueueNode<Q>*next;
    QueueNode(): next(NULL){}
    QueueNode(Customer_Information<Q> element)
    {
        this->element=element;
        next=nullptr;
    }
};
template<typename Q>
class CustomerQueue
{
    private: 
    QueueNode<Q>*Front;
    QueueNode<Q>*Rear;
    int counter;

public:
CustomerQueue(): Front(nullptr),Rear(nullptr), counter(0){}

void enqueue( const Customer_Information<Q>&customer)
{
    QueueNode<Q>* newNode=new QueueNode<Q>(customer);
    if(Front==nullptr)
    {
        Front=newNode;
        Rear=newNode;
    }
    else
    {
        Rear->next=newNode;
        Rear=newNode;
    }
    counter++;
}
Customer_Information<Q> dequeue()
{
    if(counter==0)
    {
        throw runtime_error("there is currently no recorded information about customers!");
    }
    else
    {
        QueueNode<Q>* delptr=Front;
        Front=Front->next;
        counter--;
        if(Front==nullptr)
        {
            Rear=nullptr;
        }
        Customer_Information<Q> C=delptr->element;
        delete delptr;
        return C;
    }
}
void display() const {
    if(Front == nullptr){
        cout << "No waiting customers.\n";
        return;
    }

    QueueNode<Q>* temp = Front;
    while(temp != nullptr){
        cout << "Name: " << temp->element.get_fullName() << endl;
        cout << "Phone: " << temp->element.get_phoneNo() << endl;
        cout << "------------------\n";
        temp = temp->next;
    }
}
void writeToFile(ofstream &file)const{
    QueueNode<Q>* temp = Front;
    while(temp!=nullptr){
        file<<temp->element.get_phoneNo()<<'|'<<temp->element.get_fullName()<<'\n';
        temp=temp->next;
    }
}
bool Check_queue_isEmpty()
{
    return Front==nullptr;
}
void Clear_queue()
{
    while(!Check_queue_isEmpty())
    {
        dequeue();
    }
}
};




// files for cars
template <typename T>
class Files{
    public: 
    // save a single car
    void saveCar(const Car_Rental<T>& car){
        ofstream file("cars.txt",ios::app);
        if(!file){
            cout<<"Error opening file\n";
            return;
        }
        file<<car.getID()<<" "
        <<car.getPrice()<<" "
        <<car.getAvailable()<<" "
        <<car.getName()<<endl;
        file.close();
    }
    // save all cars 3lshan n3ml overwrite 3la el file 
    void saveAllCars(const LL<T>& list){
        ofstream file("cars.txt",ios::trunc);
        if(!file){
            cout<<"Error opening file\n";
            return;
        }
        list.writeToFile(file);
        file.close();
    }
    void loadCars(BST<T>& tree, LL<T>& list){
        ifstream file("cars.txt");
        if(!file){
            cout<<"File not found\n";
            return;
        }
        T id;
        double price;
        bool available;
        string name;
        while(file>>id>>price>>available){
            file.ignore();
            getline(file, name);
            Car_Rental<T> car(id,name,price,available);
            tree.insert(car);
            list.addCar(car);
        }
        file.close();
        cout<<"Cars loaded successfully\n";
    }
    // customers

    // save a single customer ( for new customers)
    void SaveCustomers(const Customer_Information<T>& customer){
        ofstream file("customers.txt",ios::app);
        if(!file){
            cout<<"Error opening file\n";
            return;
        }
        file << customer.get_fullName() << " "
            << customer.get_phoneNo() << endl;
        file.close();
        cout<<"Customer saved successfully";
    }
    // save all customers 3lshan el overwrite 
    void saveALLCustomers(const CustomerQueue<T>& queue){
        ofstream file("customers.txt",ios::trunc);
        if(!file){
            cout<<"Error opening file!\n";
            return;
        }
        queue.writeToFile(file);
        file.close();
    }
    CustomerQueue<T> loadCustomers(){
        CustomerQueue<T> queue;
        ifstream file("customers.txt");
        if(!file){
            cout<<"File not found\n";
            return queue;
        }
        string name;
        int  phoneNumber;
        while(file>>phoneNumber){
            file.ignore();
            getline(file,name);
            Customer_Information<T> customer(name, phoneNumber, "");
            queue.enqueue(customer);
        }
        file.close();
        return queue;
    }
};




// rental logic 

template<typename T>
void rentCar(
    BST<T>& tree,
    stack<Car_Rental<T>>& rentedStack,
    CustomerQueue<T>& customers,
    LL<T>& carList
)
{
    Files<T> files;
    if(customers.Check_queue_isEmpty()){
        cout<<"No customers Waiting!\n";
        return;
    }
    T id;
    cout<<"Enter Car ID to rent:";
    cin>>id;
    
    BSTNode<T>* carNode = tree.SearchById(id);

    if(carNode==nullptr){
        cout<<"car not found!\n";
        return;
    }
    if(!carNode->data.getAvailable()){
        cout<<"Car is already rented!\n";
        return;
    }

    // rent the car
    carNode->data.setAvailable(false);
    Car_Rental<T>* carInList = carList.findByID(id);
if(carInList != nullptr){
    carInList->setAvailable(false);
}
    rentedStack.push(carNode->data);
    customers.dequeue();
    files.saveALLCustomers(customers);
    files.saveAllCars(carList);
    cout<<"Car rented successfully!\n";
}


// return a car 

template <typename T>
void returnCar(BST<T>& tree,
    LL<T>& carList, 
    stack<Car_Rental<T>>& rentedStack )
    {
        Files<T> files;
    if(rentedStack.isempty()){
        cout<<"No rented Cars!\n";
        return;
    }
    T id;
    cout<<"Enter the ID of the car to return:";
    cin>>id;
    //helping function to search
    stack<Car_Rental<T>> tempStack;
    bool found = false;
    Car_Rental<T> car;
    while(!rentedStack.isempty()){
        Car_Rental<T> topCar=rentedStack.pop();
        if(topCar.getID()==id){
            car=topCar;
            found= true;
            break; // stop when u found it
        }
        else{
            tempStack.push(topCar);
        }
    }
    if(!found){
        cout<<"Car with ID "<<id<<" not found in rented cars.\n";

        // restore the stack
        while(!tempStack.isempty()){
            rentedStack.push(tempStack.pop());
        
        }
        return;
    }
// restore remaining rented cars
while(!tempStack.isempty()){
    rentedStack.push(tempStack.pop());
}
    BSTNode<T>* carNode = tree.SearchById(id);
    if(carNode != nullptr){
        carNode->data.setAvailable(true);
    }
    Car_Rental<T>* carInList = carList.findByID(id);
    if(carInList != nullptr){
    carInList->setAvailable(true);
    }
    files.saveAllCars(carList);
    cout<<"Car returned successfully!\n";
}



// menu 

void showMenu(){
    cout<<"---------------------------------------------\n";
    cout<<"            CAR RENTAL SYSTEM\n";
    cout<<"---------------------------------------------\n";
    cout<<"1. show all cars\n";
    cout<<"2.search car by ID\n";
    cout<<"3.show cars sorted by ID\n";
    cout<<"4.show cars sorted by price\n";
    cout<<"5.show cars sorted by name\n";
    cout<<"6. add new car\n";
    cout<<"7. add new customer\n";
    cout<<"8. Rent a car\n";
    cout<<"9. Return a car\n";
    cout<<"10. Show recently rented cars\n";
    cout<<"11. Show waiting customers\n";
    cout<<"12. Exit\n";
    cout<<"---------------------------------------------\n";
}
int main(){
    BST<int> tree;
    LL<int> carList;
    stack<Car_Rental<int>> rentedStack;
    CustomerQueue<int> customers;
    Files<int> files;
    files.loadCars(tree,carList);
    customers = files.loadCustomers();
    int choice;

    do {
        showMenu();
        cout<<"Enter choice: ";
        cin>>choice;

        switch(choice){
            case 1: // show all cars
                carList.display();
                break;
            case 2:{ // search car by ID
                int id;
                cout<<"enter ID: ";
                cin>>id;
                BSTNode<int>* car = tree.SearchById(id);
                if(car) car->data.display();
                else 
                cout<<"car not found\n";
                break;
            }
            case 3: // show cars sorted by ID
            tree.displaySorted();
            break;
            case 4 : // show sorted by price
            carList.sortByPrice();
            carList.display();
            break;
            case 5:// show sorted by name
            carList.sortByName();
            carList.display();
            break;
            case 6 :  { // add new
                int id;
                string name;
                double price;
                cout<<" Enter ID: ";
                cin>>id;
                cout<<"Enter price: ";
                cin>>price;
                cin.ignore();
                cout<<"Enter car name: ";
                getline(cin,name);
                Car_Rental<int> car(id,name,price,true);
                carList.addCar(car);
                tree.insert(car);
                files.saveAllCars(carList);
                break;
            }
            case 7:{ // add new customer
                string name;
                int phone;
                cout<<"Enter Phone number : ";
                cin>>phone;
                cin.ignore();
                cout<<"Enter full name: ";
                getline(cin,name);

                Customer_Information<int> customer(name,phone," ");
                customers.enqueue(customer);
                files.SaveCustomers(customer);
            break;
            }

            case 8: // rent a car
                rentCar(tree,rentedStack,customers,carList);
                files.saveAllCars(carList);
                break;

            case 9: // return a car
                returnCar(tree,carList, rentedStack);
                files.saveAllCars(carList);
                break;

            case 10: // show recently rented cars
                rentedStack.display();
                break;

            case 11: // show waiting customers
            customers.display();
            break;
            case 12: // exit
                cout<<"Exiting...\n";
            break;

            default:
                cout<<"Invalid choice!\n";
            }
    }
    while(choice!=12);
    return 0;
}