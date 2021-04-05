To tackle any system design question firstly we should seek answer for

    * What are all the different architectural pieces that we can use?
    * How will they interact and work with each other?
    * How to best utilize these pieces? what are the right tradeoffs?

**Key Concepts of Distributed System:-**

_Scalability_, _Reliability_, _Availability_, _Efficiency_, _Maintainability_ are 5 pillars to decide how good a Distributed System(DS) is.

**Scalability**

A good Scalable system is the one which achieve Scalability without performance loss. Scalable systems are those systems which can be expend based upon the requirement and need and that expansion should not break the existing system. But its practically not possible. So we should take into account of impacts after we scale the system.

Bottle next for scaling are atomic components and such design flows which can't be moved to different systems after expansion.

_Horizontal scaling:-_ Adding more servers, systems, processes is horizontal scaling. Good horizontal scaling examples are Cassandra and MongoDB.

_Vertical scaling:-_ Giving more power to existing system is vertical scaling. like increasing RAM/CPU/Storage etc. A verticle system mostly requires a downtime to upgrade it. MySql is a good vertical scaling example.

**Reliability**

Reliability is the probability a system fail in a give time. A more reliable system is the one which don't break or fail.

**Availability**

To measure Availability we check the percentage of time a system remains operational under normal conditions.

A highly reliable system is also a highly available system. But we can achieve high availability even for the systems which are not highly reliable. A system is breaking in between the transactions or not able to execute them in time limit is not a reliable system but its a highly available system.

**Efficiency**

Two factors to measure efficiency are response time(latency) and throughput(bandwidth). Latency means in how much time a system respond. Throughput is the number of items delivered in a given time. The two measures corresponds to the following unit costs:-
* Number of messages globally sent by the nodes of the system regardless of the message size.
* Size of messages representing the volume of data exchanges

**Maintainability**

How easy to operate or maintain a system. A good system is easily manageable.

----
## Load Balancing
A load balancer diverts the incoming packets or messages to the available servers or databases based upon the algorithm used. A good balancers store the status of available servers. If a server goes down then it will not send the packets to that server which is unresponsive. Load balancer reside between server and client.

But we can use it between :-

    * User and webserver
    * webserver and internal platform layer like app server or cache server.
    * Internal platform layer and database

A load balancer apart from distributing the load also do the **Health Checking** of a system. How alive a system is?

**Load Balancing algorithms:-**

* Least connection Method
* Least Responsive Time Method
* Least Bandwidth Method
* Round Robin Method
* Weighted Round Robin Method (Like RR but take into account the priority of systems and current load)
* IP Hash

_Redundant load balancer_ can also be used as a backup load balancer in case of single point failure of load balancer occurs.

----
## Caching
Caching works on locality of reference principle.

**App Server cache** Placing a cache directly on a request layer node enables the local storage of response data. Each time a request is made to the service, the node will quickly return local cached data if it exists. A same request from multiple users can go to different servers. To handle that we can use a _Global cache_ or a _Distributed cache_.

**Content Distribution Network** CDNs are a kind of cache that comes into play for sites serving large amounts of static media.

**Cache Invalidation:-**

If there is a write operation on the data then data will be modified by the processor. Then the current copy in cache needs is an invalid copy we need to update the copy on cache as well as on disk. Here are 3 ways to do that.

* _Write through cache_ Update in cache as well as on disk. + On power failure data can be retrieved safely from disk. - Updating disk an expensive operation.
* _Write around cache_ Update only on disk. + No data loss on power failure. - cache have old copy
* _Write back cache_ Update only on cache and update on disk after some time. + No expensive calls to update on disk. - Will loss the data on power failure.

**Cache Eviction Policies:-**
Which entry should be removed from cache on a miss.

1. FIFO
2. LIFO
3. LRU
4. MostRU
5. LFU(Least Frequently Used, count the number of times a page is referred)
6. Random Replacement
7. ARC (Adaptive Replacement Cache) :  Introduced in 2003 by IBM (patent) which uses 4 LRU cache to maintain the cache. The intuition is to maintain 1 cache having elements that are accessed only once and the second LRU list having elements that are accessed more than once. For each LRU cache, there is a corresponding ghost cache whose size keeps changing based on some parameter. This cache policy is known to have better performance than the LRU scheme. For more information, kindly read the following paper  : [ARC paper](https://www.usenix.org/conference/fast-03/arc-self-tuning-low-overhead-replacement-cache)
8. Offline MIN cache : When a new cache policy is introduced, we need a benchmarking policy which we can use to test the performance. In this policy, we know in advance the time at which the item will be requested next in the policy. So the item which will not be needed in the near future will be evicted.

----
## Sharding or Data Partitioning:-  
When Data bases are large then we need to partition the databases in multiple DBs on different servers.

**Partitioning Methods:-**

_Horizontal Partitioning_ or(_Range based Partitioning_) divide database based upon number of rows. like rows having pin number ranged from 1 to 10000 will go in one DB. In this method difficult part is the value whose range is used for sharding.

_Vertical Partitioning_ or(_Feature based Partitioning_) divide DB based upon features like all house number goes into one DB. all resident names goes into another. Problem which this method is that if the DB size increased further then we may need to partition DBs further.

_Directory based Partitioning_ Its a loosely coupled approach to create a lookup table or service or server(known as directory server) which knows current partitioning schema and abstract it away from the DB access code. But here we will introduce a single point failure like directory server.

**Partitioning Criteria:-**

_Keys or hash based_ like add the current record in partition id % number of servers. But this has a problem if we keep no of servers into account while calculating hash then if the servers increased then we need to refactor everything based upon new hash. Consistent hashing can be used to solve this problem.

_List partitioning_ Store based upon list of values. like store all north Indian record in one DB. find the DB based upon state name.

_Round Robin Partitioning_ simply add a new entry in the next DB.

_Composite partitioning_ can use multiple criteria to decide where should the new record goes. Consistent hashing is a composite hashing which composed of list and hash partitioning.

**Problems of sharding**

_Joins and denormalization_ join across multiple servers is a difficult task. Need to compile data from multiple servers. We need to denormalize DB to perform join on single table.

_Referential integrity_ applying foreign key across servers is very difficult. we need to frequently cleanup the dangling references of those entries which are no more there.

_Rebalancing_ if distribute is not even or a DB is facing too much load then we need to rebalance the DBs based upon different criteria.

----
## Indexes
When DBs expend then to find the records quickly we do the indexing like find all books of chetan bhagat and then arrange in order of name. This will speed up the searching .

But it will decrease the write performance as we need to update the indexes whenever a new record will be added. For a heavy write and low read we should avoid indexing.

----
## Proxies
A proxy server is an intermediate server between the client and the back-end server. Proxies are used to filter requests, log requests, or sometimes
transform requests. Another advantage of a proxy server is that its cache can serve a lot of requests.

**Proxy server types:-**

_Open proxy_ anyone can use to access a server on internet. These can be `Anonymous proxies` which hides the user information. or `Transparent Proxies` which provide the local caching of websites.

_Reverse proxy_ A reverse proxy retrieves resources on behalf of a client from one or more servers. These resources are then returned to the client, appearing as if they originated from the proxy server itself.

----
## Redundancy and Replication
Redundancy is having a backup or copy of the original data. Replication means sharing information to ensure consistency between redundant resources, such as software or hardware components, to improve reliability, fault-tolerance, or accessibility. Replication in DBMS is maintained by Master slave architecture. The master gets all the updates, which then ripple through to the slaves.

----
## SQL vs NoSQL
Relational DB or non-relational DB

**SQL DB** works on rows and columns. Each row contain information about one entity. e.g. MySQL Oracle, SQLite, MS SQL Server

**NoSQL DB** stores data in various formats. Few are
* Key-Value Stores: Key is attribute name which is linked to 'value'. e.g. Redis, Dynamo, Voldemort.
* Document DB: Data stored in Documents. Documents grouped to form collections. Document DB is represented as jsons. e.g. MongoDB, CouchDB.
* Wide-Column DB: Columns are containers for rows. Unlike SQL DB all rows need not to have all columns and we can add columns easily later on. e.g. Cassandra and HBase.
* Graph DB: These databases are used to store data whose relations are best represented in a graph. Websites which are too interconnected use Graph DB like facebook. e.g. Neo4j and InfiniteGraph

**Difference in SQL and NoSQL**
* _Scalability_: SQL is Vertically scaled and NoSQL can be easily scaled horizontally.
* _Storage_: SQL is row column modal NoSQL have different modals like key-value, document , wide-column and Graph.
* _Schema_: SQL have fixed Schema for each row. Alteration is expensive. NoSQL Schema is dynamic. each to expand.
* _Querying_: SQL used sql. No SQL uses different languages. Sometimes its called Unstructured query language(UnQL).
* _Reliability or ACID Compliancy_: SQL are ACID compliance. NoSQL is not for performance and scalability.

**Which one to use?**

Reasons to choose SQL: We need ACID compliance. Protect the integrity of DB. Our data is structure and unchanging.

Reason to choose NoSQL: For big dynamic data with no specific structure and different types of data use NoSQL. It can be expand on cloud. Which is cost effective. If we don't know before hand how the DB will look like and need to frequently change the DB structure then use NoSQL.

----
## CAP Theorem
CAP theorem states that it is impossible for a distributed software system to simultaneously provide more than two out of three of the following guarantees (CAP): Consistency, Availability, and Partition tolerance. Which 2 out of 3 to choose is the design decision we should make.

**Consistency:-** All nodes(users) see the same data at the same time.

**Availability:-** System continue to function even with node failure.

**Partition tolerance:-** System continues to function even if the communication fails between nodes. A system that is partition-tolerant can sustain any amount of network failure that doesn’t result in a failure of the entire network.

e.g.
C + A => RDMBS
A + P => Cassandra, CouchDB
C + P => BigTable, MongoDB, HBase

_Why we can't choose all three?_

To be consistent, all nodes should see the same set of updates in the same order. But if the network suffers a partition, updates in one partition might not make it to the other partitions before a client reads from the out-of-date partition after having read from the up-to-date one. The only thing that can be done to cope with this possibility is to stop serving requests from the out-of-date partition, but then the service is no longer 100% available.

----
## Consistent Hashing

Normal hashing `index = hash_function(key)` have problem of NON horizontally scalability and that may not be load balanced. To improve caching in those cases we use consistent hashing.

It allows us to distribute data across a cluster in such a way that will minimize reorganization when nodes are added or removed. Hence, the
caching system will be easier to scale up or scale down.

In Consistent Hashing, when the hash table is resized (e.g. a new cache host is added to the system), only ‘k/n’ keys need to be remapped where ‘k’ is the total number of keys and ‘n’ is the total number of servers. Recall that in a caching system using the ‘mod’ as the hash function, all keys need to be remapped. Load of any host removed or added will be shared among all the available hosts.

**How does it work?**
As a typical hash function, consistent hashing maps a key to an integer. Suppose the output of the hash function is in the range of [0, 256). Imagine
that the integers in the range are placed on a ring such that the values are wrapped around.
Here’s how consistent hashing works:
1. Given a list of cache servers, hash them to integers in the range.
2. To map a key to a server,
* Hash it to a single integer.
* Move clockwise on the ring until finding the first cache it encounters.
* That cache is the one that contains the key.

For load balancing, as we discussed in the beginning, the real data is essentially randomly distributed and thus may not be uniform. It may make the keys on caches unbalanced.
To handle this issue, as well as issue of adding and removing servers, we add “virtual replicas” for caches. Instead of mapping each cache to a single point on the ring, we map it to multiple points on the ring, i.e. replicas. This way, each cache is associated with multiple portions of the ring. If the hash function “mixes well,” as the number of replicas increases, the keys will be more balanced. for better understanding [refer](https://www.youtube.com/watch?v=zaRkONvyGr8).

----
## Long polling vs WebSockets vs Server Sent Events
**Ajax Polling** Polling is a standard technique used by the vast majority of AJAX applications.
1. The client opens a connection and requests data from the server using regular HTTP.
2. The requested webpage sends requests to the server at regular intervals (e.g., 0.5 seconds).
3. The server calculates the response and sends it back, just like regular HTTP traffic.
4. The client repeats the above three steps periodically to get updates from the server.

Client keep on asking for updates in this modal. So a lot of empty response of no update creates HTTP overhead.

**HTTP Long Polling** Server may not respond immediately(if serve don't have any update) to the sent request. It will store the request and send whenever the update will be available. Its also known as `Hanging GET`.

Client will immediately send re-request so that server can respond whenever it has the update.
1. The client makes an initial request using regular HTTP and then waits for a response.
2. The server delays its response until an update is available or a timeout has occurred.
3. When an update is available, the server sends a full response to the client.
4. The client typically sends a new long-poll request, either immediately upon receiving a response or after a pause to allow an acceptable latency period.
5. Each Long-Poll request has a timeout. The client has to reconnect periodically after the connection is closed due to timeouts.

**WebSockets** provides full-duplex TCP connection for fast realtime data exchange. Socket is opened after the initial handshake betweek client and server. This is made possible by providing a standardized way for the server to send content to the browser without being asked by the client and allowing for messages to be passed back and forth while keeping the connection open.

**Server-Sent Events(SSE)** client open a persistent long term connection with server for real time updates. If the client wants to send data to the server, it would require the use of another technology/protocol to do so.
1. Client requests data from a server using regular HTTP.
2. The requested webpage opens a connection to the server.
3. The server sends the data to the client whenever there’s new information available.

----

#### In memory Cache vs In memory Database

**Cache** - By definition means it is stored in memory. Any data stored in memory (RAM) for faster access is called cache. Examples: Ehcache, Memcache Typically you put an object in cache with String as Key and access the cache using the Key. It is very straight forward. It depends on the application when to access the cache vs database and no complex processing happens in the Cache. If the cache spans multiple machines, then it is called distributed cache. For example, Netflix uses EVCAche which is built on top of Memcache to store the users movie recommendations that you see on the home screen.

**In Memory Database** - It has all the features of a Cache plus come processing/querying capabilities. Redis falls under this category. Redis supports multiple data structures and you can query the data in the Redis ( examples like get last 10 accessed items, get the most used item etc). It can span multiple machine and is usually very high performant and also support persistence to disk if needed. For example, Twitter uses Redis database to store the timeline information.

----

#### How to reduce latency of your system?

**Use HTTP/2 instead of HTTP** - we can send multiple requests at once in http/2 and server combines the response of multiple requests in one response. CDN also helps to reduce latency. CDN is a type of cache which is near to user. Browser cache/cookies also helps to reduce it, static content is stored by browser like images, icons.

----

#### Message flow between two ends

Message flows between sender and receiver can be Asynchronously or Synchronously.

Asynchronous message flow is better because sender is not blocked. Sender sends the message to a queue and receiver can get message from whenever receiver comes online. Java message service(JMS) provide such type of service. Its also called as **queue based approach**. Queue based approach is a point to point communication.

**Topic based approach** -> It works on pub-sub approach. Any number subscriber can subscribe to a topic. Its a one to many relation. JMS can also provide this type of service. One end is JMS Client. JMS provider(like active MQ) is the entity which receives message from JMS client.

#### Kafka

**Kafka** give higher throughput, reliability, and replication has made this technology replace conventional message brokers. Kafka can work with HBase, Flink, Flafka, and Spark for analysis and processing real-time data, which makes Kafka scalable as it allows us to build distributed applications.

Whenever there is a continuous streams or real time streams of messages we should use Kafka. Kafka is highly available, scalable, and it follows pub-sub type of serivce. Kafka components are Kafka cluster(which is a combination of Kafka brokers), Kafka topic(named stream of records), partitions, consumers group, producer, consumer.

For any scalable distributed system its always better to use Kafka as a message queue rather than Message queue or Active MQ

**Kafka** is a huge system. It uses Apache zookeeper to manage its services.

**Spark Streaming** use Kafka like system to get the required data on one of the kafka topic and generate real time analytical reports by using different algos like map, reduce.

----

The **Circuit breaker** pattern helps to prevent such a catastrophic cascading failure across multiple systems. The circuit breaker pattern allows you to build a fault tolerant and resilient system that can survive gracefully when key services are either unavailable or have high latency. It is used in microservice architecture.

----

latency vs consistency vs availability

**Highly available system**:- To design this we can use the consistent hashing and keep multiple copies(known as replication factor) on multiple machines to handle the failure scenario.

**Highly Consistent system**:- To design such system we can use multiple masters and make sure that if not all then a majority of systems should be updated with new data before sending the confirmation back to the client. A master node will act as a coordinator to manage this. But that will create a single point of failure. We can use a standby node that is getting all the updates same as of master through a shared file system.

#### References

### Authors

* **The Philomath**
* **Manish Kumar**
