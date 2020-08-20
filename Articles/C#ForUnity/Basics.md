## About

This article doesn't contain all the C# topics. Instead it a quick reference article if you want to develop C# script for Unity.

**Points**

* MonoBehaviour // Base class for all the unity provided functions.

* UnityEngine // MonoBehavior is present under this name space
* Awake() // This function get called before start. It get called even if the script which contains this function is disabled.
* Start() // First function to get callled when script is enabled and script get called first time. Or we can say object is created.
* Update() // Get called once every frame
* Destroy(gameObject, ntime); // Destorys 'gameObject' after duration of 'ntime'.
* foreach(int i in arr) {} // A general C# foreach function
* Vector2, Vector3, vector4 can store 2,3 and 4 variables respecivialy. For example we can store 2D position in Vector2 and 3D position in Vector3.
* Vector2 pos = new Vector2(5f, 6f); to use them : pos.x, pos.y // so the first parameter of 2D vector is represent by x and second by y
* Objects in unity can have multiple components. A component is a set of properties and operations of one type.
* Transform component=> Every object have this component. It have properties representing position, rotation and scale parameters of the object.
* To access transform component in C# script use : transform.position, transform.localScale, transform.rotation. We can store the return value of these calls in a Vector3 variable.
* We can't directly assign values to transform.position.x, instead we must use transform.poisiton = pos; where pos is of type Vector3.
OR we can use transform.Translate() function to modify the position or move the object. For example:
      Update(){
       // Move the object forward along its z axis 5 unit/second.
        transform.Translate(0, 0, 5* Time.deltaTime);}
* To rotate the object use transform.Rotate()
* **Tags**: We can tag all similar objects to recognize them. To access it in code use: gameObject.tag
* For a collisiion an object must have two components
    1. a Rigid body(it tells mass , gravity of object)
    2. collider (it is a space around the object which shows the  colliding space or proximity of object).


* OnCollisionEnter2D(Collision2D col){} // override this function to handle what should happen when this object collides. the passed Collision2D contains the object to which this object collided.

* col.gameObject.tag to access tag of the object to which object collided.
* OnTriggerEnter2D(Collider2D col) // if object to which this object is going to collide is a trigger
* [SerializeField] // mark private variables with this to make them visible in Inspector
* [HideInInspector] // mark public variable with this to hide them in Inspector
* GameObject.FindWithTag("tag"); // returns a game object with the 'tag' name
* GameObject.FindGameObjectsWithTag("tag"); returns an array of all the objects with 'tag' name
* Prefabs // like a mold or receipe with which can create all the objects of that type
* Instantiate(prefabName, position, rotation) //to create an object from a prefab in code.
* InvokeRepeating(fnctionName, time, repeatRate) // funcationName will get called repeatedly after time.
* Input.GetKeyDown(KeyCode.Space), GetKeyUp, GetKey // To handle inputs
* Input.GetButtonDown("Jump") , GetButtonUp, GetButton //In project settings we can see what button is assigned to what functionality and we can get the input with that funcationality name like 'Jump' in this example.
* Input.GetMouseButtonDown(0), GetMouseButtonUp, GetMouseButton // 0 is left click, 1 is right click, 2 is scroll click
* Input.MousePosition; // returns Vector3 position of mouse cursor
* float x = Input.GetAxis("Horizontal");// to get the left and right arrow press
* float y = Input.GetAxis("Vertical");// to get the up and down arrow press
We can use these two APIs to move the object using translate function towards that direction
* **Coroutine** A coroutine is a function that can suspend its execution (yield) until the given YieldInstruction finishes. Coroutines always have a return type of IEnumerator
       StartCoroutine("funcitonName"); OR StartCoroutine(functionName());// To start the coroutine
* yield return new WaitForSeconds(3f); // To wait for 3 seconds  before executing next statement. its just like wait.
* Rigidbody rb = GetComponent<Rigidbody>();// To Access any component(it can be a script) from script. After that we can access parameters of that component
* Rigidbody rb = GetComponentInChildren<Rigidbody>();// To Access any component in the children of current object.
* To load the scene from another scene first add both of them to build settings then use
* SceneManager.LoadScene(index_number); // can pass another parameters (LoadScene.Additive OR LoadScene.Single) as mode to load 2 scenes at the same time. Otherwise there will only be one scene at a time.
* Camera.main.ScreenToWorldPoint(mousePos); //To convert mouse positions to world position
* Quaternion.identity //This quaternion corresponds to "no rotation" - the object is perfectly aligned with the world or parent axes.
* Random.Range(x,y); // returns random value between x and y
