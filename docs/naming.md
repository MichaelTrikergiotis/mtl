# Naming conventions

We are strict with naming and styling of the code.

The line length used in **mtl** is **100**, please adhere to it and never surpass it. The reason is that 80 is it is too restrictive for modern C++ when you want to call a function that exists inside multiple namespaces. Even decades old projects have already abandoned the 80 characters line length like the Linux kernel.

**mtl** uses allman style for brackets.

```c++
// GOOD EXAMPLE :
void print(const int x)
{

}

// BAD EXAMPLE :
void print(const int x){

}
```

You should use snake_case for naming everything except template types because we use the same naming scheme as C++ standard library. Although there are some differences that you can learn about [here](./differences.md).

```c++
// GOOD EXAMPLE :
monster generate_monster(const monster_head& head, const monster_body& body)
{

}

// BAD EXAMPLE :
monster GenerateMonster(const MonsterHead& head, const MonsterBody& body)
{

}
```

All templates types use CamelCase, which means they should have the first letter uppercase and use uppercase between words.

```c++
// GOOD EXAMPLE :
template<typename HeadType, typename BodyType>
monster generate_monster(const HeadType& head, const BodyType& body)
{

}

// BAD EXAMPLE :
template<typename head_type, typename body_type>
monster generate_monster(const head_type& head, const body_type& body)
{

}
```

Do not use ```#define``` use constant variables instead. Constant variables shouldn't be capitalized and should retain the snake_case style.

```c++
// GOOD EXAMPLE :
const float milk_kg = 10.0f;
const int gold_coins = 1000;

// BAD EXAMPLE :
#define FOOD 10.0f
#define GOLDCOINS = 1000;
```

Always initialize variables and each variable declaration should be in it's own line. You should never declare two or more variables in the same line. If the variable doesn't change always declare it as const.

```c++
// GOOD EXAMPLE :
const int food = 10;
const int coins = 1000;

// BAD EXAMPLE :
int food, coins;
```

The template declaration is always in its own line.

```c++
// GOOD EXAMPLE :
template<typename HeadType, typename BodyType>
monster generate_monster(const HeadType& head, const BodyType& body)
{

}

// BAD EXAMPLE :
template<typename HeadType, typename BodyType> monster generate_monster(const HeadType& head, const BodyType& body)
{

}
```

The if and else brackets should appear in separate lines for their declaration.

```c++
// GOOD EXAMPLE :
if(x == 10)
{
    y = 11;
}
else
{
    y = 1000;
}

// BAD EXAMPLE :
if(x == 10) { y = 11; }
else { y = 1000; }
```

All control statements should always include starting and ending brackets { }.

```c++
// GOOD EXAMPLE :
if(x == 10)
{
    y = 11;
}
else
{
    y = 1000;
}

for(int i = 0; i < 10; i++)
{
    x++;
}

// BAD EXAMPLE :
if(x == 10) y = 11;
else y == 1000;
for(int i = 0; i < 10; i++) x++;
```

Never use the ternary operator use if and else instead.

```c++
// GOOD EXAMPLE :
if(x == 10)
{
    y = 11;
}
else
{
    y = 1000;
}

// BAD EXAMPLE :
y = (x == 10) ? 11 : 1000;
```

Never use switch instead use if / elseif / else.

```c++
// GOOD EXAMPLE :
if(x == 10)
{
    y = 11;
}
else if(x == 11)
{
    y = 33;
}
else
{
    y = 1000;
}

// BAD EXAMPLE :
switch(x)
{
    case 10:
    {
        y = 11;
        break;
    }
    case 11:
    {
        y = 33;
        break;
    }
    default:
    {
        y = 1000;
        break;
    }
}
```

## Comments

Do not use

```c++
/* */
```

for commenting only use

```c++
//
```

In Visual Studio you can select all the lines you want and press ```Ctrl + K, C``` to comment everything selected with ```//```.

In Visual Studio Code you can select all the lines you want and press ```Ctrl + /``` to comment everything selected with ```//```.

Comment everything out of the ordinary so future maintainers know what you are doing. Every little trick for performance or compatibility hack should have detailed comments for why it was used over a simpler solution.

When including something from a header add as a comment next to the header with what exactly you used.

```C++
// GOOD EXAMPLE :
#include <algorithm> // std::sort, std::copy

// BAD EXAMPLE :
#include <algorithm>
```

Comments inside the scope of a function start with non capital letter and don't end with a period punctuation mark. All comments should have a single space after the double slashes. May have an informal tone.

```c++
// this is a comment inside the scope of a function
const int eggs = 10;
```

Comments everywhere outside the scope of functions start triple slash and a space. This includes classes and enums. Proper full sentences with a formal tone ending with a period punctuation mark.

```c++
/// This is a comment everywhere else except inside the scope of a function.
const int eggs = 10;
```

Comments of functions should also include @param[in] or @param[out] for all parameters passed as well @return for all functions that return something.

```c++
/// Given a number of chickens and a number of days calculates how many eggs will be produced.
/// @param[in] chickens The number of chickens.
/// @param[in] days The number of days.
/// @return The number of eggs produced.
int egg_production(const int chickens, const int days)
{

}
```

### A note about mtl-format

You can check for some of the formatting errors in your code with the use of the mtl-format script in the utilities folder.

### A note about clang-format

Sadly clang-format can't be used on this project because no amount of configuration can make clang-format to adhere to the exact formatting we require.
