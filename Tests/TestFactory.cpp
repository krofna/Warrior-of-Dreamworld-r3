#include <iostream>
#include <string>
#include <map>
#include "Factory.hpp"

class Object
{
    int m_GUID;
    public:
    Object() = default;
    struct Factory
    {
        std::map<int, Object* > Database;
        virtual Object* Create(short Entry)
        {
            Database[Entry+1] = new Object(Entry+1);
            return Database[Entry+1];
        }
        virtual Object* Load(int GUID)
        {
            std::map<int, Object* >::iterator it = Database.find(GUID);
            return (it != Database.end()) ? (*it).second : nullptr;
        }
    };
    Object(int GUID) : m_GUID(GUID) { }

    int GetGUID() const { return m_GUID; }

};
class AI
{
    void* p_Me;
    public:
    AI() = default;
    struct Factory
    {
        virtual AI* Create(void* ObjectLinked)
        {
            return new AI(ObjectLinked);
        }
        virtual AI* Load(void* ObjectLinked)
        {
            return new AI(ObjectLinked);
        }
    };

    AI(void* Me) : p_Me(Me) { }

    void* GetMe() const { return p_Me; }
};

int main(int argc, char** argv)
{
    Factory EntityFactory;
    EntityFactory.Register<Object>("Object");
    EntityFactory.Register<AI>("AI");

    int* ptr = new int[5];

    {
        Object* ptr_Object;
        AI* ptr_AI;

        EntityFactory.Create(ptr_Object, "Object", 230);
        EntityFactory.Create(ptr_AI, "AI", ptr);

        std::cout << ptr_Object->GetGUID() << std::endl;
        std::cout << ptr_AI->GetMe() << std::endl;
   }

    {
        Object* ptr_Object;
        AI* ptr_AI;

        EntityFactory.Load(ptr_Object, "Object", 231);
        EntityFactory.Load(ptr_AI, "AI", ptr);

        if (!ptr_Object || !ptr_AI)
            std::cout << "Ptr(s) is/are invalid." << std::endl;

        std::cout << ptr_Object->GetGUID() << std::endl;
        std::cout << ptr_AI->GetMe() << std::endl;

        delete ptr_Object;
        delete ptr_AI;
    }

    delete[] ptr;

    return 0;
}
