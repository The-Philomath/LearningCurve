Two basic Characteristics of a distributed system are:-

**Characteristic 1**: collection of autonomous computing elements

* open group:- any node is allowed to join the distributed system, effectively meaning that it can send messages to any other node in the system.

* closed group:- only the members of that group can communicate with each other and a separate mechanism is needed to let a node join or leave the group.

Practice shows that a distributed system is often organized as an **overlay network**. In this case, a node is typically a software process equipped with a list of other processes it can directly send messages to. It may also be the case that a neighbor needs to be first looked up. Message passing is then done through TCP/IP or UDP channels, but higher-level facilities may be available as well.

Types of overlay networks:-

* Structured overlay:- In this case, each node has a well-defined set of neighbors with whom it can communicate. For example, the nodes are organized in a tree or logical ring.

* Unstructured overlay:- In these overlays, each node has a number of references to randomly selected other nodes.

In any case, an overlay network should in principle always be connected, meaning that between any two nodes there is always a communication path allowing those nodes to route messages from one to the other. A well-known class of overlays is formed by peer-to-peer (P2P) networks.

----

**Characteristic 2**: single coherent system

This so-called distribution transparency is an important design goal of distributed systems

Middleware and distributed systems:-

To assist the development of distributed applications, distributed systems are often organized to have a separate layer of software that is logically placed on top of the respective operating systems of the computers that are part of the system. This organization leads to what is known as middleware.

A distributed system organized as middleware. The middleware layer extends over multiple machines, and offers each application the same interface.

In a sense, middleware is the same to a distributed system as what an operating system is to a computer: a manager of resources offering its applications to efficiently share and deploy those resources across a network. Next to resource management, it offers services that can also be found in most operating systems, including:-

* Facilities for interapplication communication.
* Security services.
* Accounting services.
* Masking of and recovery from failures.
