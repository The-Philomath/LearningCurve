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

----
## Sharding or Data Partitioning:-  
When Data bases are large then we need to partition the databases in multiple DBs on different servers.

**Partitioning Methods:-**

_Horizontal Partitioning_ or(_Range based Partitioning_) divide database based upon number of rows. like rows having pin number ranged from 1 to 10000 will go in one DB. In this method difficult part is the value whose range is used for sharding.

_Vertical Partitioning_ or(_Feature based Partitioning_) divide DB based upon features like all house number goes into one DB. all resident names goes into another. Problem which this method is that if the DB size increased further then we may need to partition DBs further.

_Directory based Partitioning_ Its a loosely coupled approach to create a lookup table or service or server which knows current partitioning schema and abstract it away from the DB access code. But here we will introduce a single point failure like directory server.

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
* Document DB: Data stored in Documents. Documents grouped to form collections. e.g. MongoDB, CouchDB.
* Wide-Column DB: Columns are containers for rows. Unlike SQL DB all rows need not to have all columns and we can add columns easily later on. e.g. Cassandra and HBase.
* Graph DB: These databases are used to store data whose relations are best represented in a graph. e.g. Neo4j and InfiniteGraph

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
