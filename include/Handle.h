/*
 *    Copyright (c) 2017 by Maciej Wiecierzewski
 */

#ifndef HANDLE_H
#define HANDLE_H

namespace gui
{

//! Template class for widget handles.

template<class T> class Handle
{
    public:
        Handle() : pointer(NULL) {};

        T* operator->() { return pointer; }
        T& operator*() { return *pointer; }

    protected:

    private:
        Handle(T *pointer) : pointer(pointer) {};

        T *pointer;

    friend class GUISystem;
};

}

#endif // HANDLE_H
