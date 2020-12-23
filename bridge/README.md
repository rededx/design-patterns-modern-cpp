## Bridge

Decouple an abstraction from its implementation so that the two can vary independently. 
Bridge pattern has structural purpose and applies to objects, so it deals with the composition of objects. 

### When to use

* you want to avoid a permanent binding between an abstraction and its implementation
* both the abstractions and their implementations should be extensible by subclassing
* changes in the implementation of an abstraction should have no impact on clients
* you want to hide the implementation of an abstraction completely from clients

### Clarification
So, abstraction (or interface) is a figurative layer of control over something. It does not do the work on its own, but delegates it to the implementation layer (sometimes called the platform).

Just don't confuse these terms with interfaces or abstract classes from your programming language, they are not the same thing.