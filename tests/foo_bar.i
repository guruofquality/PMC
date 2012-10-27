%module foo_bar

%{

struct FooBar
{
    int _foo;
    float _bar;

    int foo(void) const
    {
        return _foo;
    }

    float bar(void) const
    {
        return _bar;
    }
};

bool operator==(const FooBar &lhs, const FooBar &rhs)
{
    return (lhs.foo() == rhs.foo()) && (lhs.bar() == rhs.bar());
}

%}

struct FooBar
{
    int _foo;
    float _bar;

    int foo(void);

    float bar(void);
};

%include <PMC.i>

DECL_PMC_SWIG_TYPE(FooBar, swig_foo_bar)
