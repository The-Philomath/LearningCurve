#### What Steps to follow to answer a System design question?

1. Requirement Clarification
2. System interface Design
3. Back of the envelope estimation
4. Defining Data Model
5. High Level Design
6. Detailed Design
7. Identifying and resolving bottlenecks.

Generic example:-
1. Why We need it?
2. Requirements and goals
   * Functional
   * Non-Functional
   * Extended
3. Capacity estimation and constraints
   * New URLs 200/s
   * URL redirections 20K/s
   * Incoming data 100KB/s
   * Outgoing data 10MB/s
   * Storage for 5 years 15TB
   * Memory for cache 170GB
4. System APIs
```
   createURL(api_dev_key, original_url, custom_alias=None, user_name=None, expire_date=None)
   deleteURL(api_dev_key, url_key)
```
5. Database Design
6. Basic System Design and Algorithm
7. Data partioning and Replication
8. Cache
9. Load Balancer
10. Purging or DB Cleanup
11. Telemetry
12. Security and Permission
