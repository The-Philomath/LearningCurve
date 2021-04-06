**Interface Segregation Principle** Clients should not be forced to depend upon interfaces that they do not use. Instead of one fat interface many small interfaces are preferred based on groups of methods, each one serving one submodule.

```cpp
// Bad Design
struct Document;
struct IMachine {
    virtual void print(Document &doc) = 0;
    virtual void fax(Document &doc) = 0;
    virtual void scan(Document &doc) = 0;
};
struct MultiFunctionPrinter : IMachine {      // OK
    void print(Document &doc) override { }
    void fax(Document &doc) override { }
    void scan(Document &doc) override { }
};
struct Scanner : IMachine {                   // Not OK
    void print(Document &doc) override { /* Blank */ }
    void fax(Document &doc) override { /* Blank */ }
    void scan(Document &doc) override {  
        // Do scanning ...
    }
};
```

```cpp
// Good Design
/* -------------------------------- Interfaces ----------------------------- */
struct IPrinter {
    virtual void print(Document &doc) = 0;
};
struct IScanner {
    virtual void scan(Document &doc) = 0;
};
/* ------------------------------------------------------------------------ */
struct Printer : IPrinter {
    void print(Document &doc) override;
};
struct Scanner : IScanner {
    void scan(Document &doc) override;
};
struct IMachine : IPrinter, IScanner { };
struct Machine : IMachine {
    IPrinter&   m_printer;
    IScanner&   m_scanner;
    Machine(IPrinter &p, IScanner &s) : printer{p}, scanner{s} { }
    void print(Document &doc) override { printer.print(doc); }
    void scan(Document &doc) override { scanner.scan(doc); }
};
```
