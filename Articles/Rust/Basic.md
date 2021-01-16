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
