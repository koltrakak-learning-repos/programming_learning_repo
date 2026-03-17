#include <iostream>
#include <string>
#include <utility>
#include <vector>

// CRTP: una classe base (Animal) è parametrizzata dal tipo della sua sottoclasse.
// La classe base sa già, a compile-time, il tipo concreto che la eredita, e può
// quindi chiamare metodi della sottoclasse senza virtual dispatch, con zero overhead
// a runtime.
template <typename Derived>
struct Animal
{
    // La base chiama il metodo della sottoclasse
    void speak()
    {
        // Dispatch a compile time tramite static_cast
        static_cast<Derived *>(this)->do_speak();
    }
};

struct Dog : Animal<Dog>
{
    void do_speak() { std::cout << "Woof!\n"; }
};

struct Cat : Animal<Cat>
{
    void do_speak() { std::cout << "Meow!\n"; }
};

// Polimorfismo a compile-time, in base a chi chiama questa
// funzione (Dog, Cat, ...), lo static_cast dentro alla
// classe CRTP Animal, sarà diverso
template <typename T>
void make_noise(Animal<T> &a)
{
    // questa è la funzione speak() della specifica istanza
    // di questa funzione generata per il tipo T.
    // Se T == Dog -> stiamo chiamando Animal<Dog>::speak
    // Non c'è indirezione tramite vtable, il compilatore
    // sa qual'è funzione da chiamare e quindi può fare
    // inlining
    a.speak();
}

/*
    I CRTP sono particolarmente utili con i Mixin: classi pensate per essere ereditate in modo da
    aggiungere funzionalità ortogonali (clonare, serializzare, ...) utili alle classi ereditanti.
    Mixin e CRTP sono una buona combo dato che spesso un mixin deve fare riferimento al tipo concreto
    che lo eredita per implementare la sua funzionalità (ad esempio, nel caso della clonazione,che
    tipo clono?). Senza CRTP l'unica alternativa è utilizzare delle classi astratte virtuali e
    implementare in ogni classe derivata il metodo virtuale, ma questo aggiunge il costo di dispatch
    e mi porta a duplicare in molti posti la stessa logica (cio che voglio evitare con il mixin).
    Applicando CRTP, la classe base conosce già il tipo concreto (è il parametro del template) e
    quindi può catturare in unico posto la logica del tratto.
*/

// Base CRTP Mixin
template <typename Derived>
struct Serializable
{
    const Derived &self() const
    {
        return *static_cast<const Derived *>(this);
    }

    // tutte le classi derivate hanno la stessa logica
    // di serializzazione, l'unica cosa che cambia sono
    // i campi degli oggetti
    std::string to_json() const
    {
        std::string out = "{";
        for (auto &[k, v] : self().fields()) // le sottoclassi definiscono fields()
            out += "\"" + k + "\":" + v + ",";
        if (out.back() == ',')
            out.pop_back();
        return out + "}";
    }
};

// La sottoclasse definisce SOLO fields()
struct User : Serializable<User>
{
    std::string name;
    int age;

    User(std::string name, int age)
        : name(std::move(name)), age(age) {}

    auto fields() const
    {
        return std::vector<std::pair<std::string, std::string>>{
            {"name", "\"" + name + "\""},
            {"age", std::to_string(age)}};
    }
};

struct Product : Serializable<Product>
{
    std::string name;
    double price;

    Product(std::string name, double price)
        : name(std::move(name)), price(price) {}

    auto fields() const
    {
        return std::vector<std::pair<std::string, std::string>>{
            {"name", "\"" + name + "\""},
            {"price", std::to_string(price)}};
    }
};

int main()
{
    Dog d;
    Cat c;
    make_noise(d); // stampa: Woof!
    make_noise(c); // stampa: Meow!

    User u{"Alice", 30};
    Product p{"SKU-42", 9.99};
    std::cout << u.to_json() << "\n";
    std::cout << p.to_json() << "\n";
}
