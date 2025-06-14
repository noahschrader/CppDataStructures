class Constructable
{
public:
    Constructable() : value(0)
    {
        ++constructorCalls;
    }

    Constructable(int v) : value(v)
    {
        ++constructorCalls;
    }

    Constructable(const Constructable& other)
    {
        value = other.value;
        ++constructorCalls;
    }

    ~Constructable()
    {
        ++destructorCalls;
    }

    static void Reset()
    {
        constructorCalls = 0;
        destructorCalls = 0;
    }

    static int GetConstructorCalls()
    {
        return constructorCalls;
    }

    static int GetDestructorCalls()
    {
        return destructorCalls;
    }

    int GetValue()
    {
        return value;
    }

private:
    static inline int constructorCalls = 0;
    static inline int destructorCalls = 0;
    int value;
};