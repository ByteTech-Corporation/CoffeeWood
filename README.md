# CoffeeWood
CoffeeWood is a programming language coded in Java & C++ and C. This programming language is made for ***adults*** and ***kids***. It works with Android and MacOS and Windows and last but not least Unix/Linux.

CoffeeWood is a simple compiled language. It is compiled when you run the compiler along with your .cw script. Example Compiler syntax (command-line):

```
cw compiler [script.cw]
cw compiler [script.cw] -quiet
                        ^^^^^^
                        Say no messages from the compiler except for errors and warnings

cw compiler [script.cw] -Verbose.print
                        ^^^^^^^^^^^^^^
                        Say messages in verbose mode

cw compiler [script.cw] -debugplugin:[debug_plugin_url],[plugin_id]
                        ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
                        Debugging plugin URL and ID, read debugplugins.md for more info
```

# What about syntax?

Here is some example syntax:

```

class some_function_name 
      ^^^^^^^^^^^^^^^^^^
      Your function name (No numbers in function name allowed! Exception is using 'cw.AllowNumbersInFunctionName(true)' at the beginning of your script.)

```

```
import [cw.]
class some_function_name() {

      @Function
      static class some_sub_function_name() {

            @StaticFunction
            
      }
}
```
import [cw.]
class some_function_name() {

      @Function
      static class some_sub_function_name() {

            @StaticFunction
            
      }

      math(add(num_1="4", num_2="4")
      math(divide(num_1="3", num_2="9"))
      math(multiply(num_1="8", num_2="4"))
      math(subtract(num_1="45", num_2="12"))

      if [Null, Nullptr]: {
             break(errorlist(toconsole))
      } else {
             continue()
      }
}
```

```
