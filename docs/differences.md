# Similarities and differences with the C++ standard library naming

## Naming similarities with C++ standard library

### Functions with the same name as the C++ standard library

Functions that have the same name as their C++ standard library counterparts are usually functions that act almost the same way but have some added functionality. For example ```mtl::for_each``` has the same functionality as ```std::for_each``` with the added benefit that it can also be used on ```std::pair``` and ```std::tuple```.

```c++
#include <tuple>
#include "mtl/console.hpp"
#include "mtl/algorithm.hpp"

int main()
{
    std::tuple<int, char, const char*> tp = std::make_tuple(111, 'a', "Hello");
    mtl::for_each(tp, [](auto& v){ mtl::console::println(v); });
}
```

Another example is ```mtl::iota``` which is a better version of ```std::iota```. It accepts all numeric types and you can set an optional starting value as well as an optional step value. With ```mtl::iota``` for example you could easily fill a ```std::vector<float>``` with the following values ```[5.0, 0.5, -4.0, -8.5, -13.0]``` using a starting value of ```5.0f``` and a step value of ```-4.5f```.

```c++
#include <vector>
#include "mtl/numeric.hpp"

int main()
{
    std::vector<float> numbers(5);
    mtl::iota(numbers.begin(), numbers.end(), 5.0f, -4.5f);
}
```

### Namespaces with the same name as the C++ standard library

Namespaces that share the same name as C++ standard library have the same functionality. Two examples of this are the ```std::chrono``` and ```std::filesystem``` namespaces that are used for functionality that has to do with time and the filesystem respectively. The **mtl** has ```mtl::chrono``` and ```mtl::filesystem``` for the exact same reason. We try to keep the names of namespaces as familiar as possible to ease the learning curve for new users.

### Functions ending with ```_n```

Functions that end with ```_n``` are equivalent versions of functions without it but instead require a count of items to operate on.
Like C++ has ```std::copy``` and ```std::copy_n``` in the **mtl** header *safety.hpp* we have ```mtl::safe_copy``` and the ```mtl::safe_copy_n```.

## Naming differences with C++ standard library

That said there are some differences in naming in **mtl** compared to the C++ standard library. Those differences arise because **mtl** has some different concepts.

### Functions starting with ```safe_```

These are functions that are safer alternatives of C++ standard library or **mtl** functions. They try to eliminate or reduce the number of bugs and errors that can happen during development.
An example of these functions are ```mtl::safe_copy``` and ```mtl::safe_copy_n``` that are much safer versions of ```std::copy``` and ```std::copy_n```.

### Functions ending with ```_all```

These are functions that take iterators to a range instead of individual variables and iterate over the range to perform an operation.
An example of a function like that is ```mtl::string::join``` that takes a variable number of heterogeneous variables
and joins them to a ```std::string```. Then the analogous ```mtl::string::join_all``` uses iterators to iterate over
a range of similar elements and joins them all to a ```std::string```.

### Functions ending with ```_noex```

These are functions that perform the same action as their exception throwing counterparts but do not throw exceptions and are marked as ```no_except```. For example there is ```mtl::to_num``` that converts an ```std::string``` to the selected type of number and in case of an error throws an exception. The analogous function ```mtl::to_num_noex``` does the same but doesn't throw in case of an error. It has two overloads. One overload has the same number of parameters as ```mtl::to_num``` but that instead returns an ```std::pair<Type, bool>``` that contains the result and the `bool` that informs about success or failure. The second overload returns the same type as ```mtl::to_num``` but has one extra parameter, a `bool` used as an output to inform about success or failure.

### Functions ending with ```_sorted```

Functions that end with ```_sorted``` expect the container to be sorted to work properly. If the elements are not sorted then behavior is undefined, but that usually means they tend to just produce incorrect results. An example of this is ```mtl::rem_duplicates``` that doesn't require the elements to be sorted, and sorts them before removing duplicates. But in case you know you have sorted elements then you can use ```mtl::rem_duplicates_sorted``` to have significant gains in performance.

### Functions ending with ```_preserve```

Functions that end with ```_preserve``` preserve the ordering of elements for the container. An example of this is ```mtl::rem_duplicates``` that removes duplicate items but doesn't preserve ordering and ```mtl::rem_duplicates_preserve``` that preserves the exact ordering of the elements that remain.
