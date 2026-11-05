#ifndef _LISTA_H_
#define _LISTA_H_

#include <iostream>
using namespace std;

template <typename T>
class Lista {
    public:
    Lista();
    ~Lista();

    int longitud();

    void agregarAtras(const T elemento);

    // Pre: 0 <= posicion < longitud()
    T iesimo(const int posicion);

    void borrarIesimo(int posicon);

    void borrarUltimo();

    T cursor();

    void avanzar();

    void retroceder();

    private:
        struct nodo {
            nodo(T un_elemento) : elemento(un_elemento), siguiente(nullptr), anterior(nullptr) {}
            T elemento;
            nodo* siguiente;
            nodo* anterior;
        };

        nodo* _primero;
        int _longitud;
        nodo* _cursor;
};

template <typename T>
Lista<T>::Lista() : _primero(nullptr), _longitud(0), _cursor(nullptr) {}

template <typename T>
int Lista<T>::longitud() {
    return _longitud;
}

template <typename T>
void Lista<T>::agregarAtras(const T elemento) {
    nodo * nuevo = new nodo(elemento);
    if(!_cursor){
        _cursor = nuevo;
    }

    if (_primero == nullptr) {
          _primero = nuevo;
    } else {
        // avanzo hasta que actual sea el último nodo
        nodo* actual = _primero;
        while (actual->siguiente != nullptr) {
            actual = actual->siguiente;
        }

        actual->siguiente = nuevo;
        nuevo->anterior = actual;
    }
    _longitud++;
}

template <typename T>
T Lista<T>::iesimo(const int posicion) {
    // avanzo hasta que actual sea el iésimo nodo
    nodo* actual = _primero;
    int i = 0;
    while (i < posicion){
        actual = actual->siguiente;
        i++;
    }

    return actual->elemento;
}

template <typename T>
Lista<T>::~Lista() {
    nodo * actual = _primero;
    while (actual != nullptr) {
        nodo* sig = actual->siguiente;
        delete actual;
        actual = sig;
    }
    _primero = nullptr;
    _longitud = 0;
    _cursor = nullptr;
}

template <typename T>
void Lista<T>::borrarIesimo(int posicion) {
    nodo *actual = _primero;
    int i = 0;
    while(i < posicion){
        actual = actual->siguiente;
        i++;
    }
    if(_cursor == actual){
        if(actual->siguiente != 0){
            avanzar();
        }
        else {
            retroceder();
        }
    }
    if(!actual->anterior){
        _primero = actual->siguiente;
    } else {
        actual->anterior->siguiente = actual->siguiente;
    }
    if (actual->siguiente){
        actual->siguiente->anterior = actual->anterior;
    }
    delete actual;
    _longitud -= 1;
}

template <typename T>
void Lista<T>::borrarUltimo() {
    borrarIesimo(_longitud-1);
}

template <typename T>
T Lista<T>::cursor() {
    return _cursor->elemento;
}

template <typename T>
void Lista<T>::avanzar() {
    if(_cursor->siguiente != 0){
    _cursor = _cursor->siguiente;
    }
}

template <typename T>
void Lista<T>::retroceder() {
    if(_cursor->anterior != 0){
    _cursor = _cursor->anterior;
    }
}

#endif