Hi,

1. I ask the format of the file. no one replies me before i just finish my project. Therefore, I just creat the format by myself. the format you can see in every CSV files. The character in the csv file is 
sensitive. I think that format is restrict, so no need to make the program detect the character case. If it needs, it is easy, just use the tolower or toupper function.

2. I created 5 class, 1 base class for cars, 2 derived class for suvs and sedan, 1 class for company and 1 class for customer information. company class has two vector to store the base class pointer, and
has 1 vector record the customer and 1 map to record the customer rent record. The company class has three functions. One for printing all cars information which i have used in the first test. Second is
used to store the new cars company bought and store the old cars customer returned. It differentiate two operation by the first row of the file. The third funtion is the rent funtion, which is used to
lent the car to the customer.

3. store function only can store suv and sedan, if you store other type car it will print error messages. return function need customer name and SSN(like uniqe member number) matches and car is totally same
as the rent one, otherwise, it will print error messages.

4. this rar includes carRental.h, carRental.cpp ,Test.cpp , rent.csv, store.csv, return.csv. you must place the csv file at the same path with cpp file. 

5. There are other ideas i have, but due to the time limitation, i do not implement. For example, if some customers has rent the car without returning and wanna rent another car. We can introduce a credit to
judge whether we should lend the car.

6. the test case have tested most situation: store the other types car, request car is ran out, no request car, return car is not correct, return customer does not match the ssn, return car does not match the rent car.
I also have randomized the return order, it is not same as the rent file.

thank you for read.


