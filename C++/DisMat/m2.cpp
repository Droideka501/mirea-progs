#include <iomanip>
#include <iostream>
#include <fstream>
#include <typeinfo>


// Abstract class. 
class Information {};



// class InformationProgrammer. Contain all inforamtion about object `Object<InformatrionProgrammer>`.
class InformationProgrammer : public Information
{
public:
    // default constructor.
    InformationProgrammer (const int         &level =              0,
                           const std::string &lang =       "unknown",
                           const std::string &name =       "unknown",
                           const std::string &surname =    "unknown",
                           const std::string &email =      "unknown",
                           const std::string &telegramID = "unknown",
                           const std::string &skypeID =    "unknown",
                           const std::string &job =        "unknown")

    {
        level_      = level;
        lang_       = lang;
        name_       = name;
        surname_    = surname;
        email_      = email;
        telegramID_ = telegramID;
        skypeID_    = skypeID;
        job_        = job;
    }



    // destructor
    ~InformationProgrammer() { std::cout << "Object \"InformationPragrammer\" was deleted" << '\n'; }



    // copy constructor.
    InformationProgrammer (const InformationProgrammer &programmer)
    {
        level_ = programmer.level_;
        lang_ = programmer.lang_;
        name_ = programmer.name_;
        surname_ = programmer.surname_;
        email_ = programmer.email_;
        telegramID_ = programmer.telegramID_;
        skypeID_ = programmer.skypeID_;
        job_ = programmer.job_;
    }



    friend std::ostream& operator<< (std::ostream &output, const InformationProgrammer &programmer);

    void SetLevel(int level) { level_ = level; }

protected:
    int            level_;
    std::string    lang_;
    std::string    name_;
    std::string    surname_;
    std::string    email_;
    std::string    telegramID_;
    std::string    skypeID_;
    std::string    job_;
};
std::ostream& operator<< (std::ostream &output, const InformationProgrammer &programmer)
{
    output << '\n' << "---------------------START--------------------" << '\n';

    output << "   name: " << programmer.name_ << '\n'
           << "surname: " << programmer.surname_ << '\n'
                   <<"------------------Information:----------------" << '\n';

    output << "     level: " << programmer.level_ << '\n'
           << "      lang: " << programmer.lang_ << '\n'
           << "     email: " << programmer.email_ << '\n'
           << "telegramID: " << programmer.telegramID_ << '\n'
           << "   skypeID: " << programmer.skypeID_ << '\n'
           << "       job: " << programmer.job_ << '\n' 
                   << "----------------------END---------------------" << '\n';


    return output;
}



// template of `class Object`.
template<class Type> class Object
{
public:
    // default constructor
    Object<Type>(const Type &information)
    {
        predecessor_ = sucessor_ = nullptr;
        information_ = information;
    }



    // full constructor
    Object<Type>(const Type& information, Object<Type> *predecessor = nullptr, Object<Type> *sucessor = nullptr)
    // Object<Type>(const Object<Type>* prev, cosnt Object<Type> *next, const Information<Type> &info)
        // ïî÷åìó íå ðàáîòàåò ñ êîíñòàíòíûìè óêàçàòåëÿìè?
    {
        predecessor_ = predecessor;
        sucessor_ = sucessor;
        information_ = information;
    }



    // copy constructor
    Object<Type>(const Object<Type> &object)
    {
        predecessor_ = object.predecessor_;
        sucessor_ = object.sucessor_;
        information_ = object.information_;
    }



    // get & set 
    Object* GetPredecessor() { return predecessor_; } const 
    void SetPredecessor(Object* predecessor) { predecessor_ = predecessor; }

    Object* GetSucessor() { return sucessor_; } const
    void SetSucessor(Object* sucessor) { sucessor_ = sucessor; }



    friend std::ostream& operator<< (std::ostream &output, const Object<Type> &object);



protected:
    Object  *sucessor_;
    Object  *predecessor_; 
    Type   information_;
};
template<class Type> std::ostream& operator<< (std::ostream &output, const Object<Type> &object)
{
    if (typeid(output).name() == typeid(std::ostream).name())
    {

    }
    else
    {
        output << '\n' << typeid(object).name() << '\n';

        output << "Previous value is: " << *(object.predecessor_) 
            << '\n' << "Next value is: " << *(object.sucessor_) << object.information_;
    }


    return output;
}


// Linked list.
template<class Type> class List
{
    // defaul constructor.
    List<Type>()
    {
        head_ = tail_ = nullptr;
        amount_ = 0;
    }



    // copy constructor.
    //List<Type> (const List<Type> &list)
    //{
    //    if (list.head_ == nullptr) // <=> if (list.amount_ == 0) 
    //    {
    //        head_ = tail_ = nullptr;
    //        amount_ = 0;
    //    }
    //    else
    //    {
    //        for (Object<Type>* ptr = list.head_; ptr != nullptr; ptr = ptr->sucessor)
    //        {
    //            Object<Type> object = new Object<Type>(ptr->information_);

    //            if (head_ == nullptr) 
    //            {
    //                head->predes
    //                head_ = object;
    //            }


    //        }
    //    }
    //    
    //}



    //~List<Type>()
    //{
    //    if (list.head_ != nullptr) // <=> if (list.amount_ != 0) 
    //    {
    //        for (Object<Type>* ptr1 = ptr2 = head_, ; ptr1 != tail; ptr1 = ptr2;) // ptr1 = ptr1->ptr2
    //        { 
    //            ptr2 = ptr1->sucessor;
    //            delete ptr1;
    //        }
    //    }
    //}
protected:
    Object<Type> *head_;
    Object<Type> *tail_;
    int amount_;
};




int main()
{
    // Çàäàíèå 6.0: Ïðîâåðêà îáùåé ðàáîòîñïîñîáíîñòè ñèñòåìû.
    //////////////////////////////////////////////////////////////////////////////
    InformationProgrammer Rustem(1, "c++", "Rustem", "Sirazetdinov",
        "avesirazetdinov@gmail.com", "I_getsuga");
    

    InformationProgrammer* ptr1 = &Rustem;
    InformationProgrammer* ptr2 = new InformationProgrammer(*ptr1);
    ptr2->SetLevel(8);

    std::cout << *ptr1 << *ptr2;
    //delete ptr2;
}