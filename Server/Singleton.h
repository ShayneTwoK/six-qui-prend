#pragma once
/**
 * The Singleton's constructor/destructor should always be private to
 * prevent direct construction/desctruction calls with the `new`/`delete`
 * operator.
 */
template <class T>
class Singleton
{
public:
    static T* get_instance()
    {
        if (!instance_)
        {
            instance_ = new T;
        }

        return instance_;
    }

    static
        void destroy_instance()
    {
        delete instance_;
        instance_ = nullptr;
    }

private:
    static T* instance_;
};


