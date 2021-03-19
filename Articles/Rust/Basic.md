* Memory management at compile time. There is no need of garbage collector.
* There is no concept of _Null_ in Rust.
* Rust provide zero cost abstraction.
* Rust provide safety, its cross platform friendly, its fast.
* Most of the times code will always be correct before code review phase. Compiler will complain if it will not correct.
* cargo tool take care of compilation of rust.
* To compile only execute `cargo build`
* to run the binary execute `cargo run`
* hello world of rust looks like : add the following code in `main.rs` files
    ```
    fn main(){
        println!("Hello, World!");
    }
    ```
* `#[allow(unused_variables)]` // don't treat unused variables as errors
* `#[allow(unused_assignments)]` // don't treat unused assignments as errors
* `#[allow(non_snake_case)]`// As a convention rust expect variable names as snake case
* `let some_data: bool = true;` Or `let some_data = true` //declare a variable
* `println!("Min i8 is {}", std::i8::MIN);` //print min value of i8
* primitive types in rust are `bool`, `i8, i16, i32, i64,i128`, `u8, u16, u32, u64,u128`, `char`, `isize, usize`, `f32, f64`
* `isize and usize` are underlying computer architecture dependent types
* `f64`default for float types. `i32` is default for integral types
* `char` can store more than Ascii, it can store chinese characters, emojis etc.
* By default variables are immutable in rust. Use `mut` keyword to make them mutable.
* Memory tradeoff for strings makes them complex in rust. But that provide flexibility and make system fast.
* 2 types of string in Rust i) string slice ii) string

* **Ownership and Borrowing**
* Stack memory creation and retrieval is fast. Default is stack for rust variables. stack variables are fixed in size.
* strings are collections of `u8's` . Strings can grow so they can't be on stack.
* Heap can grow in size, Runtime performance cost, strings resides in heap. Heap memory got automatically cleaned up when last owner goes out of scope.
* `let heap_vector: Vec<i8> = Vec::new(); //vec![5,2]`
* `let heap_string: String = String::from("Hello");`
* `let heap_i8: Box<i8> = Box::new(30);``
  `let heap_i8_2 = heap_i8` // Transfer of ownership of memory allocated to heap_i8 to heap_i8_2
  `println!("{}", heap_i8)` //error There can only be one owner of the memory at a time.
* `stack_i8_2 = stack_i8` //stacks are cheap so a new copy will be created and there will be no error when we will print stack_i8
* `let heap_i8_2 = &heap_i8;` //Borrowing
* `let heap_i8_2 = heap_i8.clone();` // clone creates a copy of the memory. Cloning is expensive prefer not to do it.
* As two variables can't point to same memory so there will be no parallel and concurrency issue in rust.
* Strings are always on the heap while string slice can either be on heap or on stack. String slice don't own the memory it borrows.
* **Rust Lifetimes** enforce a piece of memory is still valid for a reference. In rust there can be only 1 owner of the memory but anyone can borrow that with a reference. The one who borrowed the memory must know that the piece of memory it is working on is still valid. TO enforce that rust uses lifetimes.

```
let a;
{
  let b = String::from("Howdy!!");
  a = b; // transferred Ownership
  a = &b // borrowed. But there is a compile time error at this line as the scope of b will end next line so the borrowed memory will gone. so a will dangle. Rust don't allow this.
}
```

* In beow code `<'a>` is the lifetime which is attached to input and output parameter of function. So we are saying these two are in same scope and have same lifetime. Lifetimes are need to assigned to references only because they can only cause the dangling problems. Even if we don't write explicitly compile will provide lifetimes by itself. Multiple parameters can have different lifetimes.

```
fn get_inf_ref<'a, 'b: 'a>(param_1: &'a i32, param_2: &'b i8) ->&'a i32{  // 'b will live at least as long as 'a
param1 //return statement no semicolon
}
```
* To apply the lifetimes there should be reference input as well as outputs in a function.
* Any reference parameter that never returned as output, the rust compiler provided lifetime is fine.
* **Static** lifetime means the lifetime that lasts the entire program. **Constants** are static by nature. We can declare static variables. For static lifetimes notation is `'static`. We can pass a static variable to a function parameter accepting `<'a>`lifetime. But reverse is not true.
* For `structs`
```
struct temp<'a, 'b: 'a>{
  some_data: Vec<i32>,
  some_reference_data: &'a Vec<i32>,
  some_other_reference_data: &'b Vec<i32>,
}
```

Rust has made the memory tradeoff decisions vs other language

Other languages hides the underlying complexity to make the things like strings easier. But rust do not. Rust makes the developer to handle the complexity of strings. Benefits of doing that are runtime speed, concurrency etc. In Rust simple things are harder.
```
let example_str: &str = "Howdy"; //string slice
let example_string: string = String::from("Partner");
```

Both `String` and `&str` are a grouping of characters(U8's). Difference is how to use and how they stored in memory.

`Strings` are stored in heap and they are mutable.

`&str` is immutable. Often allocated on the stack, sometimes a heap reference, sometimes embedded in the code

We can translate between `String` and `str`

So we generally use `str` for speed and `string` for holding longer

Translating between two:
```
let string_from_str: String = example_str.to_string();
let ..:string = "abcd".to_string();
```

"abcd" is a string literal having properties of a string slice.
```
let string_from_hd = String::from("");
let string_from_str_var = String::from(example_str);

let str_from_string: &str = &example_string;
let combine_string_literals = ["",""].concat(); //return string adding 2 string slice
let combine_with format_macro = format!("{}{}","first","second"); //return strings

let string_plus_str = example_string + example_str; //string should be first and string slice should be second

let mut mut_string = string::new();
mut_string.push_str(example_str);
mut_string.push('m');

let combined = a+ &b &mut_string;
let str_from_substring: &str = &example_str[0..2]; //default is 0 if we not mention works doe both string and slice. not include 2
[2..=4]; include 4

let char_by_index = &example_str.chars().nth(1);

//match deamon
match char_by_index{
   some(c) => println!("found{}",c),
   None => {}
}
if let Some(c) = example.str.chars().nth(2){
   print...
}
```

#### References
[Doug Milford](https://www.youtube.com/channel/UCmBgC0JN41HjyjAXfkdkp-Q)

### Authors

* **The Philomath**
